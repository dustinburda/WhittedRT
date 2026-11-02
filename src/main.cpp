#include "../include/parsers/ConfigParser.h"
#include "../include/parsers/SceneParser.h"
#include "../include/renderer/Renderer.h"

#include "../include/shapes/Cylinder.h"

int main(int, char**)
{
    std::string config_path = "../config/Config.xml";
    Config config = ConfigParser::GetInstance().ParseConfig(config_path);

    std::string scene_description_path = config.scene_description_path_;
    auto scene = SceneParser::GetInstance().ParseScene(scene_description_path);

    scene->Build();
    Canvas canvas {config.width_, config.height_};

    Renderer::GetInstance().Render(*scene, canvas);

    std::string output_path = config.output_path_;
    canvas.Flush(output_path);
}