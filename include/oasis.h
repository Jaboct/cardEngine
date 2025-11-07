#pragma once

/** AUTO GENERATED CODE */

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalb/jalbSay.h>

#include <jalb/jfile.h>
#include <jalb/jalb_addCanvas.h>
#include <jalbDraw/drawCutString.h>

#include <jalbXml/jalbXml_02.h>



void oasis_preInit ( );




/** Structs */

struct card {
	int id;
	int mana;
	int type;
	union  {
		struct minionBase *minion;
		struct spell *spell;
	};
};

enum cardEnum {
	Minion = 0,
	Spell,
};
struct cardBase {
	char name[256];
	struct card *card;
};

struct cardMod {
	// 0 taunt
	// 1 heal?
	// 2 damage?
	int type;
	char name[256];
};

struct oasis_game {
	// 0 = in a lobby,
	// 1 = in a game
	int oasis_stage;
	// 0 = first pick 3,
	// 1 = second pick 3 (if there is one)
	// 2, about to start game (hit play button?)
	int lobby_stage;
	// just keeps track of many bosses you have beat
	int oasis_round;
	// 0 player,
	// 1 enemy
	int oasis_turn;
	struct player *enemy;
	struct player *player;
};

struct spell {
	int type;
	struct targeting *tar;
	ArrayList *effList;	// (struct spellEffect*)
	char modName[256];
	int discard;
};

struct targeting {
	// 0: ally, 1: enemy, 2: either/both
	int side;
	// 0: champ(s), 1: minions, 2: both, 3: random
	int who;
	// 0, everyone, 1+ that many targets
	int count;
};

struct spellEffect {
	int type;
	int heal;
	int dmg;
};

struct minionBase {
	int attack;
	int health;
	ArrayList *mods;	// (struct cardMod*)
	// -1 if i just played the card this turn.
	// -2 is not played yet (in hand)
	// at the start of each turn iterate through and set to 0.
	// then i need to stop attacking at 1 normally, 2 windfury, etc.
	// actually i think i want this to be the number of re
	int numAttacks;
};

struct player {
	ArrayList *deck;	// (struct card*)
	ArrayList *deckTotal;	// (struct card*)
	struct card *hand[10];
	struct card *board[7];
	int health;
	int mana;
	int manaMax;
	int fatigue;
};

struct pick3 {
	char name[256];
	int cards[3];
};



/** Post Includes */


/** Functions */

/** card */
struct card *cardInit ( );
void cardFill ( struct card *var );
void cardTypeChange0 ( struct card *var, int type );
void *cardInitMask ( );
void cardClose ( struct card *var );
void cardBodyToVal ( void *varPass, int nameI, char *body );
int cardNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cardBase */
struct cardBase *cardBaseInit ( );
void cardBaseFill ( struct cardBase *var );
void *cardBaseInitMask ( );
void cardBaseClose ( struct cardBase *var );
void cardBaseBodyToVal ( void *varPass, int nameI, char *body );
int cardBaseNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cardMod */
struct cardMod *cardModInit ( );
void cardModFill ( struct cardMod *var );
void *cardModInitMask ( );
void cardModClose ( struct cardMod *var );
void cardModBodyToVal ( void *varPass, int nameI, char *body );
int cardModNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** oasis_game */
struct oasis_game *oasis_gameInit ( );
void oasis_gameFill ( struct oasis_game *var );
void *oasis_gameInitMask ( );
void oasis_gameClose ( struct oasis_game *var );
void oasis_gameBodyToVal ( void *varPass, int nameI, char *body );
int oasis_gameNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** spell */
struct spell *spellInit ( );
void spellFill ( struct spell *var );
void *spellInitMask ( );
void spellClose ( struct spell *var );
void spellBodyToVal ( void *varPass, int nameI, char *body );
int spellNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** targeting */
struct targeting *targetingInit ( );
void targetingFill ( struct targeting *var );
void *targetingInitMask ( );
void targetingClose ( struct targeting *var );
void targetingBodyToVal ( void *varPass, int nameI, char *body );
int targetingNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** spellEffect */
struct spellEffect *spellEffectInit ( );
void spellEffectFill ( struct spellEffect *var );
void *spellEffectInitMask ( );
void spellEffectClose ( struct spellEffect *var );
void spellEffectBodyToVal ( void *varPass, int nameI, char *body );
int spellEffectNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** minionBase */
struct minionBase *minionBaseInit ( );
void minionBaseFill ( struct minionBase *var );
void *minionBaseInitMask ( );
void minionBaseClose ( struct minionBase *var );
void minionBaseBodyToVal ( void *varPass, int nameI, char *body );
int minionBaseNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** player */
struct player *playerInit ( );
void playerFill ( struct player *var );
void *playerInitMask ( );
void playerClose ( struct player *var );
void playerBodyToVal ( void *varPass, int nameI, char *body );
int playerNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** pick3 */
struct pick3 *pick3Init ( );
void pick3Fill ( struct pick3 *var );
void *pick3InitMask ( );
void pick3Close ( struct pick3 *var );
void pick3BodyToVal ( void *varPass, int nameI, char *body );
int pick3NameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
