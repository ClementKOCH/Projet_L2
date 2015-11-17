#ifndef GENERATION_H
#define GENERATION_H
#include "SDL.h"

/*Definition des objets*/

typedef struct object{


    SDL_Surface *sprite;
    int sprite_size;
    SDL_Rect Rcsprite, Rcsource;
    int speed;
    int trans;
    int life;
    double angle;
    int orientation;

}object;

typedef struct liste{

    struct object obj;
    struct liste* tail;

}liste;


/*Definition des fonctions*/

liste* insert();
void freelist();
liste freeObj();
void create_house();
object create_wall();
object create_ceiling();
object create_door();
object create_bullet();
object create_zombie();
void spawn_zombie();
void shoot();
void draw_player();
void HandleEvent();
int collision_player_left();
int collision_player_right();
int collision();
void spawn_player();
object create_player();

/*Definition objets*/

object player;
object zombie;
object wall;
object door;
object fence;
object bullet;
object playerd;
object playerg;
object zombid;
object zombig;

/* Definition des listes */

liste* w_house;
liste* d_house;
liste* proj;
liste* swarm;
liste* l_player;



#endif
