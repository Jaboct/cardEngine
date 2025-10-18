#include "oasis_render.h"


/** Includes */

#include <jalb/jalbSay.h>

#include "oasis.h"

#include "card_util.h"
#include "oasis_hand.h"



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
float colorLBlue[4] = { 0.6, 0.6, 1.0, 1.0 };
float colorLGreen[4] = { 0.6, 1.0, 0.6, 1.0 };



extern struct player *player;
extern struct player *enemy;




extern ArrayList *cardBaseList;	// (struct cardBase*)

extern int oasis_cursor;

extern int oasis_cursor_hand;
extern int oasis_cursor_board;
extern int oasis_cursor_board_end;



/// debug

extern int debugPrint_oasisRender;




extern int oasisInited;




/// Render

/*
DOM - data object model
assume screenDims { 1200, 800 }


*/

int cardW = 100;
int cardH = 160;

int cardGap = 20;	// 20 px between each card.
int highlightMargin = 4;

int playerCharWH[2] = { 200, 100 };

// relevent elements.
int playerCharXY[2];
int enemyCharXY[2];

int playerHandXY[2];
int enemyHandXY[2];

int playerBoardXY[2];
int enemyBoardXY[2];






/** Functions */


void set_debugPrint_oasisRender ( int i ) {
	printf ( "set_debugPrint_oasisRender ( )\n" );
	printf ( "i: %d\n", i );

	debugPrint_oasisRender = i;
}



void oasis_assemble_dom ( int *XYWHpass ) {
	printf ( "oasis_assemble_dom ( )\n" );
	sayIntArray ( "XYWHpass", XYWHpass, 2 );

//	int midX = XYWHpass[2] / 2;
	int midY = XYWHpass[3] / 2;


	enemyCharXY[0] = centerX_px ( 0, XYWHpass[2], playerCharWH[0] );
	enemyCharXY[1] = 0;

	playerCharXY[0] = centerX_px ( 0, XYWHpass[2], playerCharWH[0] );
	playerCharXY[1] = XYWHpass[3] - playerCharWH[1];


	playerBoardXY[0] = 100;
	playerBoardXY[1] = midY + cardGap / 2;

	playerHandXY[0] = 100;
	playerHandXY[1] = XYWHpass[3] - (cardH + (cardGap * 2) + playerCharWH[1]);

	enemyHandXY[0] = 100;
	enemyHandXY[1] = (cardGap * 2) + playerCharWH[1];

	enemyBoardXY[0] = 100;
//	enemyBoardXY[1] = (cardGap * 2) + cardH + cardGap;
	int boardH = cardH + cardGap;
	enemyBoardXY[1] = midY - boardH - cardGap / 2;
	sayIntArray ( "enemyBoardXY", enemyBoardXY, 2 );
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

//	int midX = XYWHpass[2] / 2;
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


	char buffer[256];
	int slen;
	int rect[4];

	/// render enemy hp
	render_character ( screenDims, glBuffers, enemy, enemyCharXY );
/*
	sprintf ( buffer, "%d", enemy->health );
	int slen = strlen ( buffer );
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
*/






	// my hp
	render_character ( screenDims, glBuffers, player, playerCharXY );
/*
	sprintf ( buffer, "%d", player->health );
	slen = strlen ( buffer );
	rect[0] = centerX ( midX, 0, glyphW, slen );
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
*/


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


	// render player deck
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






	// player
//	int XY[2] = {
//		100,
//		XYWHpass[3] - cardH - (cardGap * 2),
//		playerHandXY[0],
//		playerHandXY[1],
//	};

	render_hand ( screenDims, glBuffers, player, playerHandXY, oasis_cursor );
	render_board ( screenDims, glBuffers, player, playerBoardXY, oasis_cursor );


	// enemy
//	XY[1] = (cardGap * 2);
	render_hand ( screenDims, glBuffers, enemy, enemyHandXY, -1 );

//	XY[0] = enemyBoardXY[0];
//	XY[1] = enemyBoardXY[1];
	render_board ( screenDims, glBuffers, enemy, enemyBoardXY, -1 );





	if ( debugPrint_oasisRender ) {
		printf ( "oasis_game_render ( ) OVER\n" );
	}
}

