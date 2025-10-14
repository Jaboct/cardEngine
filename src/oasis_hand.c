#include "oasis_hand.h"


/** Includes */

#include "oasis.h"
#include "card_util.h"


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


float colorTan[4] = { 0.8, 0.6, 0.4, 1.0 };
float colorDYellow[4] = { 0.8, 0.8, 0.0, 1.0 };
float colorDBlue[4] = { 0.0, 0.8, 0.8, 1.0 };	// actually cyan rn
float colorDRed[4] = { 0.8, 0.0, 0.0, 1.0 };




#define HAND_MAX 10
#define BOARD_MAX 7
#define MANA_MAX 10


int debugPrint_oasisRender = 0;

ArrayList *cardBaseList = NULL;	// (struct cardBase*)


int oasis_cursor_hand = 1;
int oasis_cursor_board = 1 + HAND_MAX;
int oasis_cursor_board_end = 1 + HAND_MAX + BOARD_MAX - 1;

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

	return var;
}



/** Functions */

// MODNAME	NICKNAME	oasis_init	oasis_render	oasis_event	oasis_close	oasis_number
int oasis_id = -1;

void *oasis_init ( ) {
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

	oasis_game_render ( screenDims, glBuffers, XYWHpass, data );
}

int oasis_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	if ( e->type == SDL_QUIT ) {
	} else if ( e->type == SDL_KEYDOWN ) {
//		if ( e->key.keysym.sym == SDLK_1 ) {
//		}
	} else if ( e->type == SDL_KEYUP ) {
	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		int ret = oasis_game_event ( e, clickXY, eleWH, data );
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


	copyCard_id ( player->deck, 0 );
	copyCard_id ( player->deck, 1 );
	copyCard_id ( player->deck, 2 );
	copyCard_id ( player->deck, 3 );
	copyCard_id ( player->deck, 4 );
	copyCard_id ( player->deck, 5 );
	copyCard_id ( player->deck, 6 );
//	copyCard_id ( player->deck, 7 );




	copyCard_id ( enemy->deck, 0 );
	copyCard_id ( enemy->deck, 1 );
	copyCard_id ( enemy->deck, 2 );
	copyCard_id ( enemy->deck, 3 );
	copyCard_id ( enemy->deck, 4 );
	copyCard_id ( enemy->deck, 5 );
	copyCard_id ( enemy->deck, 6 );
//	copyCard_id ( enemy->deck, 7 );


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

	// spell, "Power World Shield"
//	base = make_card ( 2, 3, 5, "Shield Master" );

	printf ( "hand_make_cards ( ) OVER\n" );
}

// adds to the base list, but also returns card so you can edit it afterwards.
struct cardBase *make_card ( int mana, int atk, int hp, char *name ) {
	struct cardBase *base = cardBaseInit ( );
	int id = arrayListGetLength ( cardBaseList );
	arrayListAddEndPointer ( cardBaseList, base );
	base->id = id;
	base->mana = mana;
	base->attack = atk;
	base->health = hp;
	strcpy ( base->name, name );

	return base;
}

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
	card->id = id;
	card->mana = base->mana;
	card->attack = base->attack;
	card->health = base->health;

	return card;
}


/// Render

/*
DOM - data object model
assume screenDims { 1200, 800 }


*/

int cardW = 100;
int cardH = 160;

int cardGap = 20;	// 20 px between each card.
int highlightMargin = 4;

// relevent elements.
int playerHandXY[2];
int playerBoardXY[2];
int enemyBoardXY[2];

void oasis_assemble_dom ( int *XYWHpass ) {
//	int midX = XYWHpass[2] / 2;
	int midY = XYWHpass[3] / 2;

	playerBoardXY[0] = 100;
	playerBoardXY[1] = midY + cardGap / 2;

	playerHandXY[0] = 100;
	playerHandXY[1] = XYWHpass[3] - cardH - (cardGap * 2);

// i dont like this.
	enemyBoardXY[0] = 100;
	enemyBoardXY[1] = (cardGap * 2) + cardH + cardGap;
}

