//----------------------------------------------------------------------------
//
// Project      : Call To Power 2
// File type    : C++ source
// Description  : Effect actor
// Id           : $Id$
//
//----------------------------------------------------------------------------
//
// Disclaimer
//
// THIS FILE IS NOT GENERATED OR SUPPORTED BY ACTIVISION.
//
// This material has been developed at apolyton.net by the Apolyton CtP2 
// Source Code Project. Contact the authors at ctp2source@apolyton.net.
//
//----------------------------------------------------------------------------
//
// Compiler flags
//
// - None
//
//----------------------------------------------------------------------------
//
// Modifications from the original Activision code:
//
// - Removed some unused local variables. (Sep 9th 2005 Martin G�hmann)
//
//----------------------------------------------------------------------------

#include "c3.h"
#include "EffectActor.h"

#include "aui.h"
#include "pixelutils.h"
#include "tileutils.h"

#include "FacedSpriteWshadow.h"
#include "EffectSpriteGroup.h"
#include "SpriteState.h"
#include "Actor.h"
#include "SpriteGroupList.h"
#include "tiledmap.h"
#include "Anim.h"
#include "Action.h"
#include "director.h"
#include "colorset.h"
#include "maputils.h"

#define k_doInvisible FALSE

extern SpriteGroupList	*g_effectSpriteGroupList;
extern TiledMap			*g_tiledMap;
extern Director			*g_director;

EffectActor::EffectActor(SpriteState * ss, const MapPoint & pos)
: 
    Actor                       (ss),
    m_pos                       (pos),
    m_savePos                   (),
    m_shX                       (0), 
    m_shY                       (0), 
    m_effectSpriteGroup         (NULL),
    m_facing                    (0),
    m_lastMoveFacing            (k_DEFAULTSPRITEFACING),
    m_frame                     (0),
//    m_transparency;
    m_curAction                 (NULL),
    m_curEffectAction           (EFFECTACTION_NONE),
    m_actionQueue               (k_MAX_ACTION_QUEUE_SIZE),
//    m_playerNum;
    m_effectVisibility          (0), 
//    m_effectSaveVisibility; 
    m_dieAtTick                 (0),
//    m_directionalAttack; 
    m_needsToDie                (false), 
    m_killNow                   (false), 
    m_generateDeath             (false),
    m_bVisSpecial               (false) 
{
    if (ss && g_effectSpriteGroupList)
    {
	    m_effectSpriteGroup = (EffectSpriteGroup *)
            g_effectSpriteGroupList->GetSprite
                (ss->GetIndex(), GROUPTYPE_EFFECT, LOADTYPE_FULL,(GAME_ACTION) 0);
    }
}


EffectActor::~EffectActor()
{
    if (g_effectSpriteGroupList && m_spriteState)
    {
	    g_effectSpriteGroupList->ReleaseSprite(m_spriteState->GetIndex(), LOADTYPE_FULL);
    }

    /// @todo Check moving m_spriteState delete to Actor
	delete m_spriteState;
	m_spriteState = NULL;
}

void EffectActor::ChangeType(SpriteState *ss, sint32 type,  Unit id)
{
	delete m_spriteState;
	m_spriteState = ss;

	
	m_effectSpriteGroup = (EffectSpriteGroup *)g_effectSpriteGroupList->GetSprite(ss->GetIndex(), GROUPTYPE_EFFECT, LOADTYPE_FULL,(GAME_ACTION)0);

}