void render_character ( int *screenDims, GLuint *glBuffers, struct player *player, int *XY ) {

	struct jalbFont *font = fonts[0];
	int glyphW = font->atlasInfo.glyphW;
	int glyphH = font->atlasInfo.glyphH;


	int fullRect[4] = {
		XY[0],
		XY[1],
		playerCharWH[0],
		playerCharWH[1],
	};

	char buffer[256];
	int rect[4];
	int slen;


	draw2dApi->drawRect ( fullRect, colorBlack, screenDims, glBuffers );


	// my hp
	sprintf ( buffer, "%d", player->health );
	slen = strlen ( buffer );
	rect[0] = centerX ( fullRect[0], fullRect[2], glyphW, slen );
//	rect[0] = centerX ( midX, 0, glyphW, slen );
	slen = strlen ( buffer );
//	rect[1] = XYWHpass[3] - cardGap - font->atlasInfo.glyphH;
	rect[1] = fullRect[1] + fullRect[3] - cardGap - glyphH;

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );

	rect[0] += 40;

	// player mana
	sprintf ( buffer, "%d / %d", player->mana, player->manaMax );
	slen = strlen ( buffer );
//	rect[1] = XYWHpass[3] - cardGap - font->atlasInfo.glyphH;

	draw2dApi->drawCharPre ( font, colorDBlue );
	draw2dApi->drawString ( screenDims, glBuffers, rect, font, buffer );


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
	struct cardBase *base = arrayListGetPointer ( cardBaseList, card->id );
	oasis_card_render_base ( screenDims, glBuffers, XYWHpass,
		base->name, card->type, card->mana, card->attack, card->health, card->numAttacks, card->mods );
}

void oasis_cardBase_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct cardBase *base ) {
	oasis_card_render_base ( screenDims, glBuffers, XYWHpass,
		base->name, base->type, base->mana, base->attack, base->health, -2, NULL );
}

void oasis_card_render_base ( int *screenDims, GLuint *glBuffers, int *XYWHpass,
		char *name, int type, int mana, int attack, int health, int numAttacks, ArrayList *mods ) {

	if ( debugPrint_oasisRender ) {
		printf ( "oasis_card_render ( )\n" );
	}
//	sayIntArray ( "XYWHpass", XYWHpass, 4 );

	int XYWH[4] = {
		XYWHpass[0],
		XYWHpass[1],
		XYWHpass[2],
		XYWHpass[3],
	};

//	struct cardBase *base = arrayListGetPointer ( cardBaseList, card->id );

	struct jalbFont *font = fonts[0];
	char buffer[256];

	if ( type == 0 ) {
		// minion.
		draw2dApi->fillRect ( XYWH, colorGray, screenDims, glBuffers );
	} else if ( type == 1 ) {
		// spell
		draw2dApi->fillRect ( XYWH, colorLBlue, screenDims, glBuffers );
	}
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

	sprintf ( buffer, "%d", mana );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, buffer );


	if ( type == 0 ) {
	// attack
	XYWH[0] = XYWHpass[0] + 2;
	XYWH[1] = XYWHpass[1] + cardH - 2;

	draw2dApi->fillCircle ( XYWH, w, colorDYellow, screenDims, glBuffers );
	XYWH[0] -= font->atlasInfo.glyphW / 2;
	XYWH[1] -= font->atlasInfo.glyphH / 2;

	sprintf ( buffer, "%d", attack );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, buffer );



	// health
	XYWH[0] = XYWHpass[0] + cardW - 2;
	XYWH[1] = XYWHpass[1] + cardH - 2;

	draw2dApi->fillCircle ( XYWH, w, colorDRed, screenDims, glBuffers );
	XYWH[0] -= font->atlasInfo.glyphW / 2;
	XYWH[1] -= font->atlasInfo.glyphH / 2;

	sprintf ( buffer, "%d", health );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, buffer );
	}


	// -1, renders nothing
	if ( numAttacks == -1 ) {
		// "ZZZ" in top right corner.
		XYWH[0] = XYWHpass[0] + cardW - 2;
		XYWH[1] = XYWHpass[1] + 2;
		text_in_circle ( screenDims, glBuffers, XYWH, colorWhite, "Zzz" );
	} else if ( numAttacks == 0 ) {
		XYWH[0] = XYWHpass[0] + cardW - 2;
		XYWH[1] = XYWHpass[1] + 2;
		text_in_circle ( screenDims, glBuffers, XYWH, colorWhite, "Zzz" );
	} else if ( numAttacks > 0 ) {
		XYWH[0] = XYWHpass[0] + cardW - 2;
		XYWH[1] = XYWHpass[1] + 2;

		sprintf ( buffer, "%d", numAttacks );

		text_in_circle ( screenDims, glBuffers, XYWH, colorLGreen, buffer );
	}


	// name
	int glyphWH[2] = { font->atlasInfo.glyphW, font->atlasInfo.glyphH };

	int slen = strlen ( name );
	XYWH[0] = centerX ( XYWHpass[0], XYWHpass[2], glyphWH[0], slen );
	XYWH[1] = centerX ( XYWHpass[1], XYWHpass[3], glyphWH[1], 1 );
	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, name );

	// modifiers
	XYWH[1] += font->atlasInfo.glyphH;
	int i = 0;
	int numMods = arrayListGetLength ( mods );
