#include "solitaire_hand.h"

/** Includes */

#include <jalbDraw/jalb_draw2d_api.h>


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

float colorDGreen[4] = { 0.1, 0.5, 0.1, 1.0 };
float colorDRed[4] = { 0.9, 0.5, 0.5, 1.0 };

/** Functions */

/// Solitaire

// MODNAME	NICKNAME	solitaire_init	solitaire_render	solitaire_event	solitaire_close	solitaire_number
int solitaire_id = -1;

void *solitaire_init ( ) {
	srand(time(NULL));   // Initialization, should only be called once.

	return NULL;
}

void solitaire_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data ) {
//	printf ( "solitaire_render ( )\n" );


	solitair_render_full ( screenDims, glBuffers, XYWHpass, NULL );

/*
	struct jalbFont *font = fonts[0];

//	draw2dApi->fillRect ( XYWHpass, colorBlack, screenDims, glBuffers );
	draw2dApi->fillRect ( XYWHpass, colorDGreen, screenDims, glBuffers );

	draw2dApi->drawCharPre ( fonts[0], colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWHpass, fonts[0], "solitaire_render ( )" );

	int cardXYWH[4] = {
		XYWHpass[0] + 40,
		XYWHpass[1] + 40,
		100,
		160,
	};

	card_render ( screenDims, glBuffers, cardXYWH, NULL );

	cardXYWH[0] += font->atlasInfo.glyphW * 8;
	cardXYWH[1] += font->atlasInfo.glyphH * 1;
	card_render ( screenDims, glBuffers, cardXYWH, NULL );
*/
}

int solitaire_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	if ( e->type == SDL_QUIT ) {
	} else if ( e->type == SDL_KEYDOWN ) {
//		if ( e->key.keysym.sym == SDLK_1 ) {
//		}
	} else if ( e->type == SDL_KEYUP ) {
	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		if ( e->button.button == SDL_BUTTON_LEFT ) {
			int ret = solitaire_game_event ( e, clickXY, eleWH, NULL );
			return ret;

//			e->button.x, or clickXY[0]
		} else if ( e->button.button == SDL_BUTTON_RIGHT ) {
		}
	} else if ( e->type == SDL_MOUSEBUTTONUP ) {
	} else if ( e->type == SDL_MOUSEMOTION ) {
	} else if ( e->type == SDL_MOUSEWHEEL ) {
	}

	return 0;
}

void solitaire_close ( char *data ) {
}

void solitaire_number ( int id ) {
	solitaire_id = id;
}


int stockLen = 52;
int stock[52] = { 0 };

// for when i flip through stock for the hand.
int stockTop = 0;	// aka hand index?

int boardH[7];
int board[7][20][2];
// [w][h][1] = 0, face up. 1, face down.




// 0 is nothing.
// 1 is hand
// 2-8 is deck
// 9-12 are winning thing.
int solitair_cursor = 0;
// this needs to remember which part of the stack i am clicking on.
int cursor_h = 0;

int boardOffset = 2;



int foundation[4] = { -1, -1, -1, -1 };











// this doesnt feel like true random?
// comapre it to haveingj an al that i remove from when the card is picked.
// this actually feels just like that? im not sure.
// its different
// in this case, lets say card 0-10 have been picked, there is now a 11/52 chance of rolling an 11?
// when i removed, there is then a 1/42 chance of rolling an 11.
// so this is crap.

// wait idk if that is true.
// the only way to roll an 11 is to roll a 0, then that gets updated to 11.
// if i roll a 1... idk think about this later, and make some examples...

