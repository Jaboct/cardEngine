#include "mod.h"

/** AUTO GENERATED CODE */

char altKeys[akNum] = {0};

float colorWhite[4] = { 1.00, 1.00, 1.00, 1.0 };
float colorGray[4] = { 0.5, 0.5, 0.5, 1.0 };
float colorDGray[4] = { 0.08, 0.08, 0.08, 1.0 };
float colorDGray1[4] = { 0.16, 0.16, 0.16, 1.0 };
float colorDGray2[4] = { 0.24, 0.24, 0.24, 1.0 };
float colorBlack[4] = { 0.00, 0.00, 0.00, 1.0 };
float colorGold[4] =  { 1.00, 0.80, 0.00, 1.0 };
float colorOrange[4] = { .9, 0.5, 0.0, 1.0 };




void mod_preInit ( ) {
}


int debugPrint_projectName_init = 0;


/** Variables */

struct draw2dStruct *draw2dApi = NULL;
struct draw3dStruct *draw3dApi = NULL;
//struct jalbFont *font16 = NULL;
struct jalbFont *fonts[2] = { NULL, NULL };

//void (*addCanvas)(int id, void *data, int *xywh) = NULL;
addCanvasF *addCanvas = NULL;

struct uiGen_api *uiGenApi = NULL;

/** Key */

//void keyWord ( char *line, void *data ) {
//}

/** Getter + Setter */

void setDraw2dApi ( void *api ) {
	printf ( "setDraw2dApi ( %p )\n", api );
	draw2dApi = api;
}

void setDraw3dApi ( void *api ) {
	printf ( "setDraw3dApi ( %p )\n", api );
	draw3dApi = api;
}

void setFont16 ( void *data ) {
	printf ( "setFont16 ( ): %p\n", data );
	fonts[0] = data;
}

void setFont32 ( void *data ) {
	printf ( "setFont32 ( ): %p\n", data );
	fonts[1] = data;
}

void setAddCanvas ( void *f ) {
	printf ( "setAddCanvas ( ): %p\n", f );
	addCanvas = f;
}

void setUiGenApi ( void *f ) {
	printf ( "setUiGenApi ( ): %p\n", f );
	uiGenApi = f;
}

/** Functions */

/** Other Functs */