void oasis_game_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data ) {
	if ( debugPrint_oasisRender ) {
		printf ( "oasis_game_render ( )\n" );
	}

	if ( !oasisInited ) {
		oasis_assemble_dom ( XYWHpass );
		init_oasis_game ( );

		oasisInited = 1;
	}

	draw2dApi->fillRect ( XYWHpass, colorTan, screenDims, glBuffers );

//	sayIntArray ( "XYWHpass", XYWHpass, 4 );

	struct jalbFont *font = fonts[0];
	int glyphW = font->atlasInfo.glyphW;
	int glyphH = font->atlasInfo.glyphH;

//	printf ( "glyphWH { %d, %d }\n", glyphW, glyphH );

	int cardGap = 20;	// 20 px between each card.

	int midX = XYWHpass[2] / 2;
	int midY = XYWHpass[3] / 2;

	/// render board
/*
	int boardXYWH[4] = {
		100,
		midY - cardGap/2 - cardH,
		cardW,
		cardH,
	};
*/


	/// render enemy hp
	char buffer[256];
	sprintf ( buffer, "%d", enemy->health );
	int slen = strlen ( buffer );
	int rect[4];
	rect[0] = centerX ( midX, 0, glyphW, slen );
	rect[1] = cardGap;
	rect[2] = XYWHpass[2];
	rect[3] = XYWHpass[3];

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );

	// enemy mana
	rect[0] += 40;
	sprintf ( buffer, "%d / %d", enemy->mana, enemy->manaMax );
	slen = strlen ( buffer );
	draw2dApi->drawCharPre ( font, colorDBlue );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );


	// my hp
	rect[0] = centerX ( midX, 0, glyphW, slen );
	sprintf ( buffer, "%d", player->health );
	slen = strlen ( buffer );
	rect[1] = XYWHpass[3] - cardGap - font->atlasInfo.glyphH;

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );

	rect[0] += 40;

	// player mana
	sprintf ( buffer, "%d / %d", player->mana, player->manaMax );
	slen = strlen ( buffer );
//	rect[1] = XYWHpass[3] - cardGap - font->atlasInfo.glyphH;

	draw2dApi->drawCharPre ( font, colorDBlue );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );



	int card[4];

	// render deck
	// enemy
	card[0] = XYWHpass[0] + XYWHpass[2] - cardGap - cardW;
	card[1] = midY - cardGap - cardH;
	card[2] = cardW;
	card[3] = cardH;

	if ( debugPrint_oasisRender ) {
		sayIntArray ( "card", card, 4 );
	}

	draw2dApi->fillRect ( card, colorOrange, screenDims, glBuffers );
	draw2dApi->drawRect ( card, colorBlack, screenDims, glBuffers );

	int enemyDeckLen = arrayListGetLength ( enemy->deck );
	sprintf ( buffer, "%d", enemyDeckLen );
	slen = strlen ( buffer );
	rect[0] = centerX ( card[0], card[2], glyphW, slen );
	rect[1] = centerX ( card[1], card[3], glyphH, 1 );

	if ( debugPrint_oasisRender ) {
		sayIntArray ( "rect", rect, 2 );
	}

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );


	// render my deck
	card[1] += cardH + cardGap;

	draw2dApi->fillRect ( card, colorOrange, screenDims, glBuffers );
	draw2dApi->drawRect ( card, colorBlack, screenDims, glBuffers );

	int myDeckLen = arrayListGetLength ( player->deck );
	sprintf ( buffer, "%d", myDeckLen );
	slen = strlen ( buffer );
	rect[0] = centerX ( card[0], card[2], glyphW, slen );
	rect[1] = centerX ( card[1], card[3], glyphH, 1 );

	if ( debugPrint_oasisRender ) {
		sayIntArray ( "rect", rect, 2 );
	}

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );

/*
	/// render my hand
	int handLen = get_hand_len ( player );


//	printf ( "handLen: %d\n", handLen );

	card[0] = 100;
	card[1] = XYWHpass[3] - cardH - (cardGap * 2);
	int i = 0;
	while ( i < handLen ) {
		struct card *handCard = player->hand[i];

		if ( oasis_cursor - oasis_cursor_hand == i ) {
			card_render_highlight ( screenDims, glBuffers, card );
		}

		oasis_card_render ( screenDims, glBuffers, card, handCard );

		card[0] += cardW + cardGap;

		i += 1;
	}
*/

