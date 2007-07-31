
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#ifndef __Building_RECORD_H__
#define __Building_RECORD_H__

/*
 * Building description
 */
#include "CTPRecord.h"
//
// m_flags0
#define k_Building_Capitol_Bit                   0x00000001
#define k_Building_DefendersPercent_Bit          0x00000002
#define k_Building_HappyInc_Bit                  0x00000004
#define k_Building_DoubleTelevangelists_Bit      0x00000008
#define k_Building_ProductionPercent_Bit         0x00000010
#define k_Building_FoodPercent_Bit               0x00000020
#define k_Building_CommercePercent_Bit           0x00000040
#define k_Building_SciencePercent_Bit            0x00000080
#define k_Building_IncreaseBaseOvercrowding_Bit  0x00000100
#define k_Building_IncreaseMaxPopulation_Bit     0x00000200
#define k_Building_FoodVat_Bit                   0x00000400
#define k_Building_Airport_Bit                   0x00000800
#define k_Building_NoUnhappyPeople_Bit           0x00001000
#define k_Building_NoRushBuyPenalty_Bit          0x00002000
#define k_Building_LowerCrime_Bit                0x00004000
#define k_Building_PreventConversion_Bit         0x00008000
#define k_Building_PreventSlavery_Bit            0x00010000
#define k_Building_AllowGrunts_Bit               0x00020000
#define k_Building_LowerPeaceMovement_Bit        0x00040000
#define k_Building_GoldPerCitizen_Bit            0x00080000
#define k_Building_ProtectFromNukes_Bit          0x00100000
#define k_Building_ProtectFromBioAgents_Bit      0x00200000
#define k_Building_ProtectFromNanoVirus_Bit      0x00400000
#define k_Building_Television_Bit                0x00800000
#define k_Building_CityWalls_Bit                 0x01000000
#define k_Building_IsReligious_Bit               0x02000000
#define k_Building_ForceField_Bit                0x04000000
#define k_Building_CantBuildInSea_Bit            0x08000000
#define k_Building_CantBuildOnLand_Bit           0x10000000
#define k_Building_Cathedral_Bit                 0x20000000
#define k_Building_Brokerage_Bit                 0x40000000
#define k_Building_NuclearPlant_Bit              0x80000000
//
// m_flags1
#define k_Building_SciencePerPop_Bit             0x00000001
#define k_Building_RaiseOvercrowdingLevel_Bit    0x00000002
#define k_Building_RaiseMaxPopulation_Bit        0x00000004
#define k_Building_StarvationProtection_Bit      0x00000008
#define k_Building_CoastalBuilding_Bit           0x00000010
#define k_Building_OffenseBonusLand_Bit          0x00000020
#define k_Building_OffenseBonusWater_Bit         0x00000040
#define k_Building_OffenseBonusAir_Bit           0x00000080
#define k_Building_PopulationPollutionPercent_Bit 0x00000100
#define k_Building_ProductionPollutionPercent_Bit 0x00000200
#define k_Building_PollutionAmount_Bit           0x00000400
#define k_Building_GLHidden_Bit                  0x00000800
//
// Range definitions
#define k_MAX_ObsoleteAdvance                5

/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
class IconRecord;
class AdvanceRecord;
class AdvanceRecord;
class BuildingRecord;

class BuildingRecord : public CTPRecord
{
public:
    typedef sint32 (BuildingRecord::*IntAccessor)() const;
    typedef bool (BuildingRecord::*BoolAccessor)() const;
    typedef double (BuildingRecord::*FloatAccessor)() const ;
    typedef bool (BuildingRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool (BuildingRecord::*BitFloatAccessor)(double &val) const;
private:
    uint32 m_flags0;
    uint32 m_flags1;

    sint32            m_DefaultIcon; // Index into Icon database
    sint32            m_Description;
    sint32            m_EnableAdvance; // Index into Advance database
    sint32            m_ObsoleteAdvance[k_MAX_ObsoleteAdvance]; // Index into Advance database
    sint32           m_numObsoleteAdvance;
    sint32           *m_PrerequisiteBuilding; // Index into Building database
    sint32           m_numPrerequisiteBuilding;
    sint32            m_ProductionCost;
    sint32            m_Upkeep;
    double            m_DefendersPercentValue;
    sint32            m_HappyIncValue;
    double            m_ProductionPercentValue;
    double            m_FoodPercentValue;
    double            m_CommercePercentValue;
    double            m_SciencePercentValue;
    sint32            m_IncreaseBaseOvercrowdingValue;
    sint32            m_IncreaseMaxPopulationValue;
    double            m_FoodVatValue;
    double            m_LowerCrimeValue;
    double            m_PreventConversionValue;
    double            m_PreventSlaveryValue;
    double            m_LowerPeaceMovementValue;
    sint32            m_GoldPerCitizenValue;
    double            m_ProtectFromBioAgentsValue;
    double            m_ProtectFromNanoVirusValue;
    double            m_SciencePerPopValue;
    sint32            m_RaiseOvercrowdingLevelValue;
    sint32            m_RaiseMaxPopulationValue;
    sint32            m_StarvationProtectionValue;
    double            m_OffenseBonusLandValue;
    double            m_OffenseBonusWaterValue;
    double            m_OffenseBonusAirValue;
    double            m_PopulationPollutionPercentValue;
    double            m_ProductionPollutionPercentValue;
    double            m_PollutionAmountValue;

public:
    BuildingRecord() { Init(); };
    ~BuildingRecord();
    Init();
    // These methods are needed for records to conform to
    // 'Orthodox Cannonical Form' and work with resizing STL vectors. 
    BuildingRecord(const BuildingRecord &rval) { Init(); *this = rval; }
    void operator=(const BuildingRecord &rval);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex);

