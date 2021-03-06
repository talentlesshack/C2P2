//----------------------------------------------------------------------------
//
// Project      : Call To Power 2
// File type    : C++ header file
// Description  : Global declarations
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
/// \file   Globals.h
/// \brief  Global declarations

#if defined(HAVE_PRAGMA_ONCE)
#pragma once
#endif

#ifndef GLOBALS_H
#define GLOBALS_H

//----------------------------------------------------------------------------
// Library dependencies
//----------------------------------------------------------------------------

// None

//----------------------------------------------------------------------------
// Export overview
//----------------------------------------------------------------------------

#define k_GAME_OBJ_TYPE_NOTHING                 0
#define k_GAME_OBJ_TYPE_UNIT                    1
#define k_GAME_OBJ_TYPE_POP                     2
#define k_GAME_OBJ_TYPE_IMPROVEMENT             3
#define k_GAME_OBJ_TYPE_TRADE_ROUTE             4
#define k_GAME_OBJ_TYPE_TRADE_OFFER             5
#define k_GAME_OBJ_TYPE_TERRAIN_IMPROVEMENT     6
#define k_GAME_OBJ_TYPE_DIPLOMATIC_REQUEST      7
#define k_GAME_OBJ_TYPE_INSTALLATION            8
#define k_GAME_OBJ_TYPE_WONDER                  9
#define k_GAME_OBJ_TYPE_CIVILISATION            10
#define k_GAME_OBJ_TYPE_AGREEMENT               11
#define k_GAME_OBJ_TYPE_MESSAGE                 12
#define k_GAME_OBJ_TYPE_ARMY                    13
#define k_GAME_OBJ_TYPE_ENDGAME_OBJECT          14
#define k_GAME_OBJ_TYPE_TERRAIN_IMPROVEMENT_DB  15
#define k_GAME_OBJ_TYPE_CAPITALIZATION          16
#define k_GAME_OBJ_TYPE_INFRASTRUCTURE          17


#define k_MAP_WRAPAROUND 5


enum ATTITUDE
{
	ATTITUDE_NULL,
	ATTITUDE_HAPPY,
	ATTITUDE_CONTENT,
	ATTITUDE_ANGRY,
	ATTITUDE_NO_EFFECT
};

enum MAPSIZE
{
	MAPSIZE_SMALL,
	MAPSIZE_MEDIUM,
	MAPSIZE_LARGE,
	MAPSIZE_GIGANTIC
};


// Global utilities for allocated object pointers
namespace allocated
{

/// Reassign an allocated object
/// \param      a_Pointer	Pointer to reassign to
/// \param      a_NewPointer  New value to assign
/// \remarks    The pointer shall have been allocated with new (or be 
///             NULL, in which case this function is an assignment).
/// This looked like a nice idea, but is not working well. The 
/// new pointer parameter was constructed before deleting the old, 
/// so too much memory is used.
/// A posibilty would be to create the new object inside template
/// function by using the default constructor of type T.
template <typename T> void reassign(T * & a_Pointer, T * a_NewPointer)
{
    delete a_Pointer;
    a_Pointer = a_NewPointer;
}

/// Clear an allocated object
/// \param      a_Pointer	Pointer to clear
/// \remarks    The pointer shall have been allocated with new (or be 
///             NULL, in which case this function has no effect). 
template <typename T> void clear(T * & a_Pointer)
{
    delete a_Pointer;
    a_Pointer = NULL;
}

/// Delete items from a container containing pointers
/// \param a_Container The container to delete from
/// \remarks The container will be cleared after its items have been deleted
template <typename T> void clearContainer(T & a_Container)
{
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
    for (T::iterator p = a_Container.begin(); p != a_Container.end(); ++p)
    {
        delete *p;
    }
#else
    for (int i = 0; i < a_Container.size(); i++) {
        delete a_Container[i];
    }
#endif

    T().swap(a_Container);
};


} // namespace allocated

#endif
