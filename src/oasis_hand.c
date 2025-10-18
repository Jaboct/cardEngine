#include "oasis_hand.h"


/** Includes */

#include "oasis.h"
#include "card_util.h"
#include "oasis_render.h"
#include "oasis_event.h"


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct jalbFont *fonts[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];
extern float colorOrange[];

/*
float colorTan[4] = { 0.8, 0.6, 0.4, 1.0 };
float colorDYellow[4] = { 0.8, 0.8, 0.0, 1.0 };
float colorDBlue[4] = { 0.0, 0.8, 0.8, 1.0 };	// actually cyan rn
float colorDRed[4] = { 0.8, 0.0, 0.0, 1.0 };
float colorLBlue[4] = { 0.6, 0.6, 1.0, 1.0 };
*/




int debugPrint_oasisRender = 0;

ArrayList *cardBaseList = NULL;	// (struct cardBase*)







int turn = 0;
// 0 is other
// 1 is player
// 2 is enemy


// can be combined w/ oasisInited and turn?
// 0 = pre draw
// 1 = mid picking first 3 cards
// 2 = actual game.
// i want like the hide button and stuff.
int oasis_stage = 0;



/*
0: nothing
1-7, hand
8-17: board
*/
int oasis_cursor = 0;



/// temp struct functs

struct player *playerInit ( ) {
	struct player *var = malloc ( sizeof ( *var ) );

	var->deck = initArrayList ( 10, sizeof ( struct card* ), 10 );
	var->deckTotal = initArrayList ( 10, sizeof ( struct card* ), 10 );

	int i = 0;
	while ( i < HAND_MAX ) {
		var->hand[i] = NULL;
		i += 1;
	}

	i = 0;
	while ( i < BOARD_MAX ) {
		var->board[i] = NULL;
		i += 1;
	}

	var->health = 30;

	var->mana = 0;
	var->manaMax = 0;

	var->fatigue = 0;

	return var;
}

void set_oasis_stage ( int i ) {
	oasis_stage = i;
}

/** Functions */

// MODNAME	NICKNAME	oasis_init	oasis_render	oasis_event	oasis_close	oasis_number
int oasis_id = -1;

void *oasis_init ( ) {
	srand(time(NULL));   // Initialization, should only be called once.

	return NULL;
}

void oasis_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data ) {
	if ( debugPrint_oasisRender ) {
		printf ( "oasis_render ( )\n" );
	}

/*
	draw2dApi->fillRect ( XYWHpass, colorBlack, screenDims, glBuffers );

	draw2dApi->drawCharPre ( fonts[0], colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWHpass, fonts[0], "oasis_render ( )" );
*/

	if ( oasis_stage == 0 ) {
		oasis_game_render ( screenDims, glBuffers, XYWHpass, data );
	} else if ( oasis_stage == 4 ) {
		render_pick3 ( screenDims, glBuffers );
	}
}

int oasis_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	if ( e->type == SDL_QUIT ) {
	} else if ( e->type == SDL_KEYDOWN ) {
//		if ( e->key.keysym.sym == SDLK_1 ) {
//		}
	} else if ( e->type == SDL_KEYUP ) {
	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		int ret = 0;
		if ( oasis_stage == 0 ) {
			ret = oasis_game_event ( e, clickXY, eleWH, data );
		} else if ( oasis_stage == 4 ) {
			ret = event_pick3 ( e, clickXY, eleWH );
		}

		return ret;

//		if ( e->button.button == SDL_BUTTON_LEFT ) {
//			e->button.x, or clickXY[0]
//		} else if ( e->button.button == SDL_BUTTON_RIGHT ) {
//		}
	} else if ( e->type == SDL_MOUSEBUTTONUP ) {
	} else if ( e->type == SDL_MOUSEMOTION ) {
	} else if ( e->type == SDL_MOUSEWHEEL ) {
	}

	return 0;
}

void oasis_close ( char *data ) {
}

void oasis_number ( int id ) {
	oasis_id = id;
}



/// Other Functions

struct player *player;
struct player *enemy;

int oasisInited = 0;

