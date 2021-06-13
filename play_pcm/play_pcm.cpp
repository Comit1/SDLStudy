
#include <SDL_audio.h>
#include <iostream>
#include <SDL_events.h>
#include <SDL.h>
#include <zconf.h>

using namespace std;

int main() {

    SDL_Init(SDL_INIT_AUDIO);

    const int width = 500;
    const int height = 500;
    SDL_Window *pWindow = SDL_CreateWindow(
            "Hello PCM",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_AudioSpec audioSpec;
    audioSpec.freq = 44100;
    audioSpec.format = AUDIO_S16SYS;
    audioSpec.channels = 2;
    audioSpec.silence = 0;
    audioSpec.samples = 1024;
    // 因为是推模式，所以这里为 nullptr
    audioSpec.callback = nullptr;

    SDL_AudioDeviceID deviceId;
    deviceId = SDL_OpenAudioDevice(nullptr, 0,
                                   &audioSpec, nullptr,
                                   SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (deviceId < 2) {
        cout << "open audio device failed: " << SDL_GetError() << endl;
        return -1;
    }

    bool bQuit = false;
    SDL_Event windowEvent;

    int num;
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    string currentWorkingDir(buff);
    int index = currentWorkingDir.find("SDL");
    string currentSourceDir = currentWorkingDir.substr(0, index);

    string pcmPath = currentSourceDir + "SDL/play_pcm/test.pcm";
    FILE *pFile = fopen(pcmPath.c_str(), "rb");

    // 播放音频
    SDL_PauseAudioDevice(deviceId, 0);

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

        int bufferSize = 4096;
        char *buffer = (char *) malloc(bufferSize);
        // 省略中间代码
        num = fread(buffer, bufferSize, 1, pFile);
        if (num) {
            // 填充
            SDL_QueueAudio(deviceId, buffer, bufferSize);
        }
    }

    fclose(pFile);
    SDL_DestroyWindow(pWindow);
    SDL_CloseAudioDevice(deviceId);

    return 0;
}

