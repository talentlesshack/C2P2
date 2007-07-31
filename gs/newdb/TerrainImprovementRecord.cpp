
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#include "c3.h"
#include "c3errors.h"
#include "TerrainImprovementRecord.h"
#include "DBLexer.h"
#include "DBTokens.h"
#include "CTPDatabase.h"
#include "StrDB.h"
#include "BitArray.h"

#include "TerrainRecord.h"
#include "IconRecord.h"
#include "TerrainRecord.h"
#include "TerrainRecord.h"
#include "AdvanceRecord.h"
#include "AdvanceRecord.h"

CTPDatabase<TerrainImprovementRecord> *g_theTerrainImprovementDB = NULL;

TerrainImprovementRecord::Init()
{
    m_flags0 = 0;
    m_Class = 0;
    m_Excludes = 0;
    m_CanSee = 0;
    m_CantBuildOn = NULL;
    m_numCantBuildOn = 0;
    memset(&m_EffectValue, 0, sizeof(m_EffectValue));
    m_TerrainEffect = NULL;
    m_numTerrainEffect = 0;
    m_Icon = 0x7fffffff;
    m_Tooltip = 0;
    m_Statusbar = 0;
    m_Level = 0;
    memset(m_ConstructionTiles, 0, sizeof(m_ConstructionTiles));
    m_numConstructionTiles = 0;
    m_TerraformTerrainValue = 0;
    m_ColumnValue = 0;
    m_IntBorderRadiusValue = 0;
    m_SquaredBorderRadiusValue = 0;
}

TerrainImprovementRecord::~TerrainImprovementRecord()
{
	int index = 0;
	// free array CantBuildOn 
 	if (m_numCantBuildOn > 0) 
		delete [m_numCantBuildOn] m_CantBuildOn; 
	m_CantBuildOn = NULL; 
	m_numCantBuildOn = 0; 

	// free array TerrainEffect 
 			// free struct elements
	if (m_numTerrainEffect > 0) 
		delete [m_numTerrainEffect] m_TerrainEffect; 
	m_TerrainEffect = NULL; 
	m_numTerrainEffect = 0; 

}

void TerrainImprovementRecord::operator=(const TerrainImprovementRecord & rval)
{
	int index = 0;
	m_index = rval.m_index;
	m_Class = rval.m_Class; 

	m_Excludes = rval.m_Excludes; 

	m_CanSee = rval.m_CanSee; 

	// free array CantBuildOn 
 	if (m_numCantBuildOn > 0) 
	{
		delete [m_numCantBuildOn] m_CantBuildOn; 
		m_CantBuildOn = NULL; 
		m_numCantBuildOn = 0; 
	}
	if (rval.m_numCantBuildOn > 0) 
	{
		m_CantBuildOn = new sint32 [rval.m_numCantBuildOn]; 
		memcpy(m_CantBuildOn, rval.m_CantBuildOn, sizeof(sint32)*rval.m_numCantBuildOn); 

	} 
	m_numCantBuildOn = rval.m_numCantBuildOn;

	m_flags0 = rval.m_flags0; 
		m_EffectValue = rval.m_EffectValue; 

	// free array TerrainEffect 
 	// free struct elements of TerrainEffect[]
	if (m_numTerrainEffect > 0) 
	{
		delete [m_numTerrainEffect] m_TerrainEffect; 
		m_TerrainEffect = NULL; 
	}

	if (rval.m_numTerrainEffect > 0) 
	{
		m_TerrainEffect = new Effect [rval.m_numTerrainEffect];
	}

	// copy struct elements of TerrainEffect[]
	for (index = 0; index < rval.m_numTerrainEffect; index++) 
		{ 
			m_TerrainEffect[index] = rval.m_TerrainEffect[index]; 
	} 
	m_numTerrainEffect = rval.m_numTerrainEffect;

	m_Icon = rval.m_Icon; 

	m_Tooltip = rval.m_Tooltip; 

	m_Statusbar = rval.m_Statusbar; 

	m_Level = rval.m_Level; 

	// copy fixed sized array ConstructionTiles[] 
 		memcpy(m_ConstructionTiles, rval.m_ConstructionTiles, sizeof(sint32)*rval.m_numConstructionTiles); 

	m_flags0 = rval.m_flags0; 
		m_TerraformTerrainValue = rval.m_TerraformTerrainValue; 

	m_flags0 = rval.m_flags0; 
		m_ColumnValue = rval.m_ColumnValue; 

	m_flags0 = rval.m_flags0; 
		m_IntBorderRadiusValue = rval.m_IntBorderRadiusValue; 

	m_flags0 = rval.m_flags0; 
		m_SquaredBorderRadiusValue = rval.m_SquaredBorderRadiusValue; 

	m_flags0 = rval.m_flags0; 
}

