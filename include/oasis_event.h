#pragma once


/** Includes */

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>


/** Structs */


// Forward Declaring

struct player;
struct card;

struct spell;
struct spellEffect;


/// spell enums

enum target_side {
	tar_aly = 0,
	tar_enemy,
	tar_either,
};

enum target_count {
	target_everyone = 0,
	target_num,
};

enum target_who {
	tar_champ = 0,
	tar_minion,
	tar_both,
	tar_rand,
};

// this is going to be an exhaustive list of every spell type i want.
// and i need to write it in by hand.
// these can be scripted together.
enum effect_type {
	eff_dmg = 0,
	eff_heal,	// increases cur hp
	eff_draw,
	eff_summon,
	eff_buffHp,	// increases max hp and cur hp
	eff_buffMaxHp,	// increases max but leaves cur
	eff_buffAtk,
};


enum cardMod_type {
	cardMod_taunt = 0,
	cardMods_asdf,
};


enum spell_discard_type {
	discard_disc = 0,
	discard_shuf_playDeck,
	discard_shuf_playHand,
	discard_shuf_enemHand,
	discard_shuf_enemDeck,
};



// should i have a union of this stuff.



/** Functions */

/// Event

int oasis_game_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );

int get_clickZone ( int *clickXYpass, int *fullBoard );

// doesnt simply return the index, it also makes sure a minion exists there.
int board_click_index ( struct player *player, int *clickXY, int *boardXYWH );

// for for the player only.
//void play_hand_to_board ( struct player *player, int handI, int clickZone );
void play_hand_to_board ( struct player *player, int handI, int board, int clickZone );





/// Other

void shuffle_into_deck ( struct card *card, ArrayList *deck );

// board: 0 is enemy, 1 is player.
int play_spell ( struct card *card, int board, int clickZone );
// board: 0 is enemy, 1 is player.
void apply_spell_minion ( struct spell *spell, struct card *minion );
void apply_spellEffect_minion ( struct spellEffect *eff, struct card *minion );

// i am removing card at arr[i], so shift everything at an index above that, left by 1.
// make sure the final arr[index] is set to null.
void shrink_array ( struct card *arr[], int i, int max );

void card_attack ( struct player *attacker, struct player *defender, int attackIndex, int defendIndex );







