
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#ifndef __SpecialEffect_RECORD_H__
#define __SpecialEffect_RECORD_H__

/*
 * SpecialEffect description
 */
#include "CTPRecord.h"
//
// Range definitions

/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */

class SpecialEffectRecord : public CTPRecord
{
public:
    typedef sint32 (SpecialEffectRecord::*IntAccessor)() const;
    typedef bool (SpecialEffectRecord::*BoolAccessor)() const;
    typedef double (SpecialEffectRecord::*FloatAccessor)() const ;
    typedef bool (SpecialEffectRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool (SpecialEffectRecord::*BitFloatAccessor)(double &val) const;
private:
    sint32            m_Value;
    char            * m_NameText;

public:
    SpecialEffectRecord() { Init(); };
    ~SpecialEffectRecord();
    Init();
    // These methods are needed for records to conform to
    // 'Orthodox Cannonical Form' and work with resizing STL vectors. 
    SpecialEffectRecord(const SpecialEffectRecord &rval) { Init(); *this = rval; }
    void operator=(const SpecialEffectRecord &rval);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex);

    void ResolveDBReferences();
    void Merge(const SpecialEffectRecord & rval);
    //
    // Accessors
    //
    sint32           GetValue() const { return m_Value; }
    const char      *GetNameText() const { return m_NameText; }
}; /* SpecialEffectRecord */

struct SpecialEffectRecordAccessorInfo {
    SpecialEffectRecord::IntAccessor m_intAccessor;
    SpecialEffectRecord::BoolAccessor m_boolAccessor;
    SpecialEffectRecord::FloatAccessor m_floatAccessor;
    SpecialEffectRecord::BitIntAccessor m_bitIntAccessor;
    SpecialEffectRecord::BitFloatAccessor m_bitFloatAccessor;
};
extern SpecialEffectRecordAccessorInfo g_SpecialEffectRecord_Accessors[];
extern char *g_SpecialEffect_Tokens[];
#define k_Num_SpecialEffectRecord_Tokens 2

template <class T> class CTPDatabase;
extern CTPDatabase<SpecialEffectRecord> *g_theSpecialEffectDB;

#endif /* ifndef __SpecialEffect_RECORD_H__ */