void init_oasis_game ( ) {
	printf ( "init_oasis_game ( )\n" );

	// init player and enemy.
	player = playerInit ( );
	enemy = playerInit ( );

	hand_make_cards ( );


	copyCard_id ( player->deckTotal, 0 );
	copyCard_id ( player->deckTotal, 1 );
	copyCard_id ( player->deckTotal, 2 );
	copyCard_id ( player->deckTotal, 3 );
	copyCard_id ( player->deckTotal, 4 );
	copyCard_id ( player->deckTotal, 5 );
	copyCard_id ( player->deckTotal, 6 );
	copyCard_id ( player->deckTotal, 7 );




	copyCard_id ( enemy->deckTotal, 0 );
	copyCard_id ( enemy->deckTotal, 1 );
	copyCard_id ( enemy->deckTotal, 2 );
	copyCard_id ( enemy->deckTotal, 3 );
	copyCard_id ( enemy->deckTotal, 4 );
	copyCard_id ( enemy->deckTotal, 5 );
	copyCard_id ( enemy->deckTotal, 6 );
	copyCard_id ( enemy->deckTotal, 7 );


	/// TODO, shuffle


	printf ( "init_oasis_game ( ) OVER\n" );
}

enum allMyCards {
	card_defender = 0,
	card_attacker,
	card_lvl2,
	card_taunter,
	card_priest,
	card_warrior,
	card_shieldMaster,
	card_pws,
};

struct pick3 pick3[3];

void hand_make_cards ( ) {
	printf ( "hand_make_cards ( )\n" );

	if ( !cardBaseList ) {
		cardBaseList = initArrayList ( 10, sizeof ( struct cardBase* ), 10 );
	}

	struct cardBase *base = make_card ( 1, 1, 2, "defender" );

/*
	struct cardBase *base = cardBaseInit ( );
	arrayListAddEndPointer ( cardBaseList, base );
	base->id = 0;	// arrayListGetLength ( cardBaseList );
	base->mana = 1;
	base->attack = 1;
	base->health = 2;
	strcpy ( base->name, "defender" );

	base = cardBaseInit ( );
	arrayListAddEndPointer ( cardBaseList, base );
	base->id = 1;
	base->mana = 1;
	base->attack = 2;
	base->health = 1;
	strcpy ( base->name, "attacker" );
*/

	base = make_card ( 1, 2, 1, "atacker" );
	base = make_card ( 2, 3, 2, "lvl 2" );
	base = make_card ( 2, 1, 3, "taunter" );	// taunt

	if ( base ) {
	}

	base = make_card ( 2, 1, 3, "priest" );		// buff firendly hp 2
	base = make_card ( 2, 3, 3, "warrior" );	// rush
	base = make_card ( 2, 3, 5, "Shield Master" );

// TODO this is wrong.
	struct cardMod *mod = malloc ( sizeof ( *mod ) );	// taunt cardMod
	mod->type = 0;
	arrayListAddEndPointer ( base->modifiers, mod );

	// spell, "Power Word Shield"
	base = make_cardBase_spell ( "Power Word Shield" );
	base->mana = 1;

	struct pick3 *p3 = &pick3[0];
	strcpy ( p3->name, "Taunts" );
	p3->cards[0] = card_taunter;
	p3->cards[1] = card_shieldMaster;
	p3->cards[2] = card_taunter;


	p3 = &pick3[1];
	strcpy ( p3->name, "Killers" );
	p3->cards[0] = card_attacker;
	p3->cards[1] = card_lvl2;
	p3->cards[2] = card_warrior;


	p3 = &pick3[1];
	strcpy ( p3->name, "Spells" );
	p3->cards[0] = card_attacker;
	p3->cards[1] = card_lvl2;
	p3->cards[2] = card_warrior;

	printf ( "hand_make_cards ( ) OVER\n" );
}

// this make a minion only
// adds to the base list, but also returns card so you can edit it afterwards.
struct cardBase *make_card ( int mana, int atk, int hp, char *name ) {
	struct cardBase *base = cardBaseInit ( );
	int id = arrayListGetLength ( cardBaseList );
	arrayListAddEndPointer ( cardBaseList, base );
	base->type = 0;
	base->id = id;
	base->mana = mana;
	base->attack = atk;
	base->health = hp;
	strcpy ( base->name, name );

	return base;
}

struct cardBase *make_cardBase_spell ( char *name ) {
	struct cardBase *base = cardBaseInit ( );
	base->type = 1;	// TODO
	int id = arrayListGetLength ( cardBaseList );
	base->id = id;

	arrayListAddEndPointer ( cardBaseList, base );

	strcpy ( base->name, name );

/*
	base->mana = mana;
	base->attack = atk;
	base->health = hp;
*/
	return base;
}


