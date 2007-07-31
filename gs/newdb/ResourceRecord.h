
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#ifndef __Resource_RECORD_H__
#define __Resource_RECORD_H__

/*
 * Resource description
 */
#include "CTPRecord.h"
//
// m_flags0
#define k_Resource_GLHidden_Bit                  0x00000001
//
// Range definitions

/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
class SoundRecord;
class IconRecord;

class ResourceRecord : public CTPRecord
{
public:
    typedef sint32 (ResourceRecord::*IntAccessor)() const;
    typedef bool (ResourceRecord::*BoolAccessor)() const;
    typedef double (ResourceRecord::*FloatAccessor)() const ;
    typedef bool (ResourceRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool (ResourceRecord::*BitFloatAccessor)(double &val) const;
private:
    uint32 m_flags0;

    sint32            m_Gold;
    sint32            m_Food;
    sint32            m_Production;
    sint32            m_SpriteID;
    double            m_Probability;
    sint32            m_Sound; // Index into Sound database
    sint32            m_Icon; // Index into Icon database

public:
    ResourceRecord() { Init(); };
    ~ResourceRecord();
    Init();
    // These methods are needed for records to conform to
    // 'Orthodox Cannonical Form' and work with resizing STL vectors. 
    ResourceRecord(const ResourceRecord &rval) { Init(); *this = rval; }
    void operator=(const ResourceRecord &rval);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex);

    void ResolveDBReferences();
    void Merge(const ResourceRecord & rval);
    //
    // Accessors
    //
    sint32           GetGold() const { return m_Gold; }
    sint32           GetFood() const { return m_Food; }
    sint32           GetProduction() const { return m_Production; }
    sint32           GetSpriteID() const { return m_SpriteID; }
    double           GetProbability() const { return m_Probability; }
    sint32           GetSoundIndex() const { return m_Sound; }
    const SoundRecord *GetSound() const;
    sint32           GetIconIndex() const { return m_Icon; }
    const IconRecord *GetIcon() const;
    bool             GetGLHidden() const { return (m_flags0 & k_Resource_GLHidden_Bit) != 0; }
}; /* ResourceRecord */

struct ResourceRecordAccessorInfo {
    ResourceRecord::IntAccessor m_intAccessor;
    ResourceRecord::BoolAccessor m_boolAccessor;
    ResourceRecord::FloatAccessor m_floatAccessor;
    ResourceRecord::BitIntAccessor m_bitIntAccessor;
    ResourceRecord::BitFloatAccessor m_bitFloatAccessor;
};
extern ResourceRecordAccessorInfo g_ResourceRecord_Accessors[];
extern char *g_Resource_Tokens[];
#define k_Num_ResourceRecord_Tokens 8

template <class T> class CTPDatabase;
extern CTPDatabase<ResourceRecord> *g_theResourceDB;

#endif /* ifndef __Resource_RECORD_H__ */