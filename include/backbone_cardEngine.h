#pragma once

#include <jalb/backbone.h>
#include <jalbXml/jalbXml.h>

#include "mod.h"
#include "solitaire.h"
#include "oasis.h"


/** Functions */


/// Getters

struct backbone_structStruct **get_backbone_arr_cardEngine ( );
int get_backbone_arr_len_cardEngine ( );
int get_backbone_arr_total_cardEngine ( struct backbone_structStruct ***arrPtr );


