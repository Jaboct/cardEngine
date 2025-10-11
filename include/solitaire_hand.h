#pragma once


/** Includes */

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <time.h>
#include <stdlib.h>



/** Forward Declaring */

struct jalbFont;


/** Functions */


/// Solitaire

void *solitaire_init ( );
void solitaire_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data );
int solitaire_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );
void solitaire_close ( char *data );
void solitaire_number ( int id );


void fill_stock ( );
void solitair_render_full ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data );

void center_text ( int pass[4], int ret[4], struct jalbFont *font, int strl );
int inBox ( int XY[], int XYWH[] );
int solitaire_game_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );

// return the card index of the cursor
int cursor_to_index ( int cursor, int c2 );
int board_to_index ( int cb, int c2 );

// return 1 if the card can be merged onto the other.
int stack_merge ( int c, int c2, int i, int i2 );
void remove_hand ( );

int move_check ( int click_index, int cursor_index );
// move check foundation.
int move_check_found ( int click_index, int cursor_index );
int stack_move ( int click_index, int cursor_index, int cb, int c2, int ib, int i2 );

void stack_copy ( int cb, int c2, int ib, int i2 );

/// Other Functions

char *suite_to_string ( int i );
char *num_to_string ( int i );


void card_render_index ( int *screenDims, GLuint *glBuffers, int *XYWHpass, int val[] );

//void card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data );
//oid card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, char *num, char *suite );
void card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, int n, int s );

void card_render_back ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data );


void say_card_index ( int i );




