#pragma once

/** Includes */

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>
#include <stdlib.h>

#include <jalbDraw/jalb_draw2d_api.h>

/** Structs */

struct player {
	ArrayList *deck;	// (struct card*)
	struct card *hand[10];
	struct card *board[7];
	int health;

	int mana;
	int manaMax;
};



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

void copyCard_id ( ArrayList *list, int id );
struct card *copyCard_base ( int id );


/// Render

void oasis_game_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data );
void render_board ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY, int cursor );
void render_hand ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY, int cursor );

void card_render_highlight ( int *screenDims, GLuint *glBuffers, int *XYWHpass );
void oasis_card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct card *card );


/// Event

int oasis_game_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );

// doesnt simply return the index, it also makes sure a minion exists there.
int board_click_index ( struct player *player, int *clickXY, int *boardXYWH );

// for for the player only.
void play_hand_to_board ( struct player *player, int handI );


/// Other

// i am removing card at arr[i], so shift everything at an index above that, left by 1.
// make sure the final arr[index] is set to null.
void shrink_array ( struct card *arr[], int i, int max );

void card_attack ( struct player *attacker, struct player *defender, int attackIndex, int defendIndex );

void turn_change ( );

void enemy_ai ( struct player *player );

void draw_player ( struct player *player );
void mana_increment ( struct player *player );


/// Utilities

// render

int centerX ( int x, int w, int glyphW, int numChars );


// game

int get_hand_len ( struct player *player );
int get_board_len ( struct player *player );

