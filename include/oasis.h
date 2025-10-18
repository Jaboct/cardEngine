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


struct spell {
	int type;
	struct targeting *tar;
	struct spellEffect *eff;
};

struct spellEffect {
	int type;
	int heal;
	int dmg;
	ArrayList *mods;	// ( struct cardMod*)
};


struct card {
	int id;
	int mana;

	int type;
	union {
		struct {
			int attack;
			int health;
			ArrayList *mods;
			int numAttacks;
		};
		struct spell *spell;
	};
};

struct cardBase {
	int id;

	char name[256];
	int mana;

	int type;
	union {
		struct {
			int attack;
			int health;
			ArrayList *modifiers;	// (struct cardMod*)
		};
		struct spell *spell;
	};
};

struct cardMod {
	int type;
	// 0 taunt
	// 1 heal?
	// 2 damage?
};






struct minionBase {
	int attack;
	int health;
	ArrayList *mods;

	int numAttacks;	// -1 if i just played the card this turn.
			// -2 is not played yet (in hand)
			// at the start of each turn iterate through and set to 0.
			// then i need to stop attacking at 1 normally, 2 windfury, etc.
			// actually i think i want this to be the number of remaining attacks
};

struct cardB {
	int id;

	char name[256];
	int mana;

	int type;
	union {
		struct minionBase *minion;
		struct spell *spell;
	};
};





/** Post Includes */


/** Functions */

/** card */
struct card *cardInit ( );
void cardFill ( struct card *var );
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

/** Other Functs */
