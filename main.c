#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "definition.h"

//Déclaration des variables
int colorkey, mem_jump, continuer = 1;
float vy = 0;
SDL_Surface *screen = NULL, *temp;
Uint8 *keystate;

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

void HandleEvent(SDL_Event event)
{
  switch (event.type){
    case SDL_QUIT:
      continuer = 0;
      break;
  }
}

int main(int argc, char *argv[])
{
    // Déclaration des variables
    int v=1, memx = 556 ;
    SDL_Event event;
    
    playerg.Rcsprite.y = 444;
    playerd.Rcsprite.y = 444;

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
        playerd.Rcsprite.y -= vy;

        temp = SDL_LoadBMP("playerg.bmp");
        playerg.sprite = SDL_DisplayFormat(temp);
        colorkey = SDL_MapRGB(screen->format, 255, 0, 221);
        SDL_SetColorKey(playerg.sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
        SDL_FreeSurface(temp);

        playerg.Rcsprite.x = memx - 73;
        playerg.Rcsprite.y -= vy;

        // Affichage du joueur
        draw_player(v);
        // Flip de l'écran
        SDL_Flip(screen);

        // Libération de la surface du joueur
        SDL_FreeSurface(playerd.sprite);
	SDL_FreeSurface(playerg.sprite);
	
        //Gestion des events
	if (SDL_PollEvent(&event)){
	  HandleEvent(event);
	}
	
	keystate = SDL_GetKeyState(NULL);
	
	if(keystate[SDLK_RIGHT]){
	  v = 1;
          memx += 1;
	}
	
	if(keystate[SDLK_LEFT]){
	  v = 0;
          memx -= 1;
	}
	
	if((keystate[SDLK_SPACE]) && (mem_jump == 0)){
          vy = 5.0;
	  mem_jump = 1;
	}
	
	if(mem_jump == 1){
	  vy -= 0.1;
	  printf("%d\n",playerd.Rcsprite.y);
	}
       
	if(vy < -5.8){
	  mem_jump = 0;
	  vy = 0.0;
	}
        
        

        
    }

    SDL_Quit();
    

    return 0;
}
