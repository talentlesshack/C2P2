











#ifndef __Squad_And_Goal_Types_h__
#define __Squad_And_Goal_Types_h__












enum GOAL_CLASS
{
	DEFAULT_GOAL_CLASS = 0,
	SETTLER_GOAL_CLASS,
	CITY_GOAL_CLASS,
	EXPLORE_GOAL_CLASS,
	BOMBARD_GOAL_CLASS,
	SEIGE_GOAL_CLASS,
	PROTECT_GOAL_CLASS,
	DEFENSE_GOAL_CLASS,
	MILITARY_GOAL_CLASS,
	SLAVER_GOAL_CLASS,
	GOD_GOAL_CLASS,
	ESPIONAGE_GOAL_CLASS,
	DEFUSE_MINES_GOAL_CLASS,
	BONUS_FOOD_GOAL_CLASS,
	MEDIA_GOAL_CLASS,
	DIPLOMATIC_GOAL_CLASS,
	BUSINESS_GOAL_CLASS,
	LAW_GOAL_CLASS,
	ABOLITIONIST_GOAL_CLASS,
	DESTROY_CITY_GOAL_CLASS,
	TRANSPORT_HACK_GOAL_CLASS,
	WORMHOLE_PROBE_GOAL_CLASS,
	PROMISCUOUS_GOAL_CLASS,
	MAX_GOAL_CLASSES
};







enum SQUAD_CLASS
{
	DEFAULT_SQUAD = 0,
	CITY_SQUAD,
	EXPLORE_SQUAD,
	MILITARY_SQUAD,
	DEFENSE_SQUAD,
	PROTECT_SQUAD,
	SEIGE_SQUAD,
	BOMBARD_SQUAD,
	SLAVER_SQUAD,
	GOD_SQUAD,
	ESPIONAGE_SQUAD,
	DEFUSE_MINES_SQUAD,
	BONUS_FOOD_SQUAD,
	ENVIRONMENTALIST_SQUAD,
	MEDIA_SQUAD,
	DIPLOMATIC_SQUAD,
	BUSINESS_SQUAD,
	LAW_SQUAD,
	ABOLITIONIST_SQUAD,
	SETTLER_SQUAD,
	DESTROY_CITY_SQUAD,
	TRANSPORT_HACK_SQUAD,
	WORMHOLE_PROBE_SQUAD,
	MAX_SQUAD_CLASSES
};


enum GOAL_TYPE 
{     
    GOAL_TYPE_NULL=0,  
    GOAL_TYPE_DEFENSE, 

	GOAL_TYPE_SEIGE,
	GOAL_TYPE_ATTACK_REGION,
    GOAL_TYPE_ATTACK, 
    GOAL_TYPE_SETTLE, 
    GOAL_TYPE_EXPLORE, 
    GOAL_TYPE_CONSTRUCT_BUILDING, 
    GOAL_TYPE_CONSTRUCT_FREIGHT,
	GOAL_TYPE_CONSTRUCT_WONDER,
    GOAL_TYPE_TRANSPORT,
    GOAL_TYPE_ENSLAVE, 
	GOAL_TYPE_BUILD_SUPPLEMENTAL,
	GOAL_TYPE_BUILD_LIST,
	GOAL_TYPE_PERIMETER,
	GOAL_TYPE_CHOKEPOINT,
	GOAL_TYPE_PATROL,
	GOAL_TYPE_CONVERT_CITY,
    GOAL_TYPE_BIOTERROR_CITY, 
    GOAL_TYPE_NANOATTACK_CITY, 
	GOAL_TYPE_HARASS_CITY,
	GOAL_TYPE_BOMBARD,
	GOAL_TYPE_RUSTLE,
	GOAL_TYPE_EXPEL,
	GOAL_TYPE_RETREAT,
    GOAL_TYPE_HURT_ARMY, 

	GOAL_TYPE_PILLAGE,
	GOAL_TYPE_PIRATE,
	GOAL_TYPE_COUNTER_STEALTH,
	GOAL_TYPE_BONUS_FOOD,
	GOAL_TYPE_GOODY_HUT,
	GOAL_TYPE_PLANT_NUKE,
	GOAL_TYPE_MAKE_PARK,
	GOAL_TYPE_CAUSE_UNHAPPINESS,
	GOAL_TYPE_ESTABLISH_EMBASSY,
	GOAL_TYPE_FRANCHISING,
	GOAL_TYPE_STEAL_TECHNOLOGY,
	GOAL_TYPE_INCITE_REVOLUTION,
	GOAL_TYPE_INJOIN,
	GOAL_TYPE_ASSASINATE_RULER,
	GOAL_TYPE_UNDERGROUND_RAILWAY,
	GOAL_TYPE_NUKE_CITY,
	GOAL_TYPE_WANDER,
	GOAL_TYPE_SALLY,
	GOAL_TYPE_REFORM_CITY,
	GOAL_TYPE_SUE_FRANCHISE,
	GOAL_TYPE_PROBE_WORMHOLE,
	GOAL_TYPE_RECOVER_PROBE,
	GOAL_TYPE_MAX, 
}; 

#define SAVE_NO_GOAL -1


#endif 
