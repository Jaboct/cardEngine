#include "xmlFunctGrouper_cardEngine.h"



int num_structStruct_cardEngine = 10;


extern struct xmlFuncts cardXml;
extern struct xmlFuncts cardBaseXml;
extern struct xmlFuncts cardModXml;
extern struct xmlFuncts oasis_gameXml;
extern struct xmlFuncts spellXml;
extern struct xmlFuncts targetingXml;
extern struct xmlFuncts spellEffectXml;
extern struct xmlFuncts minionBaseXml;
extern struct xmlFuncts playerXml;
extern struct xmlFuncts pick3Xml;


struct xmlFuncts *xmlFuncts_arr_cardEngine[] = {
	&cardXml,
	&cardBaseXml,
	&cardModXml,
	&oasis_gameXml,
	&spellXml,
	&targetingXml,
	&spellEffectXml,
	&minionBaseXml,
	&playerXml,
	&pick3Xml,
};


void *get_num_structStruct ( ) {
	return &num_structStruct_cardEngine;
}
void *get_xmlFuncts_arr ( ) {
	return xmlFuncts_arr_cardEngine;
}
extern struct backbone_structStruct *backbone_arr_cardEngine[];
void *get_backbone_arr ( ) {
	return backbone_arr_cardEngine;
}
int num_projectVars_cardEngine = 1;
/*
extern out of range (type: 0) (typeIndex: -1) modifierList;

struct backbone_projectVar proj_modifierList = {
	{
		.name = "modifierList",
		.type = 0,
		.typeIndex = -1,
		.initType = 0,
		.length = 0,
		.literal = 1,
		.data = {
			.id = 0,
		},
		.saveFlag = 1,
		.naked = 0,
	},
	.data = &modifierList,
};
*/
struct backbone_projectVar *projectVar_arr_cardEngine[] = {
//	&proj_modifierList,
	NULL,
};

void *get_num_projectVars ( ) {
	return &num_projectVars_cardEngine;
}

void *get_projectVars_list ( ) {
	return projectVar_arr_cardEngine;
}