// copy from the caseBaseList[id] to list.
void copyCard_id ( ArrayList *list, int id ) {
	struct card *card = copyCard_base ( id );
	if ( card == NULL ) {
		printf ( "ERROR, copyCard_id ( )\n" );
		return;
	}
	arrayListAddEndPointer ( list, card );
}

struct card *copyCard_base ( int id ) {
	int baseLen = arrayListGetLength ( cardBaseList );
	if ( id >= baseLen ) {
		printf ( "ERROR, copyCard_base ( )\n" );
		return NULL;
	}

	struct cardBase *base = arrayListGetPointer ( cardBaseList, id );

	struct card *card = cardInit ( );
	card->type = base->type;
	card->id = id;

	card->mana = base->mana;

	if ( base->type == 0 ) {
		// minion
	card->attack = base->attack;
	card->health = base->health;
	card->numAttacks = -2;

	int i = 0;
	int len = arrayListGetLength ( base->modifiers );
	while ( i < len ) {
		struct cardMod *copy = arrayListGetPointer ( base->modifiers, i );
		struct cardMod *newMod = cardMod_copy ( copy );
		arrayListAddEndPointer ( card->mods, newMod );

		i += 1;
	}
	} else if ( base->type == 1 ) {
//		copySpell ( );
	}

	return card;
}

// this should be autogenerated
struct card *copyCard ( struct card *card ) {

	struct card *var = cardInit ( );
	var->type = card->type;
	var->id = card->id;
	var->mana = card->mana;
	var->attack = card->attack;
	var->health = card->health;
	var->numAttacks = -2;

	int i = 0;
	int len = arrayListGetLength ( card->mods );
	while ( i < len ) {
		struct cardMod *copy = arrayListGetPointer ( card->mods, i );
		struct cardMod *newMod = cardMod_copy ( copy );
		arrayListAddEndPointer ( var->mods, newMod );

		i += 1;
	}

	return var;
}


struct cardMod *cardMod_copy ( struct cardMod *copy ) {
	struct cardMod *var = malloc ( sizeof ( *var ) );
	var->type = copy->type;

	return var;
}











void turn_change ( ) {
	printf ( "turn_change ( )\n" );


	// initial turn.
	if ( turn == 0 ) {
		// shuffle both, draw both.
		shuffle_to ( player->deck, player->deckTotal );
		shuffle_to ( enemy->deck, enemy->deckTotal );

		draw_player ( player );
		draw_player ( player );
		draw_player ( player );

		draw_player ( enemy );
		draw_player ( enemy );
		draw_player ( enemy );
	}


	turn += 1;
	if ( turn > 2 ) {
		turn = 1;
	}
	if ( turn == 1 ) {
		// player

		startTurn_player ( player );
	} else {
		// enemy
		int drew = draw_player ( enemy );
		if ( drew == 1 ) {
			// failed to draw 1 card.
			enemy->fatigue += 1;
			player_damage ( enemy, enemy->fatigue );
		}

		mana_increment ( enemy );

		enemy_ai ( enemy );
	}

	printf ( "turn_change ( ) OVER\n" );
}

void startTurn_player ( struct player *player ) {
	int drew = draw_player ( player );

	if ( drew == 1 ) {
		// failed to draw 1 card.
		player->fatigue += 1;
		player_damage ( player, player->fatigue );
	}

	mana_increment ( player );

	// iterate through boards, reset numAttacks
	int boardLen = get_board_len ( player );
	int i = 0;
	while ( i < boardLen ) {
		player->board[i]->numAttacks = 1;
		i += 1;
	}
}

void shuffle_to ( ArrayList *deck, ArrayList *deckTotal ) {
//	printf ( "shuffle_to ( )\n" );

	// free deck
	freeArrayListFunctionSave ( deck, (void(*)(void *))cardClose );

//	printf ( "deck.len: %d\n", arrayListGetLength ( deck ) );

	int len = arrayListGetLength ( deckTotal );

//	printf ( "deckTotal.len: %d\n", len );
//	printf ( "deck.len: %d\n", arrayListGetLength ( deck ) );

	// fill deck
	int i = 0;
	while ( i < len ) {
		// i need the copy funct.

		struct card *cardTotal = arrayListGetPointer ( deckTotal, i );
		struct card *card = copyCard ( cardTotal );

//		printf ( "card coppied: %p\n", card );
		arrayListAddEndPointer ( deck, card );

		i += 1;
	}

//	printf ( "deck.len: %d\n", arrayListGetLength ( deck ) );
//	sayPtrArrayList ( "deck pre", deck );

	// shuffle deck
	i = len - 1;
	while ( i > 0 ) {
//		printf ( "iter: %d\n", i );

		int r = rand ( ) % i;
//		printf ( "r: %d\n", r );

		// swap r and i.
		// i need to write an arraylist swap function.

//		printf ( "swap ( %d, %d )\n", i, r );
		arrayListSwap ( deck, i, r );

		i -= 1;
	}

//	sayPtrArrayList ( "deck post", deck );

//	printf ( "deck.len: %d\n", arrayListGetLength ( deck ) );
//	printf ( "shuffle_to ( ) OVER\n" );
}


