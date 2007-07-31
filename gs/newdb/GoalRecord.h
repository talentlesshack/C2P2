
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#ifndef __Goal_RECORD_H__
#define __Goal_RECORD_H__

/*
 * Goal description
 */
#include "CTPRecord.h"
//
// m_flags0
#define k_Goal_NeedsEscort_Bit                   0x00000001
#define k_Goal_IsSally_Bit                       0x00000002
#define k_Goal_AvoidWatchfulCity_Bit             0x00000004
#define k_Goal_ExecuteIncrementally_Bit          0x00000008
#define k_Goal_NeverSatisfied_Bit                0x00000010
#define k_Goal_RemoveWhenComplete_Bit            0x00000020
#define k_Goal_RallyFirst_Bit                    0x00000040
#define k_Goal_NoTransport_Bit                   0x00000080
#define k_Goal_TargetProtectionWonder_Bit        0x00000100
//
// m_SquadClass bit group
#define k_Goal_SquadClass_CanExplore_Bit         0x00000001
#define k_Goal_SquadClass_CanAttack_Bit          0x00000002
#define k_Goal_SquadClass_CanDefend_Bit          0x00000004
#define k_Goal_SquadClass_HasZoc_Bit             0x00000008
#define k_Goal_SquadClass_CanCaptureCity_Bit     0x00000010
#define k_Goal_SquadClass_CanBombard_Bit         0x00000020
#define k_Goal_SquadClass_Special_Bit            0x00000040
#define k_Goal_SquadClass_CanTransport_Bit       0x00000080
//
// m_TargetType bit group
#define k_Goal_TargetType_AttackUnit_Bit         0x00000001
#define k_Goal_TargetType_SpecialUnit_Bit        0x00000002
#define k_Goal_TargetType_SettleLand_Bit         0x00000004
#define k_Goal_TargetType_SettleSea_Bit          0x00000008
#define k_Goal_TargetType_City_Bit               0x00000010
#define k_Goal_TargetType_ChokePoint_Bit         0x00000020
#define k_Goal_TargetType_GoodyHut_Bit           0x00000040
#define k_Goal_TargetType_TradeRoute_Bit         0x00000080
#define k_Goal_TargetType_Improvement_Bit        0x00000100
#define k_Goal_TargetType_Unexplored_Bit         0x00000200
#define k_Goal_TargetType_Border_Bit             0x00000400
#define k_Goal_TargetType_Endgame_Bit            0x00000800
#define k_Goal_TargetType_Random_Bit             0x00001000
//
// m_TargetOwner bit group
#define k_Goal_TargetOwner_Self_Bit              0x00000001
#define k_Goal_TargetOwner_Ally_Bit              0x00000002
#define k_Goal_TargetOwner_Neutral_Bit           0x00000004
#define k_Goal_TargetOwner_ColdEnemy_Bit         0x00000008
#define k_Goal_TargetOwner_HotEnemy_Bit          0x00000010
#define k_Goal_TargetOwner_NoContact_Bit         0x00000020
//
// m_ThreatenType bit group
#define k_Goal_ThreatenType_AttackCity_Bit       0x00000001
#define k_Goal_ThreatenType_Pirate_Bit           0x00000002
#define k_Goal_ThreatenType_SpecialAttackCity_Bit 0x00000004
#define k_Goal_ThreatenType_DestroyCity_Bit      0x00000008
#define k_Goal_ThreatenType_None_Bit             0x00000010
//
// m_ForceMatch bit group
#define k_Goal_ForceMatch_Offensive_Bit          0x00000001
#define k_Goal_ForceMatch_Defensive_Bit          0x00000002
#define k_Goal_ForceMatch_StealthAttack_Bit      0x00000004
#define k_Goal_ForceMatch_Bombard_Bit            0x00000008
#define k_Goal_ForceMatch_Special_Bit            0x00000010
#define k_Goal_ForceMatch_Harass_Bit             0x00000020
//
// Range definitions

