# Ray Tracer Review Report

## Scope

This review covers the current codebase, including `src`, `include`, `test`,
`scenes`, `CMakeLists.txt`, `README.md`, and `todo.txt`.

The project currently builds from `cmake-build-debug`, and `ctest --test-dir
cmake-build-debug --output-on-failure` reports 30/30 passing tests. That result
is weaker than it looks because several test files contain empty tests or no
assertions.

## Correctness Issues

### Thread count can underflow

`std::thread::hardware_concurrency() - 2` in `src/main.cpp` and
`hardware_concurrency() - 4` in `include/ThreadPool.h` can underflow or produce
zero. If hardware concurrency returns 0, 1, or 2, the renderer can reserve a huge
thread vector, divide by zero, or spawn far too many threads.

Files:

- `src/main.cpp:28`
- `include/ThreadPool.h:14`

Fix:

- Clamp worker count to a sane range.
- Treat `hardware_concurrency() == 0` as unknown and choose a fallback such as 1
  or 2.
- Keep thread count calculation in one place.

### Render chunking mutates loop step sizes

`chunk_x_size` and `chunk_y_size` are used as loop increments, then reassigned
inside the loop for edge chunks. Once an edge tile shrinks one of those values,
subsequent scheduling can create incorrect tile sizes or far more threads than
intended.

Files:

- `src/main.cpp:46`
- `src/main.cpp:51`
- `src/main.cpp:52`

Fix:

- Keep base tile size immutable.
- Use local `tile_w` and `tile_h` inside the loop.

### Missing or invalid sampler can crash rendering

`SceneParser` can leave `sampler` null if `<antialiasing>` is absent or uses an
unknown type. `main` then installs that null sampler into the camera, and the
camera dereferences it. If a sampler returns zero rays, `pixel_color /= rays.size()`
divides by zero.

Files:

- `src/main.cpp:83`
- `src/main.cpp:90`
- `src/main.cpp:40`
- `src/ProjectiveCamera.cpp:16`
- `src/SceneParser.cpp:204`

Fix:

- Provide a default sampler, probably one-sample regular sampling.
- Validate sampler type and sample count during parsing.
- Make camera construction require a sampler or make `GetRayAt` fail clearly.

### Scene parsing is order-dependent and stateful

The parser stores transformations, instances, and materials in static global maps.
Those maps persist across scene parses. Shapes also need materials and
transformations to have already been parsed, because `ParseShape` immediately
looks them up. Missing attributes silently create empty map entries through
`operator[]`.

Files:

- `src/SceneParser.cpp:26`
- `src/SceneParser.cpp:27`
- `src/SceneParser.cpp:28`
- `src/SceneParser.cpp:137`
- `src/SceneParser.cpp:144`
- `src/SceneParser.cpp:145`

Fix:

- Replace static maps with per-parse local state.
- Parse definitions first, then instantiate shapes after validation.
- Use `find`/`contains` instead of `operator[]` for required references.
- Emit useful errors for unknown material, transformation, shape, sampler, and
  light types.

### BVH cannot handle empty worlds

If `World::Build()` is called with no instances, `BVH::Build` has no base case
for an empty vector and recurses indefinitely. `BVH::Hit` also dereferences
`root_` without checking whether the BVH was built.

Files:

- `src/World.cpp:18`
- `src/BVH.cpp:35`
- `src/BVH.cpp:43`

Fix:

- Add an empty-world case.
- Have `BVH::Hit` return false when `root_ == nullptr`.
- Add tests for empty world and single-object world.

### Bounding boxes have multiple numeric bugs

Several bbox implementations initialize max points with
`std::numeric_limits<double>::min()`, which is the smallest positive normalized
number, not the most negative number. Transformed bbox corner generation also
uses bit masks as multipliers, producing coordinates like `2 * length` and
`4 * length` instead of 0 or 1 times the length. `BoundingBox::Hit` ignores the
ray interval in `ShadeContext` and divides by direction components without
handling zero.

Files:

