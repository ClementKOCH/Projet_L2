#include "definition.h"
#include "SDL.h"
#include "math.h"

/*insert element in list*/

liste* insert(object obj, liste* L)
{
	liste* node = malloc (sizeof (liste));
	node->obj = obj;
	node->tail = L;
	return node;
}

/*clear list*/

void freelist(liste* L)
{
	liste* it = L;
	while(it != NULL) {
		// liberation d'object
		liste* reste = it->tail;
		free(it);
		it = reste;
	}
}

liste* freeObj(liste* L)
{
  liste* pit = L;
  liste* new_pit = NULL;
  while(pit != NULL) {
    struct object test = pit -> obj;
    if (test.life != 0) {
      new_pit = insert(test, new_pit);
    }else{
      free(pit);
    }
    pit = pit ->tail;
  }
  return new_pit;
}

void create_house()
{
  int debx = 412, deby = 494, compt = 0;
  while(compt < 3){
    deby -= 44;
    object wall = create_wall(debx,deby);
    w_house = insert(wall, w_house);
    compt ++;
  }
  compt = 0;
  deby -= 44;
  while(compt < 6){
    object wall = create_ceiling(debx,deby);
    w_house = insert(wall, w_house);
    compt ++;
    debx += 60;
  }
  compt = 0;
  debx -= 60;
  deby += 44;
  while(compt < 3){
    object wall = create_wall(debx,deby);
    w_house = insert(wall, w_house);
    deby += 44;
    compt ++;
  }
  debx = 429;
  deby = 494;
  object door = create_door(debx,deby);
  d_house = insert(door, d_house);
  debx += 300;
  door = create_door(debx,deby);
  d_house = insert(door, d_house);
}

object create_wall(int posx, int posy)
{
  wall.Rcsprite.x = posx;
  wall.Rcsprite.y = posy;
  wall.trans = 1;
  return wall;
}

object create_ceiling(int posx, int posy)
{
  wall.Rcsprite.x = posx;
  wall.Rcsprite.y = posy;
  wall.trans = 0;
  return wall;
}

object create_door(int posx, int posy)
{
  door.Rcsprite.x = posx;
  door.Rcsprite.y = posy;
  door.trans = 0;
  return door;
}

int collision_player_left(int memx, int memy)
{
  int res = 0;
  liste* col = w_house;
  while(col != NULL) {
    object w = col -> obj;
    if((memx <= w.Rcsprite.x + 60) && (memx >= w.Rcsprite.x) && (memy <= w.Rcsprite.y + 40) && (memy >= w.Rcsprite.y) ){
      res = 1;
    }  
    col -> obj = w;
    col = col -> tail;
  }
  return res;
}

int collision_player_right(int memx, int memy)
{
  int res = 0;
  liste* col = w_house;
  while(col != NULL) {
    object w = col -> obj;
    if((memx + 73 >= w.Rcsprite.x) && (memx <= w.Rcsprite.x + 60) && (memy <= w.Rcsprite.y + 40) && (memy >= w.Rcsprite.y)){
      res = 1;
    }  
    col -> obj = w;
    col = col -> tail;
  }
  return res;
}
  
object create_bullet(int posx, int posy, int direct){
  bullet.Rcsprite.x = posx;
  bullet.Rcsprite.y = posy;
  bullet.direct = direct;
  bullet.life = 1;
  return bullet;
}

void shoot(int posx, int posy, int direct){
  object bullet = create_bullet(posx,posy,direct);
  proj = insert(bullet, proj);
}

object create_zombie(int posx, int posy, int orientation){
  zombie.Rcsprite.x=posx;
  zombie.Rcsprite.y=posy;
  zombie.orientation=orientation;
  zombie.life = 1;
  return zombie;
}

void spawn_zombie(int posx, int posy){
  int orientation;
  if(posx<550){
    orientation = 1;
  }else{
    orientation = 0;
  }
  object zombie = create_zombie(posx,posy,orientation);
  swarm = insert(zombie,swarm);
}

int collision(object p, object z){
  if((p.Rcsprite.x >= z.Rcsprite.x) && (p.Rcsprite.x <= z.Rcsprite.x + 84)){
    return 1;
  }else{
    return 0;
  }
}
