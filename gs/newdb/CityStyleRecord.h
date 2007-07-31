
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#ifndef __CityStyle_RECORD_H__
#define __CityStyle_RECORD_H__

/*
 * CityStyle description
 */
#include "CTPRecord.h"
//
// Range definitions

/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
class AgeCityStyleRecord;

class CityStyleRecord : public CTPRecord
{
public:
    typedef sint32 (CityStyleRecord::*IntAccessor)() const;
    typedef bool (CityStyleRecord::*BoolAccessor)() const;
    typedef double (CityStyleRecord::*FloatAccessor)() const ;
    typedef bool (CityStyleRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool (CityStyleRecord::*BitFloatAccessor)(double &val) const;
private:
    sint32           *m_AgeStyle; // Index into AgeCityStyle database
    sint32           m_numAgeStyle;

public:
    CityStyleRecord() { Init(); };
    ~CityStyleRecord();
    Init();
    // These methods are needed for records to conform to
    // 'Orthodox Cannonical Form' and work with resizing STL vectors. 
    CityStyleRecord(const CityStyleRecord &rval) { Init(); *this = rval; }
    void operator=(const CityStyleRecord &rval);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex);

    void ResolveDBReferences();
    void Merge(const CityStyleRecord & rval);
    //
    // Accessors
    //
    sint32           GetAgeStyleIndex(sint32 index) const;
    const AgeCityStyleRecord *GetAgeStyle(sint32 index) const;
    sint32           GetNumAgeStyle() const { return m_numAgeStyle;}
}; /* CityStyleRecord */

struct CityStyleRecordAccessorInfo {
    CityStyleRecord::IntAccessor m_intAccessor;
    CityStyleRecord::BoolAccessor m_boolAccessor;
    CityStyleRecord::FloatAccessor m_floatAccessor;
    CityStyleRecord::BitIntAccessor m_bitIntAccessor;
    CityStyleRecord::BitFloatAccessor m_bitFloatAccessor;
};
extern CityStyleRecordAccessorInfo g_CityStyleRecord_Accessors[];
extern char *g_CityStyle_Tokens[];
#define k_Num_CityStyleRecord_Tokens 1

template <class T> class CTPDatabase;
extern CTPDatabase<CityStyleRecord> *g_theCityStyleDB;

#endif /* ifndef __CityStyle_RECORD_H__ */