void player_damage ( struct player *player, int dmg ) {
	// return 1 if they die?
	player->health -= dmg;
	if ( player->health <= 0 ) {
		printf ( "game over\n" );
		// TODO
	}
}


void enemy_ai ( struct player *player ) {
	printf ( "enemy_ai ( )\n" );

	// ok, so this is going to be very complicated.
	// start simple, look for any cards which take all the mana.

	int i = 0;
	int handLen = get_hand_len ( player );
	int boardLen = get_board_len ( player );

	int minionsPlayed = 0;

	// first look for cards to play
	if ( boardLen < BOARD_MAX ) {
		// the board isnt full, so try to play a minion.

		int manaSearch = player->mana;

		printf ( "manaSearch: %d\n", manaSearch );

		int searching = 1;
		int cardFound = 0;
		while ( searching ) {
			searching = 0;

			i = 0;
			while ( i < handLen ) {
printf ( "i: %d\n", i );
				struct card *card = player->hand[i];
				if ( card->mana == manaSearch && 
				     card->type == 0 ) {	// only play minions.
					// play this card.
					cardFound = 1;

					// play the card
play_hand_to_board ( player, i );
manaSearch = player->mana;
					minionsPlayed += 1;
					handLen -= 1;

					if ( cardFound && player->mana > 0 ) {
						// continue the outer search.

			searching = 1;

						break;
					}
				}

				i += 1;
			}
			// there is still mana left, but no card that costs the current ammount of mana.
			// so look for a card which costs 1 less mana.
			if ( !searching && manaSearch > 0 ) {
				manaSearch -= 1;
				searching = 1;
printf ( "decrement manaSearch: %d\n", manaSearch );
			}
		}
	}

	printf ( "minionsPlayed: %d\n", minionsPlayed );
	printf ( "mana remaining: %d\n", player->mana );

	printf ( "enemy_ai ( ) OVER\n" );
}

// draws 1 card
// returns the number of cards that i fail to draW
int draw_player ( struct player *player ) {
	// draws a carf from player deck to player hand.

	int deckLen = arrayListGetLength ( player->deck );
	if ( deckLen == 0 ) {
		printf ( "DECK EMPTY, take dmg\n" );

		return 1;
	}
	// deck not empty, continue;

	struct card *card = arrayListGetPointer ( player->deck, deckLen - 1 );
	arrayListRemove ( player->deck, deckLen - 1 );

	int handLen = get_hand_len ( player );
	if ( handLen == HAND_MAX ) {
		// dont add to hand.
		printf ( "delete drawn card\n" );
	} else {
		player->hand[handLen] = card;
	}
	return 0;
}


void mana_increment ( struct player *player ) {

		// refill mana and increment max
		player->manaMax += 1;
		if ( player->manaMax > MANA_MAX ) {
			player->manaMax = MANA_MAX;
		}
		player->mana = player->manaMax;
}


// game

int get_hand_len ( struct player *player ) {
	int i = 0;
	while ( i < HAND_MAX ) {
		if ( player->hand[i] == NULL ) {
			return i;
		}
		i += 1;
	}
	return i;
}

int get_board_len ( struct player *player ) {
	int i = 0;
	while ( i < BOARD_MAX ) {
		if ( player->board[i] == NULL ) {
			return i;
		}
		i += 1;
	}
	return i;
}


char modStr[256];

enum mod_types {
	mod_taunt = 0,
};

char *mod_to_str ( struct cardMod *mod ) {
	if ( mod->type == mod_taunt ) {
		strcpy ( modStr, "Taunt" );
	} else if ( mod->type == 1 ) {
		strcpy ( modStr, "PWS" );
	} else {

		strcpy ( modStr, "TODO" );
	}

	return modStr;
}




void oasis_dead_check ( ) {
	// every time a character takes damage run this.

	if ( player->health <= 0 ) {
		// i lose
	}
	if ( enemy->health <= 0 ) {
		// i win
	}
}















