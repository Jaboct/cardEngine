#include "oasis_event.h"


/** Includes */

#include "card_util.h"
#include "oasis.h"
#include "oasis_hand.h"


/** Variables */


//extern struct player *player;
//extern struct player *enemy;


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


extern struct oasis_game *glob_oasis;


/** Functions */

int oasis_game_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	printf ( "oasis_game_event ( )\n" );


	struct oasis_game *game = glob_oasis;
	struct player *player = game->player;
	struct player *enemy = game->enemy;


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

		int clickZone = get_clickZone ( clickXY, fullBoard );
		printf ( "clickZone: %d\n", clickZone );

		if ( oasis_cursor >= oasis_cursor_hand &&
		     oasis_cursor < oasis_cursor_board ) {
			// hand is selected, try to play to board.
			printf ( "hand is selected, try to play to board.\n" );

// what area am i clicking in.
// rn just try to player a spell to board[0]
// break clicking into a few areas.
// for spells: am i clicking on a minion
// for minions, am i clicking, idk lets call it left or right of a card (including on the card, split 50% of the way throught it horizontally)

			int clickZone = get_clickZone ( clickXY, fullBoard );
			int board = 0;

			play_hand_to_board ( player, oasis_cursor - oasis_cursor_hand, board, clickZone );

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

			enemy->health -= attackCard->minion->attack;
		}
	}

	oasis_cursor = 0;

	return 0;
}

int get_clickZone ( int *clickXYpass, int *fullBoard ) {
	// margin between cards is: cardGap
	// cardWidth is: cardW

	sayIntArray ( "clickXYpass", clickXYpass, 2 );

	int clickXY[2] = {
		clickXYpass[0] - fullBoard[0],
		clickXYpass[1] - fullBoard[1],
	};

	int card = clickXY[0] / (cardW + cardGap);
	clickXY[0] %= (cardW + cardGap);

	sayIntArray ( "clickXY", clickXY, 2 );

	int zone = 0;

	int leftMargin = cardGap + (cardGap / 2);	// gap/2 for the left of the card. gap for the first x px of the card
	int centMargin = (cardW - cardGap) + (cardGap / 2);

	printf ( "leftMargin: %d\n", leftMargin );
	printf ( "centMargin: %d\n", centMargin );

	if ( clickXY[0] < leftMargin ) {
		// its left of the first card
		// zone = 0;
	} else if ( clickXY[0] < centMargin ) {
		zone = 1;
	} else {
		zone = 2;
	}
	zone += card * 3;

	return zone;
}

/// TODO, similar to above.
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
// board: 0 player, 1 enemy.
void play_hand_to_board ( struct player *player, int handI, int board, int clickZone ) {
	printf ( "play_hand_to_board ( )\n" );
	printf ( "clickZone: %d\n", clickZone );

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

	int played = 0;

	if ( handCard->type == Minion ) {
		player->mana -= handCard->mana;
		player->board[boardLen] = player->hand[handI];
		player->board[boardLen]->minion->numAttacks = -1;	// -1 means sleeping cuz it was just played

		played = 1;

	} else if ( handCard->type == Spell ) {
		// spell.
		// TODO, figure which minion i apply this to.

		// zone to minion.
//		int minionIndex = clickZone / 3;

		struct cardBase *base = get_base_id ( handCard->id );

//		printf ( "base->card->spell->discard: %d\n", base->card->spell->discard );

		played = play_spell ( base->card, board, clickZone );
		if ( base->card->spell->discard == discard_shuf_playDeck ) {
			shuffle_into_deck ( handCard, player->deck );
		}
/*
		if ( boardLen > minionIndex ) {
			player->mana -= handCard->mana;
			struct card *minion = player->board[minionIndex];
			apply_spell_minion ( handCard->spell, minion );

			played = 1;
		}
*/
	}

	if ( played ) {
		shrink_array ( player->hand, handI, HAND_MAX );
	}

	printf ( "play_hand_to_board ( ) OVER\n" );
}

void shuffle_into_deck ( struct card *card, ArrayList *deck ) {
	printf ( "shuffle_into_deck ( )\n" );
	int len = arrayListGetLength ( deck );
	printf ( "deck.len: %d\n", len );
	if ( len > 0 ) {
		// if len == 1, %(len+1) = %2, meaning u can have 0 or 1 remainder.
		int r = rand ( ) % (len + 1);
		arrayListAddPointerI ( deck, card, r );
	}
	printf ( "deck.len: %d\n", arrayListGetLength ( deck ) );
}

