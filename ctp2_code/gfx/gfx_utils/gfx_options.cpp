//----------------------------------------------------------------------------
//
// Project      : Call To Power 2
// File type    : C++ source
// Description  : Cell and Army text
// Id           : $Id:$
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
// -None
//
//----------------------------------------------------------------------------
//
// Modifications from the original Activision code:
//
// - The army text now appears in the debug log. (13-Aug-2008 Martin G�hmann)
//
//----------------------------------------------------------------------------


#include "c3.h"
#include "gfx_options.h"

#include "AvlTree.h"

#include "Army.h"
#include "ArmyData.h"
#include "Globals.h"
#include "ctpaidebug.h"

GraphicsOptions * g_graphicsOptions = NULL;

namespace
{

cmp_t CellAVLCompare(CellText *obj1, CellText *obj2)
{
	if (obj1->m_key < obj2->m_key) return MIN_CMP;
	if (obj1->m_key > obj2->m_key) return MAX_CMP;

	return EQ_CMP;
}

/// Encode a map position into a value (for fast comparison)
/// \param pos The map position to encode
/// \return Encoded 32 bit value
uint32 PackCellAVLKey(MapPoint const & pos)
{
	return (pos.x << 16 | pos.y);
}

} // namespace

GraphicsOptions::GraphicsOptions()
:
    m_armyTextOn              (false),
    m_cellTextOn              (false),
    m_armyNameOn              (false),
    m_cellAVL                 (new AvlTree<CellText *>())
{
}

GraphicsOptions::~GraphicsOptions()
{
    delete m_cellAVL;
}

void GraphicsOptions::Initialize(void)
{
	delete g_graphicsOptions;
	g_graphicsOptions = new GraphicsOptions();
}

void GraphicsOptions::Cleanup(void)
{
	allocated::clear(g_graphicsOptions);
}

// ArmyName added by E
void GraphicsOptions::ArmyNameOn(void)
{
	m_armyNameOn = true;
}

void GraphicsOptions::ArmyNameOff(void)
{
	m_armyNameOn = false;
}

void GraphicsOptions::ArmyTextOn(void)
{
	m_armyTextOn = true;
}

void GraphicsOptions::ArmyTextOff(void)
{
	m_armyTextOn = false;
}

bool GraphicsOptions::AddTextToArmy(Army army, const char *text, const uint8 &colorMagnitude, const sint32 goalType) const
{
	if (!army.IsValid())
		return false;

	army.AccessData()->SetDebugString(text);
	army.AccessData()->SetDebugStringColor(colorMagnitude);

	AI_DPRINTF(k_DBG_SCHEDULER, army->GetOwner(), goalType, army.m_id, ("\t\t%s\n", text));

	return true;
}

void GraphicsOptions::ResetArmyText(Army army)
{
	if (army.IsValid())
	{
		army.AccessData()->SetDebugString(NULL);
	}
}

void GraphicsOptions::CellTextOn(void)
{
	m_cellTextOn = true;
}

void GraphicsOptions::CellTextOff(void)
{
	m_cellTextOn = false;
}

CellText *GraphicsOptions::GetCellText(MapPoint const &pos)
{
	CellText dummyCellText;
	dummyCellText.m_key = PackCellAVLKey(pos);
	
	Comparable<CellText *> * avlObject = m_cellAVL->Search(&dummyCellText);
	return (avlObject) ? avlObject->Key() : NULL;
}

bool GraphicsOptions::AddTextToCell(const MapPoint &pos, const char *text, 
									const uint8 &colorMagnitude)
{
	if (!m_cellTextOn) return false;

	CellText * cellText = GetCellText(pos);
	if (cellText) 
	{
		delete [] cellText->m_text;
		cellText->m_text = NULL;
	}

	if (text)
	{
		MBCHAR * newText = new MBCHAR[strlen(text) + 1];
		strcpy(newText, text);

		if (!cellText)
		{
			cellText = new CellText;
			cellText->m_key = PackCellAVLKey(pos);
			m_cellAVL->Insert(new Comparable<CellText *>(cellText, CellAVLCompare));
		}

		cellText->m_text = newText;
		cellText->m_color = colorMagnitude;
	}

	return true;
}

void GraphicsOptions::ResetCellText(const MapPoint &pos)
{
	CellText *cellText = GetCellText(pos);
	if (cellText) 
	{
		delete [] cellText->m_text;
		m_cellAVL->Delete(cellText);
		delete cellText;
	}
}
