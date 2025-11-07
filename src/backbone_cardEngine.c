#include "backbone_cardEngine.h"


/** mod */



/** solitaire */



/** oasis */

int card_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_card_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct card, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_card_mana = {
	.name = "mana",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct card, mana ),
	.saveFlag = 1,
	.naked = 0,
};
int card__attributes[] = {
	0,
	0,
};
struct backbone_subVar backboneVar_card__minion = {
	.name = "minion",
	.type = 1,
	.typeIndex = 7,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct card, minion ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_card__spell = {
	.name = "spell",
	.type = 1,
	.typeIndex = 4,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct card, spell ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *card__varArr[] = {
	&backboneVar_card__minion,
	&backboneVar_card__spell,
};
struct backbone_subComplex card__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 2,
	.arr = card__varArr,
	.prefix = ""
};
struct backbone_subVar backboneVar_card_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &card__complex,
	},
	.external = offsetof ( struct card, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *card_varArr[] = {
	&backboneVar_card_id,
	&backboneVar_card_mana,
	&backboneVar_card_,
};
struct backbone_structStruct backboneStru_card = {
	.name = "card",
	.varsLen = 3,
	.vars = card_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct card ),
	.attributes = card_attributes,
};




int cardBase_attributes[] = {
	0,
	0,
};
struct backbone_subVar backboneVar_cardBase_name = {
	.name = "name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cardBase, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_cardBase_card = {
	.name = "card",
	.type = 1,
	.typeIndex = 0,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cardBase, card ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *cardBase_varArr[] = {
	&backboneVar_cardBase_name,
	&backboneVar_cardBase_card,
};
struct backbone_structStruct backboneStru_cardBase = {
	.name = "cardBase",
	.varsLen = 2,
	.vars = cardBase_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct cardBase ),
	.attributes = cardBase_attributes,
};




int cardMod_attributes[] = {
	0,
	0,
};
struct backbone_subVar backboneVar_cardMod_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cardMod, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_cardMod_name = {
	.name = "name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cardMod, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *cardMod_varArr[] = {
	&backboneVar_cardMod_type,
	&backboneVar_cardMod_name,
};
struct backbone_structStruct backboneStru_cardMod = {
	.name = "cardMod",
	.varsLen = 2,
	.vars = cardMod_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct cardMod ),
	.attributes = cardMod_attributes,
};




