#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "math.h"
#include "definition.h"

//Déclaration des variables
int colorkey, mem_jump, v=1, direct, val;
float vy = 0;
Uint8 *keystate;
SDL_Surface *screen = NULL, *temp;
SDL_Event event;
int  continuer = 1, memx = 556;
SDL_Rect mouse;

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
    if(event.type == SDL_QUIT){
      continuer = 0;
    }
    if(event.type == SDL_MOUSEMOTION){
      mouse.x = event.motion.x;
      mouse.y = event.motion.y;
      if(mouse.x < memx){
	v=0;
      } else {
	v=1;
      }
    }
    if(event.type == SDL_MOUSEBUTTONDOWN) {
      if(mouse.y > playerd.Rcsprite.y){
	val = +100;
      } else {
	val = -100;
      }
      if(v==1){
	shoot(memx + 73, playerd.Rcsprite.y + 16, 1, mouse.x , mouse.y );
      } else {
	shoot(memx - 7, playerd.Rcsprite.y + 16,-1, mouse.x, mouse.y );
      }
    }
}

int main(int argc, char *argv[])
{
    // Déclaration des variables
    
    
    playerg.Rcsprite.y = 504;
    playerd.Rcsprite.y = 504;

    //Création de la maison
    create_house();
    
    // Début du jeu
    while (continuer)
    {
	int result = 1;
	
        // Initialisation de la fenêtre
        SDL_Init(SDL_INIT_VIDEO);
        screen = SDL_SetVideoMode(1184, 666, 32, SDL_HWSURFACE);
        SDL_WM_SetCaption("Trivial Zombie", NULL);
	putenv("SDL_VIDEO_WINDOW_POS=center");

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

        playerg.Rcsprite.x = memx;
        playerg.Rcsprite.y -= vy;
	
	temp = SDL_LoadBMP("wall.bmp");
	wall.sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	temp = SDL_LoadBMP("door.bmp");
	door.sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	temp = SDL_LoadBMP("bullet.bmp");
	bullet.sprite = SDL_DisplayFormat(temp);
	colorkey = SDL_MapRGB(screen->format, 255, 0, 221);
        SDL_SetColorKey(bullet.sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	SDL_FreeSurface(temp);
	
        // Affichage du joueur
        draw_player(v);
	
	// Affichage de la maison
	liste* it = w_house;
	while(it != NULL) {
	  object w = it -> obj;
	  SDL_BlitSurface(wall.sprite, NULL, screen, &w.Rcsprite);
	  
	  it -> obj = w;
	  it = it -> tail;
	}
	
	// Affichage des portes
	liste* prt = d_house;
	while(prt != NULL) {
	  object d = prt -> obj;
	  SDL_BlitSurface(door.sprite, NULL, screen, &d.Rcsprite);
	  
	  prt -> obj = d;
	  prt = prt -> tail;
	}
	
	// Affichage des projectiles
	liste* pr = proj;
	double xA,yA,xB,yB,px,py;
	while(pr != NULL) {
	  object p = pr -> obj;
	  SDL_BlitSurface(bullet.sprite, NULL, screen, &p.Rcsprite);
	  xA = p.dep.x;
	  yA = p.dep.y;
	  xB = p.dest.x;
	  yB = p.dest.y;
	  px = p.Rcsprite.x;
	  
	  if((xA-xB)<1 && (xA-xB)>-1){
	    py += (1*abs(p.dep.y - p.dest.y))/100;
	  } else {
	    px += (1*abs(p.dep.x - p.dest.x))/100 * p.direct;
	    py = ((yB - yA)*px + (xB*yA-xA*yB))/(xB - xA);
	    p.Rcsprite.x = px;
	    p.Rcsprite.y = py;
	  }
	  pr -> obj = p;
	  pr = pr -> tail;
	}
	
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
	
	if(keystate[SDLK_ESCAPE]){
	  continuer = 0;
	}
	
	if(keystate[SDLK_d]){
	  if(!collision_player_right(memx,playerg.Rcsprite.y)){ 
	    v = 1;
	    memx += 2;
	  }
	}
	
	if(keystate[SDLK_q]){
	  if(!collision_player_left(memx,playerg.Rcsprite.y)){ 
	    v = 0;
	    memx -= 2;
	  }
	}
	
	//Gestion des Sauts
	if((keystate[SDLK_SPACE]) && (mem_jump == 0)){
          liste* col = w_house;
	  while(col != NULL) {
	    object w = col -> obj;
	    if(v==1){
	      if((playerd.Rcsprite.x <= w.Rcsprite.x + 60) && (playerd.Rcsprite.x + 73 >= w.Rcsprite.x) && (w.trans == 1)) {
		result = 0;
	      }
	    } else {
	      if((playerg.Rcsprite.x <= w.Rcsprite.x +60) && (playerg.Rcsprite.x + 73 >= w.Rcsprite.x) && (w.trans == 1)){
		result = 0;
	      }
	    }
	    col -> obj = w;
	    col = col -> tail;
	  }
	  if(result){
	    vy = 4;
	    mem_jump = 1;
	  }
	}
	
	// Persistance des sauts
	if(mem_jump == 1){
	  vy -= 0.1;
	}
	if(vy < -4.8){
	  mem_jump = 0;
	  vy = 0.0;
	}
    }

    SDL_Quit();
    return 0;
}