void fill_stock ( ) {
	printf ( "fill_stock ( )\n" );

	int i = 0;
	while ( i < stockLen ) {
		int r = rand() % (stockLen - i);

		int updated = 0;
		int j = 0;
		while ( j < i ) {
			// this doesnt work, if i have r = 1, i = 2, deck = { 1, 0 }.
			// this will result in 1.
			if ( stock[j] <= r ) {
				r += 1;
				// this is lazy
				updated = 1;

// since the above checks only looked for cards between 0 and r-1.
// but now r is 1 higher, it may have ignored a card of value r.
// so look back for the value of r, if i found it, then repeat.
while ( updated ) {
	updated = 0;
	// iterate back
	int k = j - 1;
	while ( k >= 0 ) {
		if ( stock[k] == r ) {
			r += 1;
			updated = 1;
			continue;
		}
		k -= 1;
	}
}
			}

			j += 1;
		}

		stock[i] = r;

		i += 1;
	}

	sayIntArray ( "stock", stock, stockLen );

	// make sure there are no duplicated
	int duplicate = 0;
	i = 0;
	while ( i < stockLen ) {
		int j = i-1;
		while ( j >= 0 ) {
			if ( stock[i] == stock[j] ) {
				printf ( "error, duplicat of %d at %d and %d\n", stock[i], i, j );
				duplicate = 1;
			}
			j -= 1;
		}
		i += 1;
	}
	if ( !duplicate ) {
		printf ( "there are no duplicates\n" );
	}

	printf ( "fill_stock ( ) OVER\n" );
}

void solitair_game_init ( ) {
	printf ( "solitair_game_init ( )\n" );

	// now shuffle stock
	fill_stock ( );

	// now deal it out.
	int i = 0; // i is height
	while ( i < 7 ) {
		printf ( "i: %d\n", i );

		int w = i;
		while ( w < 7 ) {
			printf ( "w: %d\n", w );

			board[w][i][0] = stock[stockLen-1];
			if ( w == i ) {
				// face up.
				board[w][i][1] = 0;
			} else {
				board[w][i][1] = 1;
			}
			boardH[w] += 1;
			stockLen -= 1;

			w += 1;
		}
		i += 1;
	}

	// for debugging
	// king board to empty board
	if ( 0 ) {
		boardH[1] = 0;
		board[0][0][0] = 12 + 13;
	}

	// king hand to empty board
	if ( 0 ) {
		boardH[1] = 0;
		stock[2] = 12 + 13;

		// for debugging hand < 3
		stock[1] = 0;
		stock[0] = 13;
	}

	// ace to foundation
	if ( 0 ) {
		stock[2] = 0;
	}

	// from foundation to board.
	if ( 0 ) {
		board[0][0][0] = 0;	// black ace
		board[1][1][0] = 13 + 1;	// red 2
	}

	sayIntArray ( "boardH", boardH, 7 );
}

int solitair_new = 1;

// pixel difference between 2 cards stacked ontop of eachother.
// should be atleast (margin*2 + glyphH*2) so u can see the number and suit.
int card_head = 50;

void solitair_render_full ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data ) {

	if ( solitair_new ) {
		solitair_game_init ( );
		solitair_new = 0;
	}

	struct jalbFont *font = fonts[0];

//	draw2dApi->fillRect ( XYWHpass, colorBlack, screenDims, glBuffers );
	draw2dApi->fillRect ( XYWHpass, colorDGreen, screenDims, glBuffers );

	int cardW = 100;
	int cardH = 160;
	int cardXYWH[4] = {
		XYWHpass[0] + 40,
		XYWHpass[1] + 40,
		cardW,
		cardH,
	};

	/// draw stock
	if ( (stockLen - stockTop) > 0 ) {
		card_render_back ( screenDims, glBuffers, cardXYWH, NULL );
	} else {
		draw2dApi->drawRect ( cardXYWH, colorBlack, screenDims, glBuffers );
	}

	// number of cards in the stock
	char numCards[24];
	sprintf ( numCards, "%d", (stockLen - stockTop) );

	int center[4] = {
		cardXYWH[0] + (cardXYWH[2] / 2) - (font->atlasInfo.glyphW * strlen ( numCards)) / 2,
		cardXYWH[1] + (cardXYWH[3] / 2) - (font->atlasInfo.glyphH / 2 ),
		cardW,
		cardH,
	};


	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, center, font, numCards );


	int highlightMargin = 4;

	/// draw hand

	cardXYWH[1] += cardH + 100;

	sprintf ( numCards, "%d", stockTop );

	center[1] = cardXYWH[1] - (font->atlasInfo.glyphH + 4);
	center[0] = cardXYWH[0] + (cardXYWH[2] - strlen(numCards) * font->atlasInfo.glyphW) / 2;
	draw2dApi->drawCharPre ( font, colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, center, font, numCards );


