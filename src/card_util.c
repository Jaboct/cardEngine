#include "card_util.h"


/** Includes */




/** Functions */


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




/// Utilities

// render

int centerX ( int x, int w, int glyphW, int numChars ) {
	int pos = x + (w / 2) - (numChars * glyphW) / 2;

	return pos;
}

int centerX_px ( int x, int wTot, int wObj ) {
	return x + (wTot - wObj) / 2;
}







