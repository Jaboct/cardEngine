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










