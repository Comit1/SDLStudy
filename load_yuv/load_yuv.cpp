
#include <SDL.h>
#include <string>
#include <zconf.h>

using namespace std;

unsigned char *readFile(string path, int width, int height) {
    // 打开文件
    FILE *pFile = fopen(path.c_str(), "rb");
    // 读取文件内容到 buffer 中
    unsigned char *yuvData;
    // yuv420p 格式的文件大小
    int frameSize = width * height * 3 / 2;
    yuvData = static_cast<unsigned char *>(malloc(frameSize * sizeof(unsigned char)));
    fread(yuvData, frameSize, 1, pFile);
    // 关闭文件
    fclose(pFile);

    return yuvData;
}

int main() {

    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    string currentWorkingDir(buff);
    int index = currentWorkingDir.find("SDL");
    string currentSourceDir = currentWorkingDir.substr(0, index);

    string yuvPath = currentSourceDir + "SDL/load_yuv/test.yuv";

    const int width = 500;
    const int height = 318;
    SDL_Window *pWindow = SDL_CreateWindow(
            "Hello YUV",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *pRenderer = nullptr;
    // 创建渲染器
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    SDL_Texture *pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_IYUV,
                                              SDL_TEXTUREACCESS_STATIC,
                                              width, height);
    if (pTexture != nullptr) {
        unsigned char *yuvData = readFile(yuvPath, width, height);
        // 更新纹理内容，就是把读取的 YUV 数据转换成纹理
        SDL_UpdateTexture(pTexture, nullptr, yuvData, width);
        // 清屏操作
        SDL_RenderClear(pRenderer);
        // 将指定纹理复制到要渲染的地方
        SDL_RenderCopy(pRenderer, pTexture, nullptr, nullptr);
        // 上屏操作
        SDL_RenderPresent(pRenderer);
    }

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
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyTexture(pTexture);
    SDL_Quit();

    return 0;

}