- `src/Triangle.cpp:56`
- `src/Triangle.cpp:57`
- `src/Instance.cpp:59`
- `src/Instance.cpp:60`
- `src/Instance.cpp:61`
- `src/BoundingBox.cpp:43`
- `src/BoundingBox.cpp:47`
- `src/Plane.cpp:33`

Fix:

- Use `std::numeric_limits<double>::lowest()` for initial max bounds.
- Generate transformed bbox corners with boolean bit checks, not the bit mask
  value itself.
- Implement standard slab intersection with `t_min`/`t_max`.
- Handle near-zero ray directions.
- Decide how infinite primitives like planes participate in the BVH.

### Matrix math has serious latent bugs

The matrix implementation has several correctness problems:

- Const unary minus multiplies a zero-initialized matrix by `-data_[i][j]`,
  leaving the result zero.
- Member scalar multiply does not return `*this`.
- `Determinant` is declared as returning `Matrix<T, N, N>` but computes and
  returns a scalar.
- `Inverse` has no pivoting or singular-matrix handling.
- Matrix-vector multiply loops over `N` rows even though the row count is `M`.

Files:

- `include/Matrix.h:63`
- `include/Matrix.h:86`
- `include/Matrix.h:163`
- `include/Matrix.h:183`
- `include/Matrix.h:265`

Fix:

- Add real matrix tests first.
- Fix return types and arithmetic.
- Add pivoting and singular checks to inverse.
- Consider using a well-tested math library or a much smaller purpose-built
  transform matrix implementation.

### `Point::ToVector` and `Normal::ToVector` drop the last component

Both functions copy only `N - 1` components into an `N`-dimensional vector. That
corrupts view vectors and any reflection code that uses normals.

Files:

- `include/Point.h:64`
- `include/Normal.h:105`
- `src/Material.cpp:40`

Fix:

- Copy all `N` components.
- Add tests for point-to-vector and normal-to-vector conversion.

### Random sampling has a data race

`RandomDouble` and `RandomInt` use shared static generators and distributions.
The renderer calls random and jittered samplers from multiple threads, so this is
a data race.

Files:

- `include/Util.h:29`
- `include/Util.h:38`
- `src/JitteredSampler.cpp:12`
- `src/RandomSampler.cpp:10`

Fix:

- Use `thread_local` RNG state, or pass a sampler/RNG instance per worker.
- Do not use static distributions whose bounds are supplied per call.

### Orthographic camera ignores pixel coordinates

`OrthographicCamera::GetRayAt` computes the canvas upper-left corner but never
offsets by `x` and `y`. Every pixel samples the same region.

File:

- `src/OrthographicCamera.cpp:7`

Fix:

- Match `ProjectiveCamera` and compute `pixel_upper_left_corner`.

### OBJ parsing is fragile

OBJ parsing assumes non-empty lines, positive 1-based indices, only triangular or
fan-triangulated faces, and limited face formats. It does not validate index
ranges before using them.

Files:

- `src/OBJParser.cpp:38`
- `src/OBJParser.cpp:41`
- `src/OBJParser.cpp:84`
- `src/OBJParser.cpp:91`

Fix:

- Skip empty/comment lines safely.
- Validate indices before access.
- Decide which OBJ face forms are supported and reject others clearly.

## Ray Tracing and Rendering Gaps

### This is not Whitted tracing yet

`Trace` only finds a hit and invokes local shading. There are no shadow rays,
reflection rays, refraction rays, recursion depth, or secondary ray handling.

Files:

- `src/main.cpp:17`
- `src/Material.cpp:26`

Fix:

- Introduce a `Tracer` or `Integrator`.
- Add recursive ray evaluation with a max depth.
- Add shadow rays before adding reflection/refraction.

### Some scene files do not match material parsing

Several scene files define materials with a `color` attribute only. The parser
only recognizes `type="simple_phong"`, so those materials become black.

Files:

- `src/SceneParser.cpp:187`
- `scenes/SingleSphere.xml:2`
- `scenes/BVHTestScene.xml:2`
- `scenes/CessnaScene.xml:2`

Fix:

- Either update scenes to use the current material schema or support a simple
  flat material parser.
