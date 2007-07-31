
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#include "c3.h"
#include "c3errors.h"
#include "AgeRecord.h"
#include "DBLexer.h"
#include "DBTokens.h"
#include "CTPDatabase.h"
#include "StrDB.h"
#include "BitArray.h"


CTPDatabase<AgeRecord> *g_theAgeDB = NULL;

AgeRecord::Init()
{
    m_Age = 0;
    m_StartingRound = 0;
    m_NeedAdvances = 0;
    m_SlicObject = NULL;
}

AgeRecord::~AgeRecord()
{
	int index = 0;
	// free string attribute SlicObject
	if (m_SlicObject) 
		delete m_SlicObject; 
	m_SlicObject = NULL; 

}

void AgeRecord::operator=(const AgeRecord & rval)
{
	int index = 0;
	m_index = rval.m_index;
	m_Age = rval.m_Age; 

	m_StartingRound = rval.m_StartingRound; 

	m_NeedAdvances = rval.m_NeedAdvances; 

	if (m_SlicObject) 
	{ 
	delete m_SlicObject; 

	}

	if (rval.m_SlicObject) 
	{ 
		m_SlicObject = new char [strlen(rval.m_SlicObject)+1]; 
		strcpy(m_SlicObject, rval.m_SlicObject);
	}

}

char *g_Age_Tokens[] =
{
    "Age",
    "StartingRound",
    "NeedAdvances",
    "SlicObject",
};

AgeRecordAccessorInfo g_AgeRecord_Accessors[] = 
{
    { AgeRecord::GetAge, NULL, NULL, NULL, NULL },
    { AgeRecord::GetStartingRound, NULL, NULL, NULL, NULL },
    { AgeRecord::GetNeedAdvances, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL}, /* SlicObject */
};

#define k_Token_Age_Age                          ((k_Token_Custom_Base) + 0)
#define k_Token_Age_StartingRound                ((k_Token_Custom_Base) + 1)
#define k_Token_Age_NeedAdvances                 ((k_Token_Custom_Base) + 2)
#define k_Token_Age_SlicObject                   ((k_Token_Custom_Base) + 3)
#define k_Token_Age_Max                          ((k_Token_Custom_Base) + 4)


static BitArray s_ParsedTokens(4);
void AgeRecord::CheckRequiredFields(DBLexer *lex)
{
    // Ick.
    if(!s_ParsedTokens.Bit(k_Token_Age_Age - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field Age missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_Age_StartingRound - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field StartingRound missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_Age_NeedAdvances - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field NeedAdvances missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_Age_SlicObject - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field SlicObject missing"));
    }
}
    
sint32 AgeRecord::Parse(DBLexer *lex)
{
    bool done = false;
    sint32 result = 0;
    sint32 tok;
    DBPARSE_ERROR err = DBPARSE_OK;
    s_ParsedTokens.Clear();
    lex->SetTokens(g_Age_Tokens, k_Token_Age_Max);
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
        if(tok >= k_Token_Custom_Base && tok < k_Token_Age_Max) { 
            s_ParsedTokens.SetBit(tok - k_Token_Custom_Base);
        }
        switch(tok) {
            case k_Token_Age_Age:
                if(!lex->GetIntAssignment(m_Age)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_Age_StartingRound:
                if(!lex->GetIntAssignment(m_StartingRound)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_Age_NeedAdvances:
                if(!lex->GetIntAssignment(m_NeedAdvances)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_Age_SlicObject:
                if(!lex->GetFileAssignment(m_SlicObject)) {
                    DBERROR(("Expected string"));
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

void AgeRecord::ResolveDBReferences()
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
void AgeRecord::Merge(const AgeRecord & rval){
	int index = 0, obj_index = 0;
} 

/*
 * Data accessors
 * (DO NOT EDIT!  Automatically generated file)
 */