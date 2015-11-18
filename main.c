#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include "math.h"
#include "definition.h"

//Déclaration des variables
int colorkey, mem_jump, v=1, direct, val, point, compteur = 0, compteur_life =0, life = 1000, pos_x, game_over;
float vy = 0;
Uint8 *keystate;
SDL_Surface *screen = NULL, *temp, *texte_score, *texte_vie;
SDL_Event event;
int  continuer = 1, memx = 556;
SDL_Rect mouse, pos_score, pos_vie;
TTF_Font *score, *vie;
SDL_Color blanc = {255,255,255};

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
}

int main(int argc, char *argv[])
{
    // Déclaration des variables
    
    TTF_Init();
    
    score = TTF_OpenFont("score.ttf",20);
    pos_score.x = 30;
    pos_score.y = 10;

    vie = TTF_OpenFont("score.ttf",20);
    pos_vie.x = 1050;
    pos_vie.y = 10;
    
    playerg.Rcsprite.y = 504;
    playerd.Rcsprite.y = 504;

    //Création de la maison
    create_house();
    
    // Début du jeu
    while (continuer)
    {
	int result = 1;
	compteur += 1;
	compteur_life += 1;
	
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
	
	char points[200];
	sprintf(points, "Score : %d", point);
	texte_score = TTF_RenderText_Blended(score,points,blanc);
	SDL_BlitSurface(texte_score, NULL, screen, &pos_score);

	char vies[200];
	sprintf(vies, "Vie : %d",life );
	texte_vie = TTF_RenderText_Blended(vie,vies,blanc);
	SDL_BlitSurface(texte_vie, NULL, screen, &pos_vie);
	
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
	
	//Spawn des zombies
	if(compteur_life == 10){
	  pos_x = rand()%2;
	  spawn_zombie(pos_x * 1184 ,504);
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
	  liste* pr = proj;
	  while(pr != NULL){
	    object p = pr -> obj;
	    if(collision(p,z)){
	      z.life = 0;
	      p.life = 0;
	      point += 100;
	    }
	    pr -> obj = p;
	    pr = pr -> tail;
	  }
	  swarm_t -> obj = z;
	  swarm_t = swarm_t ->tail;
	  //printf("%d\n",z.life);
	}
	//printf("\n");
	swarm = freeObj(swarm);
	proj = freeObj(proj);
	
	// Affichage des projectiles
	liste* pr = proj;
	while(pr != NULL) {
	  object p = pr -> obj;
	  SDL_BlitSurface(bullet.sprite, NULL, screen, &p.Rcsprite);
	  p.Rcsprite.x += p.direct*5;
	  if((p.Rcsprite.x < 0) || (p.Rcsprite.x > 1184)){
	    p.life = 0;
	  }
	  pr -> obj = p;
	  pr = pr -> tail;
	}
	
	proj = freeObj(proj);
	
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
	  if(!collision_player_right(memx,playerg.Rcsprite.y) && playerd.Rcsprite.x < 1111){ 
	    v = 1;
	    memx += 3;
	  }
	}
	
	if(keystate[SDLK_q]){
	  if(!collision_player_left(memx,playerg.Rcsprite.y) && playerg.Rcsprite.x > 0){ 
	    v = 0;
	    memx -= 3;
	  }
	}

	if(keystate[SDLK_RIGHT]){
	  if(compteur == 1){
	    v = 1;
	    shoot(memx + 73, playerd.Rcsprite.y + 16, 1);
	  }
	}
	
	if(keystate[SDLK_LEFT]){
	  if(compteur == 1){
	    v = 0;
	    shoot(memx - 7, playerd.Rcsprite.y + 16,-1);
	  }
	}
	
	//Mouvement des zombies
	liste* swarm_m = swarm;
	while(swarm_m != NULL){
	  object z = swarm_m -> obj;
	  if(z.orientation == 1){
	    if (z.Rcsprite.x + 84 < memx) {
	      z.Rcsprite.x += 1;
	    }else if(z.Rcsprite.x > memx + 73) {
	      z.orientation = 0;
	    }else if(z.Rcsprite.x >= memx && z.Rcsprite.x <= memx +73) {
	      if(compteur_life == 1){
		life -= 50;
	      }
	    }
	   }else{
	      if (z.Rcsprite.x + 84 < memx) {
		z.orientation = 1;
	      }else if(z.Rcsprite.x > memx + 73) {
		z.Rcsprite.x -= 1;
	      }else if(z.Rcsprite.x >= memx && z.Rcsprite.x <= memx +73) {
		if(compteur_life == 1){
		  life -=50;
		}
	      }
	   }
	   swarm_m -> obj = z;
	   swarm_m = swarm_m ->tail;
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
	
	if(compteur == 20){
	  compteur = 0;
	}
	
	if(compteur_life == 100){
	  compteur_life = 0;
	}
	
	if(life <= 0){
	  continuer = 0;
	  game_over = 1;
	}
	
    }
    
    TTF_Quit();
    SDL_Quit();
    return 0;
}