//	cardXYWH[1] += cardH + 100;
	if ( stockTop == 0 ) {
		// hand is empty
		draw2dApi->drawRect ( cardXYWH, colorBlack, screenDims, glBuffers );
	} else {
		int i = 3;
		if ( stockTop < 3 ) {
			i = stockTop;
		}

		while ( i > 0 ) {
			if ( solitair_cursor == 1 ) {
				if ( i == 1 ) {
					if ( solitair_cursor == 1 ) {
						int highlightXYWH[4] = {
							cardXYWH[0] - highlightMargin,
							cardXYWH[1] - highlightMargin,
							cardXYWH[2] + 2 * highlightMargin,
							cardXYWH[3] + 2 * highlightMargin,
						};
						draw2dApi->fillRect ( highlightXYWH, colorGold, screenDims, glBuffers );
					}
				}
			}

			int val[2] = { stock[stockTop - i], 0 };
			card_render_index ( screenDims, glBuffers, cardXYWH, val );
			cardXYWH[1] += card_head;

			i -= 1;
		}
/*
		if ( stockTop >= 3 ) {
			// draw the top 3.
			if ( stockLen > 3 ) {
			int val[2] = { stock[stockTop - 3], 0 };
			card_render_index ( screenDims, glBuffers, cardXYWH, val );

			cardXYWH[1] += card_head;
			val[0] = stock[stockTop - 2];
			card_render_index ( screenDims, glBuffers, cardXYWH, val );

			cardXYWH[1] += card_head;
			if ( solitair_cursor == 1 ) {
				int highlightXYWH[4] = {
					cardXYWH[0] - highlightMargin,
					cardXYWH[1] - highlightMargin,
					cardXYWH[2] + 2 * highlightMargin,
					cardXYWH[3] + 2 * highlightMargin,
				};
				draw2dApi->fillRect ( highlightXYWH, colorGold, screenDims, glBuffers );
			}
			val[0] = stock[stockTop - 1];
			card_render_index ( screenDims, glBuffers, cardXYWH, val );
			}
		}
*/
	}



	cardXYWH[0] += cardW + 100;
	cardXYWH[1] = XYWHpass[1] + 40;

//	printf ( "solitair_cursor: %d\n", solitair_cursor );

	int i = 0;
	while ( i < 7 ) {
		cardXYWH[1] = XYWHpass[1] + 40;

		int this_selected = 0;
		if ( solitair_cursor == i + boardOffset ) {
			// this board spot is selected.
			this_selected = 1;
		}

		if ( boardH[i] == 0 ) {
			draw2dApi->drawRect ( cardXYWH, colorBlack, screenDims, glBuffers );
		}

		int h = 0;
		while ( h < boardH[i] ) {
			if ( this_selected &&
			     cursor_h == h ) {
				// this card (and everything below) is selected.

				int kids = boardH[i] - h - 1;

				int highlightXYWH[4] = {
					cardXYWH[0] - highlightMargin,
					cardXYWH[1] - highlightMargin,
					cardXYWH[2] + 2 * highlightMargin,
					cardXYWH[3] + kids * card_head + 2 * highlightMargin,
				};
				draw2dApi->fillRect ( highlightXYWH, colorGold, screenDims, glBuffers );
			}

			card_render_index ( screenDims, glBuffers, cardXYWH, board[i][h] );

			cardXYWH[1] += card_head;

			h += 1;
		}

		cardXYWH[0] += cardW + 20;

		i += 1;
	}


	// render the suit stacks (foundation)

	cardXYWH[0] = XYWHpass[0] + 40 + cardW + 100;
	cardXYWH[1] = XYWHpass[1] + 40 + 500;

	printf ( "solitair_cursor: %d\n", solitair_cursor );

	i = 0;
	while ( i < 4 ) {
		if ( foundation[i] == -1 ) {
			// it is empty

			draw2dApi->drawRect ( cardXYWH, colorBlack, screenDims, glBuffers );

			char *suit = suite_to_string ( i );

			int center[4];
			center_text ( cardXYWH, center, font, strlen ( suit ) );
			center[2] = 100;
			center[3] = 100;

			draw2dApi->drawCharPre ( fonts[0], colorWhite );
			draw2dApi->drawString ( screenDims, glBuffers, center, fonts[0], suit );

		} else {
			if ( solitair_cursor == boardOffset + 7 + i ) {
				// it is highlighted.

				int highlightXYWH[4] = {
					cardXYWH[0] - highlightMargin,
					cardXYWH[1] - highlightMargin,
					cardXYWH[2] + 2 * highlightMargin,
					cardXYWH[3] + 2 * highlightMargin,
				};
				draw2dApi->fillRect ( highlightXYWH, colorGold, screenDims, glBuffers );
			}

			int index = i * 13 + foundation[i];
			int val[2] = { index, 0 };
			card_render_index ( screenDims, glBuffers, cardXYWH, val );
		}

		cardXYWH[0] += cardW + 40;

		i += 1;
	}

