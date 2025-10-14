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
	int attack;
	int health;
	int mana;
};

struct cardBase {
	int id;
	char name[256];
	int attack;
	int health;
	ArrayList *modifiers;	// (struct cardMod*)
	int mana;
};

struct cardMod {
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