char *g_TerrainImprovement_Tokens[] =
{
    "Class",
    "Excludes",
    "CanSee",
    "CantBuildOn",
    "Effect",
    "EffectValue",
    "TerrainEffect",
    "Icon",
    "Tooltip",
    "Statusbar",
    "Level",
    "ConstructionTiles",
    "TerraformTerrain",
    "TerraformTerrainValue",
    "Column",
    "ColumnValue",
    "IntBorderRadius",
    "IntBorderRadiusValue",
    "SquaredBorderRadius",
    "SquaredBorderRadiusValue",
    "GLHidden",
};

TerrainImprovementRecordAccessorInfo g_TerrainImprovementRecord_Accessors[] = 
{
    { NULL, NULL, NULL, NULL, NULL}, /* Class */
    { NULL, NULL, NULL, NULL, NULL}, /* Excludes */
    { NULL, NULL, NULL, NULL, NULL}, /* CanSee */
    { NULL, NULL, NULL, NULL, NULL}, /* CantBuildOn (array) */
    { NULL, NULL, NULL, NULL, NULL}, /* Effect */
    { NULL, NULL, NULL, NULL, NULL}, /* Effect */
    { NULL, NULL, NULL, NULL, NULL}, /* TerrainEffect */
    {TerrainImprovementRecord::GetIconIndex, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL}, /* Tooltip */
    { NULL, NULL, NULL, NULL, NULL}, /* Statusbar */
    { TerrainImprovementRecord::GetLevel, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL}, /* ConstructionTiles (array) */
    { NULL, NULL, NULL, NULL, NULL}, /* TerraformTerrain */
    { NULL, NULL, NULL, NULL, NULL}, /* TerraformTerrain */
    { NULL, NULL, NULL, TerrainImprovementRecord::GetColumn, NULL },
    { NULL, NULL, NULL, NULL, NULL}, /* Column */
    { NULL, NULL, NULL, TerrainImprovementRecord::GetIntBorderRadius, NULL },
    { NULL, NULL, NULL, NULL, NULL}, /* IntBorderRadius */
    { NULL, NULL, NULL, TerrainImprovementRecord::GetSquaredBorderRadius, NULL },
    { NULL, NULL, NULL, NULL, NULL}, /* SquaredBorderRadius */
    { NULL, TerrainImprovementRecord::GetGLHidden, NULL, NULL, NULL },
};

#define k_Token_TerrainImprovement_Class         ((k_Token_Custom_Base) + 0)
#define k_Token_TerrainImprovement_Excludes      ((k_Token_Custom_Base) + 1)
#define k_Token_TerrainImprovement_CanSee        ((k_Token_Custom_Base) + 2)
#define k_Token_TerrainImprovement_CantBuildOn   ((k_Token_Custom_Base) + 3)
#define k_Token_TerrainImprovement_Effect        ((k_Token_Custom_Base) + 4)
#define k_Token_TerrainImprovement_Effect_Value  ((k_Token_Custom_Base) + 5)
#define k_Token_TerrainImprovement_TerrainEffect ((k_Token_Custom_Base) + 6)
#define k_Token_TerrainImprovement_Icon          ((k_Token_Custom_Base) + 7)
#define k_Token_TerrainImprovement_Tooltip       ((k_Token_Custom_Base) + 8)
#define k_Token_TerrainImprovement_Statusbar     ((k_Token_Custom_Base) + 9)
#define k_Token_TerrainImprovement_Level         ((k_Token_Custom_Base) + 10)
#define k_Token_TerrainImprovement_ConstructionTiles ((k_Token_Custom_Base) + 11)
#define k_Token_TerrainImprovement_TerraformTerrain ((k_Token_Custom_Base) + 12)
#define k_Token_TerrainImprovement_TerraformTerrain_Value ((k_Token_Custom_Base) + 13)
#define k_Token_TerrainImprovement_Column        ((k_Token_Custom_Base) + 14)
#define k_Token_TerrainImprovement_Column_Value  ((k_Token_Custom_Base) + 15)
#define k_Token_TerrainImprovement_IntBorderRadius ((k_Token_Custom_Base) + 16)
#define k_Token_TerrainImprovement_IntBorderRadius_Value ((k_Token_Custom_Base) + 17)
#define k_Token_TerrainImprovement_SquaredBorderRadius ((k_Token_Custom_Base) + 18)
#define k_Token_TerrainImprovement_SquaredBorderRadius_Value ((k_Token_Custom_Base) + 19)
#define k_Token_TerrainImprovement_GLHidden      ((k_Token_Custom_Base) + 20)
#define k_Token_TerrainImprovement_Max           ((k_Token_Custom_Base) + 21)