/*
	draw2dApi->drawCharPre ( fonts[0], colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWHpass, fonts[0], "solitaire_render ( )" );

	int cardXYWH[4] = {
		XYWHpass[0] + 40,
		XYWHpass[1] + 40,
		100,
		160,
	};

	card_render ( screenDims, glBuffers, cardXYWH, NULL );

	cardXYWH[0] += font->atlasInfo.glyphW * 8;
	cardXYWH[1] += font->atlasInfo.glyphH * 1;
	card_render ( screenDims, glBuffers, cardXYWH, NULL );
*/
}

void center_text ( int pass[4], int ret[4], struct jalbFont *font, int strl ) {
	ret[0] = pass[0] + ( pass[2] - font->atlasInfo.glyphW * strl ) / 2;
	ret[1] = pass[1] + ( pass[3] - font->atlasInfo.glyphH ) / 2;
}

/*
DOM
{ 40, 40, cardW, cardH, 0 }	// 0, the deck
// its height varies, but i dont nede to care about that
{ 40, 40 + 100 + cardH, cardW, cardH, 1 }	// 1, the hand
// assumes there are a total of 7 cards, probably nto true but w/e
// ther are 7 of these
{ 40, 40 + cwardW + 100, cardW, cardH + 20 * 6, 1 }	// 1, the hand
*/

int inBox ( int XY[], int XYWH[] ) {
	if ( XY[0] > XYWH[0] &&
	     XY[0] < XYWH[0] + XYWH[2] ) {
		if ( XY[1] > XYWH[1] &&
		     XY[1] < XYWH[1] + XYWH[3] ) {
			return 1;
		}
	}
	return 0;
}


