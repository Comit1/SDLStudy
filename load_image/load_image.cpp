#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <zconf.h>

using namespace std;

int main() {

    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    string currentWorkingDir(buff);
    int index = currentWorkingDir.find("SDL");
    string currentSourceDir = currentWorkingDir.substr(0, index);

    string imagePath = currentSourceDir + "SDL/load_image/test.jpg";

    const int width = 500;
    const int height = 318;
    SDL_Window *pWindow = SDL_CreateWindow(
            "Hello Image",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Surface *pWindowSurface = SDL_GetWindowSurface(pWindow);
    SDL_Surface *pImageSurface = IMG_Load(imagePath.c_str());

    // 将 pImageSurface 的内容传输到上
    SDL_BlitSurface(pImageSurface, nullptr, pWindowSurface, nullptr);
    // 上屏操作，将 Surface 内容显示到屏幕上
    SDL_UpdateWindowSurface(pWindow);

    bool bQuit = false;
    SDL_Event windowEvent;
    while (!bQuit) {
        while (SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type) {
                case SDL_QUIT:
                    bQuit = true;
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return 0;
}
