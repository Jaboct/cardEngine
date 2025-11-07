#include "oasis.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void oasis_preInit ( ) {
}


extern int cardEditId;
extern int cardBaseEditId;
extern int cardModEditId;
extern int oasis_gameEditId;
extern int spellEditId;
extern int targetingEditId;
extern int spellEffectEditId;
extern int minionBaseEditId;
extern int playerEditId;
extern int pick3EditId;
extern int debugPrint_projectName_init;


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_card;
extern struct backbone_structStruct backboneStru_cardBase;
extern struct backbone_structStruct backboneStru_cardMod;
extern struct backbone_structStruct backboneStru_oasis_game;
extern struct backbone_structStruct backboneStru_spell;
extern struct backbone_structStruct backboneStru_targeting;
extern struct backbone_structStruct backboneStru_spellEffect;
extern struct backbone_structStruct backboneStru_minionBase;
extern struct backbone_structStruct backboneStru_player;
extern struct backbone_structStruct backboneStru_pick3;

/** Functions */

/** card */

struct card *cardInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cardInit ( )\n" );
	}
	struct card *var = malloc ( sizeof ( struct card ) );
	cardFill ( var );
	return var;
}
void cardFill ( struct card *var ) {
	var->id = 0;
	var->mana = 0;
	var->type = -1;
//	cardTypeChange0 ( var, 0 );
}
void cardTypeChange0 ( struct card *var, int type ) {
	if ( var->type == type ) {
		return;
	}
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	}
	if ( type == 0 ) {
		var->minion = minionBaseInit ( );
	} else if ( type == 1 ) {
		var->spell = spellInit ( );
	}
	var->type = type;
}


void *cardInitMask ( ) {
	void *ret = cardInit ( );
	return ret;

}
void cardClose ( struct card *var ) {
	if ( var->type == 0 ) {
		if ( var->minion ) {
			minionBaseClose ( var->minion );
		}
	} else if ( var->type == 1 ) {
		if ( var->spell ) {
			spellClose ( var->spell );
		}
	}
	free ( var );

}
int card_attrib_arr[] = {
	0,
	0,
	0,
};
void cardBodyToVal ( void *varPass, int nameI, char *body ) {

	struct card *var = varPass;

	if ( nameI == 0 ) {
		var->id = atoi ( body );
	} else if ( nameI == 1 ) {
		var->mana = atoi ( body );
	} else if ( nameI == 2 ) {
		if ( var->type == 0 ) {
			// wont get called?
		} else if ( var->type == 1 ) {
			// wont get called?
		}
	}
}

int cardNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct card *var = data;
	if ( strcmp ( body, "id" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "mana" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "minion" ) == 0 ) {
		cardTypeChange0 ( var, 0 );
		*strPtr = "minionBase";
		void **retPtr = ret;
		*retPtr = &var->minion;
		return jxnPtr;
	} else if ( strcmp ( body, "spell" ) == 0 ) {
		cardTypeChange0 ( var, 1 );
		*strPtr = "spell";
		void **retPtr = ret;
		*retPtr = &var->spell;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts cardXml = {
	.typeName = "card",
	.init = cardInitMask,
	.nameToIndex = cardNameToIndex,
	.bodyToVal = cardBodyToVal,
	.typeChange = (void (*) (void*, int))cardTypeChange0,
};

void card_print ( struct card *stru ) {
	printf ( "card_print ( )\n" );
}
/** cardBase */

struct cardBase *cardBaseInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cardBaseInit ( )\n" );
	}
	struct cardBase *var = malloc ( sizeof ( struct cardBase ) );
	cardBaseFill ( var );
	return var;
}
void cardBaseFill ( struct cardBase *var ) {
	var->name[0] = '\0';
	var->card = cardInit ( );
}

void *cardBaseInitMask ( ) {
	void *ret = cardBaseInit ( );
	return ret;

}
void cardBaseClose ( struct cardBase *var ) {
	if ( var->card ) {
		cardClose ( var->card );
	}
	free ( var );

}
int cardBase_attrib_arr[] = {
	0,
	0,
};
void cardBaseBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cardBase *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->name, body );
	} else if ( nameI == 1 ) {
		// wont get called?
	}
}

int cardBaseNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct cardBase *var = data;
	if ( strcmp ( body, "name" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "card" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->card;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts cardBaseXml = {
	.typeName = "cardBase",
	.init = cardBaseInitMask,
	.nameToIndex = cardBaseNameToIndex,
	.bodyToVal = cardBaseBodyToVal,
};

void cardBase_print ( struct cardBase *stru ) {
	printf ( "cardBase_print ( )\n" );
}
/** cardMod */

struct cardMod *cardModInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cardModInit ( )\n" );
	}
	struct cardMod *var = malloc ( sizeof ( struct cardMod ) );
	cardModFill ( var );
	return var;
}
void cardModFill ( struct cardMod *var ) {
	var->type = 0;
	var->name[0] = '\0';
}

void *cardModInitMask ( ) {
	void *ret = cardModInit ( );
	return ret;

}
void cardModClose ( struct cardMod *var ) {
	free ( var );

}
int cardMod_attrib_arr[] = {
	0,
	0,
};
void cardModBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cardMod *var = varPass;

	if ( nameI == 0 ) {
		var->type = atoi ( body );
	} else if ( nameI == 1 ) {
		strcpy ( var->name, body );
	}
}

int cardModNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "type" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "name" ) == 0 ) {
		return 1;
	}
	return -1;
}

struct xmlFuncts cardModXml = {
	.typeName = "cardMod",
	.init = cardModInitMask,
	.nameToIndex = cardModNameToIndex,
	.bodyToVal = cardModBodyToVal,
};

void cardMod_print ( struct cardMod *stru ) {
	printf ( "cardMod_print ( )\n" );
}
/** oasis_game */

struct oasis_game *oasis_gameInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "oasis_gameInit ( )\n" );
	}
	struct oasis_game *var = malloc ( sizeof ( struct oasis_game ) );
	oasis_gameFill ( var );
	return var;
}
void oasis_gameFill ( struct oasis_game *var ) {
	var->oasis_stage = 0;
	var->lobby_stage = 0;
	var->oasis_round = 0;
	var->oasis_turn = 0;
	var->enemy = playerInit ( );
	var->player = playerInit ( );
}

void *oasis_gameInitMask ( ) {
	void *ret = oasis_gameInit ( );
	return ret;

}
void oasis_gameClose ( struct oasis_game *var ) {
	free ( var );

}
int oasis_game_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
void oasis_gameBodyToVal ( void *varPass, int nameI, char *body ) {

	struct oasis_game *var = varPass;

	if ( nameI == 0 ) {
		var->oasis_stage = atoi ( body );
	} else if ( nameI == 1 ) {
		var->lobby_stage = atoi ( body );
	} else if ( nameI == 2 ) {
		var->oasis_round = atoi ( body );
	} else if ( nameI == 3 ) {
		var->oasis_turn = atoi ( body );
	} else if ( nameI == 4 ) {
		// wont get called?
	} else if ( nameI == 5 ) {
		// wont get called?
	}
}

int oasis_gameNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct oasis_game *var = data;
	if ( strcmp ( body, "oasis_stage" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "lobby_stage" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "oasis_round" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "oasis_turn" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "enemy" ) == 0 ) {
		*strPtr = "player";
		void **retPtr = ret;
		*retPtr = &var->enemy;
		return jxnPtr;
	} else if ( strcmp ( body, "player" ) == 0 ) {
		*strPtr = "player";
		void **retPtr = ret;
		*retPtr = &var->player;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts oasis_gameXml = {
	.typeName = "oasis_game",
	.init = oasis_gameInitMask,
	.nameToIndex = oasis_gameNameToIndex,
	.bodyToVal = oasis_gameBodyToVal,
};

void oasis_game_print ( struct oasis_game *stru ) {
	printf ( "oasis_game_print ( )\n" );
}
/** spell */

struct spell *spellInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "spellInit ( )\n" );
	}
	struct spell *var = malloc ( sizeof ( struct spell ) );
	spellFill ( var );
	return var;
}
void spellFill ( struct spell *var ) {
	var->type = 0;
	var->tar = targetingInit ( );
	var->effList = initArrayList ( 10, sizeof ( struct spellEffect* ), 10 );
	var->modName[0] = '\0';
	var->discard = 0;
}

