#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

#include "Engine3D.hpp"

int main(int argc, char* argv[]) {
    TIE::Engine3D::GetInstance().Start();
    return 0;
}