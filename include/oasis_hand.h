#pragma once


/** Includes */

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <jalbDraw/jalb_draw2d_api.h>


/** Forward Declaring */

struct card;
struct cardMod;


/** Structs */

struct player {
	ArrayList *deck;	// (struct card*)
	ArrayList *deckTotal;	// (struct card*)

	struct card *hand[10];
	struct card *board[7];
	int health;

	int mana;
	int manaMax;

	int fatigue;
};

struct pick3 {
	char name[256];
	int cards[3];
};


#define HAND_MAX 10
#define BOARD_MAX 7
#define MANA_MAX 10




/** Functions */

void *oasis_init ( );
void oasis_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data );
int oasis_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );
void oasis_close ( char *data );
void oasis_number ( int id );



/// Other Functions

void init_oasis_game ( );
void hand_make_cards ( );

// adds to the base list, but also returns card so you can edit it afterwards.
struct cardBase *make_card ( int mana, int atk, int hp, char *name );
struct cardBase *make_cardBase_spell ( char *name );

void copyCard_id ( ArrayList *list, int id );
struct card *copyCard_base ( int id );
struct card *copyCard ( struct card *card );

struct cardMod *cardMod_copy ( struct cardMod *copy );



void turn_change ( );

void startTurn_player ( struct player *player );

void shuffle_to ( ArrayList *deck, ArrayList *deckTotal );
void player_damage ( struct player *player, int dmg );

void enemy_ai ( struct player *player );

int draw_player ( struct player *player );
void mana_increment ( struct player *player );


// game

int get_hand_len ( struct player *player );
int get_board_len ( struct player *player );



char *mod_to_str ( struct cardMod *mod );




