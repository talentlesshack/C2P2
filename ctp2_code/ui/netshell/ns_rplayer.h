//----------------------------------------------------------------------------
//
// Project      : Call To Power 2
// File type    : C++ header
// Description  : 
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
//----------------------------------------------------------------------------
//
// Modifications from the original Activision code:
//
// - Corrected strange access of non-static members from static data.
//
//----------------------------------------------------------------------------

#ifndef __NS_RPLAYER_H__
#define __NS_RPLAYER_H__

#include "ns_object.h"


class ns_RPlayer : public ns_Object<NETFunc::Player, ns_RPlayer>
{
public:
	ns_RPlayer(NETFunc::Player * player);
	void Update( NETFunc::Player *player );

	char *m_name;
	int m_ping;
};

#endif 