/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
class OrderRecord;
class WonderRecord;

class GoalRecord : public CTPRecord
{
public:
    typedef sint32 (GoalRecord::*IntAccessor)() const;
    typedef bool (GoalRecord::*BoolAccessor)() const;
    typedef double (GoalRecord::*FloatAccessor)() const ;
    typedef bool (GoalRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool (GoalRecord::*BitFloatAccessor)(double &val) const;
private:
    uint32 m_flags0;

    uint32            m_SquadClass;
    uint32            m_TargetType;
    uint32            m_TargetOwner;
    sint32            m_Execute; // Index into Order database
    sint32            m_ThreatBonus;
    sint32            m_EnemyValueBonus;
    sint32            m_AlliedValueBonus;
    sint32            m_PowerBonus;
    sint32            m_DistanceToHomeBonus;
    sint32            m_DistanceToEnemyBonus;
    sint32            m_ChokePointBonus;
    sint32            m_UnexploredBonus;
    sint32            m_ObsoleteArmyBonus;
    sint32            m_TreaspassingArmyBonus;
    uint32            m_ThreatenType;
    sint32            m_ThreatenBonus;
    uint32            m_ForceMatch;
    sint32            m_TargetProtectionWonderValue; // Index into Wonder database

public:
    GoalRecord() { Init(); };
    ~GoalRecord();
    Init();
    // These methods are needed for records to conform to
    // 'Orthodox Cannonical Form' and work with resizing STL vectors. 
    GoalRecord(const GoalRecord &rval) { Init(); *this = rval; }
    void operator=(const GoalRecord &rval);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex);

    void ResolveDBReferences();
    void Merge(const GoalRecord & rval);
    sint32 ParseSquadClassBit(DBLexer *lex);
    sint32 ParseTargetTypeBit(DBLexer *lex);
    sint32 ParseTargetOwnerBit(DBLexer *lex);
    sint32 ParseThreatenTypeBit(DBLexer *lex);
    sint32 ParseForceMatchBit(DBLexer *lex);
    //
    // Accessors
    //
    bool             GetNeedsEscort() const { return (m_flags0 & k_Goal_NeedsEscort_Bit) != 0; }
    bool             GetIsSally() const { return (m_flags0 & k_Goal_IsSally_Bit) != 0; }
    bool             GetAvoidWatchfulCity() const { return (m_flags0 & k_Goal_AvoidWatchfulCity_Bit) != 0; }
    bool             GetExecuteIncrementally() const { return (m_flags0 & k_Goal_ExecuteIncrementally_Bit) != 0; }
    bool             GetNeverSatisfied() const { return (m_flags0 & k_Goal_NeverSatisfied_Bit) != 0; }
    bool             GetRemoveWhenComplete() const { return (m_flags0 & k_Goal_RemoveWhenComplete_Bit) != 0; }
    bool             GetRallyFirst() const { return (m_flags0 & k_Goal_RallyFirst_Bit) != 0; }
    bool             GetNoTransport() const { return (m_flags0 & k_Goal_NoTransport_Bit) != 0; }

    //
    // SquadClass flag group
    uint32           GetSquadClass() const { return m_SquadClass; }
    bool             GetSquadClassCanExplore() const { return (m_SquadClass & k_Goal_SquadClass_CanExplore_Bit) != 0; }
    bool             GetSquadClassCanAttack() const { return (m_SquadClass & k_Goal_SquadClass_CanAttack_Bit) != 0; }
    bool             GetSquadClassCanDefend() const { return (m_SquadClass & k_Goal_SquadClass_CanDefend_Bit) != 0; }
    bool             GetSquadClassHasZoc() const { return (m_SquadClass & k_Goal_SquadClass_HasZoc_Bit) != 0; }
    bool             GetSquadClassCanCaptureCity() const { return (m_SquadClass & k_Goal_SquadClass_CanCaptureCity_Bit) != 0; }
    bool             GetSquadClassCanBombard() const { return (m_SquadClass & k_Goal_SquadClass_CanBombard_Bit) != 0; }
    bool             GetSquadClassSpecial() const { return (m_SquadClass & k_Goal_SquadClass_Special_Bit) != 0; }
    bool             GetSquadClassCanTransport() const { return (m_SquadClass & k_Goal_SquadClass_CanTransport_Bit) != 0; }
    // End SquadClass flag group
    //

