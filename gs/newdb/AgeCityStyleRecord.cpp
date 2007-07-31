
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#include "c3.h"
#include "c3errors.h"
#include "AgeCityStyleRecord.h"
#include "DBLexer.h"
#include "DBTokens.h"
#include "CTPDatabase.h"
#include "StrDB.h"
#include "BitArray.h"


CTPDatabase<AgeCityStyleRecord> *g_theAgeCityStyleDB = NULL;

AgeCityStyleRecord::Init()
{
    m_Sprites = NULL;
    m_numSprites = 0;
}

AgeCityStyleRecord::~AgeCityStyleRecord()
{
	int index = 0;
	// free array Sprites 
 			// free struct elements
	if (m_numSprites > 0) 
		delete [m_numSprites] m_Sprites; 
	m_Sprites = NULL; 
	m_numSprites = 0; 

}

void AgeCityStyleRecord::operator=(const AgeCityStyleRecord & rval)
{
	int index = 0;
	m_index = rval.m_index;
	// free array Sprites 
 	// free struct elements of Sprites[]
	if (m_numSprites > 0) 
	{
		delete [m_numSprites] m_Sprites; 
		m_Sprites = NULL; 
	}

	if (rval.m_numSprites > 0) 
	{
		m_Sprites = new SizeSprite [rval.m_numSprites];
	}

	// copy struct elements of Sprites[]
	for (index = 0; index < rval.m_numSprites; index++) 
		{ 
			m_Sprites[index] = rval.m_Sprites[index]; 
	} 
	m_numSprites = rval.m_numSprites;

}

char *g_AgeCityStyle_Tokens[] =
{
    "Sprites",
};

AgeCityStyleRecordAccessorInfo g_AgeCityStyleRecord_Accessors[] = 
{
    { NULL, NULL, NULL, NULL, NULL}, /* Sprites */
};

#define k_Token_AgeCityStyle_Sprites             ((k_Token_Custom_Base) + 0)
#define k_Token_AgeCityStyle_Max                 ((k_Token_Custom_Base) + 1)


static BitArray s_ParsedTokens(1);
void AgeCityStyleRecord::CheckRequiredFields(DBLexer *lex)
{
    // Ick.
}
    