//	printf ( "numMods: %d\n", numMods );
	while ( i < numMods ) {
		printf ( "i: %d\n", i );

		struct cardMod *mod = arrayListGetPointer ( mods, i );

		char *str = mod_to_str ( mod );
		int slen = strlen ( str );

		XYWH[0] = centerX ( XYWHpass[0], XYWHpass[2], glyphWH[0], slen );
		XYWH[1] += font->atlasInfo.glyphH;

		draw2dApi->drawCharPre ( font, colorBlack );
		draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, str );

		i += 1;
	}

	if ( debugPrint_oasisRender ) {
		printf ( "oasis_card_render ( ) OVER\n" );
	}
}




void text_in_circle ( int *screenDims, GLuint *glBuffers, int *XY, float *color, char *str ) {
	struct jalbFont *font = fonts[0];

	int XYWH[4] = {
		XY[0],
		XY[1],
	};

	float w = 20;

	draw2dApi->fillCircle ( XYWH, w, color, screenDims, glBuffers );
	XYWH[0] -= font->atlasInfo.glyphW / 2;
	XYWH[1] -= font->atlasInfo.glyphH / 2;

//	sprintf ( buffer, "%d", card->health );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, str );
}





/** Pick 3 */

// pick 3 DOM

int row0[4];

int row3_inited = 0;

extern struct pick3 pick3[];
int pick3_button[4];

int row3_cursor = 0;

int pick3_round = 0;

void row3_init ( int *screenDims ) {
	struct jalbFont *font = fonts[0];

	row0[0] = 100 + cardGap/2;
	row0[1] = 100;
	row0[2] = (cardW + cardGap) * 3;
	row0[3] = cardH + font->atlasInfo.glyphH + 4 + cardGap;

	pick3_button[0] = screenDims[0] - 120;
	pick3_button[1] = screenDims[1] - 120;
	pick3_button[2] = 100;
	pick3_button[3] = 100;
}