- Reject unknown material types instead of silently using black.

### Phong shading assumes a fixed camera

The view vector is computed from `-context.point_`, which assumes the camera is
at the world origin. The projective camera currently emits rays from
`(0, 0, -focal_distance)`.

Files:

- `src/Material.cpp:40`
- `src/ProjectiveCamera.cpp:17`

Fix:

- Store the incoming ray or view direction in the hit record.
- Compute view direction from the ray, not from a hard-coded camera assumption.

### Normals are not consistently normalized

Sphere normals and transformed normals are not normalized before shading. Non-
uniform transforms can produce incorrect lighting.

Files:

- `src/Sphere.cpp:47`
- `src/Instance.cpp:41`
- `src/Transformation.cpp:122`

Fix:

- Normalize normals after transform.
- Use inverse-transpose correctly and test non-uniform scaling.

## Design Issues

### `main.cpp` is doing too much

`main.cpp` performs resource path construction, scene parsing orchestration,
camera construction, sampler wiring, BVH building, rendering, thread scheduling,
timing, and output naming.

Files:

- `src/main.cpp:60`
- `src/main.cpp:70`
- `src/main.cpp:77`
- `src/main.cpp:79`
- `src/main.cpp:88`
- `src/main.cpp:92`
- `src/main.cpp:94`

Fix:

- Introduce `Scene`, `RenderConfig`, `Renderer`, and `Tracer`.
- Keep `main` as argument parsing plus high-level orchestration.

Suggested direction:

```cpp
int main(int argc, char** argv) {
    RenderConfig config = ParseArgs(argc, argv);
    Scene scene = SceneParser::GetInstance().ParseScene(config.scene_path);
    Renderer renderer(config.render_settings);
    Canvas image = renderer.Render(scene);
    image.Flush(config.output_path);
}
```

### `ShapeInterface::Hit` is overloaded with too many responsibilities

`Hit` answers whether an intersection exists, mutates nearest-hit state, updates
UVs, stores normals and hit points, and relies on `Instance` to inject material.

Files:

- `include/ShapeInterface.h:15`
- `include/ShadeContext.h:17`
- `src/Instance.cpp:28`

Fix:

- Introduce `HitRecord`.
- Pass an explicit ray interval.
- Return `std::optional<HitRecord>` or `bool Hit(ray, interval, record&)`.

### `ShadeContext` mixes intersection and shading concerns

`ShadeContext` contains hit point, normal, material, UV, and ray interval. This
couples geometry traversal, materials, and shading.

File:

- `include/ShadeContext.h:17`

Fix:

- Split `RayInterval`, `HitRecord`, and `ShadingContext`.

### `ThreadPool` is not a thread pool

The current type stores `std::thread` objects and joins them in the destructor.
It does not have persistent workers or a job queue.

Files:

- `include/ThreadPool.h:12`
- `src/ThreadPool.cpp:8`

Fix:

- Rename it to something like `ThreadJoiner`, or implement a real worker pool.
- For rendering, prefer a tile queue consumed by fixed worker threads.

### Parser singletons and globals make tests and reuse harder

`SceneParser`, `XMLParser`, and `OBJParser` are singletons. `XMLParser` also
stores parse state internally. This makes parser behavior less predictable and
harder to use concurrently.

Files:

- `include/SceneParser.h:18`
- `include/XMLParser.h:35`
- `src/XMLParser.cpp:16`
- `src/OBJParser.cpp:23`

Fix:

- Make parsing functions stateless where practical.
- Store parser state on the stack per parse.

## Leaky Abstractions

### Canvas dimensions leak into renderer globals

`Render` accepts a `Canvas&` but uses global `WIDTH` and `HEIGHT`. The canvas,
camera, and renderer must be kept in sync manually.

Files:

- `src/main.cpp:14`
- `src/main.cpp:15`
- `src/main.cpp:46`
- `include/Canvas.h:36`

Fix:

- Add `Canvas::Width()` and `Canvas::Height()`.
- Use canvas dimensions in `Render`.

### Camera abstraction is undermined by construction in `main`