int solitaire_game_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	// 100 px between deck and board
	// 20 px between each board stack.

	int cardW = 100;
	int cardH = 160;

	int XYWH[4] = {
		40, 
		40,
		cardW,
		cardH,
	};

	// check the stocks
	if ( inBox ( clickXY, XYWH ) ) {
		printf ( "click on deck\n" );

		if ( stockTop == stockLen ) {
			stockTop = 0;
		} else {
			stockTop += 3;
			if ( stockTop > stockLen ) {
				stockTop = stockLen;
			}
		}

		printf ( "stockTop: %d\n", stockTop );

		solitair_cursor = 0;

		return 1;
	}


	// check the hands
	if ( stockTop > 0 ) {
	int cardsInHand = stockTop;
	if ( cardsInHand > 3 ) {
		cardsInHand = 3;
	}
	XYWH[1] += cardH + 100 + (card_head * (cardsInHand-1));
	// todo, adjust height
	if ( inBox ( clickXY, XYWH ) ) {
		printf ( "click on hand\n" );
		solitair_cursor = 1;

		return 1;
	}
	}


	// check teh board
	XYWH[1] = 40;
	XYWH[0] += cardW + 100;

	int i = 0;
	while ( i < 7 ) {
		XYWH[3] = cardH + card_head * (boardH[i] - 1);

		if ( inBox ( clickXY, XYWH ) ) {
			printf ( "click on board: %d\n", i );

			int h = clickXY[1] - XYWH[1];
			int c = h / card_head;	// card of the stack i am clicking on.
			if ( c >= boardH[i] ) {
				c = boardH[i] - 1;
			}

			printf ( "c: %d\n", c );

			if ( board[i][c][1] == 0 ) {
				// the card im clicking on is flipped over
			} else {
				// its not flipepd over, so break and clear cursor
				solitair_cursor = 0;
				break;
			}

			if ( solitair_cursor == 0 ) {
				// nothing is selected, so slect a new
				if ( board[i][c][1] == 0 ) {
					// make sure its flipped over
					solitair_cursor = i + boardOffset;
					cursor_h = c;
				}
			} else {
				// something is selected.

int ret = stack_merge ( solitair_cursor, cursor_h, i+boardOffset, c );
if ( ret ) {
}
solitair_cursor = 0;
			}

			return 1;
		}

		XYWH[0] += cardW + 20;

		i += 1;
	}

	// foundation
	XYWH[0] = 40 + cardW + 100;
	XYWH[1] = 40 + 500;
	i = 0;
	while ( i < 4 ) {
		if ( inBox ( clickXY, XYWH ) ) {
			printf ( "click in foundation: %d\n", i );
			printf ( "foundation[i]: %d\n", foundation[i] );

			printf ( "solitair_cursor: %d\n", solitair_cursor );

			if ( solitair_cursor == 0 ) {
				// i currently have nothing selected, so if this foundation isnt empty, select it.
				if ( foundation[i] >= 0 ) {
					solitair_cursor = boardOffset + 7 + i;
					return 1;
				}
			}

			// if i have a board card selected.
			if ( solitair_cursor >= boardOffset &&
			     solitair_cursor < boardOffset + 7 ) {
				// make sure im clicking on the bottom.
				if ( cursor_h == boardH[solitair_cursor - boardOffset] - 1 ) {
					printf ( "end of board selected\n" );

				} else {
					printf ( "NOT end of board selected\n" );
					continue;
				}
			} else {
				// dont use _to_index
			}


			int cursor_index = cursor_to_index ( solitair_cursor, cursor_h );
			printf ( "cursor card (%d): ", cursor_index );
			say_card_index ( cursor_index );

//			int click_index = cursor_to_index ( solitair_cursor, cursor_h );
//			if ( foundation[i] == 0 ) {
//				// see if the click is of the same 
//			}

			printf ( "foundation[i]: %d\n", foundation[i] );
			int click_index = i * 13 + foundation[i] + 1;	// +1 cuz it wants to see the card its expecting (and the -1 gltiches it out?)
			printf ( "click card (%d): ", click_index );
			say_card_index ( click_index );

//			int canMove = move_check_found ( click_index, cursor_index );
//			printf ( "canMove: %d\n", canMove );

			printf ( "click_index: %d\n", click_index );
			printf ( "cursor_index: %d\n", cursor_index );

			if ( cursor_index == click_index ) {
				printf ( "card matches, add to foundation\n" );

				if ( solitair_cursor >= boardOffset &&
				     solitair_cursor < boardOffset + 7 ) {
					int cb = solitair_cursor - boardOffset;
					boardH[cb] -= 1;
//					board[cb][boardH[cb]][0]

					int suit = cursor_index / 13;
					foundation[suit] += 1;
					if ( boardH[cb] > 0 ) {
						// make sure the lower cardis facing up.
						board[cb][boardH[cb]-1][1] = 0;
					}
				} else {
					// the only way it can match is either board or hand.
					// so this must be hand.
					remove_hand ( );
					foundation[i] += 1;
					
				}
			}
		}

		XYWH[0] += cardW + 40;

		i += 1;
	}


	solitair_cursor = 0;

	return 1;
}

