#include "oasis_event.h"


/** Includes */

#include "card_util.h"
#include "oasis.h"
#include "oasis_hand.h"


/** Variables */


extern struct player *player;
extern struct player *enemy;


extern int oasis_cursor;

int oasis_cursor_hand = 1;
int oasis_cursor_board = 1 + HAND_MAX;
int oasis_cursor_board_end = 1 + HAND_MAX + BOARD_MAX - 1;


/// Event

/// DOM externs
extern int cardW;
extern int cardH;

extern int cardGap;	// px between each card.
extern int highlightMargin;

extern int playerCharWH[];

// relevent elements.
extern int playerCharXY[];
extern int enemyCharXY[];

extern int playerHandXY[];
extern int enemyHandXY[];

extern int playerBoardXY[];
extern int enemyBoardXY[];


/** Functions */

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

// what area am i clicking in.
// rn just try to player a spell to board[0]
// break clicking into a few areas.
// for spells: am i clicking on a minion
// for minions, am i clicking, idk lets call it left or right of a card (including on the card, split 50% of the way throught it horizontally)

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

	// check the enemy character
	int charRect[4] = {
		enemyCharXY[0],
		enemyCharXY[1],
		playerCharWH[0],
		playerCharWH[1],
	};
	if ( inBox ( clickXY, charRect ) ) {
		// if the card i have selected is on my board
		if ( oasis_cursor >= oasis_cursor_board &&
		     oasis_cursor <= oasis_cursor_board_end ) {
			// then deal dmg
			int attackIndex = oasis_cursor - oasis_cursor_board;

			struct card *attackCard = player->board[attackIndex];

			enemy->health -= attackCard->attack;
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

	if ( handCard->type == 0 ) {
		player->mana -= handCard->mana;
		player->board[boardLen] = player->hand[handI];
		player->board[boardLen]->numAttacks = -1;	// -1 means sleeping cuz it was just played
	} else if ( handCard->type == 1 ) {
		// spell.
		// TODO, figure which minion i apply this to.
		if ( boardLen > 0 ) {
			player->mana -= handCard->mana;
			struct card *minion = player->board[0];
			apply_spell_minion ( handCard, minion );
		}
	}

	shrink_array ( player->hand, handI, HAND_MAX );

	printf ( "play_hand_to_board ( ) OVER\n" );
}

void apply_spell_minion ( struct card *spell, struct card *minion ) {
	minion->health += 2;

	// TODO handle spell better
	struct cardMod *mod = malloc ( sizeof ( *mod ) );
	mod->type = 1;
	arrayListAddEndPointer ( minion->mods, mod );
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

	if ( attackCard->numAttacks > 0 ) {
		attackCard->numAttacks -= 1;
	} else {
		return;
	}

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