// board 0 is enemy, 1 is player.
int play_spell ( struct card *card, int board, int clickZone ) {
	printf ( "play_spell ( )\n" );
	printf ( "board: %d\n", board );

	struct oasis_game *game = glob_oasis;

	struct spell *spell = card->spell;
	struct targeting *target = spell->tar;

	printf ( "target: %p\n", target );
	printf ( "target->count: %d\n", target->count );
	printf ( "target->who: %d\n", target->who );
	printf ( "target->side: %d\n", target->side );


	if ( target->count == target_everyone ) {
		printf ( "target everyone\n" );
		if ( target->side == tar_aly ||
		     target->side == tar_either ) {
			// apply to all alies
		}
		if ( target->side == tar_enemy ||
		     target->side == tar_either ) {
			// apply to all enemies.
		}

	} else {
		printf ( "printf target->count == target_num: %d\n", target->count );

		// first see if its randon.
		if ( target->who == tar_rand ) {
			// doesnt matter where i click?
			// well if its tar random enemy do i want to have to click on the enemy board?
			// i dont care.
			printf ( "TODO apply random spell\n" );
		}

		if ( target->side == tar_aly ) {
			printf ( "case on aly\n" );
			if ( board == 0 ) {
				// cast on aly.

				int minionIndex = clickZone / 3;
				int numAlyBoard = get_board_len ( game->player );
printf ( "single target aly\n" );
printf ( "minionIndex: %d\n", minionIndex );
printf ( "numAlyBoard: %d\n", numAlyBoard );



				if ( minionIndex < numAlyBoard ) {
					apply_spell_minion ( spell, game->player->board[minionIndex] );
					return 1;
				}
			}
		} else if ( target->side == tar_enemy ) {
			if ( board == 1 ) {
				// cast on enemy.
			}
		} else if ( target->side == tar_either ) {
			// cast on click
		}
	}
	return 0;
}

void apply_spell_minion ( struct spell *spell, struct card *minion ) {
	printf ( "apply_spell_minion ( )\n" );

	int i = 0;
	int len = arrayListGetLength ( spell->effList );
	while ( i < len ) {
		struct spellEffect *eff = arrayListGetPointer ( spell->effList, i );

		apply_spellEffect_minion ( eff, minion );

		i += 1;
	}

	struct cardMod *mod = cardModInit ( );
	strcpy ( mod->name, spell->modName );

	mod->type = eff_buffHp;
	arrayListAddEndPointer ( minion->minion->mods, mod );


	printf ( "apply_spell_minion ( ) OVER\n" );
}

void apply_spellEffect_minion ( struct spellEffect *eff, struct card *minion ) {
	printf ( "apply_spellEffect_minion ( )\n" );
	printf ( "eff->type: %d\n", eff->type );

	if ( eff->type == eff_buffHp ) {
		minion->minion->health += eff->heal;
//		minion->minion->maxHp += 2;
	} else if ( eff->type == eff_buffAtk ) {
		minion->minion->attack += eff->heal;
		
	} else {
		printf ( "ERROR, apply_spellEffect_minion ( )\n" );
	}

	printf ( "apply_spellEffect_minion ( ) OVER\n" );
}



// i am removing card at arr[i], so shift everything at an index above that, left by 1.
// make sure the final arr[index] is set to null.
// this doenst free, sometimes i will want it to free, othertimes i wont...
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

	struct minionBase *atkMinion = attackCard->minion;
	struct minionBase *defMinion = defendCard->minion;

	// todo, do i need to make sure attackCard->type == minion? one day im sure
	if ( atkMinion->numAttacks > 0 ) {
		atkMinion->numAttacks -= 1;
	} else {
		return;
	}

	// TODO, check for poison, lifesteal, sheild, etc.
	atkMinion->health -= defMinion->attack;
	defMinion->health -= atkMinion->attack;

	if ( atkMinion->health <= 0 ) {
		shrink_array ( attacker->board, attackIndex, BOARD_MAX );
	}
	if ( defMinion->health <= 0 ) {
		shrink_array ( defender->board, defendIndex, BOARD_MAX );
	}
}