void EffectActor::Process(void)
{
	

	
	
	
	
	if(!m_curAction)
		GetNextAction();
			
	if (m_curAction) {

		if(GetActionQueueNumItems() > 0)
			m_curAction->Process(LookAtNextAction());
		else
			m_curAction->Process();

			
		
		
		
		if (m_curAction->Finished()) 
		{
			MapPoint  end;
			m_curAction->GetEndMapPoint(end);
			if (end.x != 0 || end.y != 0) {
				m_pos = end;
			}

			GetNextAction();
		}
	}
	
	
	if (m_curAction != NULL) {
		sint32 x, y;

		maputils_MapXY2PixelXY(m_pos.x, m_pos.y, &x, &y);

		
		
		m_shX = m_x = x;
		m_shY = m_y = y;


		POINT curPt;

		
		if (m_curAction->GetPath() != NULL) {
			
			curPt = m_curAction->GetPosition();

			m_shX = m_x = curPt.x;
			m_shY = m_y = curPt.y;
		}

		if(m_curAction->GetActionType() == EFFECTACTION_PLAY)
		{
			m_lastMoveFacing = m_curAction->GetFacing();
		}

		if(m_curAction->SpecialDelayProcess())
		{
			m_facing = m_lastMoveFacing;
		}
		else
		{
			
			m_facing = m_curAction->GetFacing();
		}
		
		m_frame = m_curAction->GetSpriteFrame();
		
		m_transparency = m_curAction->GetTransparency();
		
		
		
		
		if(GetNeedsToDie() && m_curAction->GetCurrentEndCondition() == ACTIONEND_INTERRUPT)
		{
			SetKillNow();
		}

	}
}

void EffectActor::EndTurnProcess(void)
{
	

	
	while(GetActionQueueNumItems() > 0) 
	{
		GetNextAction(k_doInvisible);
		MapPoint  end;
		m_curAction->GetEndMapPoint(end);
		if (end.x != 0 || end.y != 0) 
		{
			m_pos = end;
		}
	}

	

	if (m_curAction != NULL) 
	{
		sint32 x, y;

		maputils_MapXY2PixelXY(m_pos.x, m_pos.y, &x, &y);

		m_shX = m_x = x;
		m_shY = m_y = y;

		
		m_frame = m_curAction->GetSpriteFrame();

		
		m_transparency = m_curAction->GetTransparency();

		POINT curPt;

		
		if (m_curAction->GetPath() != NULL) {
			
			curPt = m_curAction->GetPosition();

			m_shX = m_x = curPt.x;
			m_shY = m_y = curPt.y;
		}

		
		m_facing = m_curAction->GetFacing();

		
		
		
		if(GetNeedsToDie())
		{
			SetDieAtTick(0);  
			SetKillNow();
		}
	}
}

void EffectActor::GetNextAction(BOOL isVisible)
{
	uint32 numItems = GetActionQueueNumItems();

	delete m_curAction;
	m_curAction = NULL;

//	Action *pendingAction = LookAtNextAction(); // Not used
		
		
	if (numItems > 0) 
	{

		
		m_actionQueue.Dequeue(m_curAction);

		
		
				
		MapPoint curStartMapPoint, curEndMapPoint;
		m_curAction->GetStartMapPoint(curStartMapPoint);
		m_curAction->GetEndMapPoint(curEndMapPoint);
			
		if (m_curAction)
		{
			m_curEffectAction = (EFFECTACTION)m_curAction->GetActionType();
		}
		else
		{
			
			Assert(FALSE);
		}
	}
	else
	{
		
		if(numItems <= 0)
		{
			
			
			
			

			
			SetKillNow();
		}
		
	}
}


void EffectActor::AddAction(Action *actionObj)
{
	Assert(m_effectSpriteGroup && actionObj);
	if (!m_effectSpriteGroup || !actionObj) return;

	m_actionQueue.Enqueue(actionObj);
}

Anim *EffectActor::CreateAnim(EFFECTACTION action)
{
	Assert(m_effectSpriteGroup);
	if (!m_effectSpriteGroup) return NULL;

	Anim	* origAnim = m_effectSpriteGroup->GetAnim((GAME_ACTION) action);
	return origAnim ? new Anim(*origAnim) : NULL;
}

void EffectActor::Draw(void)
{
	uint16			flags   = k_DRAWFLAGS_NORMAL;;
	Pixel16			color   = 0x0000;
	sint32			xoffset = (sint32)((double)k_ACTOR_CENTER_OFFSET_X * g_tiledMap->GetScale());
	sint32			yoffset = (sint32)((double)k_ACTOR_CENTER_OFFSET_Y * g_tiledMap->GetScale());

	m_effectSpriteGroup->Draw(m_curEffectAction, m_frame, m_x+xoffset, m_y+yoffset, 
								m_shX+xoffset, m_shY+yoffset, m_facing, 
								g_tiledMap->GetScale(), m_transparency, color, flags,
								m_curAction->SpecialDelayProcess());
}