    //
    // TargetType flag group
    uint32           GetTargetType() const { return m_TargetType; }
    bool             GetTargetTypeAttackUnit() const { return (m_TargetType & k_Goal_TargetType_AttackUnit_Bit) != 0; }
    bool             GetTargetTypeSpecialUnit() const { return (m_TargetType & k_Goal_TargetType_SpecialUnit_Bit) != 0; }
    bool             GetTargetTypeSettleLand() const { return (m_TargetType & k_Goal_TargetType_SettleLand_Bit) != 0; }
    bool             GetTargetTypeSettleSea() const { return (m_TargetType & k_Goal_TargetType_SettleSea_Bit) != 0; }
    bool             GetTargetTypeCity() const { return (m_TargetType & k_Goal_TargetType_City_Bit) != 0; }
    bool             GetTargetTypeChokePoint() const { return (m_TargetType & k_Goal_TargetType_ChokePoint_Bit) != 0; }
    bool             GetTargetTypeGoodyHut() const { return (m_TargetType & k_Goal_TargetType_GoodyHut_Bit) != 0; }
    bool             GetTargetTypeTradeRoute() const { return (m_TargetType & k_Goal_TargetType_TradeRoute_Bit) != 0; }
    bool             GetTargetTypeImprovement() const { return (m_TargetType & k_Goal_TargetType_Improvement_Bit) != 0; }
    bool             GetTargetTypeUnexplored() const { return (m_TargetType & k_Goal_TargetType_Unexplored_Bit) != 0; }
    bool             GetTargetTypeBorder() const { return (m_TargetType & k_Goal_TargetType_Border_Bit) != 0; }
    bool             GetTargetTypeEndgame() const { return (m_TargetType & k_Goal_TargetType_Endgame_Bit) != 0; }
    bool             GetTargetTypeRandom() const { return (m_TargetType & k_Goal_TargetType_Random_Bit) != 0; }
    // End TargetType flag group
    //

    //
    // TargetOwner flag group
    uint32           GetTargetOwner() const { return m_TargetOwner; }
    bool             GetTargetOwnerSelf() const { return (m_TargetOwner & k_Goal_TargetOwner_Self_Bit) != 0; }
    bool             GetTargetOwnerAlly() const { return (m_TargetOwner & k_Goal_TargetOwner_Ally_Bit) != 0; }
    bool             GetTargetOwnerNeutral() const { return (m_TargetOwner & k_Goal_TargetOwner_Neutral_Bit) != 0; }
    bool             GetTargetOwnerColdEnemy() const { return (m_TargetOwner & k_Goal_TargetOwner_ColdEnemy_Bit) != 0; }
    bool             GetTargetOwnerHotEnemy() const { return (m_TargetOwner & k_Goal_TargetOwner_HotEnemy_Bit) != 0; }
    bool             GetTargetOwnerNoContact() const { return (m_TargetOwner & k_Goal_TargetOwner_NoContact_Bit) != 0; }
    // End TargetOwner flag group
    //
    sint32           GetExecuteIndex() const { return m_Execute; }
    const OrderRecord *GetExecute() const;
    sint32           GetThreatBonus() const { return m_ThreatBonus; }
    sint32           GetEnemyValueBonus() const { return m_EnemyValueBonus; }
    sint32           GetAlliedValueBonus() const { return m_AlliedValueBonus; }
    sint32           GetPowerBonus() const { return m_PowerBonus; }
    sint32           GetDistanceToHomeBonus() const { return m_DistanceToHomeBonus; }
    sint32           GetDistanceToEnemyBonus() const { return m_DistanceToEnemyBonus; }
    sint32           GetChokePointBonus() const { return m_ChokePointBonus; }
    sint32           GetUnexploredBonus() const { return m_UnexploredBonus; }
    sint32           GetObsoleteArmyBonus() const { return m_ObsoleteArmyBonus; }
    sint32           GetTreaspassingArmyBonus() const { return m_TreaspassingArmyBonus; }

