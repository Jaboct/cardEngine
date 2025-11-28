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


char *saveDir = "/home/jadeb/workspace/jHigh/cardEngine/res/saves/game_00.xml";


int debugPrint_oasisRender = 0;
int debugPrint_oasis_copy = 0;

ArrayList *cardBaseList = NULL;	// (struct cardBase*)





struct oasis_game *glob_oasis = NULL;

// glob_oasis->oasis_turn
//int turn = 0;
// 0 is other
// 1 is player
// 2 is enemy


// can be combined w/ oasisInited and turn?
// 0 = pre draw
// 1 = mid picking first 3 cards
// 2 = actual game.
// i want like the hide button and stuff.
//int oasis_stage = 0;



/*
0: nothing
1-7, hand
8-17: board
*/
int oasis_cursor = 0;



//struct player *player;
//struct player *enemy;

int oasisInited = 0;


enum allMyCards {
	card_defender = 0,
	card_attacker,
	card_lvl2,
	card_taunter,
	card_priest,
	card_warrior,
	card_shieldMaster,
	card_pws,
	card_hat,
	card_torch,
	card_journal,
};

struct pick3 pick3[3];





/// temp struct functs
/*
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
*/

void set_oasis_stage ( int i ) {
	printf ( "set_oasis_stage ( )\n" );
	printf ( "i: %d\n", i );

	printf ( "glob_oasis: %p\n", glob_oasis );
	if ( glob_oasis ) {
		glob_oasis->oasis_stage = i;
	}

	printf ( "set_oasis_stage ( ) OVER\n" );
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


	if ( !oasisInited ) {
		oasis_assemble_dom ( XYWHpass );

		glob_oasis = oasis_gameInit ( );
		init_oasis_game ( glob_oasis );

		oasisInited = 1;
	}


	struct oasis_game *game = glob_oasis;

	if ( game->oasis_stage == 0 ) {
		render_pick3 ( screenDims, glBuffers );
	} else if ( game->oasis_stage == 1 ) {
		oasis_game_render ( screenDims, glBuffers, XYWHpass, data );
	}
}

