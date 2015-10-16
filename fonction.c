#include "definition.h"
#include "SDL.h"
#include "math.h"

/*fonctions listes*/

/*insert element in list*/

liste* insert(object obj, liste* L)
{
	liste* node = malloc (sizeof (liste));
	node->obj = obj;
	node->tail = L;
	return node;
}

s_liste_lvl* insert_lvl(s_level lv, s_liste_lvl* li)
{
	s_liste_lvl* node = malloc (sizeof (s_liste_lvl));
	node->lvl = lv;
	node->tail = li;
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


/*house creation*/

liste roof(posx,posy){

    for(int i;i++; i<=12){


    }



}