    //
    // ThreatenType flag group
    uint32           GetThreatenType() const { return m_ThreatenType; }
    bool             GetThreatenTypeAttackCity() const { return (m_ThreatenType & k_Goal_ThreatenType_AttackCity_Bit) != 0; }
    bool             GetThreatenTypePirate() const { return (m_ThreatenType & k_Goal_ThreatenType_Pirate_Bit) != 0; }
    bool             GetThreatenTypeSpecialAttackCity() const { return (m_ThreatenType & k_Goal_ThreatenType_SpecialAttackCity_Bit) != 0; }
    bool             GetThreatenTypeDestroyCity() const { return (m_ThreatenType & k_Goal_ThreatenType_DestroyCity_Bit) != 0; }
    bool             GetThreatenTypeNone() const { return (m_ThreatenType & k_Goal_ThreatenType_None_Bit) != 0; }
    // End ThreatenType flag group
    //
    sint32           GetThreatenBonus() const { return m_ThreatenBonus; }

    //
    // ForceMatch flag group
    uint32           GetForceMatch() const { return m_ForceMatch; }
    bool             GetForceMatchOffensive() const { return (m_ForceMatch & k_Goal_ForceMatch_Offensive_Bit) != 0; }
    bool             GetForceMatchDefensive() const { return (m_ForceMatch & k_Goal_ForceMatch_Defensive_Bit) != 0; }
    bool             GetForceMatchStealthAttack() const { return (m_ForceMatch & k_Goal_ForceMatch_StealthAttack_Bit) != 0; }
    bool             GetForceMatchBombard() const { return (m_ForceMatch & k_Goal_ForceMatch_Bombard_Bit) != 0; }
    bool             GetForceMatchSpecial() const { return (m_ForceMatch & k_Goal_ForceMatch_Special_Bit) != 0; }
    bool             GetForceMatchHarass() const { return (m_ForceMatch & k_Goal_ForceMatch_Harass_Bit) != 0; }
    // End ForceMatch flag group
    //
    bool             GetTargetProtectionWonder() const { return (m_flags0 & k_Goal_TargetProtectionWonder_Bit) != 0; }
    bool             GetTargetProtectionWonderIndex(sint32 &index) const {
                         if((m_flags0 & k_Goal_TargetProtectionWonder_Bit) == 0) return false;
                         index = m_TargetProtectionWonderValue;
                         return true;
                     }
    bool             GetTargetProtectionWonder(const WonderRecord *&rec) const;
    const WonderRecord  *GetTargetProtectionWonderPtr() const;
}; /* GoalRecord */

struct GoalRecordAccessorInfo {
    GoalRecord::IntAccessor m_intAccessor;
    GoalRecord::BoolAccessor m_boolAccessor;
    GoalRecord::FloatAccessor m_floatAccessor;
    GoalRecord::BitIntAccessor m_bitIntAccessor;
    GoalRecord::BitFloatAccessor m_bitFloatAccessor;
};
extern GoalRecordAccessorInfo g_GoalRecord_Accessors[];
extern char *g_Goal_Tokens[];
#define k_Num_GoalRecord_Tokens 27

template <class T> class CTPDatabase;
extern CTPDatabase<GoalRecord> *g_theGoalDB;

#endif /* ifndef __Goal_RECORD_H__ */