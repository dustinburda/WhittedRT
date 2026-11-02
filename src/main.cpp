#include "../include/ConfigParser.h"
#include "../include/parsers/SceneParser.h"
#include "../include/Renderer.h"

#include "../include/shapes/Cylinder.h"

int main(int, char**)
{
    Config config = ConfigParser::GetInstance().ParseConfig("../config/Config.xml");

    auto scene = SceneParser::GetInstance().ParseScene(config.scene_description_path_);

    scene->Build();

    Canvas canvas {config.width_, config.height_};

    Renderer::GetInstance().Render(*scene, canvas);

    canvas.Flush(config.output_path_);
}