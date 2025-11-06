#pragma once


/** Includes */

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>
#include <stdlib.h>


#include <jalb/jalbArrayList.h>


/** Forward Declaring */

struct card;
struct cardBase;
//struct cardMod;

struct player;

struct pick3;


/** Structs */


/** Functions */


void set_debugPrint_oasisRender ( int i );

/// Render

void oasis_assemble_dom ( int *XYWHpass );

void oasis_game_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data );
void render_character ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY );
void render_board ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY, int cursor );
void render_hand ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY, int cursor );

void card_render_highlight ( int *screenDims, GLuint *glBuffers, int *XYWHpass );
void oasis_card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct card *card );
void oasis_cardBase_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct cardBase *base );
void oasis_card_render_base ( int *screenDims, GLuint *glBuffers, int *XYWHpass,
		char *name, int type, int mana, int attack, int health, int numAttacks, ArrayList *mods );



void text_in_circle ( int *screenDims, GLuint *glBuffers, int *XY, float *color, char *str );




/** Pick 3 */

void row3_init ( int *screenDims );
void render_pick3 ( int *screenDims, GLuint *glBuffers );

void pick3_render_card ( int *screenDims, GLuint *glBuffers, int XYWH[], struct pick3 *p3 );


int event_pick3 ( SDL_Event *e, int *clickXY, int *eleWH );
