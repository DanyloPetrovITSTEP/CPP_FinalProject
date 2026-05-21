#include "Core/Game.h"
#include <iostream>
#include <exception>

int main() {
    try {
        Game rpgGame;
        rpgGame.run();
    } 
    catch (const std::exception& ex) {
        std::cerr << "FATAL ERROR: Unhandled exception in system core: " << ex.what() << "\n";
        return 1;
    } 
    catch (...) {
        std::cerr << "FATAL ERROR: Unknown crash in system core.\n";
        return 2;
    }

    return 0;
}
