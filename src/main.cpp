#include "../include/parsers/ConfigParser.h"
#include "../include/parsers/SceneParser.h"
#include "../include/renderer/Scene.h"
#include "../include/renderer/Renderer.h"

int main(int, char**)
{
    std::string config_path = "../config/Config.xml";
    Config config = ConfigParser::GetInstance().ParseConfig(config_path);

    std::string scene_description_path = config.scene_description_path_;
    auto scene_data = SceneParser::GetInstance().ParseScene(scene_description_path);

    Scene scene {scene_data};
    scene.Initialize(config);

    Canvas canvas {config.width_, config.height_};

    Renderer renderer;
    renderer.Initalize(config);
    renderer.Render(scene, canvas);

    std::string output_path = config.output_path_;
    canvas.Flush(output_path);
}