/*
	// render my board
	// i want half a cardGap on top and bottom
	int boardXYWH[4] = {
		playerBoardXY[0],
		playerBoardXY[1],
		(cardW + cardGap) * BOARD_MAX,
		cardH + cardGap,
	};

	draw2dApi->drawRect ( boardXYWH, colorWhite, screenDims, glBuffers );

	boardXYWH[0] += cardGap / 2;
	boardXYWH[1] += cardGap / 2;
	boardXYWH[2] = cardW;
	boardXYWH[3] = cardH;

	int boardLen = get_board_len ( player );
	i = 0;
	while ( i < boardLen ) {
		struct card *boardCard = player->board[i];

		oasis_card_render ( screenDims, glBuffers, boardXYWH, boardCard );

		boardXYWH[0] += cardW + cardGap;

		i += 1;
	}
*/
	// player
//	card[0] = XYWHpass[0] + XYWHpass[2] - cardGap - cardW;
//	card[1] = midY - cardGap - cardH;

	int XY[2] = {
		100,
		XYWHpass[3] - cardH - (cardGap * 2),
	};

	render_hand ( screenDims, glBuffers, player, XY, oasis_cursor );
	render_board ( screenDims, glBuffers, player, playerBoardXY, oasis_cursor );

	// enemy

	XY[1] = (cardGap * 2);
	render_hand ( screenDims, glBuffers, enemy, XY, -1 );

	XY[1] += cardH + cardGap;
	render_board ( screenDims, glBuffers, enemy, XY, -1 );

	if ( debugPrint_oasisRender ) {
		printf ( "oasis_game_render ( ) OVER\n" );
	}
}

void render_board ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY, int cursor ) {
//	printf ( "render_board ( )\n" );

	int i;

	// render my board
	// i want half a cardGap on top and bottom
	int boardXYWH[4] = {
		XY[0],
		XY[1],
		(cardW + cardGap) * BOARD_MAX,
		cardH + cardGap,
	};

	draw2dApi->drawRect ( boardXYWH, colorWhite, screenDims, glBuffers );

	boardXYWH[0] += cardGap / 2;
	boardXYWH[1] += cardGap / 2;
	boardXYWH[2] = cardW;
	boardXYWH[3] = cardH;

	int boardLen = get_board_len ( player );
//	printf ( "boardLen: %d\n", boardLen );
	i = 0;
	while ( i < boardLen ) {
		struct card *boardCard = player->board[i];

		if ( cursor - oasis_cursor_board == i ) {
			card_render_highlight ( screenDims, glBuffers, boardXYWH );
		}
		oasis_card_render ( screenDims, glBuffers, boardXYWH, boardCard );

		boardXYWH[0] += cardW + cardGap;

		i += 1;
	}
}

void render_hand ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY, int cursor ) {

	/// render my hand
	int handLen = get_hand_len ( player );


//	printf ( "handLen: %d\n", handLen );

	int cardXYWH[4] = {
		XY[0],
//		WH[1] - cardH - (cardGap * 2),
		XY[1],
		cardW,
		cardH,
	};
//	card[0] = 100;
//	card[1] = XYWHpass[3] - cardH - (cardGap * 2);
	int i = 0;
	while ( i < handLen ) {
		struct card *handCard = player->hand[i];

		if ( cursor - oasis_cursor_hand == i ) {
			card_render_highlight ( screenDims, glBuffers, cardXYWH );
		}

		oasis_card_render ( screenDims, glBuffers, cardXYWH, handCard );

		cardXYWH[0] += cardW + cardGap;

		i += 1;
	}
}



// pass color? 1 color for selected, another for highlight?

void card_render_highlight ( int *screenDims, GLuint *glBuffers, int *XYWHpass ) {
	int highlightXYWH[4] = {
		XYWHpass[0] - highlightMargin,
		XYWHpass[1] - highlightMargin,
		XYWHpass[2] + 2 * highlightMargin,
		XYWHpass[3] + 2 * highlightMargin,
	};
	draw2dApi->fillRect ( highlightXYWH, colorGold, screenDims, glBuffers );
}

