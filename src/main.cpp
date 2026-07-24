#include "../include/ConfigParser.h"
#include "../include/SceneParser.h"
#include "../include/Renderer.h"

int main(int argc, char** argv)
{
    Config config = ConfigParser::GetInstance().ParseConfig("../config/Config.xml");

    Scene scene = SceneParser::GetInstance().ParseScene(config.scene_description_path_);
    scene.world_->Build(); // TODO: Figure out where to put this

    Canvas canvas {config.width_, config.height_};

    Renderer::GetInstance().Render(scene, canvas);

    canvas.Flush(config.output_path_);
}