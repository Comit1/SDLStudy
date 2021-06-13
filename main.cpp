#include <iostream>
#include <SDL.h>
using namespace std;

#define SDL_CUSTOM_EVENT (SDL_USEREVENT + 1)

int sdl_thread_custom_event(void *);

/**
 * references: https://glumes.com/tags/sdl/
 */
int main() {
//    SDL_Init(SDL_INIT_EVERYTHING);

    int width = 400;
    int height = 400;

    SDL_Window *pWindow = SDL_CreateWindow(
            "Hello SDL",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *pRenderer = nullptr;
    // 创建渲染器
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    // 指定渲染颜色
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    // 清空当前窗口的颜色
    SDL_RenderClear(pRenderer);
    // 执行渲染操作，更新窗口
    SDL_RenderPresent(pRenderer);

    // 创建线程并运行
    SDL_CreateThread(sdl_thread_custom_event, "custom_event", nullptr);

    SDL_Event windowEvent;

    bool bQuit = false;
    while (!bQuit) {
//        SDL_WaitEvent() // 阻塞
        while (SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type) {
                case SDL_QUIT:
                    bQuit = true;
                    break;
                case SDL_KEYDOWN:
                    if (windowEvent.key.keysym.sym == SDLK_SPACE) {
                        cout << "user click space \n";
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("button index is %d\n", windowEvent.button.button);
                    break;
                case SDL_CUSTOM_EVENT:
                    cout << "receive user custom event\n";
                    break;
            }
        }
    }

    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    SDL_Quit();

    return 0;
}

// 线程运行函数
int sdl_thread_custom_event(void *) {
    // 延时 5 秒
    SDL_Delay(5000);
    // 创建自定义事件并发送到消息队列中去
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CUSTOM_EVENT;
    SDL_PushEvent(&sdlEvent);

    return 0;
}