void oasis_card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct card *card ) {
//	printf ( "oasis_card_render ( )\n" );
//	sayIntArray ( "XYWHpass", XYWHpass, 4 );

	int XYWH[4] = {
		XYWHpass[0],
		XYWHpass[1],
		XYWHpass[2],
		XYWHpass[3],
	};

	struct cardBase *base = arrayListGetPointer ( cardBaseList, card->id );

	struct jalbFont *font = fonts[0];
	char buffer[256];

	draw2dApi->fillRect ( XYWH, colorGray, screenDims, glBuffers );
	draw2dApi->drawRect ( XYWH, colorBlack, screenDims, glBuffers );

	// draw mana
//	XYWH[0] += 2;
//	XYWH[1] += 2;

	XYWH[0] += font->atlasInfo.glyphW / 2;
	XYWH[1] += font->atlasInfo.glyphH / 2;

	float w = 20;

	// put a blue circle behind this...
	draw2dApi->fillCircle ( XYWH, w, colorDBlue, screenDims, glBuffers );
	XYWH[0] -= font->atlasInfo.glyphW / 2;
	XYWH[1] -= font->atlasInfo.glyphH / 2;

	sprintf ( buffer, "%d", card->mana );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, buffer );



	// attack
	XYWH[0] = XYWHpass[0] + 2;
	XYWH[1] = XYWHpass[1] + cardH - 2;

	draw2dApi->fillCircle ( XYWH, w, colorDYellow, screenDims, glBuffers );
	XYWH[0] -= font->atlasInfo.glyphW / 2;
	XYWH[1] -= font->atlasInfo.glyphH / 2;

	sprintf ( buffer, "%d", card->attack );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, buffer );



	// health
	XYWH[0] = XYWHpass[0] + cardW - 2;
	XYWH[1] = XYWHpass[1] + cardH - 2;

	draw2dApi->fillCircle ( XYWH, w, colorDRed, screenDims, glBuffers );
	XYWH[0] -= font->atlasInfo.glyphW / 2;
	XYWH[1] -= font->atlasInfo.glyphH / 2;

	sprintf ( buffer, "%d", card->health );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, buffer );

	// name

	int glyphWH[2] = { font->atlasInfo.glyphW, font->atlasInfo.glyphH };

	int slen = strlen ( base->name );
	XYWH[0] = centerX ( XYWHpass[0], XYWHpass[2], glyphWH[0], slen );
	XYWH[1] = centerX ( XYWHpass[1], XYWHpass[3], glyphWH[1], 1 );
	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, base->name );
}

/// Event

int oasis_game_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	printf ( "oasis_game_event ( )\n" );

	// check if u clicked in the hand.

	int handLen = get_hand_len ( player );

	int cardXYWH[4] = {
		playerHandXY[0],
		playerHandXY[1],
		cardW,
		cardH,
	};

	int i = 0;
	while ( i < handLen ) {
		if ( inBox ( clickXY, cardXYWH ) ) {
			printf ( "click on hand: %d\n", i );

			oasis_cursor = oasis_cursor_hand + i;

			return 1;
		}

		cardXYWH[0] += cardW + cardGap;

		i += 1;
	}

	int fullBoard[4] = {
		playerBoardXY[0],
		playerBoardXY[1],
		(cardW + cardGap) * BOARD_MAX,
		cardH + cardGap,
	};
	if ( inBox ( clickXY, fullBoard ) ) {
		printf ( "clicked on player board\n" );

		if ( oasis_cursor >= oasis_cursor_hand &&
		     oasis_cursor < oasis_cursor_board ) {
			// hand is selected, try to play to board.
			printf ( "hand is selected, try to play to board.\n" );

			play_hand_to_board ( player, oasis_cursor - oasis_cursor_hand );

			oasis_cursor = 0;
		} else if ( oasis_cursor == 0 ) {
			// hand isnt selected, so try to select a card

			int cardXYWH[4] = {
				fullBoard[0] + cardGap / 2,
				fullBoard[1] + cardGap / 2,
				cardW,
				cardH,
			};

			int numBoard = get_board_len ( player );
printf ( "numBoard: %d\n", numBoard );
			int i = 0;
			while ( i < numBoard ) {
sayIntArray ( "cardXYWH", cardXYWH, 4 );
				if ( inBox ( clickXY, cardXYWH ) ) {
					// select this card
					printf ( "select a board card\n" );
					oasis_cursor = oasis_cursor_board + i;
				}
				cardXYWH[0] += cardW + cardGap;

				i += 1;
			}
		}

		return 1;
	}


	// check the enemy board
	fullBoard[0] = enemyBoardXY[0];
	fullBoard[1] = enemyBoardXY[1];
	fullBoard[2] = (cardW + cardGap) * BOARD_MAX;
	fullBoard[3] = cardH + cardGap;
	if ( inBox ( clickXY, fullBoard ) ) {
		printf ( "clicked on enemy board\n" );

		// if the card i have selected is on my board
		if ( oasis_cursor >= oasis_cursor_board &&
		     oasis_cursor <= oasis_cursor_board_end ) {
			// i have a board minion selected, it might attack.
			int enemyIndex = board_click_index ( enemy, clickXY, fullBoard );
			if ( enemyIndex > -1 ) {
				printf ( "attack enemy: %d\n", enemyIndex );
				int attackIndex = oasis_cursor - oasis_cursor_board;
				card_attack ( player, enemy, attackIndex, enemyIndex );
			}
		}
	}

	oasis_cursor = 0;

	return 0;
}