`Render` accepts `CameraInterface*`, but `main` directly constructs
`ProjectiveCamera`. Scene parsing cannot currently select a camera.

Files:

- `src/main.cpp:27`
- `src/main.cpp:79`

Fix:

- Move camera creation into `SceneParser` or a scene/camera factory.
- Store camera as `std::unique_ptr<CameraInterface>` in `Scene`.

### Sampler wiring leaks through `main`

The parser returns a sampler separately, then `main` manually installs it into
the camera. That exposes camera internals to application orchestration.

Files:

- `include/CameraInterface.h:14`
- `src/main.cpp:83`
- `src/main.cpp:90`

Fix:

- Make sampler a constructor dependency of cameras.
- Or store sampler in render settings and let `Renderer` sample pixels.

### Filesystem layout leaks into runtime behavior

The program expects scene names, then converts them to `../scenes/<name>.xml`.
This works from build directories but fails from the repo root.

Files:

- `src/main.cpp:70`
- `src/SceneParser.cpp:159`
- `src/Canvas.cpp:32`

Fix:

- Accept explicit scene and output paths.
- Resolve models relative to the scene file or a configured asset root.
- Do not base output paths on `current_path().parent_path()`.

## Unfinished or Placeholder Code

Several types exist but are not implemented:

- `include/Box.h`
- `include/Cone.h`
- `include/Cylinder.h`
- `include/AmbientLight.h`
- `include/DirectionalLight.h`
- `include/BasicDiffuseShading.h`
- `include/Texture.h`

The README claims image/procedural textures, but the texture classes currently
return default colors and destructors are declared without visible definitions.

Fix:

- Remove placeholders from public feature claims, or mark them clearly as
  planned.
- Do not expose incomplete concrete classes as if they are usable.

## Test Coverage Issues

The suite passes, but many important files are not meaningfully tested.

Empty or nearly empty files:

- `test/SphereTest.cpp`
- `test/TriangleTest.cpp`
- `test/PointTest.cpp`
- `test/NormalTest.cpp`
- `test/MatrixTest.cpp`
- `test/TransformationTest.cpp`

Missing coverage:

- Matrix determinant/inverse
- Point/normal conversions
- Shape intersections
- Transformed instances
- BVH empty/single/multi-object behavior
- Bounding box slab intersections
- Scene parser validation and ordering
- Sampler behavior and invalid sample counts
- Renderer smoke tests
- Multithreaded random sampling safety

Fix:

- Add focused unit tests before refactoring.
- Add at least one low-resolution render smoke test.
- Test parser error paths, not just successful XML syntax.

## Build and Project Hygiene

### CMake uses globbed source files

`file(GLOB SOURCE_FILES "src/*.cpp")` can hide source list changes from CMake
regeneration in some workflows.

File:

- `CMakeLists.txt:19`

Fix:

- Prefer explicit source lists for a project this size.

### C++ standard mismatch

CMake sets C++20, while README says C++17.

Files:

- `CMakeLists.txt:4`
- `README.md:31`

Fix:

- Update README or lower the CMake standard.

### Generated build directories and images are in the repo tree

The workspace contains `cmake-build-debug`, `cmake-build-release`, and generated
PPM files under `images`.

Fix:

- Ensure `.gitignore` excludes build directories and generated renders.
- Keep sample outputs only if intentionally curated.

## Recommended Fix Order

1. Fix immediate crash and undefined behavior risks:
   thread count, render chunking, null sampler, parser validation, empty BVH,
   random sampler data race.

2. Fix math and geometry foundations:
   matrix operations, point/normal conversion, bbox construction, bbox hit,
   transformed normals, and transformed hit distance.

3. Add focused tests:
   matrix, transforms, shape hits, BVH, parser, samplers, and one small render
   smoke test.

4. Refactor architecture:
   add `Scene`, `Renderer`, `Tracer`, `HitRecord`, `RayInterval`, and resource
   path handling.

5. Implement real Whitted features:
   shadow rays, recursive reflection/refraction, max depth, attenuation, and
   material/texture integration.