void *spellInitMask ( ) {
	void *ret = spellInit ( );
	return ret;

}
void spellClose ( struct spell *var ) {
	if ( var->effList ) {
		freeArrayListPointerFunction ( var->effList, (void (*)(void*))spellEffectClose );
	}
	free ( var );

}
int spell_attrib_arr[] = {
	0,
	0,
	0,
	0,
};
void spellBodyToVal ( void *varPass, int nameI, char *body ) {

	struct spell *var = varPass;

	if ( nameI == 0 ) {
		var->type = atoi ( body );
	} else if ( nameI == 1 ) {
		// wont get called?
	} else if ( nameI == 2 ) {
	} else if ( nameI == 3 ) {
		strcpy ( var->modName, body );
	}
}

int spellNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct spell *var = data;
	if ( strcmp ( body, "type" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "tar" ) == 0 ) {
		*strPtr = "targeting";
		void **retPtr = ret;
		*retPtr = &var->tar;
		return jxnPtr;
	} else if ( strcmp ( body, "effList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->effList;
		return jxnAlPtr;
	} else if ( strcmp ( body, "modName" ) == 0 ) {
		return 3;
	}
	return -1;
}

struct xmlFuncts spellXml = {
	.typeName = "spell",
	.init = spellInitMask,
	.nameToIndex = spellNameToIndex,
	.bodyToVal = spellBodyToVal,
};

void spell_print ( struct spell *stru ) {
	printf ( "spell_print ( )\n" );
}
/** targeting */

struct targeting *targetingInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "targetingInit ( )\n" );
	}
	struct targeting *var = malloc ( sizeof ( struct targeting ) );
	targetingFill ( var );
	return var;
}
void targetingFill ( struct targeting *var ) {
	var->side = 0;
	var->who = 0;
	var->count = 0;
}

void *targetingInitMask ( ) {
	void *ret = targetingInit ( );
	return ret;

}
void targetingClose ( struct targeting *var ) {
	free ( var );

}
int targeting_attrib_arr[] = {
	0,
	0,
	0,
};
void targetingBodyToVal ( void *varPass, int nameI, char *body ) {

	struct targeting *var = varPass;

	if ( nameI == 0 ) {
		var->side = atoi ( body );
	} else if ( nameI == 1 ) {
		var->who = atoi ( body );
	} else if ( nameI == 2 ) {
		var->count = atoi ( body );
	}
}

int targetingNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "side" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "who" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "count" ) == 0 ) {
		return 2;
	}
	return -1;
}

struct xmlFuncts targetingXml = {
	.typeName = "targeting",
	.init = targetingInitMask,
	.nameToIndex = targetingNameToIndex,
	.bodyToVal = targetingBodyToVal,
};

void targeting_print ( struct targeting *stru ) {
	printf ( "targeting_print ( )\n" );
}
/** spellEffect */

struct spellEffect *spellEffectInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "spellEffectInit ( )\n" );
	}
	struct spellEffect *var = malloc ( sizeof ( struct spellEffect ) );
	spellEffectFill ( var );
	return var;
}
void spellEffectFill ( struct spellEffect *var ) {
	var->type = 0;
	var->heal = 0;
	var->dmg = 0;
}

void *spellEffectInitMask ( ) {
	void *ret = spellEffectInit ( );
	return ret;

}
void spellEffectClose ( struct spellEffect *var ) {
	free ( var );

}
int spellEffect_attrib_arr[] = {
	0,
	0,
	0,
};
void spellEffectBodyToVal ( void *varPass, int nameI, char *body ) {

	struct spellEffect *var = varPass;

	if ( nameI == 0 ) {
		var->type = atoi ( body );
	} else if ( nameI == 1 ) {
		var->heal = atoi ( body );
	} else if ( nameI == 2 ) {
		var->dmg = atoi ( body );
	}
}

int spellEffectNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "type" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "heal" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "dmg" ) == 0 ) {
		return 2;
	}
	return -1;
}

struct xmlFuncts spellEffectXml = {
	.typeName = "spellEffect",
	.init = spellEffectInitMask,
	.nameToIndex = spellEffectNameToIndex,
	.bodyToVal = spellEffectBodyToVal,
};

void spellEffect_print ( struct spellEffect *stru ) {
	printf ( "spellEffect_print ( )\n" );
}
/** minionBase */

struct minionBase *minionBaseInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "minionBaseInit ( )\n" );
	}
	struct minionBase *var = malloc ( sizeof ( struct minionBase ) );
	minionBaseFill ( var );
	return var;
}
void minionBaseFill ( struct minionBase *var ) {
	var->attack = 0;
	var->health = 0;
	var->mods = initArrayList ( 10, sizeof ( struct cardMod* ), 10 );
	var->numAttacks = 0;
}

void *minionBaseInitMask ( ) {
	void *ret = minionBaseInit ( );
	return ret;

}
void minionBaseClose ( struct minionBase *var ) {
	if ( var->mods ) {
		freeArrayListPointerFunction ( var->mods, (void (*)(void*))cardModClose );
	}
	free ( var );

}
int minionBase_attrib_arr[] = {
	0,
	0,
	0,
	0,
};
void minionBaseBodyToVal ( void *varPass, int nameI, char *body ) {

	struct minionBase *var = varPass;

	if ( nameI == 0 ) {
		var->attack = atoi ( body );
	} else if ( nameI == 1 ) {
		var->health = atoi ( body );
	} else if ( nameI == 2 ) {
	} else if ( nameI == 3 ) {
		var->numAttacks = atoi ( body );
	}
}

int minionBaseNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct minionBase *var = data;
	if ( strcmp ( body, "attack" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "health" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "mods" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->mods;
		return jxnAlPtr;
	} else if ( strcmp ( body, "numAttacks" ) == 0 ) {
		return 3;
	}
	return -1;
}

struct xmlFuncts minionBaseXml = {
	.typeName = "minionBase",
	.init = minionBaseInitMask,
	.nameToIndex = minionBaseNameToIndex,
	.bodyToVal = minionBaseBodyToVal,
};

void minionBase_print ( struct minionBase *stru ) {
	printf ( "minionBase_print ( )\n" );
}
/** player */

struct player *playerInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "playerInit ( )\n" );
	}
	struct player *var = malloc ( sizeof ( struct player ) );
	playerFill ( var );
	return var;
}
void playerFill ( struct player *var ) {
	var->deck = initArrayList ( 10, sizeof ( struct card* ), 10 );
	var->deckTotal = initArrayList ( 10, sizeof ( struct card* ), 10 );
	var->hand[0] = NULL;
	var->hand[1] = NULL;
	var->hand[2] = NULL;
	var->hand[3] = NULL;
	var->hand[4] = NULL;
	var->hand[5] = NULL;
	var->hand[6] = NULL;
	var->hand[7] = NULL;
	var->hand[8] = NULL;
	var->hand[9] = NULL;

	var->board[0] = NULL;
	var->board[1] = NULL;
	var->board[2] = NULL;
	var->board[3] = NULL;
	var->board[4] = NULL;
	var->board[5] = NULL;
	var->board[6] = NULL;

	var->health = 0;
	var->mana = 0;
	var->manaMax = 0;
	var->fatigue = 0;
}

