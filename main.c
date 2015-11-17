#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "math.h"
#include "definition.h"

//Déclaration des variables
int colorkey, mem_jump;
float vy = 0;
Uint8 *keystate;
SDL_Surface *screen = NULL, *temp;
SDL_Event event;
int  continuer = 1, memx = 556;
SDL_Rect mouse;

void HandleEvent(SDL_Event event)
{
  switch (event.type){
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_MOUSEMOTION:
      mouse.x = event.motion.x;
      mouse.y = event.motion.y;
      break;
  }
}

int main(int argc, char *argv[])
{
    // Déclaration des variables
    int p_orientation=1;
    
    playerg.Rcsprite.y = 504;
    playerd.Rcsprite.y = 504;

    //Création du personnage

    object player = create_player(memx,504,p_orientation);

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

        playerg.Rcsprite.x = memx - 73;
        playerg.Rcsprite.y -= vy;

    	//Initialisation zombie

    	temp = SDL_LoadBMP("zombid.bmp");
    	zombid.sprite = SDL_DisplayFormat(temp);
    	colorkey = SDL_MapRGB(screen->format, 255, 0, 221);
	    SDL_SetColorKey(zombid.sprite,SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    	SDL_FreeSurface(temp);	

	    temp = SDL_LoadBMP("zombig.bmp");
	    zombig.sprite = SDL_DisplayFormat(temp);
	    colorkey = SDL_MapRGB(screen->format, 255, 0, 221);
	    SDL_SetColorKey(zombig.sprite,SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	    SDL_FreeSurface(temp);	

	    //Initialisation maison

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
		while(pr != NULL) {
		  object p = pr -> obj;
		  p.Rcsprite.x += 10 *((cos(p.angle) * 2.0 * 3.14159265358979323)/360.0);
		  p.Rcsprite.y -= 10* ((sin(p.angle) * 2.0 * 3.14159265358979323)/360.0);
		  SDL_BlitSurface(bullet.sprite, NULL, screen, &p.Rcsprite);
		  
		  pr -> obj = p;
		  pr = pr -> tail;
		}

		//Affichage des zombies
		liste* swarm_t = swarm;
		while(swarm_t != NULL){
			object z = swarm_t -> obj;
			if(z.orientation == 1){
				SDL_BlitSurface(zombid.sprite,NULL,screen,&z.Rcsprite);
			}else{
				SDL_BlitSurface(zombig.sprite,NULL,screen,&z.Rcsprite);
			}
			swarm_t -> obj = z;
			swarm_t = swarm_t ->tail;
		}

		//Affichage du joueur

		if(player.orientation==1)
	  	{
	    	SDL_BlitSurface(playerd.sprite, NULL, screen, &player.Rcsprite);
	  	} else
	  	{
	    	SDL_BlitSurface(playerg.sprite, NULL, screen, &player.Rcsprite);
	  	}		 		
		
	    // Flip de l'écran
	    SDL_Flip(screen);

	    // Libération de la surface du joueur
	    SDL_FreeSurface(playerd.sprite);
		SDL_FreeSurface(playerg.sprite);

		//Libération de la surface des zombies
		SDL_FreeSurface(zombig.sprite);
		SDL_FreeSurface(zombid.sprite);
		
	    //Gestion des events
		
		if (SDL_PollEvent(&event)){
		  HandleEvent(event);
		}
		
		keystate = SDL_GetKeyState(NULL);
		
		if(keystate[SDLK_ESCAPE]){
		  continuer = 0;
		}

		if(keystate[SDLK_d]){
	 		if(!collision(player,w_house)){ 
			    player.orientation = 1;
			    memx += 5;
			    printf("%d\n", memx );
			}
		}
			
		if(keystate[SDLK_q]){
		  if(!collision(player,w_house)){ 
		    player.orientation  = 0;
		    memx -= 5;
			printf("%d\n", memx );			
			}
		}
			
		if(keystate[SDLK_z]){
			double angle = (atan(abs(memx+73 - mouse.x)) / (abs(player.Rcsprite.y - mouse.y)));
			printf("%f\n", (atan(abs(memx+73 - mouse.x)) / (abs(player.Rcsprite.y - mouse.y))));
			if(player.orientation==1){
			    shoot(memx + 73, player.Rcsprite.y + 16, angle);
			} else {
			    shoot(memx - 80, player.Rcsprite.y + 16, angle);
			}
		}

		//Gestion des Sauts
		if((keystate[SDLK_SPACE]) && (mem_jump == 0)){
			printf("test \n");
	        liste* col = w_house;
		  	while(col != NULL) {
		    	object w = col -> obj;
		    	if(player.orientation==1){
		      	if((player.Rcsprite.x <= w.Rcsprite.x + 60) && (player.Rcsprite.x + 73 >= w.Rcsprite.x) && (w.trans == 1)) {
					result = 0;
		      	}
		    	} else {
		    		if((player.Rcsprite.x <= w.Rcsprite.x +60) && (player.Rcsprite.x + 73 >= w.Rcsprite.x) && (w.trans == 1)){
						result = 0;
		      		}
		    	}
			    col -> obj = w;
			    col = col -> tail;
		  	}
		}


		if(result){
			vy = 4;
	    	mem_jump = 1;
	  	}
		
		
		// Persistance des sauts
		if(mem_jump == 1){
		  	vy -= 0.1;
		}
		if(vy < -4.8){
			mem_jump = 0;
	  		vy = 0.0;
		}

		//spawn zombie

		if(keystate[SDLK_f]){
			spawn_zombie(504,556);
			spawn_zombie(0,504);
			spawn_zombie(1000,504);
		}

		//movement zombie

		liste* swarm_m = swarm;
		while(swarm_m != NULL){
			object z = swarm_m -> obj;
			if(!collision(z,d_house)){
				if(z.orientation == 1){
					if (z.Rcsprite.x + 84 < memx)
					{
						z.Rcsprite.x += 1;
						z.orientation = 1;
					}else if(z.Rcsprite.x > memx)
					{
						z.Rcsprite.x -= 1;
						z.orientation = 0;
					}else if(z.Rcsprite.x == memx)
					{
						z.Rcsprite.x = memx;
					}
					}else{
					if (z.Rcsprite.x + 84 < memx)
					{
						z.Rcsprite.x += 1;
						z.orientation = 1;
					}else if(z.Rcsprite.x > memx)
					{
						z.Rcsprite.x -= 1;
						z.orientation = 0;
					}else if(z.Rcsprite.x == memx)
					{
					z.Rcsprite.x = memx;
					}
				}	
			}
			swarm_m -> obj = z;
			swarm_m = swarm_m ->tail;
		}
	}

    SDL_Quit();
    return 0;
}
