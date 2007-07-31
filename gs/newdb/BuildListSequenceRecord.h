
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#ifndef __BuildListSequence_RECORD_H__
#define __BuildListSequence_RECORD_H__

/*
 * BuildListSequence description
 */
#include "CTPRecord.h"
//
// m_flags0
#define k_BuildListElement_WonderBuildList_Bit   0x00000001
#define k_BuildListElement_BuildingBuildList_Bit 0x00000002
#define k_BuildListElement_AllUnitBuildList_Bit  0x00000004
#define k_BuildListElement_GarrisonUnitBuildList_Bit 0x00000008
#define k_BuildListElement_Capitalization_Bit    0x00000010
#define k_BuildListElement_Infrastructure_Bit    0x00000020
#define k_BuildListElement_Freight_Bit           0x00000040
//
// Range definitions

/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
class WonderBuildListRecord;
class BuildingBuildListRecord;

class BuildListSequenceRecord : public CTPRecord
{
public:
    typedef sint32 (BuildListSequenceRecord::*IntAccessor)() const;
    typedef bool (BuildListSequenceRecord::*BoolAccessor)() const;
    typedef double (BuildListSequenceRecord::*FloatAccessor)() const ;
    typedef bool (BuildListSequenceRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool (BuildListSequenceRecord::*BitFloatAccessor)(double &val) const;
    class BuildListElement {
    private:
        uint32 m_flags0;

        sint32            m_WonderBuildListValue; // Index into WonderBuildList database
        sint32            m_BuildingBuildListValue; // Index into BuildingBuildList database
    public:
        BuildListElement();
        ~BuildListElement();
        void operator=(const BuildListElement & rval);
        bool operator==(const BuildListElement & rval) { 
          return false; 
        } 

        sint32 Parse(DBLexer *lex);
        sint32 ParseSequential(DBLexer *lex);
        static sint32 ParseInArray(DBLexer *lex, BuildListElement **array, sint32 *numElements);
        static sint32 ParseInArray(DBLexer *lex, BuildListElement *array, sint32 *numElements, sint32 maxSize);
        void ResolveDBReferences();
        bool             GetWonderBuildList() const { return (m_flags0 & k_BuildListElement_WonderBuildList_Bit) != 0; }
    bool             GetWonderBuildListIndex(sint32 &index) const {
                         if((m_flags0 & k_BuildListElement_WonderBuildList_Bit) == 0) return false;
                         index = m_WonderBuildListValue;
                         return true;
                     }
    bool             GetWonderBuildList(const WonderBuildListRecord *&rec) const;
    const WonderBuildListRecord  *GetWonderBuildListPtr() const;
        bool             GetBuildingBuildList() const { return (m_flags0 & k_BuildListElement_BuildingBuildList_Bit) != 0; }
    bool             GetBuildingBuildListIndex(sint32 &index) const {
                         if((m_flags0 & k_BuildListElement_BuildingBuildList_Bit) == 0) return false;
                         index = m_BuildingBuildListValue;
                         return true;
                     }
    bool             GetBuildingBuildList(const BuildingBuildListRecord *&rec) const;
    const BuildingBuildListRecord  *GetBuildingBuildListPtr() const;
        bool             GetAllUnitBuildList() const { return (m_flags0 & k_BuildListElement_AllUnitBuildList_Bit) != 0; }
        bool             GetGarrisonUnitBuildList() const { return (m_flags0 & k_BuildListElement_GarrisonUnitBuildList_Bit) != 0; }
        bool             GetCapitalization() const { return (m_flags0 & k_BuildListElement_Capitalization_Bit) != 0; }
        bool             GetInfrastructure() const { return (m_flags0 & k_BuildListElement_Infrastructure_Bit) != 0; }
        bool             GetFreight() const { return (m_flags0 & k_BuildListElement_Freight_Bit) != 0; }
    }; /* class BuildListElement */

private:
    BuildListElement  *m_BuildListElement;
    sint32           m_numBuildListElement;

public:
    BuildListSequenceRecord() { Init(); };
    ~BuildListSequenceRecord();
    Init();
    // These methods are needed for records to conform to
    // 'Orthodox Cannonical Form' and work with resizing STL vectors. 
    BuildListSequenceRecord(const BuildListSequenceRecord &rval) { Init(); *this = rval; }
    void operator=(const BuildListSequenceRecord &rval);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex);

    void ResolveDBReferences();
    void Merge(const BuildListSequenceRecord & rval);
    //
    // Accessors
    //
    const BuildListElement *GetBuildListElement(sint32 index) const;
    sint32           GetNumBuildListElement() const { return m_numBuildListElement;}
}; /* BuildListSequenceRecord */

struct BuildListSequenceRecordAccessorInfo {
    BuildListSequenceRecord::IntAccessor m_intAccessor;
    BuildListSequenceRecord::BoolAccessor m_boolAccessor;
    BuildListSequenceRecord::FloatAccessor m_floatAccessor;
    BuildListSequenceRecord::BitIntAccessor m_bitIntAccessor;
    BuildListSequenceRecord::BitFloatAccessor m_bitFloatAccessor;
};
extern BuildListSequenceRecordAccessorInfo g_BuildListSequenceRecord_Accessors[];
extern char *g_BuildListSequence_Tokens[];
#define k_Num_BuildListSequenceRecord_Tokens 1

template <class T> class CTPDatabase;
extern CTPDatabase<BuildListSequenceRecord> *g_theBuildListSequenceDB;

#endif /* ifndef __BuildListSequence_RECORD_H__ */