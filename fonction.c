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
  door.life = 10;
  return door;
}



int collision(object colider_1, object colider_2){
  int res = 0;
    if((colider_1.Rcsprite.x <= colider_2.Rcsprite.x) && (colider_1.Rcsprite.x >= colider_2.Rcsprite.x) && (colider_1.Rcsprite.y <= colider_2.Rcsprite.y) && (colider_1.Rcsprite.y >= colider_2.Rcsprite.y)){
      res = 1;
    }
  return res;
}

/*int collision_player_left(int memx, int memy)
{
  int res = 0;
  liste* col = w_house;
  while(col != NULL) {
    object w = col -> obj;
    if((memx <= w.Rcsprite.x + 134) && (memx >= w.Rcsprite.x) && (memy <= w.Rcsprite.y + 40) && (memx >= w.Rcsprite.y) ){
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
    if((memx + 73 >= w.Rcsprite.x) && (memx <= w.Rcsprite.x + 60) && (memy <= w.Rcsprite.y + 40) && (memx >= w.Rcsprite.y)){
      res = 1;
    }  
    col -> obj = w;
    col = col -> tail;
  }
  return res;
}*/
  
object create_bullet(int posx, int posy, double angle){
  bullet.Rcsprite.x = posx;
  bullet.Rcsprite.y = posy;
  bullet.angle = angle;
  return bullet;
}


void shoot(int posx, int posy, double angle){
  object bullet = create_bullet(posx,posy,angle);
  proj = insert(bullet, proj);
}

object create_zombie(int posx, int posy, int orientation){
  zombie.Rcsprite.x=posx;
  zombie.Rcsprite.y=posy;
  zombie.orientation=orientation;
  return zombie;
}

void spawn_zombie(int posx, int posy){
  int orientation;
  if(posx<playerd.Rcsprite.x){
    orientation = 1;
  }else{
    orientation = 0;
  }
  object zombie = create_zombie(posx,posy,orientation);
  swarm = insert(zombie,swarm);
}

object create_player(int posx, int posy, int orientation){
  player.Rcsprite.x = posx;
  player.Rcsprite.y = posy;
  player. orientation= orientation;
  return player;
}