int oasis_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {

	struct oasis_game *game = glob_oasis;

	int ret = 0;

	if ( e->type == SDL_QUIT ) {
	} else if ( e->type == SDL_KEYDOWN ) {
		if ( game->oasis_stage == 0 ) {
			ret = event_pick3 ( e, clickXY, eleWH );
			return ret;
		}

	} else if ( e->type == SDL_KEYUP ) {
	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		if ( game->oasis_stage == 0 ) {
			ret = event_pick3 ( e, clickXY, eleWH );
		} else if ( game->oasis_stage == 1 ) {
			ret = oasis_game_event ( e, clickXY, eleWH, data );
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

void init_oasis_game ( struct oasis_game *game ) {
	printf ( "init_oasis_game ( )\n" );


	// init player and enemy.
	game->player = playerInit ( );
	game->enemy = playerInit ( );
	struct player *player = game->player;
	struct player *enemy = game->enemy;

	player->health = 15;
	enemy->health = 10;

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

	// taunt cardMod
	struct cardMod *mod = cardModInit ( );
	strcpy ( mod->name, "Taunt" );
	mod->type = cardMod_taunt;
	arrayListAddEndPointer ( base->card->minion->mods, mod );

printf ( "APPLY TAUNT\n" );
	printf ( "mod: %p\n", mod );
	printf ( "mod->name: %p\n", mod->name );
	printf ( "base->card->minion->mods: %p\n", base->card->minion->mods );


	// spell, "Power Word Shield"
	base = make_cardBase_spell ( "PW: Shield" );
	base->card->mana = 1;
	struct spell *spell = base->card->spell;
	struct targeting *tar = spell->tar;
	struct spellEffect *eff = spellEffectInit ( );;
	arrayListAddEndPointer ( spell->effList, eff );
	strcpy ( spell->modName, "PW: Shield" );

	tar->side = tarS_ally;
	tar->who = tar_minion;
	tar->count = target_num + 0;	// casts on 1+0 guy(s)

	eff->type = eff_buffHp;
	eff->heal = 2;


	printf ( "tar: %p\n", tar );
	printf ( "tar->count: %d\n", tar->count );



	base = make_cardBase_spell ( "Hat" );
	base->card->mana = 1;

	spell = base->card->spell;
	strcpy ( spell->modName, "Hat: +2/+2" );
	spell->discard = discard_shuf_playDeck;

	tar = spell->tar;
	tar->side = tarS_ally;
	tar->who = tar_minion;
	tar->count = target_num + 0;	// casts on 1+0 guy(s)

	eff = spellEffectInit ( );
	arrayListAddEndPointer ( spell->effList, eff );
	eff->type = eff_buffHp;
	eff->heal = 2;

	eff = spellEffectInit ( );
	arrayListAddEndPointer ( spell->effList, eff );
	eff->type = eff_buffAtk;
	eff->heal = 2;


	/// Torch
	base = make_cardBase_spell ( "Torch" );
	base->card->mana = 1;

	spell = base->card->spell;
	// leave it as empty so that nothing gets added.
//	strcpy ( spell->modName, "Hat: +2/+2" );
	spell->discard = discard_shuf_playDeck;

	tar = spell->tar;
	tar->side = tarS_enemy;
	tar->who = tar_both;
	tar->count = target_num + 0;	// casts on 1+0 guy(s)

	eff = spellEffectInit ( );
	arrayListAddEndPointer ( spell->effList, eff );
	eff->type = eff_dmg;
	eff->dmg = 2;


	/// Journal
	base = make_cardBase_spell ( "Journal" );
	base->card->mana = 1;



	/// Fireball (champ ability)
	/// TODO, this is a fake card, which should really be a champion ability.
	// 2 dmg to anyone, 2 mana cost.
	base = make_cardBase_spell ( "Fireball" );
	base->card->mana = 2;

	spell = base->card->spell;
	// leave it as empty so that nothing gets added.
//	strcpy ( spell->modName, "Hat: +2/+2" );
	spell->discard = discard_shuf_playDeck;

	tar = spell->tar;
	tar->side = tarS_enemy;
	tar->who = tar_both;
	tar->count = target_num + 0;	// casts on 1+0 guy(s)

	eff = spellEffectInit ( );
	arrayListAddEndPointer ( spell->effList, eff );
	eff->type = eff_dmg;
	eff->dmg = 2;




	hand_pick3_char ( );

	printf ( "hand_make_cards ( ) OVER\n" );
}

void hand_pick3_char ( ) {
	struct pick3 *p3 = &pick3[0];
	strcpy ( p3->name, "Character 00" );
	p3->cards[0] = -1;
	p3->cards[1] = -1;
	p3->cards[2] = -1;


	p3 = &pick3[1];
	strcpy ( p3->name, "Character 01" );
	p3->cards[0] = -1;
	p3->cards[1] = -1;
	p3->cards[2] = -1;


	p3 = &pick3[2];
	strcpy ( p3->name, "Character 02" );
	p3->cards[0] = -1;
	p3->cards[1] = -1;
	p3->cards[2] = -1;
}

void hand_pick3_cards ( ) {
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


	p3 = &pick3[2];
	strcpy ( p3->name, "Spells" );
	p3->cards[0] = card_attacker;
	p3->cards[1] = card_lvl2;
	p3->cards[2] = card_warrior;
}

void hand_pick3_special ( ) {
	struct pick3 *p3 = &pick3[0];
	strcpy ( p3->name, "Taunts" );
	p3->cards[0] = card_hat;
	p3->cards[1] = -1;
	p3->cards[2] = -1;


	p3 = &pick3[1];
	strcpy ( p3->name, "Killers" );
	p3->cards[0] = card_torch;
	p3->cards[1] = -1;
	p3->cards[2] = -1;


	p3 = &pick3[2];
	strcpy ( p3->name, "Spells" );
	p3->cards[0] = card_journal;
	p3->cards[1] = -1;
	p3->cards[2] = -1;
}

// this make a minion only
// adds to the base list, but also returns card so you can edit it afterwards.
struct cardBase *make_card ( int mana, int atk, int hp, char *name ) {
	printf ( "make_card ( )\n" );

	struct cardBase *base = cardBaseInit ( );
	int id = arrayListGetLength ( cardBaseList );

	arrayListAddEndPointer ( cardBaseList, base );
	base->card->id = id;
	base->card->mana = mana;

	cardTypeChange0 ( base->card, Minion );
	struct minionBase *minion = base->card->minion;
	minion->attack = atk;
	minion->health = hp;

	strcpy ( base->name, name );

	printf ( "make_card ( ) OVER\n" );

	return base;
}

// creates a card of type spell, with this name, and adds it to cardBaseList.
struct cardBase *make_cardBase_spell ( char *name ) {
	struct cardBase *base = cardBaseInit ( );
	cardTypeChange0 ( base->card, Spell );

	int id = arrayListGetLength ( cardBaseList );
	base->card->id = id;

	arrayListAddEndPointer ( cardBaseList, base );

	strcpy ( base->name, name );

	return base;
}


// copy from the caseBaseList[id] to list.
void copyCard_id ( ArrayList *list, int id ) {
	if ( debugPrint_oasis_copy ) {
		printf ( "copyCard_id ( )\n" );
	}


	struct card *card = copyCard_base ( id );
	if ( card == NULL ) {
		printf ( "ERROR, copyCard_id ( )\n" );
		return;
	}
	arrayListAddEndPointer ( list, card );


	if ( debugPrint_oasis_copy ) {
		printf ( "copyCard_id ( ) OVER\n" );
	}
}

struct card *copyCard_base ( int id ) {
	int baseLen = arrayListGetLength ( cardBaseList );
	if ( id >= baseLen ) {
		printf ( "ERROR, copyCard_base ( )\n" );
		return NULL;
	}

	struct cardBase *base = arrayListGetPointer ( cardBaseList, id );

	struct card *card = cardInit ( );
	card_copy ( card, base->card );

	return card;
}

// sets cardA to cardB
void card_copy ( struct card *cardA, struct card *cardB ) {
	if ( debugPrint_oasis_copy ) {
		printf ( "card_copy ( )\n" );
	}

//	cardA->type = cardB->type;
	cardA->id = cardB->id;
	cardA->mana = cardB->mana;
	cardTypeChange0 ( cardA, cardB->type );
	if ( cardB->type == Minion ) {
		copy_minionBase ( cardA->minion, cardB->minion );
	} else if ( cardB->type == Spell ) {
//		copy_spell ( cardA->spell, cardB->spell );
	}

	if ( debugPrint_oasis_copy ) {
		printf ( "card_copy ( ) OVER\n" );
	}
}

void copy_minionBase ( struct minionBase *baseA, struct minionBase *baseB ) {
	if ( debugPrint_oasis_copy ) {
		printf ( "copy_minionBase ( )\n" );
	}

	baseA->attack = baseB->attack;
	baseA->health = baseB->health;
	baseA->numAttacks = baseB->numAttacks;

	int i = 0;
	int len = arrayListGetLength ( baseB->mods );
	while ( i < len ) {
		struct cardMod *copy = arrayListGetPointer ( baseB->mods, i );
		struct cardMod *newMod = cardMod_copy ( copy );
		arrayListAddEndPointer ( baseA->mods, newMod );

		i += 1;
	}
}

// this should be autogenerated
struct card *copyCard ( struct card *card ) {

	struct card *var = cardInit ( );
	card_copy ( var, card );
/*
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
*/
	return var;
}



struct cardMod *cardMod_copy ( struct cardMod *copy ) {
	struct cardMod *var = cardModInit ( );
	var->type = copy->type;
	strcpy ( var->name, copy->name );

	return var;
}









void turn_change_glob ( ) {
	turn_change ( glob_oasis );
}

void turn_change ( struct oasis_game *game ) {
	printf ( "turn_change ( )\n" );

	struct player *player = game->player;
	struct player *enemy = game->enemy;

	// initial turn.
	if ( game->oasis_turn == 0 ) {
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


	game->oasis_turn += 1;
	if ( game->oasis_turn > 2 ) {
		game->oasis_turn = 1;
	}
	if ( game->oasis_turn == 1 ) {
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

void turn_change_lobby_glob ( ) {
	turn_change_lobby ( glob_oasis );
}

void turn_change_lobby ( struct oasis_game *game ) {
	game->lobby_stage += 1;
	if ( game->oasis_round == 0 ) {
		// pre game
		if ( game->lobby_stage == 5 ) {
			game->oasis_stage = 1;
		}
	}
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
		struct card *card = player->board[i];
		// its on board, so you dont need to cehck its type
		card->minion->numAttacks = 1;
		i += 1;
	}
}



void shuffle_to ( ArrayList *deck, ArrayList *deckTotal ) {
	printf ( "shuffle_to ( )\n" );

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

		if ( card->type == Minion ) {
			card->minion->numAttacks = -2;
		}

		printf ( "card coppied: %p\n", card );
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

		void *iPtr = arrayListGetPointer ( deck, i );
		void *rPtr = arrayListGetPointer ( deck, r );

//		printf ( "swap ( %d, %d )\n", i, r );
		arrayListSwap ( deck, i, r );

		if ( iPtr != arrayListGetPointer ( deck, r ) ) {
			printf ( "swap error a\n" );
			exit ( 12 );
		}
		if ( rPtr != arrayListGetPointer ( deck, i ) ) {
			printf ( "swap error b\n" );
			exit ( 12 );
		}

		i -= 1;
	}

	say_myPlayer ( );

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
int clickZone = 0;
play_hand_to_board ( player, i, 0, clickZone );	// 0 for player, cuz this is from the enmies perspective?
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
		printf ( "drawn card: %p\n", card );
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

	strcpy ( modStr, mod->name );

	return modStr;
}




void oasis_dead_check ( struct oasis_game *game ) {
	// every time a character takes damage run this.

	struct player *player = game->player;
	struct player *enemy = game->enemy;

	if ( player->health <= 0 ) {
		// i lose
	}
	if ( enemy->health <= 0 ) {
		// i win
	}
}



/// Save and Load

extern struct backbone_structStruct backboneStru_oasis_game;
extern int oasis_game_attributes[];

extern int len_backbone_arr_cardEngine;
extern struct backbone_structStruct *backbone_arr_cardEngine[];




extern int num_structStruct_cardEngine;
extern struct xmlFuncts *xmlFuncts_arr_cardEngine[];




void hand_oasis_load ( char *dir ) {
	printf ( "hand_oasis_load ( )\n" );

	char buffer[256];
	sprintf ( buffer, "/home/jadeb/workspace/jHigh/cardEngine/res/saves/save_00.xml" );
	struct oasis_game *game = loadXmlFile_03 ( buffer, xmlFuncts_arr_cardEngine, num_structStruct_cardEngine );
	glob_oasis = game;

	printf ( "game: %p\n", game );
	printf ( "game->player: %p\n", game->player );

	printf ( "hand_oasis_load ( ) OVER\n" );
}

void hand_oasis_save ( char *dir ) {
	printf ( "hand_oasis_save ( )\n" );


	char buffer[256];

	struct oasis_game *game = glob_oasis;

	sprintf ( buffer, "/home/jadeb/workspace/jHigh/cardEngine/res/saves/save_00.xml" );
	fwriteXml_backbone ( buffer, &backboneStru_oasis_game, game,
		oasis_game_attributes, backbone_arr_cardEngine, len_backbone_arr_cardEngine );


	printf ( "hand_oasis_save ( ) OVER\n" );
}

/// Proof



/// say

void say_myPlayer ( ) {
	struct oasis_game *game = glob_oasis;
	say_player ( game->player );
}

void say_player ( struct player *player ) {
	printf ( "say_player ( )\n" );
	printf ( "player: %p\n", player );

	int i = 0;
	int len = arrayListGetLength ( player->deckTotal );
	printf ( "player->deckTotal.len: %d\n", len );
	while ( i < len ) {
		struct card *card = arrayListGetPointer ( player->deckTotal, i );

		printf ( "card: %p\n", card );

		i += 1;
	}

	i = 0;
	len = arrayListGetLength ( player->deck );
	printf ( "player->deck.len: %d\n", len );
	while ( i < len ) {
		struct card *card = arrayListGetPointer ( player->deck, i );

		printf ( "card: %p\n", card );

		i += 1;
	}
}




struct cardBase *get_base_id ( int id ) {
	struct cardBase *base = arrayListGetPointer ( cardBaseList, id );
	return base;
}












