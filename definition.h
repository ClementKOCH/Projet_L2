#ifndef GENERATION_H
#define GENERATION_H
#include "SDL.h"

typedef struct object{


    SDL_Surface *sprite;
    int sprite_size;
    SDL_Rect Rcsprite, Rcsource;
    int speed;
    int x;
    int y;
    int trans;
    int life;

}object;

typedef struct liste{

    struct object head;
    struct liste* tail;

}liste;

typedef struct level{

    int nbr_zombie;

}level;

typedef struct liste_level{

    struct level head;
    struct liste_level* tail;

}liste_level;

