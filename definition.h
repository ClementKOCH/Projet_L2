#ifndef GENERATION_H
#define GENERATION_H
#include "SDL.h"

/*Definition variables*/



/*Definition des objets*/

typedef struct object{


    SDL_Surface *sprite;
    int sprite_size;
    SDL_Rect Rcsprite, Rcsource;
    int speed;
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

/*Definition des fonctions*/

liste* insert(object obj, liste* L);
void freelist(liste* L);
liste freeObj(liste* L);

/*Definition objets*/

object zombie;
object wall;
object door;
object fence;
object bullet;
object playerd;
object playerg;

/*Definition des spawn */

object spawn_zombie();

#endif
