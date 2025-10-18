#pragma once


/** Includes */

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>
#include <stdlib.h>


/** Structs */


// Forward Declaring

struct player;
struct card;


/** Functions */

/// Event

int oasis_game_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );

// doesnt simply return the index, it also makes sure a minion exists there.
int board_click_index ( struct player *player, int *clickXY, int *boardXYWH );

// for for the player only.
void play_hand_to_board ( struct player *player, int handI );





/// Other

void apply_spell_minion ( struct card *spell, struct card *minion );

// i am removing card at arr[i], so shift everything at an index above that, left by 1.
// make sure the final arr[index] is set to null.
void shrink_array ( struct card *arr[], int i, int max );

void card_attack ( struct player *attacker, struct player *defender, int attackIndex, int defendIndex );