static BitArray s_ParsedTokens(21);
void TerrainImprovementRecord::CheckRequiredFields(DBLexer *lex)
{
    // Ick.
    if(!s_ParsedTokens.Bit(k_Token_TerrainImprovement_Tooltip - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field Tooltip missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_TerrainImprovement_Statusbar - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field Statusbar missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_TerrainImprovement_Level - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field Level missing"));
    }
}
    
sint32 TerrainImprovementRecord::Parse(DBLexer *lex)
{
    bool done = false;
    sint32 result = 0;
    sint32 tok;
    DBPARSE_ERROR err = DBPARSE_OK;
    s_ParsedTokens.Clear();
    lex->SetTokens(g_TerrainImprovement_Tokens, k_Token_TerrainImprovement_Max);
    tok = lex->GetToken();
    if(tok != k_Token_Name) {
        DBERROR(("Record does not start with name"));
        return 0;
    }
    if(!g_theStringDB->GetStringID(lex->GetTokenText(), m_name)) {
        g_theStringDB->InsertStr(lex->GetTokenText(), lex->GetTokenText());
        if(!g_theStringDB->GetStringID(lex->GetTokenText(), m_name))
            SetTextName(lex->GetTokenText());
    }

    tok = lex->GetToken();
    if(tok != k_Token_OpenBrace) {
        DBERROR(("Missing open brace"));
        return 0;
    }

    while(!done) {
        tok = lex->GetToken();
        if(tok >= k_Token_Custom_Base && tok < k_Token_TerrainImprovement_Max) { 
            s_ParsedTokens.SetBit(tok - k_Token_Custom_Base);
        }
        switch(tok) {
            case k_Token_TerrainImprovement_Class:
                if(!ParseClassBit(lex)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Excludes:
                if(!ParseExcludesBit(lex)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_CanSee:
                if(!ParseCanSeeBit(lex)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_CantBuildOn:
                if(!g_theTerrainDB->ParseRecordInArray(lex, (sint32 **)&m_CantBuildOn, &m_numCantBuildOn, err)) 
                {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect:
                m_flags0 |= k_TerrainImprovement_Effect_Bit;
                if(!m_EffectValue.Parse(lex)) {
                    DBERROR(("Expected struct"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_TerrainEffect:
                if(!TerrainImprovementRecord::Effect::ParseInArray(lex, &m_TerrainEffect, &m_numTerrainEffect)) 
                {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Icon:
                if(!g_theIconDB->GetRecordFromLexer(lex, m_Icon, err)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Tooltip:
                if(!lex->GetStringIdAssignment(m_Tooltip)) {
                    DBERROR(("Expected string ID"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Statusbar:
                if(!lex->GetStringIdAssignment(m_Statusbar)) {
                    DBERROR(("Expected string ID"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Level:
                if(!lex->GetIntAssignment(m_Level)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_ConstructionTiles:
                if(!CTPRecord::ParseIntInArray(lex, (sint32 *)m_ConstructionTiles, &m_numConstructionTiles, k_MAX_ConstructionTiles)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_TerraformTerrain:
                m_flags0 |= k_TerrainImprovement_TerraformTerrain_Bit;
                if(!g_theTerrainDB->GetRecordFromLexer(lex, m_TerraformTerrainValue, err)) {
                    DBERROR(("Expected record"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Column:
                m_flags0 |= k_TerrainImprovement_Column_Bit;
                if(!lex->GetIntAssignment(m_ColumnValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_IntBorderRadius:
                m_flags0 |= k_TerrainImprovement_IntBorderRadius_Bit;
                if(!lex->GetIntAssignment(m_IntBorderRadiusValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_SquaredBorderRadius:
                m_flags0 |= k_TerrainImprovement_SquaredBorderRadius_Bit;
                if(!lex->GetIntAssignment(m_SquaredBorderRadiusValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_GLHidden:
                m_flags0 |= k_TerrainImprovement_GLHidden_Bit;
                break;
            case k_Token_CloseBrace:
                done = true;
                result = 1;
                break;
            default:
                DBERROR(("Unknown token"));
                done = true;
                break;
        }
    }
    CheckRequiredFields(lex);
    lex->RestoreTokens();
    return result;
}

void TerrainImprovementRecord::ResolveDBReferences()
{
    {
        sint32 i;
        for(i = 0; i < m_numCantBuildOn; i++) {
            if(m_CantBuildOn[i] & 0x80000000) {
                sint32 id = m_CantBuildOn[i] & 0x7fffffff;
                if(!g_theTerrainDB->GetNamedItem(id, m_CantBuildOn[i])) {
                    c3errors_ErrorDialog("DB", "%s not found in Terrain database", g_theStringDB->GetNameStr(id));
                }
            } else if(m_CantBuildOn[i] == 0x7fffffff){
                m_CantBuildOn[i] = -1;
            }
        }
    }
    m_EffectValue.ResolveDBReferences();
    {
        sint32 i;
        for(i = 0; i < m_numTerrainEffect; i++) {
            m_TerrainEffect[i].ResolveDBReferences();
        }
    }
    if(m_Icon & 0x80000000) {
        sint32 id = m_Icon & 0x7fffffff;
        if(!g_theIconDB->GetNamedItem(id, m_Icon)) {
            c3errors_ErrorDialog("DB", "%s not found in Icon database", g_theStringDB->GetNameStr(id));
        }
    } else if(m_Icon == 0x7fffffff) {
        m_Icon = -1;
    }
    if(m_TerraformTerrainValue & 0x80000000) {
        sint32 id = m_TerraformTerrainValue & 0x7fffffff;
        if(!g_theTerrainDB->GetNamedItem(id, m_TerraformTerrainValue)) {
            c3errors_ErrorDialog("DB", "%s not found in Terrain database", g_theStringDB->GetNameStr(id));
        }
    } else if(m_TerraformTerrainValue == 0x7fffffff) {
        m_TerraformTerrainValue = -1;
    }
}
/*
 * Member class Parsers
 * (DO NOT EDIT!  Automatically generated file)
 */
TerrainImprovementRecord::Effect::Effect()
{
    m_flags0 = 0;
    m_Terrain = NULL;
    m_numTerrain = 0;
    m_BonusFoodValue = 0;
    m_BonusProductionValue = 0;
    m_BonusGoldValue = 0;
    m_MoveCostValue = 0;
    m_VisionRangeValue = 0;
    m_RadarRangeValue = 0;
    m_DefenseBonusValue = 0.0;
    m_EnableAdvance = 0x7fffffff;
    m_ObsoleteAdvance = NULL;
    m_numObsoleteAdvance = 0;
    m_ProductionCost = 0;
    m_ProductionTime = 0;
    m_TilesetIndex = 0;
}
TerrainImprovementRecord::Effect::~Effect()
{
	// free array Terrain 
 	if (m_numTerrain > 0) 
		delete [m_numTerrain] m_Terrain; 
	m_Terrain = NULL; 
	m_numTerrain = 0; 

	// free array ObsoleteAdvance 
 	if (m_numObsoleteAdvance > 0) 
		delete [m_numObsoleteAdvance] m_ObsoleteAdvance; 
	m_ObsoleteAdvance = NULL; 
	m_numObsoleteAdvance = 0; 

}
void TerrainImprovementRecord::Effect::operator=(const Effect & rval)
{
	// free array Terrain 
 	if (m_numTerrain > 0) 
	{
		delete [m_numTerrain] m_Terrain; 
		m_Terrain = NULL; 
		m_numTerrain = 0; 
	}
	if (rval.m_numTerrain > 0) 
	{
		m_Terrain = new sint32 [rval.m_numTerrain]; 
		memcpy(m_Terrain, rval.m_Terrain, sizeof(sint32)*rval.m_numTerrain); 

	} 
	m_numTerrain = rval.m_numTerrain;

	m_flags0 = rval.m_flags0; 
		m_BonusFoodValue = rval.m_BonusFoodValue; 

	m_flags0 = rval.m_flags0; 
		m_BonusProductionValue = rval.m_BonusProductionValue; 

	m_flags0 = rval.m_flags0; 
		m_BonusGoldValue = rval.m_BonusGoldValue; 

	m_flags0 = rval.m_flags0; 
		m_MoveCostValue = rval.m_MoveCostValue; 

	m_flags0 = rval.m_flags0; 
	m_flags0 = rval.m_flags0; 
	m_flags0 = rval.m_flags0; 
	m_flags0 = rval.m_flags0; 
	m_flags0 = rval.m_flags0; 
		m_VisionRangeValue = rval.m_VisionRangeValue; 

	m_flags0 = rval.m_flags0; 
		m_RadarRangeValue = rval.m_RadarRangeValue; 

	m_flags0 = rval.m_flags0; 
		m_DefenseBonusValue = rval.m_DefenseBonusValue; 

	m_EnableAdvance = rval.m_EnableAdvance; 

	// free array ObsoleteAdvance 
 	if (m_numObsoleteAdvance > 0) 
	{
		delete [m_numObsoleteAdvance] m_ObsoleteAdvance; 
		m_ObsoleteAdvance = NULL; 
		m_numObsoleteAdvance = 0; 
	}
	if (rval.m_numObsoleteAdvance > 0) 
	{
		m_ObsoleteAdvance = new sint32 [rval.m_numObsoleteAdvance]; 
		memcpy(m_ObsoleteAdvance, rval.m_ObsoleteAdvance, sizeof(sint32)*rval.m_numObsoleteAdvance); 

	} 
	m_numObsoleteAdvance = rval.m_numObsoleteAdvance;

	m_ProductionCost = rval.m_ProductionCost; 

	m_ProductionTime = rval.m_ProductionTime; 

	m_TilesetIndex = rval.m_TilesetIndex; 

}
static char *s_TerrainImprovement_Effect_Tokens[] = {
    "Terrain",
    "BonusFood",
    "BonusProduction",
    "BonusGold",
    "MoveCost",
    "Radar",
    "Airport",
    "ListeningPost",
    "Endgame",
    "VisionRange",
    "RadarRange",
    "DefenseBonus",
    "EnableAdvance",
    "ObsoleteAdvance",
    "ProductionCost",
    "ProductionTime",
    "TilesetIndex",
};
#define k_Token_TerrainImprovement_Effect_Terrain ((k_Token_Custom_Base) + 0)
#define k_Token_TerrainImprovement_Effect_BonusFood ((k_Token_Custom_Base) + 1)
#define k_Token_TerrainImprovement_Effect_BonusProduction ((k_Token_Custom_Base) + 2)
#define k_Token_TerrainImprovement_Effect_BonusGold ((k_Token_Custom_Base) + 3)
#define k_Token_TerrainImprovement_Effect_MoveCost ((k_Token_Custom_Base) + 4)
#define k_Token_TerrainImprovement_Effect_Radar  ((k_Token_Custom_Base) + 5)
#define k_Token_TerrainImprovement_Effect_Airport ((k_Token_Custom_Base) + 6)
#define k_Token_TerrainImprovement_Effect_ListeningPost ((k_Token_Custom_Base) + 7)
#define k_Token_TerrainImprovement_Effect_Endgame ((k_Token_Custom_Base) + 8)
#define k_Token_TerrainImprovement_Effect_VisionRange ((k_Token_Custom_Base) + 9)
#define k_Token_TerrainImprovement_Effect_RadarRange ((k_Token_Custom_Base) + 10)
#define k_Token_TerrainImprovement_Effect_DefenseBonus ((k_Token_Custom_Base) + 11)
#define k_Token_TerrainImprovement_Effect_EnableAdvance ((k_Token_Custom_Base) + 12)
#define k_Token_TerrainImprovement_Effect_ObsoleteAdvance ((k_Token_Custom_Base) + 13)
#define k_Token_TerrainImprovement_Effect_ProductionCost ((k_Token_Custom_Base) + 14)
#define k_Token_TerrainImprovement_Effect_ProductionTime ((k_Token_Custom_Base) + 15)
#define k_Token_TerrainImprovement_Effect_TilesetIndex ((k_Token_Custom_Base) + 16)
#define k_Token_TerrainImprovement_Effect_Max ((k_Token_Custom_Base) + 17)
sint32 TerrainImprovementRecord::Effect::Parse(DBLexer *lex)
{
    bool done = false;
    sint32 tok;
    sint32 result = 0;
    DBPARSE_ERROR err = DBPARSE_OK;
    tok = lex->PeekAhead();
    if(tok != k_Token_OpenBrace) {
        DBERROR(("Expected open brace for Effect"));
        return 0;
    }
    tok = lex->GetToken();
    lex->SetTokens(s_TerrainImprovement_Effect_Tokens, k_Token_TerrainImprovement_Effect_Max);
    while(!done) {
        tok = lex->GetToken();
        switch(tok) {
            case k_Token_TerrainImprovement_Effect_Terrain:
                if(!g_theTerrainDB->ParseRecordInArray(lex, &m_Terrain, &m_numTerrain, err)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_BonusFood:
                m_flags0 |= k_Effect_BonusFood_Bit;
                if(!lex->GetIntAssignment(m_BonusFoodValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_BonusProduction:
                m_flags0 |= k_Effect_BonusProduction_Bit;
                if(!lex->GetIntAssignment(m_BonusProductionValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_BonusGold:
                m_flags0 |= k_Effect_BonusGold_Bit;
                if(!lex->GetIntAssignment(m_BonusGoldValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_MoveCost:
                m_flags0 |= k_Effect_MoveCost_Bit;
                if(!lex->GetIntAssignment(m_MoveCostValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_Radar:
                m_flags0 |= k_Effect_Radar_Bit;
                break;
            case k_Token_TerrainImprovement_Effect_Airport:
                m_flags0 |= k_Effect_Airport_Bit;
                break;
            case k_Token_TerrainImprovement_Effect_ListeningPost:
                m_flags0 |= k_Effect_ListeningPost_Bit;
                break;
            case k_Token_TerrainImprovement_Effect_Endgame:
                m_flags0 |= k_Effect_Endgame_Bit;
                break;
            case k_Token_TerrainImprovement_Effect_VisionRange:
                m_flags0 |= k_Effect_VisionRange_Bit;
                if(!lex->GetIntAssignment(m_VisionRangeValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_RadarRange:
                m_flags0 |= k_Effect_RadarRange_Bit;
                if(!lex->GetIntAssignment(m_RadarRangeValue)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_DefenseBonus:
                m_flags0 |= k_Effect_DefenseBonus_Bit;
                if(!lex->GetFloatAssignment(m_DefenseBonusValue)) {
                    DBERROR(("Expected number"));
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_EnableAdvance:
                if(!g_theAdvanceDB->GetRecordFromLexer(lex, m_EnableAdvance, err)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_ObsoleteAdvance:
                if(!g_theAdvanceDB->ParseRecordInArray(lex, &m_ObsoleteAdvance, &m_numObsoleteAdvance, err)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_ProductionCost:
                if(!lex->GetIntAssignment(m_ProductionCost)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_ProductionTime:
                if(!lex->GetIntAssignment(m_ProductionTime)) {
                    done = true; break;
                }
                break;
            case k_Token_TerrainImprovement_Effect_TilesetIndex:
                if(!lex->GetIntAssignment(m_TilesetIndex)) {
                    done = true; break;
                }
                break;
            case k_Token_CloseBrace:
                done = true;
                result = 1;
                break;
            default:
                Assert(FALSE);
                done = true;
                break;
        }
    }
    lex->RestoreTokens();
    return result;
}

sint32 TerrainImprovementRecord::Effect::ParseInArray(DBLexer *lex, Effect **array, sint32 *numElements)
{
    if(*numElements > 0) {
        Effect *oldArray = *array;
        *array = new Effect[(*numElements) + 1];
        for (int i=0; i < (*numElements); i++) 
             (*array)[i] = oldArray[i];
        delete [] oldArray;
    } else {
        *array = new Effect[1];
    }
    (*array)[*numElements].Parse(lex);
    *numElements += 1;
    return 1;
}
sint32 TerrainImprovementRecord::Effect::ParseInArray(DBLexer *lex, Effect *array, sint32 *numElements, sint32 maxSize)
{
    if(*numElements >= maxSize) {
        return 0;
    }
    array[*numElements].Parse(lex);
    *numElements += 1;
    return 1;
}
void TerrainImprovementRecord::Effect::ResolveDBReferences()
{
    {
        sint32 i;
        for(i = 0; i < m_numTerrain; i++) {
            if(m_Terrain[i] & 0x80000000) {
                sint32 id = m_Terrain[i] & 0x7fffffff;
                if(!g_theTerrainDB->GetNamedItem(id, m_Terrain[i])) {
                    c3errors_ErrorDialog("DB", "%s not found in Terrain database", g_theStringDB->GetNameStr(id));
                }
            } else if(m_Terrain[i] == 0x7fffffff){
                m_Terrain[i] = -1;
            }
        }
    }
    if(m_EnableAdvance & 0x80000000) {
        sint32 id = m_EnableAdvance & 0x7fffffff;
        if(!g_theAdvanceDB->GetNamedItem(id, m_EnableAdvance)) {
            c3errors_ErrorDialog("DB", "%s not found in Advance database", g_theStringDB->GetNameStr(id));
        }
    } else if(m_EnableAdvance == 0x7fffffff) {
        m_EnableAdvance = -1;
    }
    {
        sint32 i;
        for(i = 0; i < m_numObsoleteAdvance; i++) {
            if(m_ObsoleteAdvance[i] & 0x80000000) {
                sint32 id = m_ObsoleteAdvance[i] & 0x7fffffff;
                if(!g_theAdvanceDB->GetNamedItem(id, m_ObsoleteAdvance[i])) {
                    c3errors_ErrorDialog("DB", "%s not found in Advance database", g_theStringDB->GetNameStr(id));
                }
            } else if(m_ObsoleteAdvance[i] == 0x7fffffff){
                m_ObsoleteAdvance[i] = -1;
            }
        }
    }
}
/*
 * Data Parsers
 * (DO NOT EDIT!  Automatically generated file)
 */
static char *s_TerrainImprovement_Class_BitNames[] = {
    "Farm",
    "Road",
    "Mine",
    "ATM",
    "OceanFarm",
    "OceanMine",
    "OceanATM",
    "OceanRoad",
    "Structure1",
    "Structure2",
    "LandDetector",
    "OceanDetector",
    "Terraform",
};
#define k_TerrainImprovement_Class_Num_BitNames 13

sint32 TerrainImprovementRecord::ParseClassBit(DBLexer *lex)
{
    sint32 bitindex;
    if(!lex->GetBitIndex((const char **)s_TerrainImprovement_Class_BitNames, k_TerrainImprovement_Class_Num_BitNames, bitindex)) {
        DBERROR(("%s is not a member of Class", lex->GetTokenText()));
        return 0;
    }
    m_Class |= (1 << bitindex);
    return 1;
}

static char *s_TerrainImprovement_Excludes_BitNames[] = {
    "Farm",
    "Road",
    "Mine",
    "ATM",
    "OceanFarm",
    "OceanMine",
    "OceanATM",
    "OceanRoad",
    "Structure1",
    "Structure2",
    "LandDetector",
    "OceanDetector",
    "Terraform",
};
#define k_TerrainImprovement_Excludes_Num_BitNames 13

sint32 TerrainImprovementRecord::ParseExcludesBit(DBLexer *lex)
{
    sint32 bitindex;
    if(!lex->GetBitIndex((const char **)s_TerrainImprovement_Excludes_BitNames, k_TerrainImprovement_Excludes_Num_BitNames, bitindex)) {
        DBERROR(("%s is not a member of Excludes", lex->GetTokenText()));
        return 0;
    }
    m_Excludes |= (1 << bitindex);
    return 1;
}

static char *s_TerrainImprovement_CanSee_BitNames[] = {
    "Standard",
    "Underwater",
    "Stealth",
    "UnusedBit3",
    "UnusedBit4",
    "UnusedBit5",
    "UnusedBit6",
    "UnusedBit7",
    "UnusedBit8",
    "UnusedBit9",
    "UnusedBit10",
    "UnusedBit11",
    "UnusedBit12",
    "UnusedBit13",
    "UnusedBit14",
    "UnusedBit15",
};
#define k_TerrainImprovement_CanSee_Num_BitNames 16

sint32 TerrainImprovementRecord::ParseCanSeeBit(DBLexer *lex)
{
    sint32 bitindex;
    if(!lex->GetBitIndex((const char **)s_TerrainImprovement_CanSee_BitNames, k_TerrainImprovement_CanSee_Num_BitNames, bitindex)) {
        DBERROR(("%s is not a member of CanSee", lex->GetTokenText()));
        return 0;
    }
    m_CanSee |= (1 << bitindex);
    return 1;
}

void TerrainImprovementRecord::Merge(const TerrainImprovementRecord & rval){
	int index = 0, obj_index = 0;
	// only replace values that have been set
	if(rval.m_Class != 0x0) 
		m_Class = rval.m_Class; 

	// only replace values that have been set
	if(rval.m_Excludes != 0x0) 
		m_Excludes = rval.m_Excludes; 

	// only replace values that have been set
	if(rval.m_CanSee != 0x0) 
		m_CanSee = rval.m_CanSee; 

	// resize m_CantBuildOn if necessary
	if (rval.m_numCantBuildOn > m_numCantBuildOn)
 	{ 
		delete m_CantBuildOn;
 		m_CantBuildOn = NULL;
 		if (rval.m_numCantBuildOn > 0)
 			m_CantBuildOn = new sint32 [rval.m_numCantBuildOn]; 
		m_numCantBuildOn = rval.m_numCantBuildOn;
 	} 

	// copy values of rval.m_CantBuildOn to m_CantBuildOn
	for (index = 0; index < m_numCantBuildOn; index++) 
	{ 
 		if (index < rval.m_numCantBuildOn)
 			m_CantBuildOn[index] = rval.m_CantBuildOn[index];
	} 
 	// only replace values that have been set
	if((rval.m_flags0 & k_TerrainImprovement_Effect_Bit) != 0) 
		m_EffectValue = rval.m_EffectValue; 

	// replace struct elements of m_TerrainEffect
	for (index = 0; index < m_numTerrainEffect; index++) 
	{ 
		// find matching struct element
		for (int obj_index = 0; obj_index < rval.m_numTerrainEffect; obj_index++) 
			if (m_TerrainEffect[index] == rval.m_TerrainEffect[obj_index]) {
				// replace struct element 
				m_TerrainEffect[index] = rval.m_TerrainEffect[obj_index]; 
				}
	} 
		m_numConstructionTiles = rval.m_numConstructionTiles;
 	for (index = 0; index < m_numConstructionTiles; index++) 
	{ 
		// replace atomic element ConstructionTiles
		m_ConstructionTiles[index] = rval.m_ConstructionTiles[index]; 
	} 

	// only replace values that have been set
	if((rval.m_flags0 & k_TerrainImprovement_TerraformTerrain_Bit) != 0) 
		m_TerraformTerrainValue = rval.m_TerraformTerrainValue; 

	// only replace values that have been set
	if((rval.m_flags0 & k_TerrainImprovement_Column_Bit) != 0) 
		m_ColumnValue = rval.m_ColumnValue; 

	// only replace values that have been set
	if((rval.m_flags0 & k_TerrainImprovement_IntBorderRadius_Bit) != 0) 
		m_IntBorderRadiusValue = rval.m_IntBorderRadiusValue; 

	// only replace values that have been set
	if((rval.m_flags0 & k_TerrainImprovement_SquaredBorderRadius_Bit) != 0) 
		m_SquaredBorderRadiusValue = rval.m_SquaredBorderRadiusValue; 

} 

/*
 * Data accessors
 * (DO NOT EDIT!  Automatically generated file)
 */
sint32 TerrainImprovementRecord::GetCantBuildOnIndex(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numCantBuildOn);
    if((index < 0) || (index >= m_numCantBuildOn)) {
        return 0;
    }
    return m_CantBuildOn[index];
}

const TerrainRecord *TerrainImprovementRecord::GetCantBuildOn(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numCantBuildOn);
    if((index < 0) || (index >= m_numCantBuildOn)) {
        return 0;
    }
    return g_theTerrainDB->Get(m_CantBuildOn[index]);
}

const TerrainImprovementRecord::Effect *TerrainImprovementRecord::GetTerrainEffect(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numTerrainEffect);
    if((index < 0) || (index >= m_numTerrainEffect)) {
        return 0;
    }
    return &m_TerrainEffect[index];
}

const IconRecord *TerrainImprovementRecord::GetIcon() const
{
    return g_theIconDB->Get(m_Icon);
}

sint32 TerrainImprovementRecord::GetConstructionTiles(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numConstructionTiles);
    if((index < 0) || (index >= m_numConstructionTiles)) {
        return 0;
    }
    return m_ConstructionTiles[index];
}

const TerrainRecord *TerrainImprovementRecord::GetTerraformTerrainPtr() const
{
    return g_theTerrainDB->Get(m_TerraformTerrainValue);
}

sint32 TerrainImprovementRecord::Effect::GetTerrainIndex(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numTerrain);
    if((index < 0) || (index >= m_numTerrain)) {
        return 0;
    }
    return m_Terrain[index];
}

const TerrainRecord *TerrainImprovementRecord::Effect::GetTerrain(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numTerrain);
    if((index < 0) || (index >= m_numTerrain)) {
        return 0;
    }
    return g_theTerrainDB->Get(m_Terrain[index]);
}

const AdvanceRecord *TerrainImprovementRecord::Effect::GetEnableAdvance() const
{
    return g_theAdvanceDB->Get(m_EnableAdvance);
}

sint32 TerrainImprovementRecord::Effect::GetObsoleteAdvanceIndex(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numObsoleteAdvance);
    if((index < 0) || (index >= m_numObsoleteAdvance)) {
        return 0;
    }
    return m_ObsoleteAdvance[index];
}

const AdvanceRecord *TerrainImprovementRecord::Effect::GetObsoleteAdvance(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numObsoleteAdvance);
    if((index < 0) || (index >= m_numObsoleteAdvance)) {
        return 0;
    }
    return g_theAdvanceDB->Get(m_ObsoleteAdvance[index]);
}
