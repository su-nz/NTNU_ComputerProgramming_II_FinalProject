#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>


/*

makefile example:

	- gcc music.c -o music `sdl2-config --cflags --libs` -lSDL2_mixer

	 安裝 SDL2 和 SDL_mixer
	
	1.Ubuntu / Debian:
	
	sudo apt install libsdl2-dev libsdl2-mixer-dev
	
	2.macOS (使用 Homebrew):
	
	brew install sdl2 sdl2_mixer

*/

void handle_sigint(int sig) {
    printf("\n收到 Ctrl+C，中止程式...\n");
    exit(0);
}

int main(int argc, char* argv[]) {
   signal(SIGINT, handle_sigint);
	 if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio error: %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music* bgm = Mix_LoadMUS("music.mp3");
    if (!bgm) {
        fprintf(stderr, "Load BGM error: %s\n", Mix_GetError());
        return 1;
    }

    // 主邏輯：模擬遊戲主迴圈
    for (int i = 0; i < 10; i++) {
        printf("遊戲進行中 %d...\n", i);
        SDL_Delay(1000); // 假裝每秒進行一次遊戲邏輯
    }

    // 結束時釋放音樂
     Mix_HaltMusic();
	Mix_FreeMusic(bgm);
	Mix_CloseAudio();
	SDL_Quit();	
    return 0;
}

