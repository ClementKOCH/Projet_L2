#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int colorkey;


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *player, *temp, *screen = NULL;
    SDL_Rect rcSrc, rcSprite;

    rcSrc.x = 0;
    rcSrc.y = 0;

    rcSprite.x = 0;
    rcSprite.y = 0;

    screen = SDL_SetVideoMode(1184, 666, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Trivial Zombie", NULL);

    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            continuer = 0;
        }

        temp   = SDL_LoadBMP("player.bmp");
        player = SDL_DisplayFormat(temp);
        colorkey = SDL_MapRGB(screen->format, 255, 0, 221);
        SDL_SetColorKey(player, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
        SDL_FreeSurface(temp);

        SDL_BlitSurface(player, &rcSrc, screen, &rcSprite);
        SDL_Flip(screen);

    }
    SDL_Quit();
    return 0;
}