int oasis_game_attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_oasis_game_oasis_stage = {
	.name = "oasis_stage",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct oasis_game, oasis_stage ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_oasis_game_lobby_stage = {
	.name = "lobby_stage",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct oasis_game, lobby_stage ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_oasis_game_oasis_round = {
	.name = "oasis_round",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct oasis_game, oasis_round ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_oasis_game_oasis_turn = {
	.name = "oasis_turn",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct oasis_game, oasis_turn ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_oasis_game_enemy = {
	.name = "enemy",
	.type = 1,
	.typeIndex = 8,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct oasis_game, enemy ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_oasis_game_player = {
	.name = "player",
	.type = 1,
	.typeIndex = 8,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct oasis_game, player ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *oasis_game_varArr[] = {
	&backboneVar_oasis_game_oasis_stage,
	&backboneVar_oasis_game_lobby_stage,
	&backboneVar_oasis_game_oasis_round,
	&backboneVar_oasis_game_oasis_turn,
	&backboneVar_oasis_game_enemy,
	&backboneVar_oasis_game_player,
};
struct backbone_structStruct backboneStru_oasis_game = {
	.name = "oasis_game",
	.varsLen = 6,
	.vars = oasis_game_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct oasis_game ),
	.attributes = oasis_game_attributes,
};




int spell_attributes[] = {
	0,
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_spell_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct spell, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_spell_tar = {
	.name = "tar",
	.type = 1,
	.typeIndex = 5,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct spell, tar ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl spell_effList_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 6,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar backboneVar_spell_effList = {
	.name = "effList",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &spell_effList_subAl,
	},
	.external = offsetof ( struct spell, effList ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_spell_modName = {
	.name = "modName",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct spell, modName ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *spell_varArr[] = {
	&backboneVar_spell_type,
	&backboneVar_spell_tar,
	&backboneVar_spell_effList,
	&backboneVar_spell_modName,
};
struct backbone_structStruct backboneStru_spell = {
	.name = "spell",
	.varsLen = 4,
	.vars = spell_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct spell ),
	.attributes = spell_attributes,
};




int targeting_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_targeting_side = {
	.name = "side",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct targeting, side ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_targeting_who = {
	.name = "who",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct targeting, who ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_targeting_count = {
	.name = "count",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct targeting, count ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *targeting_varArr[] = {
	&backboneVar_targeting_side,
	&backboneVar_targeting_who,
	&backboneVar_targeting_count,
};
struct backbone_structStruct backboneStru_targeting = {
	.name = "targeting",
	.varsLen = 3,
	.vars = targeting_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct targeting ),
	.attributes = targeting_attributes,
};




int spellEffect_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_spellEffect_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct spellEffect, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_spellEffect_heal = {
	.name = "heal",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct spellEffect, heal ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_spellEffect_dmg = {
	.name = "dmg",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct spellEffect, dmg ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *spellEffect_varArr[] = {
	&backboneVar_spellEffect_type,
	&backboneVar_spellEffect_heal,
	&backboneVar_spellEffect_dmg,
};
struct backbone_structStruct backboneStru_spellEffect = {
	.name = "spellEffect",
	.varsLen = 3,
	.vars = spellEffect_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct spellEffect ),
	.attributes = spellEffect_attributes,
};




int minionBase_attributes[] = {
	0,
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_minionBase_attack = {
	.name = "attack",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct minionBase, attack ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_minionBase_health = {
	.name = "health",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct minionBase, health ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl minionBase_mods_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 2,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar backboneVar_minionBase_mods = {
	.name = "mods",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &minionBase_mods_subAl,
	},
	.external = offsetof ( struct minionBase, mods ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_minionBase_numAttacks = {
	.name = "numAttacks",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct minionBase, numAttacks ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *minionBase_varArr[] = {
	&backboneVar_minionBase_attack,
	&backboneVar_minionBase_health,
	&backboneVar_minionBase_mods,
	&backboneVar_minionBase_numAttacks,
};
struct backbone_structStruct backboneStru_minionBase = {
	.name = "minionBase",
	.varsLen = 4,
	.vars = minionBase_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct minionBase ),
	.attributes = minionBase_attributes,
};




int player_attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subAl player_deck_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 0,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_deck = {
	.name = "deck",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &player_deck_subAl,
	},
	.external = offsetof ( struct player, deck ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl player_deckTotal_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 0,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_deckTotal = {
	.name = "deckTotal",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &player_deckTotal_subAl,
	},
	.external = offsetof ( struct player, deckTotal ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_hand = {
	.name = "hand",
	.type = 1,
	.typeIndex = 0,
	.initType = 3,
	.length = 10,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct player, hand ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_board = {
	.name = "board",
	.type = 1,
	.typeIndex = 0,
	.initType = 3,
	.length = 7,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct player, board ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_health = {
	.name = "health",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct player, health ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_mana = {
	.name = "mana",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct player, mana ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_manaMax = {
	.name = "manaMax",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct player, manaMax ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_player_fatigue = {
	.name = "fatigue",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct player, fatigue ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *player_varArr[] = {
	&backboneVar_player_deck,
	&backboneVar_player_deckTotal,
	&backboneVar_player_hand,
	&backboneVar_player_board,
	&backboneVar_player_health,
	&backboneVar_player_mana,
	&backboneVar_player_manaMax,
	&backboneVar_player_fatigue,
};
struct backbone_structStruct backboneStru_player = {
	.name = "player",
	.varsLen = 8,
	.vars = player_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct player ),
	.attributes = player_attributes,
};




int pick3_attributes[] = {
	0,
	0,
};
struct backbone_subVar backboneVar_pick3_name = {
	.name = "name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pick3, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_pick3_cards = {
	.name = "cards",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = 3,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pick3, cards ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *pick3_varArr[] = {
	&backboneVar_pick3_name,
	&backboneVar_pick3_cards,
};
struct backbone_structStruct backboneStru_pick3 = {
	.name = "pick3",
	.varsLen = 2,
	.vars = pick3_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct pick3 ),
	.attributes = pick3_attributes,
};




/// Data Array

int len_backbone_arr_cardEngine = 10;
struct backbone_structStruct *backbone_arr_cardEngine[] = {
	&backboneStru_card,
	&backboneStru_cardBase,
	&backboneStru_cardMod,
	&backboneStru_oasis_game,
	&backboneStru_spell,
	&backboneStru_targeting,
	&backboneStru_spellEffect,
	&backboneStru_minionBase,
	&backboneStru_player,
	&backboneStru_pick3,
};


/// Getters

struct backbone_structStruct **get_backbone_arr_cardEngine ( ) {
	return backbone_arr_cardEngine;
}

int get_backbone_arr_len_cardEngine ( ) {
	return len_backbone_arr_cardEngine;
}

int get_backbone_arr_total_cardEngine ( struct backbone_structStruct ***arrPtr ) {
	*arrPtr = backbone_arr_cardEngine;
	return len_backbone_arr_cardEngine;
}