    void ResolveDBReferences();
    void Merge(const BuildingRecord & rval);
    //
    // Accessors
    //
    sint32           GetDefaultIconIndex() const { return m_DefaultIcon; }
    const IconRecord *GetDefaultIcon() const;
    sint32           GetDescription() const { return m_Description; }
    sint32           GetEnableAdvanceIndex() const { return m_EnableAdvance; }
    const AdvanceRecord *GetEnableAdvance() const;
    sint32           GetObsoleteAdvanceIndex(sint32 index) const;
    const AdvanceRecord *GetObsoleteAdvance(sint32 index) const;
    sint32           GetNumObsoleteAdvance() const { return m_numObsoleteAdvance;}
    sint32           GetPrerequisiteBuildingIndex(sint32 index) const;
    const BuildingRecord *GetPrerequisiteBuilding(sint32 index) const;
    sint32           GetNumPrerequisiteBuilding() const { return m_numPrerequisiteBuilding;}
    sint32           GetProductionCost() const { return m_ProductionCost; }
    sint32           GetUpkeep() const { return m_Upkeep; }
    bool             GetCapitol() const { return (m_flags0 & k_Building_Capitol_Bit) != 0; }
    bool             GetDefendersPercent() const { return (m_flags0 & k_Building_DefendersPercent_Bit) != 0; }
    bool             GetDefendersPercent(double &value) const {
                         if((m_flags0 & k_Building_DefendersPercent_Bit) == 0) return false;
                         value = m_DefendersPercentValue;
                         return true;
                     }
    bool             GetHappyInc() const { return (m_flags0 & k_Building_HappyInc_Bit) != 0; }
    bool             GetHappyInc(sint32 &value) const {
                         if((m_flags0 & k_Building_HappyInc_Bit) == 0) return false;
                         value = m_HappyIncValue;
                         return true;
                     }
    bool             GetDoubleTelevangelists() const { return (m_flags0 & k_Building_DoubleTelevangelists_Bit) != 0; }
    bool             GetProductionPercent() const { return (m_flags0 & k_Building_ProductionPercent_Bit) != 0; }
    bool             GetProductionPercent(double &value) const {
                         if((m_flags0 & k_Building_ProductionPercent_Bit) == 0) return false;
                         value = m_ProductionPercentValue;
                         return true;
                     }
    bool             GetFoodPercent() const { return (m_flags0 & k_Building_FoodPercent_Bit) != 0; }
    bool             GetFoodPercent(double &value) const {
                         if((m_flags0 & k_Building_FoodPercent_Bit) == 0) return false;
                         value = m_FoodPercentValue;
                         return true;
                     }
    bool             GetCommercePercent() const { return (m_flags0 & k_Building_CommercePercent_Bit) != 0; }
    bool             GetCommercePercent(double &value) const {
                         if((m_flags0 & k_Building_CommercePercent_Bit) == 0) return false;
                         value = m_CommercePercentValue;
                         return true;
                     }
    bool             GetSciencePercent() const { return (m_flags0 & k_Building_SciencePercent_Bit) != 0; }
    bool             GetSciencePercent(double &value) const {
                         if((m_flags0 & k_Building_SciencePercent_Bit) == 0) return false;
                         value = m_SciencePercentValue;
                         return true;
                     }
    bool             GetIncreaseBaseOvercrowding() const { return (m_flags0 & k_Building_IncreaseBaseOvercrowding_Bit) != 0; }
    bool             GetIncreaseBaseOvercrowding(sint32 &value) const {
                         if((m_flags0 & k_Building_IncreaseBaseOvercrowding_Bit) == 0) return false;
                         value = m_IncreaseBaseOvercrowdingValue;
                         return true;
                     }
    bool             GetIncreaseMaxPopulation() const { return (m_flags0 & k_Building_IncreaseMaxPopulation_Bit) != 0; }
    bool             GetIncreaseMaxPopulation(sint32 &value) const {
                         if((m_flags0 & k_Building_IncreaseMaxPopulation_Bit) == 0) return false;
                         value = m_IncreaseMaxPopulationValue;
                         return true;
                     }
    bool             GetFoodVat() const { return (m_flags0 & k_Building_FoodVat_Bit) != 0; }
    bool             GetFoodVat(double &value) const {
                         if((m_flags0 & k_Building_FoodVat_Bit) == 0) return false;
                         value = m_FoodVatValue;
                         return true;
                     }
    bool             GetAirport() const { return (m_flags0 & k_Building_Airport_Bit) != 0; }
    bool             GetNoUnhappyPeople() const { return (m_flags0 & k_Building_NoUnhappyPeople_Bit) != 0; }
    bool             GetNoRushBuyPenalty() const { return (m_flags0 & k_Building_NoRushBuyPenalty_Bit) != 0; }
    bool             GetLowerCrime() const { return (m_flags0 & k_Building_LowerCrime_Bit) != 0; }
    bool             GetLowerCrime(double &value) const {
                         if((m_flags0 & k_Building_LowerCrime_Bit) == 0) return false;
                         value = m_LowerCrimeValue;
                         return true;
                     }
    bool             GetPreventConversion() const { return (m_flags0 & k_Building_PreventConversion_Bit) != 0; }
    bool             GetPreventConversion(double &value) const {
                         if((m_flags0 & k_Building_PreventConversion_Bit) == 0) return false;
                         value = m_PreventConversionValue;
                         return true;
                     }
    bool             GetPreventSlavery() const { return (m_flags0 & k_Building_PreventSlavery_Bit) != 0; }
    bool             GetPreventSlavery(double &value) const {
                         if((m_flags0 & k_Building_PreventSlavery_Bit) == 0) return false;
                         value = m_PreventSlaveryValue;
                         return true;
                     }
    bool             GetAllowGrunts() const { return (m_flags0 & k_Building_AllowGrunts_Bit) != 0; }
    bool             GetLowerPeaceMovement() const { return (m_flags0 & k_Building_LowerPeaceMovement_Bit) != 0; }
    bool             GetLowerPeaceMovement(double &value) const {
                         if((m_flags0 & k_Building_LowerPeaceMovement_Bit) == 0) return false;
                         value = m_LowerPeaceMovementValue;
                         return true;
                     }
    bool             GetGoldPerCitizen() const { return (m_flags0 & k_Building_GoldPerCitizen_Bit) != 0; }
    bool             GetGoldPerCitizen(sint32 &value) const {
                         if((m_flags0 & k_Building_GoldPerCitizen_Bit) == 0) return false;
                         value = m_GoldPerCitizenValue;
                         return true;
                     }
    bool             GetProtectFromNukes() const { return (m_flags0 & k_Building_ProtectFromNukes_Bit) != 0; }
    bool             GetProtectFromBioAgents() const { return (m_flags0 & k_Building_ProtectFromBioAgents_Bit) != 0; }
    bool             GetProtectFromBioAgents(double &value) const {
                         if((m_flags0 & k_Building_ProtectFromBioAgents_Bit) == 0) return false;
                         value = m_ProtectFromBioAgentsValue;
                         return true;
                     }
    bool             GetProtectFromNanoVirus() const { return (m_flags0 & k_Building_ProtectFromNanoVirus_Bit) != 0; }
    bool             GetProtectFromNanoVirus(double &value) const {
                         if((m_flags0 & k_Building_ProtectFromNanoVirus_Bit) == 0) return false;
                         value = m_ProtectFromNanoVirusValue;
                         return true;
                     }
    bool             GetTelevision() const { return (m_flags0 & k_Building_Television_Bit) != 0; }
    bool             GetCityWalls() const { return (m_flags0 & k_Building_CityWalls_Bit) != 0; }
    bool             GetIsReligious() const { return (m_flags0 & k_Building_IsReligious_Bit) != 0; }
    bool             GetForceField() const { return (m_flags0 & k_Building_ForceField_Bit) != 0; }
    bool             GetCantBuildInSea() const { return (m_flags0 & k_Building_CantBuildInSea_Bit) != 0; }
    bool             GetCantBuildOnLand() const { return (m_flags0 & k_Building_CantBuildOnLand_Bit) != 0; }
    bool             GetCathedral() const { return (m_flags0 & k_Building_Cathedral_Bit) != 0; }
    bool             GetBrokerage() const { return (m_flags0 & k_Building_Brokerage_Bit) != 0; }
    bool             GetNuclearPlant() const { return (m_flags0 & k_Building_NuclearPlant_Bit) != 0; }
    bool             GetSciencePerPop() const { return (m_flags1 & k_Building_SciencePerPop_Bit) != 0; }
    bool             GetSciencePerPop(double &value) const {
                         if((m_flags1 & k_Building_SciencePerPop_Bit) == 0) return false;
                         value = m_SciencePerPopValue;
                         return true;
                     }
    bool             GetRaiseOvercrowdingLevel() const { return (m_flags1 & k_Building_RaiseOvercrowdingLevel_Bit) != 0; }
    bool             GetRaiseOvercrowdingLevel(sint32 &value) const {
                         if((m_flags1 & k_Building_RaiseOvercrowdingLevel_Bit) == 0) return false;
                         value = m_RaiseOvercrowdingLevelValue;
                         return true;
                     }
    bool             GetRaiseMaxPopulation() const { return (m_flags1 & k_Building_RaiseMaxPopulation_Bit) != 0; }
    bool             GetRaiseMaxPopulation(sint32 &value) const {
                         if((m_flags1 & k_Building_RaiseMaxPopulation_Bit) == 0) return false;
                         value = m_RaiseMaxPopulationValue;
                         return true;
                     }
    bool             GetStarvationProtection() const { return (m_flags1 & k_Building_StarvationProtection_Bit) != 0; }
    bool             GetStarvationProtection(sint32 &value) const {
                         if((m_flags1 & k_Building_StarvationProtection_Bit) == 0) return false;
                         value = m_StarvationProtectionValue;
                         return true;
                     }
    bool             GetCoastalBuilding() const { return (m_flags1 & k_Building_CoastalBuilding_Bit) != 0; }
    bool             GetOffenseBonusLand() const { return (m_flags1 & k_Building_OffenseBonusLand_Bit) != 0; }
    bool             GetOffenseBonusLand(double &value) const {
                         if((m_flags1 & k_Building_OffenseBonusLand_Bit) == 0) return false;
                         value = m_OffenseBonusLandValue;
                         return true;
                     }
    bool             GetOffenseBonusWater() const { return (m_flags1 & k_Building_OffenseBonusWater_Bit) != 0; }
    bool             GetOffenseBonusWater(double &value) const {
                         if((m_flags1 & k_Building_OffenseBonusWater_Bit) == 0) return false;
                         value = m_OffenseBonusWaterValue;
                         return true;
                     }
    bool             GetOffenseBonusAir() const { return (m_flags1 & k_Building_OffenseBonusAir_Bit) != 0; }
    bool             GetOffenseBonusAir(double &value) const {
                         if((m_flags1 & k_Building_OffenseBonusAir_Bit) == 0) return false;
                         value = m_OffenseBonusAirValue;
                         return true;
                     }
    bool             GetPopulationPollutionPercent() const { return (m_flags1 & k_Building_PopulationPollutionPercent_Bit) != 0; }
    bool             GetPopulationPollutionPercent(double &value) const {
                         if((m_flags1 & k_Building_PopulationPollutionPercent_Bit) == 0) return false;
                         value = m_PopulationPollutionPercentValue;
                         return true;
                     }
    bool             GetProductionPollutionPercent() const { return (m_flags1 & k_Building_ProductionPollutionPercent_Bit) != 0; }
    bool             GetProductionPollutionPercent(double &value) const {
                         if((m_flags1 & k_Building_ProductionPollutionPercent_Bit) == 0) return false;
                         value = m_ProductionPollutionPercentValue;
                         return true;
                     }
    bool             GetPollutionAmount() const { return (m_flags1 & k_Building_PollutionAmount_Bit) != 0; }
    bool             GetPollutionAmount(double &value) const {
                         if((m_flags1 & k_Building_PollutionAmount_Bit) == 0) return false;
                         value = m_PollutionAmountValue;
                         return true;
                     }
    bool             GetGLHidden() const { return (m_flags1 & k_Building_GLHidden_Bit) != 0; }
}; /* BuildingRecord */

struct BuildingRecordAccessorInfo {
    BuildingRecord::IntAccessor m_intAccessor;
    BuildingRecord::BoolAccessor m_boolAccessor;
    BuildingRecord::FloatAccessor m_floatAccessor;
    BuildingRecord::BitIntAccessor m_bitIntAccessor;
    BuildingRecord::BitFloatAccessor m_bitFloatAccessor;
};
extern BuildingRecordAccessorInfo g_BuildingRecord_Accessors[];
extern char *g_Building_Tokens[];
#define k_Num_BuildingRecord_Tokens 77

template <class T> class CTPDatabase;
extern CTPDatabase<BuildingRecord> *g_theBuildingDB;

#endif /* ifndef __Building_RECORD_H__ */