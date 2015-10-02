#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *zombie = NULL, *ecran = NULL;
    SDL_Rect spZombie;

    spZombie.x = 0;
    spZombie.y = 0;
    ecran = SDL_SetVideoMode(1184, 666, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Trivial Zombie", NULL);
    int continuer = 1;
    SDL_Event event;
    zombie = SDL_LoadBMP("zombie.bmp");
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            continuer = 0;
        }
        SDL_BlitSurface(zombie, NULL, ecran, &spZombie);
    }
    SDL_Quit();
    return 0;
}
