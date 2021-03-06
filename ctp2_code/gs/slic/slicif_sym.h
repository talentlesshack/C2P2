#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif
#ifndef __SLICIF_SYM_H__
#define __SLICIF_SYM_H__

typedef enum {
	SLIC_SYM_IVAR,
#ifdef SLIC_DOUBLES
	SLIC_SYM_DVAR,
#endif
	SLIC_SYM_SVAR,
	SLIC_SYM_ID,
	SLIC_SYM_FUNC,
	SLIC_SYM_REGION,
	SLIC_SYM_COMPLEX_REGION,
	SLIC_SYM_STRING,
	SLIC_SYM_CITY,
	SLIC_SYM_UNIT,
	SLIC_SYM_ARMY,
	SLIC_SYM_LOCATION,
	SLIC_SYM_ARRAY,
	SLIC_SYM_BUILTIN,
	SLIC_SYM_STRUCT,
	SLIC_SYM_STRUCT_MEMBER,
	SLIC_SYM_PLAYER,
	SLIC_SYM_UFUNC,

	SLIC_SYM_POP,  
	SLIC_SYM_PATH, 
	SLIC_SYM_IMPROVEMENT, 

	SLIC_SYM_UNDEFINED,
    // Should not have more than 256 entries
} SLIC_SYM;


#endif
