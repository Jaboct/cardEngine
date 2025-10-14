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
	var->attack = 0;
	var->health = 0;
	var->mana = 0;
}

void *cardInitMask ( ) {
	void *ret = cardInit ( );
	return ret;

}
void cardClose ( struct card *var ) {
	free ( var );

}
int card_attrib_arr[] = {
	0,
	0,
	0,
	0,
};
void cardBodyToVal ( void *varPass, int nameI, char *body ) {

	struct card *var = varPass;

	if ( nameI == 0 ) {
		var->id = atoi ( body );
	} else if ( nameI == 1 ) {
		var->attack = atoi ( body );
	} else if ( nameI == 2 ) {
		var->health = atoi ( body );
	} else if ( nameI == 3 ) {
		var->mana = atoi ( body );
	}
}

int cardNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "id" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "attack" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "health" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "mana" ) == 0 ) {
		return 3;
	}
	return -1;
}

struct xmlFuncts cardXml = {
	.typeName = "card",
	.init = cardInitMask,
	.nameToIndex = cardNameToIndex,
	.bodyToVal = cardBodyToVal,
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
	var->id = 0;
	var->name[0] = '\0';
	var->attack = 0;
	var->health = 0;
	var->modifiers = initArrayList ( 10, sizeof ( struct cardMod* ), 10 );
	var->mana = 0;
}

void *cardBaseInitMask ( ) {
	void *ret = cardBaseInit ( );
	return ret;

}
void cardBaseClose ( struct cardBase *var ) {
	if ( var->modifiers ) {
		freeArrayListPointerFunction ( var->modifiers, (void (*)(void*))cardModClose );
	}
	free ( var );

}
int cardBase_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
void cardBaseBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cardBase *var = varPass;

	if ( nameI == 0 ) {
		var->id = atoi ( body );
	} else if ( nameI == 1 ) {
		strcpy ( var->name, body );
	} else if ( nameI == 2 ) {
		var->attack = atoi ( body );
	} else if ( nameI == 3 ) {
		var->health = atoi ( body );
	} else if ( nameI == 4 ) {
	} else if ( nameI == 5 ) {
		var->mana = atoi ( body );
	}
}

int cardBaseNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct cardBase *var = data;
	if ( strcmp ( body, "id" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "name" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "attack" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "health" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "modifiers" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->modifiers;
		return jxnAlPtr;
	} else if ( strcmp ( body, "mana" ) == 0 ) {
		return 5;
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
}

void *cardModInitMask ( ) {
	void *ret = cardModInit ( );
	return ret;

}
void cardModClose ( struct cardMod *var ) {
	free ( var );

}
int cardMod_attrib_arr[] = {
};
void cardModBodyToVal ( void *varPass, int nameI, char *body ) {


}

int cardModNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

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
/** Other Functs */