// doesnt simply return the index, it also makes sure a minion exists there.
int board_click_index ( struct player *player, int *clickXY, int *boardXYWH ) {

	int cardXYWH[4] = {
		boardXYWH[0] + cardGap / 2,
		boardXYWH[1] + cardGap / 2,
		cardW,
		cardH,
	};

	int numBoard = get_board_len ( player );
	printf ( "numBoard: %d\n", numBoard );
	int i = 0;
	while ( i < numBoard ) {
	sayIntArray ( "cardXYWH", cardXYWH, 4 );
		if ( inBox ( clickXY, cardXYWH ) ) {
			// select this card
			printf ( "select a board card\n" );
//			oasis_cursor = oasis_cursor_board + i;
			return i;
		}
		cardXYWH[0] += cardW + cardGap;
		i += 1;
	}
	return -1;
}

// for for the player only.
void play_hand_to_board ( struct player *player, int handI ) {
	printf ( "play_hand_to_board ( )\n" );

	// check to make sure handI isnt out of range?

	int boardLen = get_board_len ( player );
	if ( boardLen < BOARD_MAX ) {
	} else {
		printf ( "board full\n" );
		return;
	}

	struct card *handCard = player->hand[handI];
	if ( player->mana >= handCard->mana ) {
		printf ( "enough mana to play from hand\n" );
	} else {
		// not enough mana to play
		printf ( "not enough mana to play\n" );
		return;
	}

	player->mana -= handCard->mana;
	player->board[boardLen] = player->hand[handI];

	shrink_array ( player->hand, handI, HAND_MAX );

	printf ( "play_hand_to_board ( ) OVER\n" );
}

// i am removing card at arr[i], so shift everything at an index above that, left by 1.
// make sure the final arr[index] is set to null.
void shrink_array ( struct card *arr[], int i, int max ) {
	while ( i < max - 1 ) {
		if ( arr[i+1] != NULL ) {
			arr[i] = arr[i + 1];
		} else {
			break;
		}
		i += 1;
	}
	arr[i] = NULL;
}


void card_attack ( struct player *attacker, struct player *defender, int attackIndex, int defendIndex ) {
	printf ( "card_attack ( )\n" );

	struct card *attackCard = attacker->board[attackIndex];
	struct card *defendCard = defender->board[defendIndex];

	// TODO, check for poison, lifesteal, sheild, etc.
	attackCard->health -= defendCard->attack;
	defendCard->health -= attackCard->attack;

	if ( attackCard->health <= 0 ) {
		shrink_array ( attacker->board, attackIndex, BOARD_MAX );
	}
	if ( defendCard->health <= 0 ) {
		shrink_array ( defender->board, defendIndex, BOARD_MAX );
	}
}











int turn = 0;
// 0 is other
// 1 is player
// 2 is enemy

void turn_change ( ) {
	printf ( "turn_change ( )\n" );


	if ( turn == 0 ) {
		// shuffle both, draw both.
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
		draw_player ( player );
		mana_increment ( player );
	} else {
		// enemy
		draw_player ( enemy );
		mana_increment ( enemy );

		enemy_ai ( enemy );
	}

	printf ( "turn_change ( ) OVER\n" );
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
				if ( card->mana == manaSearch ) {
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

void draw_player ( struct player *player ) {
		// draw for the player.

		int deckLen = arrayListGetLength ( player->deck );
		if ( deckLen == 0 ) {
			printf ( "DECK EMPTY, take dmg\n" );
			return;
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
}

void mana_increment ( struct player *player ) {

		// refill mana and increment max
		player->manaMax += 1;
		if ( player->manaMax > MANA_MAX ) {
			player->manaMax = MANA_MAX;
		}
		player->mana = player->manaMax;
}

/// Utilities

// render

int centerX ( int x, int w, int glyphW, int numChars ) {
	int pos = x + (w / 2) - (numChars * glyphW) / 2;

	return pos;
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











