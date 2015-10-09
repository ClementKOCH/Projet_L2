#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "definition.h"

//Déclaration des variables
int colorkey, mem_jump;
float vy = 0;
SDL_Surface *screen = NULL, *temp;

// Fonction qui affiche le joueur
void draw_player(int a)
{
  if(a==1)
  {
    SDL_BlitSurface(playerd.sprite, NULL, screen, &playerd.Rcsprite);
  } else
  {
    SDL_BlitSurface(playerg.sprite, NULL, screen, &playerg.Rcsprite);
  }
}

int main(int argc, char *argv[])
{
    // Déclaration des variables
    int continuer = 1, v=1, memx = 556, memy = 444;
    SDL_Event event;

    // Début du jeu
    while (continuer)
    {
        // Initialisation de la fenêtre
        SDL_Init(SDL_INIT_VIDEO);
        screen = SDL_SetVideoMode(1184, 666, 32, SDL_HWSURFACE);
        SDL_WM_SetCaption("Trivial Zombie", NULL);

        // Initialisation du joueur
        temp = SDL_LoadBMP("playerd.bmp");
        playerd.sprite = SDL_DisplayFormat(temp);
        colorkey = SDL_MapRGB(screen->format, 255, 0, 221);
        SDL_SetColorKey(playerd.sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
        SDL_FreeSurface(temp);

        playerd.Rcsprite.x = memx;
        playerd.Rcsprite.y = memy;

        temp = SDL_LoadBMP("playerg.bmp");
        playerg.sprite = SDL_DisplayFormat(temp);
        colorkey = SDL_MapRGB(screen->format, 255, 0, 221);
        SDL_SetColorKey(playerg.sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
        SDL_FreeSurface(temp);

        playerg.Rcsprite.x = memx - 73;
        playerg.Rcsprite.y = memy;

        // Affichage du joueur
        draw_player(v);

        // Flip de l'écran
        SDL_Flip(screen);

        // Libération de la surface du joueur
        SDL_FreeSurface(playerd.sprite);

        // Destion des events
        SDL_WaitEvent(&event);
        switch(event.type)
        {
          case SDL_QUIT:
            continuer = 0;
            break;
        }

        switch(event.key.keysym.sym)
        {
          case SDLK_RIGHT:
            v = 1;
            memx += 1;
            break;
          case SDLK_LEFT:
            v = 0;
            memx -= 1;
            break;
          case SDLK_ESCAPE:
            continuer = 0;
            break;
          case SDLK_SPACE:
            vy = 5.0;
            mem_jump = 1;
            break;
        }

        //Gestion des sauts
        memy -= vy;
        if(vy > 0) {
          vy -= 0.001;
        } else if (vy < 0)
        {
          vy += 0.001;
        }
        if((mem_jump == 1) && (vy == 0.0))
        {
          vy = -5.0;
        }
    }

    SDL_Quit();

    return 0;
}
