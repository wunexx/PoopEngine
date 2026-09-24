#include <iostream>
#include "core/engine.h"

int main(int argc, char** argv){
    RendererConfig config = { 1280, 720, 4, "Poop Engine" };
    Engine engine(config);
    engine.Run();

    std::cout << "end" << std::endl;

    return 0;
}
