#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

static void printButton(SDL_Event *e, const char *upDown) {
    printf("Joystick %d Button %d %s\n",
           (*e).jdevice.which, (*e).jbutton.button, upDown);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_JOYSTICK) == -1) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    int nJoy = SDL_NumJoysticks();
    if (nJoy < 1) {
        fprintf(stderr, "No joysticks found\n");
        return 1;
    }
    SDL_Joystick *joysticks[nJoy];
    for (int i = 0; i < nJoy; ++i) {
        SDL_Joystick *pJoystick = SDL_JoystickOpen(i);
        if (pJoystick == NULL) {
            fprintf(stderr, "Failed to open Joystick %d: %s\n",
                    i,
                    SDL_GetError());
            return 1;
        }
        joysticks[i] = pJoystick;
    }
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_JOYAXISMOTION:
                    printf("Joystick %d Axis %d %d\n",
                           e.jdevice.which, e.jaxis.axis, e.jaxis.value);
                    break;
                case SDL_JOYBUTTONDOWN:
                    printButton(&e, "DOWN");
                    break;
                case SDL_JOYBUTTONUP:
                    printButton(&e, "UP");
                    break;
            }

        }
    }
    for (int i = 0; i < nJoy; ++i) {
        SDL_JoystickClose(joysticks[i]);
    }
    SDL_Quit();
    return 0;
}