void EffectActor::DrawDirect(aui_Surface *surf, sint32 x, sint32 y)
{
	uint16			flags   = k_DRAWFLAGS_NORMAL;
	Pixel16			color   = 0;
	sint32			xoffset = (sint32)((double)k_ACTOR_CENTER_OFFSET_X * g_tiledMap->GetScale());
	sint32			yoffset = (sint32)((double)k_ACTOR_CENTER_OFFSET_Y * g_tiledMap->GetScale());


	if (m_transparency < 15) {
		flags |= k_BIT_DRAWFLAGS_TRANSPARENCY;	
	}
	BOOL specialDelayProcess = FALSE;

	if (m_curAction) {
		specialDelayProcess = m_curAction->SpecialDelayProcess();
	}
	
	m_effectSpriteGroup->DrawDirect(surf, m_curEffectAction, m_frame, m_x+xoffset, m_y+yoffset, 
								m_shX+xoffset, m_shY+yoffset, m_facing, 
								g_tiledMap->GetScale(), m_transparency, color, flags, specialDelayProcess);
}


void EffectActor::DrawDirectWithFlags(aui_Surface *surf, sint32 x, sint32 y, uint16 flags)
{
	Pixel16			color=0;
	sint32			xoffset = (sint32)((double)k_ACTOR_CENTER_OFFSET_X * g_tiledMap->GetScale());
	sint32			yoffset = (sint32)((double)k_ACTOR_CENTER_OFFSET_Y * g_tiledMap->GetScale());


	if (m_transparency < 15) {
		flags |= k_BIT_DRAWFLAGS_TRANSPARENCY;	
	}
	BOOL specialDelayProcess = FALSE;

	if (m_curAction) {
		specialDelayProcess = m_curAction->SpecialDelayProcess();
	}
	
	m_effectSpriteGroup->DrawDirect(surf, m_curEffectAction, m_frame, m_x+xoffset, m_y+yoffset, 
								m_shX+xoffset, m_shY+yoffset, m_facing, 
								g_tiledMap->GetScale(), m_transparency, color, flags, specialDelayProcess);
}

void EffectActor::DrawText(sint32 x, sint32 y, MBCHAR *effectText)
{
	m_effectSpriteGroup->DrawText(x, y, effectText);
}

uint16 EffectActor::GetWidth(void) const
{
    Assert(m_effectSpriteGroup);
    if (!m_effectSpriteGroup) return 0;

    Sprite * theSprite = m_effectSpriteGroup->GetGroupSprite((GAME_ACTION)m_curEffectAction);

    if (!theSprite && (m_curEffectAction != EFFECTACTION_PLAY))
    {
        theSprite = m_effectSpriteGroup->GetGroupSprite((GAME_ACTION)EFFECTACTION_PLAY);
    }

    return theSprite ? theSprite->GetWidth() : 0;
}

uint16 EffectActor::GetHeight(void) const
{
    Assert(m_effectSpriteGroup);
    if (!m_effectSpriteGroup) return 0;

    Sprite * theSprite = m_effectSpriteGroup->GetGroupSprite((GAME_ACTION)m_curEffectAction);

    if (!theSprite && (m_curEffectAction != EFFECTACTION_PLAY))
    {
        theSprite = m_effectSpriteGroup->GetGroupSprite((GAME_ACTION)EFFECTACTION_PLAY);
    }

    return theSprite ? theSprite->GetHeight() : 0;
}

void EffectActor::GetBoundingRect(RECT *rect) const
{
	Assert(rect);
	if (!rect) return;

	POINT	hotPoint = m_effectSpriteGroup->GetHotPoint(m_curEffectAction, m_facing);
	double	scale = g_tiledMap->GetScale();
	sint32	xoff = (sint32)((double)(k_ACTOR_CENTER_OFFSET_X - hotPoint.x) * scale), 
			yoff = (sint32)((double)(k_ACTOR_CENTER_OFFSET_Y - hotPoint.y) * scale);

	rect->left = 0;
	rect->top = 0;
	rect->right = (sint32)((double)GetWidth() * scale);
	rect->bottom = (sint32)((double)GetHeight() * scale);

	OffsetRect(rect, m_x+xoff, m_y+yoff);
}