sint32 AgeCityStyleRecord::Parse(DBLexer *lex)
{
    bool done = false;
    sint32 result = 0;
    sint32 tok;
    DBPARSE_ERROR err = DBPARSE_OK;
    s_ParsedTokens.Clear();
    lex->SetTokens(g_AgeCityStyle_Tokens, k_Token_AgeCityStyle_Max);
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
        if(tok >= k_Token_Custom_Base && tok < k_Token_AgeCityStyle_Max) { 
            s_ParsedTokens.SetBit(tok - k_Token_Custom_Base);
        }
        switch(tok) {
            case k_Token_AgeCityStyle_Sprites:
                if(!AgeCityStyleRecord::SizeSprite::ParseInArray(lex, &m_Sprites, &m_numSprites)) 
                {
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

void AgeCityStyleRecord::ResolveDBReferences()
{
    {
        sint32 i;
        for(i = 0; i < m_numSprites; i++) {
            m_Sprites[i].ResolveDBReferences();
        }
    }
}
/*
 * Member class Parsers
 * (DO NOT EDIT!  Automatically generated file)
 */
AgeCityStyleRecord::SizeSprite::SizeSprite()
{
    m_Type = 0;
    m_MinSize = 0;
    m_MaxSize = 0;
    m_Sprite = 0;
}
AgeCityStyleRecord::SizeSprite::~SizeSprite()
{
}
void AgeCityStyleRecord::SizeSprite::operator=(const SizeSprite & rval)
{
	m_Type = rval.m_Type; 

	m_MinSize = rval.m_MinSize; 

	m_MaxSize = rval.m_MaxSize; 

	m_Sprite = rval.m_Sprite; 

}
static char *s_AgeCityStyle_SizeSprite_Tokens[] = {
    "Type",
    "MinSize",
    "MaxSize",
    "Sprite",
};
#define k_Token_AgeCityStyle_SizeSprite_Type     ((k_Token_Custom_Base) + 0)
#define k_Token_AgeCityStyle_SizeSprite_MinSize  ((k_Token_Custom_Base) + 1)
#define k_Token_AgeCityStyle_SizeSprite_MaxSize  ((k_Token_Custom_Base) + 2)
#define k_Token_AgeCityStyle_SizeSprite_Sprite   ((k_Token_Custom_Base) + 3)
#define k_Token_AgeCityStyle_SizeSprite_Max ((k_Token_Custom_Base) + 4)
sint32 AgeCityStyleRecord::SizeSprite::ParseSequential(DBLexer *lex)
{
    DBPARSE_ERROR err = DBPARSE_OK;
    if(!lex->GetIntAssignment(m_Type)) {
        DBERROR(("Expected integer"));
        return 0;
    }
    if(!lex->GetIntAssignment(m_MinSize)) {
        DBERROR(("Expected integer"));
        return 0;
    }
    if(!lex->GetIntAssignment(m_MaxSize)) {
        DBERROR(("Expected integer"));
        return 0;
    }
    if(!lex->GetIntAssignment(m_Sprite)) {
        DBERROR(("Expected integer"));
        return 0;
    }
    return 1;
}
sint32 AgeCityStyleRecord::SizeSprite::Parse(DBLexer *lex)
{
    bool done = false;
    sint32 tok;
    sint32 result = 0;
    DBPARSE_ERROR err = DBPARSE_OK;
    tok = lex->PeekAhead();
    if(tok != k_Token_OpenBrace) {
        if(ParseSequential(lex)) {
            return 1;
        }
        DBERROR(("Expected open brace for SizeSprite"));
        return 0;
    }
    tok = lex->GetToken();
    lex->SetTokens(s_AgeCityStyle_SizeSprite_Tokens, k_Token_AgeCityStyle_SizeSprite_Max);
    while(!done) {
        tok = lex->GetToken();
        switch(tok) {
            case k_Token_AgeCityStyle_SizeSprite_Type:
                if(!lex->GetIntAssignment(m_Type)) {
                    done = true; break;
                }
                break;
            case k_Token_AgeCityStyle_SizeSprite_MinSize:
                if(!lex->GetIntAssignment(m_MinSize)) {
                    done = true; break;
                }
                break;
            case k_Token_AgeCityStyle_SizeSprite_MaxSize:
                if(!lex->GetIntAssignment(m_MaxSize)) {
                    done = true; break;
                }
                break;
            case k_Token_AgeCityStyle_SizeSprite_Sprite:
                if(!lex->GetIntAssignment(m_Sprite)) {
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

sint32 AgeCityStyleRecord::SizeSprite::ParseInArray(DBLexer *lex, SizeSprite **array, sint32 *numElements)
{
    if(*numElements > 0) {
        SizeSprite *oldArray = *array;
        *array = new SizeSprite[(*numElements) + 1];
        for (int i=0; i < (*numElements); i++) 
             (*array)[i] = oldArray[i];
        delete [] oldArray;
    } else {
        *array = new SizeSprite[1];
    }
    (*array)[*numElements].Parse(lex);
    *numElements += 1;
    return 1;
}
sint32 AgeCityStyleRecord::SizeSprite::ParseInArray(DBLexer *lex, SizeSprite *array, sint32 *numElements, sint32 maxSize)
{
    if(*numElements >= maxSize) {
        return 0;
    }
    array[*numElements].Parse(lex);
    *numElements += 1;
    return 1;
}
void AgeCityStyleRecord::SizeSprite::ResolveDBReferences()
{
}
/*
 * Data Parsers
 * (DO NOT EDIT!  Automatically generated file)
 */
void AgeCityStyleRecord::Merge(const AgeCityStyleRecord & rval){
	int index = 0, obj_index = 0;
	// replace struct elements of m_Sprites
	for (index = 0; index < m_numSprites; index++) 
	{ 
		// find matching struct element
		for (int obj_index = 0; obj_index < rval.m_numSprites; obj_index++) 
			if (m_Sprites[index] == rval.m_Sprites[obj_index]) {
				// replace struct element 
				m_Sprites[index] = rval.m_Sprites[obj_index]; 
				}
	} 
} 

/*
 * Data accessors
 * (DO NOT EDIT!  Automatically generated file)
 */
const AgeCityStyleRecord::SizeSprite *AgeCityStyleRecord::GetSprites(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numSprites);
    if((index < 0) || (index >= m_numSprites)) {
        return 0;
    }
    return &m_Sprites[index];
}
