#include <iostream>
#include "core/Engine.h"

int main(int argc, char** argv){
    RendererConfig config = { 1280, 720, 4, "Poop Engine" };
    Engine engine(config, 100.0);
    engine.Run();

    std::cout << "End of life" << std::endl;

    return 0;
}
