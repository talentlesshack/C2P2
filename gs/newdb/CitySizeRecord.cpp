
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#include "c3.h"
#include "c3errors.h"
#include "CitySizeRecord.h"
#include "DBLexer.h"
#include "DBTokens.h"
#include "CTPDatabase.h"
#include "StrDB.h"
#include "BitArray.h"


CTPDatabase<CitySizeRecord> *g_theCitySizeDB = NULL;

CitySizeRecord::Init()
{
    m_Population = 0;
    m_SquaredRadius = 0;
    m_IntRadius = 0;
    m_VisionRadius = 0.000000;
    m_MaxWorkers = 0;
    m_GrowthRate = 0;
    m_MinGrowthRate = 0;
    m_MaxSurplusFood = 0;
    m_BaseOvercrowding = 0;
    m_BaseMaxPop = 0;
}

CitySizeRecord::~CitySizeRecord()
{
	int index = 0;
}

void CitySizeRecord::operator=(const CitySizeRecord & rval)
{
	int index = 0;
	m_index = rval.m_index;
	m_Population = rval.m_Population; 

	m_SquaredRadius = rval.m_SquaredRadius; 

	m_IntRadius = rval.m_IntRadius; 

	m_VisionRadius = rval.m_VisionRadius; 

	m_MaxWorkers = rval.m_MaxWorkers; 

	m_GrowthRate = rval.m_GrowthRate; 

	m_MinGrowthRate = rval.m_MinGrowthRate; 

	m_MaxSurplusFood = rval.m_MaxSurplusFood; 

	m_BaseOvercrowding = rval.m_BaseOvercrowding; 

	m_BaseMaxPop = rval.m_BaseMaxPop; 

}

char *g_CitySize_Tokens[] =
{
    "Population",
    "SquaredRadius",
    "IntRadius",
    "VisionRadius",
    "MaxWorkers",
    "GrowthRate",
    "MinGrowthRate",
    "MaxSurplusFood",
    "BaseOvercrowding",
    "BaseMaxPop",
};

CitySizeRecordAccessorInfo g_CitySizeRecord_Accessors[] = 
{
    { CitySizeRecord::GetPopulation, NULL, NULL, NULL, NULL },
    { CitySizeRecord::GetSquaredRadius, NULL, NULL, NULL, NULL },
    { CitySizeRecord::GetIntRadius, NULL, NULL, NULL, NULL },
    { NULL, NULL, CitySizeRecord::GetVisionRadius, NULL, NULL },
    { CitySizeRecord::GetMaxWorkers, NULL, NULL, NULL, NULL },
    { CitySizeRecord::GetGrowthRate, NULL, NULL, NULL, NULL },
    { CitySizeRecord::GetMinGrowthRate, NULL, NULL, NULL, NULL },
    { CitySizeRecord::GetMaxSurplusFood, NULL, NULL, NULL, NULL },
    { CitySizeRecord::GetBaseOvercrowding, NULL, NULL, NULL, NULL },
    { CitySizeRecord::GetBaseMaxPop, NULL, NULL, NULL, NULL },
};

#define k_Token_CitySize_Population              ((k_Token_Custom_Base) + 0)
#define k_Token_CitySize_SquaredRadius           ((k_Token_Custom_Base) + 1)
#define k_Token_CitySize_IntRadius               ((k_Token_Custom_Base) + 2)
#define k_Token_CitySize_VisionRadius            ((k_Token_Custom_Base) + 3)
#define k_Token_CitySize_MaxWorkers              ((k_Token_Custom_Base) + 4)
#define k_Token_CitySize_GrowthRate              ((k_Token_Custom_Base) + 5)
#define k_Token_CitySize_MinGrowthRate           ((k_Token_Custom_Base) + 6)
#define k_Token_CitySize_MaxSurplusFood          ((k_Token_Custom_Base) + 7)
#define k_Token_CitySize_BaseOvercrowding        ((k_Token_Custom_Base) + 8)
#define k_Token_CitySize_BaseMaxPop              ((k_Token_Custom_Base) + 9)
#define k_Token_CitySize_Max                     ((k_Token_Custom_Base) + 10)


static BitArray s_ParsedTokens(10);
void CitySizeRecord::CheckRequiredFields(DBLexer *lex)
{
    // Ick.
    if(!s_ParsedTokens.Bit(k_Token_CitySize_Population - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field Population missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_SquaredRadius - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field SquaredRadius missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_IntRadius - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field IntRadius missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_VisionRadius - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field VisionRadius missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_MaxWorkers - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field MaxWorkers missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_GrowthRate - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field GrowthRate missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_MinGrowthRate - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field MinGrowthRate missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_MaxSurplusFood - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field MaxSurplusFood missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_BaseOvercrowding - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field BaseOvercrowding missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_CitySize_BaseMaxPop - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field BaseMaxPop missing"));
    }
}
    
sint32 CitySizeRecord::Parse(DBLexer *lex)
{
    bool done = false;
    sint32 result = 0;
    sint32 tok;
    DBPARSE_ERROR err = DBPARSE_OK;
    s_ParsedTokens.Clear();
    lex->SetTokens(g_CitySize_Tokens, k_Token_CitySize_Max);
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
        if(tok >= k_Token_Custom_Base && tok < k_Token_CitySize_Max) { 
            s_ParsedTokens.SetBit(tok - k_Token_Custom_Base);
        }
        switch(tok) {
            case k_Token_CitySize_Population:
                if(!lex->GetIntAssignment(m_Population)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_SquaredRadius:
                if(!lex->GetIntAssignment(m_SquaredRadius)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_IntRadius:
                if(!lex->GetIntAssignment(m_IntRadius)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_VisionRadius:
                if(!lex->GetFloatAssignment(m_VisionRadius)) {
                    DBERROR(("Expected number"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_MaxWorkers:
                if(!lex->GetIntAssignment(m_MaxWorkers)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_GrowthRate:
                if(!lex->GetIntAssignment(m_GrowthRate)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_MinGrowthRate:
                if(!lex->GetIntAssignment(m_MinGrowthRate)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_MaxSurplusFood:
                if(!lex->GetIntAssignment(m_MaxSurplusFood)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_BaseOvercrowding:
                if(!lex->GetIntAssignment(m_BaseOvercrowding)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_CitySize_BaseMaxPop:
                if(!lex->GetIntAssignment(m_BaseMaxPop)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
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

void CitySizeRecord::ResolveDBReferences()
{
}
/*
 * Member class Parsers
 * (DO NOT EDIT!  Automatically generated file)
 */
/*
 * Data Parsers
 * (DO NOT EDIT!  Automatically generated file)
 */
void CitySizeRecord::Merge(const CitySizeRecord & rval){
	int index = 0, obj_index = 0;
} 

/*
 * Data accessors
 * (DO NOT EDIT!  Automatically generated file)
 */