int card_to_index ( int s, int n ) {
	return s * n + n;
}

// return the card index of the cursor
int cursor_to_index ( int cursor, int c2 ) {
	printf ( "cursor_to_index ( )\n" );

	printf ( "c: %d\n", cursor );
	printf ( "c2: %d\n", c2 );

	if ( cursor == 0 ) {
		return -1;
	}

	if ( cursor == 1 ) {
		// hands
		if ( stockTop == 0 ) {
			return -1;
		}
		return stock[stockTop - 1];
	}

	if ( cursor >= boardOffset &&
	     cursor < boardOffset + 7 ) {
		// its on the board

		int cb = cursor - boardOffset;
		int index = board_to_index ( cb, c2 );
		return index;
	}

	if ( cursor >= boardOffset + 7 &&
	     cursor < boardOffset + 7 + 4 ) {
		// its from the foundation.

		int s = cursor - ( boardOffset + 7 );
		return (s * 13 + foundation[s] );
	}

	return -1;
}

int board_to_index ( int cb, int c2 ) {
//	printf ( "board_to_index ( )\n" );

	printf ( "cb: %d\n", cb );
	printf ( "c2: %d\n", c2 );

	int index = -1;
	if ( cb >= 0 && cb < 7 ) {
		// the board is selected.
		if ( boardH[cb] == 0 ) {
			// this board space is blank, so only be able to move a king in.
			printf ( "board blank\n" );

		} else if ( c2 < boardH[cb] ) {
			// make sure its facing up?
			index = board[cb][c2][0];

			printf ( "board[%d][%d][0]: %d\n", cb, c2, board[cb][c2][0] );

		} else {
			printf ( "cursor glitch\n" );
		}
	}
	return index;
}

// return 1 if the card can be merged onto the other.
// only run if i am clicking on the bottom (top?) of a stack.
int stack_merge ( int c, int c2, int i, int i2 ) {
	printf ( "stack_merge ( )\n" );

	// c is cursor, i is where u clicked.

	printf ( "(c: %d), (c2: %d)\n", c, c2 );
	printf ( "(i: %d), (i2: %d)\n", i, i2 );

	// index relative to the board.
	int cb = c - boardOffset;
	int ib = i - boardOffset;


	// cursor
	int cursor_index = cursor_to_index ( c, c2 );
//	int cursor_index = board_to_index ( cb, c2 );

	printf ( "cursor_index: %d\n", cursor_index );

/// this function is a mess, clean it up.

	// checks to see where i am clicking.

	int click_index = -1;
	if ( ib >= 0 && ib < 7 ) {
		// the board is selected.
		if ( boardH[ib] == 0 ) {

			printf ( "click on empty board slot\n" );

			// this board space is blank, so only be able to move a king in.
			int cn = cursor_index % 13;

			printf ( "cn: %d\n", cn );

			if ( cn == 12 ) {
				// confirms my cursor is selecting a king.

				if ( c == 1 ) {
					// move from hand

					board[ib][0][0] = cursor_index;
					board[ib][0][1] = 0;	// only necessary if im doing a debug setup.
					boardH[ib] += 1;
					remove_hand ( );

				} else if ( cb >= 0 && cb < 7 ) {
					// move from board
					stack_copy ( cb, c2, ib, -1 );
				}

				return 1;
			}
			return 0;

		} else if ( i2 < boardH[ib] ) {
			// make sure its facing up?
			click_index = board[ib][i2][0];

		} else {
			printf ( "click glitch\n" );
		}
	}

	printf ( "click_index: %d\n", click_index );


	// my cursor was on the hand.
	if ( c == 1 ) {
		if ( stockTop > 0 ) {
			// the hand is selected
			int handIndex = stock[stockTop - 1];
			say_card_index ( handIndex );

			int canMove = move_check ( click_index, handIndex );

//			printf ( "canMove: %d\n", canMove );

			if ( canMove ) {
				// remove this fromthe stock, add it to the clicked stack.
				board[ib][boardH[ib]][0] = handIndex;
				board[ib][boardH[ib]][1] = 0;
				boardH[ib] += 1;

				remove_hand ( );
			}
		}

		return 0;
	}


	/// check the board

	printf ( "cursor_index: %d\n", cursor_index );



	int ret = stack_move ( click_index, cursor_index, cb, c2, ib, i2 );
	return ret;
}