void *playerInitMask ( ) {
	void *ret = playerInit ( );
	return ret;

}
void playerClose ( struct player *var ) {
	if ( var->deck ) {
		freeArrayListPointerFunction ( var->deck, (void (*)(void*))cardClose );
	}
	if ( var->deckTotal ) {
		freeArrayListPointerFunction ( var->deckTotal, (void (*)(void*))cardClose );
	}
/*
	if ( var->hand ) {
		cardClose ( var->hand );
	}
	if ( var->board ) {
		cardClose ( var->board );
	}
*/

	free ( var );

}
int player_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
void playerBodyToVal ( void *varPass, int nameI, char *body ) {

	struct player *var = varPass;

	if ( nameI == 0 ) {
	} else if ( nameI == 1 ) {
	} else if ( nameI == 2 ) {
		// wont get called?
	} else if ( nameI == 12 ) {
		// wont get called?
	} else if ( nameI == 19 ) {
		var->health = atoi ( body );
	} else if ( nameI == 20 ) {
		var->mana = atoi ( body );
	} else if ( nameI == 21 ) {
		var->manaMax = atoi ( body );
	} else if ( nameI == 22 ) {
		var->fatigue = atoi ( body );
	}
}

int playerNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct player *var = data;
	if ( strcmp ( body, "deck" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->deck;
		return jxnAlPtr;
	} else if ( strcmp ( body, "deckTotal" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->deckTotal;
		return jxnAlPtr;
	} else if ( strcmp ( body, "hand[0]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[0];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[1]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[1];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[2]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[2];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[3]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[3];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[4]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[4];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[5]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[5];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[6]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[6];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[7]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[7];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[8]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[8];
		return jxnPtr;
	} else if ( strcmp ( body, "hand[9]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->hand[9];
		return jxnPtr;
	} else if ( strcmp ( body, "board[0]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->board[0];
		return jxnPtr;
	} else if ( strcmp ( body, "board[1]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->board[1];
		return jxnPtr;
	} else if ( strcmp ( body, "board[2]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->board[2];
		return jxnPtr;
	} else if ( strcmp ( body, "board[3]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->board[3];
		return jxnPtr;
	} else if ( strcmp ( body, "board[4]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->board[4];
		return jxnPtr;
	} else if ( strcmp ( body, "board[5]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->board[5];
		return jxnPtr;
	} else if ( strcmp ( body, "board[6]" ) == 0 ) {
		*strPtr = "card";
		void **retPtr = ret;
		*retPtr = &var->board[6];
		return jxnPtr;
	} else if ( strcmp ( body, "health" ) == 0 ) {
		return 19;
	} else if ( strcmp ( body, "mana" ) == 0 ) {
		return 20;
	} else if ( strcmp ( body, "manaMax" ) == 0 ) {
		return 21;
	} else if ( strcmp ( body, "fatigue" ) == 0 ) {
		return 22;
	}
	return -1;
}

struct xmlFuncts playerXml = {
	.typeName = "player",
	.init = playerInitMask,
	.nameToIndex = playerNameToIndex,
	.bodyToVal = playerBodyToVal,
};

void player_print ( struct player *stru ) {
	printf ( "player_print ( )\n" );
}
/** pick3 */

struct pick3 *pick3Init ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "pick3Init ( )\n" );
	}
	struct pick3 *var = malloc ( sizeof ( struct pick3 ) );
	pick3Fill ( var );
	return var;
}
void pick3Fill ( struct pick3 *var ) {
	var->name[0] = '\0';
	var->cards[0] = 0;
	var->cards[1] = 0;
	var->cards[2] = 0;

}

void *pick3InitMask ( ) {
	void *ret = pick3Init ( );
	return ret;

}
void pick3Close ( struct pick3 *var ) {
	free ( var );

}
int pick3_attrib_arr[] = {
	0,
	0,
};
void pick3BodyToVal ( void *varPass, int nameI, char *body ) {

	struct pick3 *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->name, body );
	} else if ( nameI == 1 ) {
		consumeStdArr ( body, 0, 1, var->cards, 3 );
	}
}

int pick3NameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "name" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "cards" ) == 0 ) {
		return 1;
	}
	return -1;
}

struct xmlFuncts pick3Xml = {
	.typeName = "pick3",
	.init = pick3InitMask,
	.nameToIndex = pick3NameToIndex,
	.bodyToVal = pick3BodyToVal,
};

void pick3_print ( struct pick3 *stru ) {
	printf ( "pick3_print ( )\n" );
}
/** Other Functs */
