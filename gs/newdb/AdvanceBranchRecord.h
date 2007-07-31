
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#ifndef __AdvanceBranch_RECORD_H__
#define __AdvanceBranch_RECORD_H__

/*
 * AdvanceBranch description
 */
#include "CTPRecord.h"
//
// Range definitions

/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */

class AdvanceBranchRecord : public CTPRecord
{
public:
    typedef sint32 (AdvanceBranchRecord::*IntAccessor)() const;
    typedef bool (AdvanceBranchRecord::*BoolAccessor)() const;
    typedef double (AdvanceBranchRecord::*FloatAccessor)() const ;
    typedef bool (AdvanceBranchRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool (AdvanceBranchRecord::*BitFloatAccessor)(double &val) const;
private:
    sint32            m_Value;
    char            * m_NameText;

public:
    AdvanceBranchRecord() { Init(); };
    ~AdvanceBranchRecord();
    Init();
    // These methods are needed for records to conform to
    // 'Orthodox Cannonical Form' and work with resizing STL vectors. 
    AdvanceBranchRecord(const AdvanceBranchRecord &rval) { Init(); *this = rval; }
    void operator=(const AdvanceBranchRecord &rval);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex);

    void ResolveDBReferences();
    void Merge(const AdvanceBranchRecord & rval);
    //
    // Accessors
    //
    sint32           GetValue() const { return m_Value; }
    const char      *GetNameText() const { return m_NameText; }
}; /* AdvanceBranchRecord */

struct AdvanceBranchRecordAccessorInfo {
    AdvanceBranchRecord::IntAccessor m_intAccessor;
    AdvanceBranchRecord::BoolAccessor m_boolAccessor;
    AdvanceBranchRecord::FloatAccessor m_floatAccessor;
    AdvanceBranchRecord::BitIntAccessor m_bitIntAccessor;
    AdvanceBranchRecord::BitFloatAccessor m_bitFloatAccessor;
};
extern AdvanceBranchRecordAccessorInfo g_AdvanceBranchRecord_Accessors[];
extern char *g_AdvanceBranch_Tokens[];
#define k_Num_AdvanceBranchRecord_Tokens 2

template <class T> class CTPDatabase;
extern CTPDatabase<AdvanceBranchRecord> *g_theAdvanceBranchDB;

#endif /* ifndef __AdvanceBranch_RECORD_H__ */