void remove_hand ( ) {
				int i = stockTop - 1;
				while ( i < stockLen ) {
					stock[i] = stock[i + 1];
					i += 1;
				}
				stockLen -= 1;
				stockTop -= 1;
}

// returns 1 if they are of different color, and click number is 1 greater than cursor number.
// rename to move_check_board
int move_check ( int click_index, int cursor_index ) {

	int cs = cursor_index / 13;
	int cn = cursor_index % 13;
	int cColor = cs % 2;

	int is = click_index / 13;
	int in = click_index % 13;
	int iColor = is % 2;

	if ( iColor != cColor ) {
		printf ( "color mismatch\n" );

		if ( cn == in - 1 ) {
			return 1;
		}
	}
	return 0;
}

// move check foundation.
int move_check_found ( int click_index, int cursor_index ) {

	int cs = cursor_index / 13;
	int cn = cursor_index % 13;

	int is = click_index / 13;
	int in = click_index % 13;


	if ( cs == is ) {
		printf ( "color mismatch\n" );

		if ( cn == in - 1 ) {
			return 1;
		}
	}
	return 0;
}

// does this already make sure im clicking on the top of the stack?
// checks if cards can be moved
int stack_move ( int click_index, int cursor_index, int cb, int c2, int ib, int i2 ) {

	int cs = cursor_index / 13;
	int cn = cursor_index % 13;
	int cColor = cs % 2;

	int is = click_index / 13;
	int in = click_index % 13;
	int iColor = is % 2;

	printf ( "cursor n: %d\n", cn );
	printf ( "click n: %d\n", in );

	if ( iColor != cColor ) {
		printf ( "color mismatch\n" );

		if ( cn == in - 1 ) {
			printf ( "cursor is 1 lower than the click\n" );
			printf ( "cb: %d\n", cb );

			if ( cb >= 7 ) {
				// a foundation card is selected.
				int fi = cb-7;	// foundation index, should be cf as in cursor foundation, rn i have cb, cursor board
				board[ib][i2+1][0] = fi * 13 + foundation[fi];
				board[ib][i2+1][0] = 0;	// make sure its face up
				boardH[ib] += 1;
				foundation[fi] -= 1;
			} else {
				// a board card is selected

				// its good, the cursor card can eb moved to the clicked card.

				// move the click stack to the cursor stack.
				stack_copy ( cb, c2, ib, i2 );
			}

			return 1;
		}
	}

	return 0;
}

// moves cards from 1 board spot to another,
void stack_copy ( int cb, int c2, int ib, int i2 ) {
	printf ( "stack_copy ( )\n" );
	printf ( "click (%d, %d)\n", cb, c2 );
	printf ( "cursor (%d, %d)\n", ib, i2 );

	// stack copy
	int j = 0;
	int len = boardH[cb] - c2;

	printf ( "boardH[cb]: %d\n", boardH[cb] );
	printf ( "len: %d\n", len );

	while ( j < len ) {
		board[ib][i2 + j + 1][0] = board[cb][c2 + j][0];
		board[ib][i2 + j + 1][1] = 0;

		j += 1;
	}
	boardH[cb] -= len;
	boardH[ib] += len;

	// if the stack removed from isnt empty
	// make sure the bottom card is face up.
	if ( boardH[cb] > 0 ) {
		board[cb][boardH[cb]-1][1] = 0;
	}
}

/// Other Functions