void render_pick3 ( int *screenDims, GLuint *glBuffers ) {
//	printf ( "render_pick3 ( )\n" );


	if ( !row3_inited ) {
		row3_init ( screenDims );
		row3_inited = 1;
	}


	struct jalbFont *font = fonts[0];

	struct pick3 *p3 = &pick3[0];

	int XYWH[4] = {
		100 + cardGap/2,
		100,
		(cardW + cardGap) * 3,
		cardH + font->atlasInfo.glyphH + 4 + cardGap
	};

	if ( row3_cursor == 1 ) {
		draw2dApi->drawRect ( XYWH, colorOrange, screenDims, glBuffers );
	} else {
		draw2dApi->drawRect ( XYWH, colorWhite, screenDims, glBuffers );
	}
	pick3_render_card ( screenDims, glBuffers, XYWH, p3 );

	p3 = &pick3[1];
	XYWH[1] += XYWH[3] + cardGap;

	if ( row3_cursor == 2 ) {
		draw2dApi->drawRect ( XYWH, colorOrange, screenDims, glBuffers );
	} else {
		draw2dApi->drawRect ( XYWH, colorWhite, screenDims, glBuffers );
	}
	pick3_render_card ( screenDims, glBuffers, XYWH, p3 );


	// on the right, render my cards.
	int cardListXYWH[4] = {
		screenDims[0] - 200,
		100,
		200,
		40,
	};

//	int deckLen = get_deck_len ( player );
	int deckLen = arrayListGetLength ( player->deckTotal );

//	printf ( "deckLen: %d\n", deckLen );

	int i = 0;
	while ( i < deckLen ) {
		draw2dApi->fillRect ( cardListXYWH, colorDGray, screenDims, glBuffers );

	struct card *card = arrayListGetPointer ( player->deckTotal, i );
	struct cardBase *base = arrayListGetPointer ( cardBaseList, card->id );
	int coppies = 1;

	char buffer[1024];
	sprintf ( buffer, "%dx %s (%d)", coppies, base->name, card->mana );

//	printf ( "buffer: %s\n", buffer );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, cardListXYWH, font, buffer );

		cardListXYWH[1] += cardListXYWH[3] + 10;

		i += 1;
	}

	XYWH[0] = pick3_button[0];
	XYWH[1] = pick3_button[1];
	XYWH[2] = pick3_button[2];
	XYWH[3] = pick3_button[3];
	draw2dApi->fillRect ( XYWH, colorDGray, screenDims, glBuffers );

	char buffer[256];
	sprintf ( buffer, "select" );
	int slen = strlen ( buffer );
	XYWH[0] = centerX ( XYWH[0], XYWH[2], slen, font->atlasInfo.glyphW );
	XYWH[1] = centerX ( XYWH[1], XYWH[3], 1, font->atlasInfo.glyphH );

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, buffer );

//	printf ( "render_pick3 ( ) OVER\n" );
}

void pick3_render_card ( int *screenDims, GLuint *glBuffers, int XYWHpass[], struct pick3 *p3 ) {
	struct jalbFont *font = fonts[0];

	int XYWH[4] = {
		XYWHpass[0],
		XYWHpass[1],
		XYWHpass[2],
		XYWHpass[3],
	};

	XYWH[2] = cardW;
	XYWH[3] = cardH;

	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, p3->name );

	XYWH[0] += cardGap / 2;
	XYWH[1] += font->atlasInfo.glyphH + 4;
	struct cardBase *base = arrayListGetPointer ( cardBaseList, p3->cards[0] );
	oasis_cardBase_render ( screenDims, glBuffers, XYWH, base );
	XYWH[0] += cardW + cardGap;

	base = arrayListGetPointer ( cardBaseList, p3->cards[1] );
	oasis_cardBase_render ( screenDims, glBuffers, XYWH, base );
	XYWH[0] += cardW + cardGap;

	base = arrayListGetPointer ( cardBaseList, p3->cards[2] );
	oasis_cardBase_render ( screenDims, glBuffers, XYWH, base );
}

int event_pick3 ( SDL_Event *e, int *clickXY, int *eleWH ) {
//	struct jalbFont *font = fonts[0];

	int XYWH[4] = {
		row0[0],
		row0[1],
		row0[2],
		row0[3],
	};

	row3_cursor = 0;

	// DOM
	if ( inBox ( clickXY, XYWH ) ) {
		printf ( "click on pick 3 row 0\n" );
		row3_cursor = 1;

		return 1;
	}

	XYWH[1] += XYWH[3] + cardGap;
	if ( inBox ( clickXY, XYWH ) ) {
		printf ( "click on pick 3 row 1\n" );
		row3_cursor = 2;

		return 1;
	}

	XYWH[0] = pick3_button[0];
	XYWH[1] = pick3_button[1];
	XYWH[2] = pick3_button[2];
	XYWH[3] = pick3_button[3];
	if ( inBox ( clickXY, XYWH ) ) {
		printf ( "click pick3 button\n" );
		if ( row3_cursor > 0 ) {
			// add these cards to the deck and move onto the next boss.
		}
	}


	return 0;
}




















