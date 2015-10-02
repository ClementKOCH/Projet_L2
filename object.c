#include "definition.h"
#include "SDL/SDL.h"
#include "math.h"

object wall(posx,posy){
    wall.speed=0;
    wall.sprite_size=60;
    wall.Rcsprite.x=posx;
    wall.Rcsprite.y=posy;
    wall.life=1;
    wall.trans=0;
    wall.Rcsource.x=0;
    wall.Rcsource.y=0;
    wall.Rcsource.h=44;
    wall.Rcsource.w=wall.sprite_size;
}