char *suite_to_string ( int i ) {
	if ( i == 0 ) {
		return "spade";
	} else if ( i == 1 ) {
		return "heart";
	} else if ( i == 2 ) {
		return "club";
	} else if ( i == 3 ) {
		return "diamond";
	}
	return "(out of range)";
}

char numBuffer[24];
char *num_to_string ( int i ) {
	if ( i < 0 ) {
	} else if ( i == 0 ) {
		return "ace";
	} else if ( i < 10 ) {
		sprintf ( numBuffer, "%d", (i+1) );
		return numBuffer;
	} else if ( i == 10 ) {
		return "jack";
	} else if ( i == 11 ) {
		return "queen";
	} else if ( i == 12 ) {
		return "king";
	}
	return "(out of range)";
}

void card_render_index ( int *screenDims, GLuint *glBuffers, int *XYWHpass, int val[] ) {
	if ( val[1] == 0 ) {
		int s = val[0] / 13;
		int n = val[0] % 13;

//		printf ( "val[0]: %d\n", val[0] );
//		printf ( "(s: %d) (n: %d)\n", s, n );

/*
		char *suite = suite_to_string ( s );
		char *num = num_to_string ( n );

		card_render ( screenDims, glBuffers, XYWHpass, num, suite );
*/

		card_render ( screenDims, glBuffers, XYWHpass, n, s );
	} else if ( val[1] == 1 ) {
		card_render_back ( screenDims, glBuffers, XYWHpass, NULL );
	}
}

//void card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data ) {
//void card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, char *num, char *suite ) {
void card_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, int n, int s ) {
//	printf ( "card_render ( )\n" );

	struct jalbFont *font = fonts[0];

	if ( s % 2 == 0 ) {
		draw2dApi->fillRect ( XYWHpass, colorGray, screenDims, glBuffers );
	} else {
		draw2dApi->fillRect ( XYWHpass, colorDRed, screenDims, glBuffers );
	}

	char *suite = suite_to_string ( s );
	char *num = num_to_string ( n );

	draw2dApi->drawRect ( XYWHpass, colorBlack, screenDims, glBuffers );

	int margin = 10;

	int XYWH[4] = {
		XYWHpass[0] + margin,
		XYWHpass[1] + margin,
		XYWHpass[2],
		XYWHpass[3],
	};

//	char *num = "number";
	int numLen = strlen ( num );

//	char *suite = "suite";
	int suiteLen = strlen ( suite );

	draw2dApi->drawCharPre ( font, colorWhite );
	// top number
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, num );

	// top suit
	XYWH[1] += font->atlasInfo.glyphH;
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, suite );

	// shift to bottom
	XYWH[1] = XYWHpass[1] + XYWHpass[3];
	XYWH[1] -= margin + font->atlasInfo.glyphH * 2;

	// bottom suits
	XYWH[0] = XYWHpass[0] + XYWHpass[2];
	XYWH[0] -= margin + suiteLen * font->atlasInfo.glyphW;
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, suite );

	// bottom number
	XYWH[1] += font->atlasInfo.glyphH;
	XYWH[0] = XYWHpass[0] + XYWHpass[2];
	XYWH[0] -= margin + numLen * font->atlasInfo.glyphW;
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, font, num );
}

void card_render_back ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data ) {
	draw2dApi->fillRect ( XYWHpass, colorOrange, screenDims, glBuffers );
	draw2dApi->drawRect ( XYWHpass, colorBlack, screenDims, glBuffers );
}


void say_card_index ( int i ) {
//	printf ( "say_card_index ( )\n" );
//	printf ( "i: %d\n", i );

	int s = i / 13;
	int n = i % 13;

	char *suite = suite_to_string ( s );
	char *num = num_to_string ( n );

	printf ( "%s of %s\n", num, suite );
}







/** Ai */

void find_move ( ) {
	// 1 iterate board (bottom) looking for anything to add to foundation.
	// 2 iterate board, look at the top of each stack to see if they can get moved to the bottom of any other stacks.
	// 3 iterate the hand, looking to add to foundation or bottom of board stacks.

	// if i see multiple potential moves at some, idk how i would determine which is priority.

}


