//----------------------------------------------------------------------------
//
// Project      : Call To Power 2
// File type    : C++ source
// Description  : Scheduler for AI goals
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
// _DEBUG
// - Generate debug version when set.
//
// _DEBUG_SCHEDULER
//
// USE_LOGGING
// - Enable logging when set, even when not a debug version. This is not
//   original Activision code.
//
//----------------------------------------------------------------------------
//
// Modifications from the original Activision code:
//
// - Do not consider invalid goals (e.g. threatened city that has been 
//   destroyed already).
// - Marked MS version specific code.
// - Added CanMatchesBeReevaluated() check -> to reevaluate the goals each turn
//   (not only first turn of war...)
// - Activated the double Goal check for all goals (not only settle goals)
// - Added Peter's Comments
// - Repaired crash when a goal type has not been defined (GOAL_SEIGE in CTC)
// - Removed double warning disable pragma.
// - Standardised list import.
// - Removed unused memory reservation.
// - New matches are now always added if a new army has been created. (30-Jun-2008 Martin Gühmann)
// - USE_LOGGING now works in a final version. (30-Jun-2008 Martin Gühmann)
// - Redesigned AI, so that the matching algorithm is now a greedy algorithm. (13-Aug-2008 Martin Gühmann)
// - Now the goals are used for the matching process, the goal match value
//   is the avarage match value of the matches needed for the goal.
//
//----------------------------------------------------------------------------

#include "c3.h"
#include "Scheduler.h"

#include "profileai.h"

#include <algorithm>
#include <list>


#include "goal.h"
#include "squad.h"
#include "Plan.h"

#include "c3errors.h"

#include "player.h"
#include "Diplomat.h"
#include "CTPDatabase.h"
#include "GoalRecord.h"
#include "ctpgoal.h"
#include "ctpaidebug.h"
#include "c3math.h"
#include "ctpagent.h"
#include "AgreementMatrix.h"
#include "gfx_options.h"
#include "Army.h"
#include "ArmyData.h"
#include "World.h"

namespace
{

//----------------------------------------------------------------------------
//
// Name       : IsValid
//
// Description: Determine whether a goal is valid in a given context
//
// Parameters : a_Goal          : the goal (type)
//              a_Context       : the context
//
// Globals    : -
//
// Returns    : bool            : the goal is valid in the context
//
// Remark(s)  : -
//
//----------------------------------------------------------------------------
	bool IsValid
	(
	    GOAL_TYPE const &                               a_Goal,
	    Scheduler::Sorted_Goal_List_Vector  const &     a_Context
	)
	{
		return static_cast<size_t>(a_Goal) < a_Context.size();
	};

} // namespace

sint32 Scheduler::s_max_match_list_cycles = 6;

Scheduler::Scheduler_Vector Scheduler::s_theSchedulers;

sint32 Scheduler::m_contactCachedPlayer       = -1;
uint32 Scheduler::m_contactCache              =  0;
sint32 Scheduler::m_neutralRegardCachedPlayer = -1;
uint32 Scheduler::m_neutralRegardCache        =  0;
sint32 Scheduler::m_allyRegardCachedPlayer    = -1;
uint32 Scheduler::m_allyRegardCache           =  0;

void Scheduler::ResizeAll(const PLAYER_INDEX & newMaxPlayerId)
{
	s_theSchedulers.resize(newMaxPlayerId + 1); // 1 extra for the Barbarians

	for(sint32 i = 0; i <= newMaxPlayerId; ++i)
	{
		s_theSchedulers[i].SetPlayerId(i);
	}
}

#if 0
// no longer used "Reason: should be able to regenerate state from game objects."
void Scheduler::LoadAll(CivArchive & archive)
{
	DPRINTF(k_DBG_AI, ("\n\ncalling Scheduler::LoadAll\n\n"));
	for(size_t i = 0; i < s_theSchedulers.size(); i++)
	{
		s_theSchedulers[i].Load(archive);
	}
}

// no longer used "Reason: should be able to regenerate state from game objects."
void Scheduler::SaveAll(CivArchive & archive)
{
	for(size_t i = 0; i < s_theSchedulers.size(); i++)
	{
		s_theSchedulers[i].Save(archive);
	}
}
#endif

//////////////////////////////
//
// used mainly in ctpai to get the player's scheduler
//
// also in Governor::ComputeDesiredUnits
//         Governor::GetTacticalAdvice
//         ThreatenedCity_MotivationEvent
//
//////////////////////////////
Scheduler & Scheduler::GetScheduler(const sint32 & playerId)
{
	Assert(playerId >= 0);
	Assert(static_cast<size_t>(playerId) < s_theSchedulers.size());
	
	return s_theSchedulers[playerId]; 
}

/// not used
void Scheduler::ValidateAll()
{
	for(size_t i = 0; i < s_theSchedulers.size(); i++)
	{
		s_theSchedulers[i].Validate();
	}
}

void Scheduler::CleanupAll(void)
{
	Scheduler_Vector().swap(s_theSchedulers);
}

Scheduler::Scheduler()
{
	m_playerId = -1;
	
	Initialize();
}

Scheduler::Scheduler(const Scheduler &scheduler)
{
	m_playerId = -1;

	*this = scheduler;
}

Scheduler::~Scheduler()
{
	Cleanup();
}

Scheduler& Scheduler::operator= (const Scheduler &scheduler)
{
	Assert(m_playerId == -1);
	Assert(scheduler.m_playerId == -1);

	Initialize();

	return *this;
}

void Scheduler::Cleanup()
{
	Squad_List::iterator squad_ptr_iter = m_new_squads.begin();
	while(squad_ptr_iter != m_new_squads.end())
	{
		delete *squad_ptr_iter;
		squad_ptr_iter = m_new_squads.erase(squad_ptr_iter);
	}

#if defined(_DEBUG_SCHEDULER)
	// Maybe removed again
	squad_ptr_iter = m_squads.begin();
	while(squad_ptr_iter != m_squads.end())
	{
		Squad_List::iterator squad2_ptr_iter = squad_ptr_iter;
		++squad2_ptr_iter;

		while(squad2_ptr_iter != m_squads.end())
		{
			Squad* squad1 = (*squad_ptr_iter);
			Squad* squad2 = (*squad2_ptr_iter);

			Assert(squad1 != squad2);

			++squad2_ptr_iter;
		}
		++squad_ptr_iter;
	}
#endif

	squad_ptr_iter = m_squads.begin();
	while(squad_ptr_iter != m_squads.end())
	{
		delete *squad_ptr_iter;
		squad_ptr_iter = m_squads.erase(squad_ptr_iter);
	}

	Goal_List::iterator goal_ptr_iter = m_new_goals.begin();
	while(goal_ptr_iter != m_new_goals.end())
	{
		delete *goal_ptr_iter;
		goal_ptr_iter = m_new_goals.erase(goal_ptr_iter);
	}

	Sorted_Goal_Iter sorted_goal_iter;
	for(size_t    goal_type = 0;
	              goal_type < m_goals_of_type.size();
	              goal_type++
	){
		sorted_goal_iter = m_goals_of_type[goal_type].begin();
		while (sorted_goal_iter != m_goals_of_type[goal_type].end() )
		{
			delete sorted_goal_iter->second;
			sorted_goal_iter++;
		}
		m_goals_of_type[goal_type].clear();
	}

	m_goals_of_type.clear();
	m_goals.clear();
}

/// No longer used "Reason: should be able to regenerate state from game objects."
void Scheduler::Load(CivArchive & archive)
{
	// Nice reason but that could be more difficult than thought.
}

/// No longer used "Reason: should be able to regenerate state from game objects."
void Scheduler::Save(CivArchive & archive)
{
	// Nice reason but that could be more difficult than thought.
}

void Scheduler::Initialize()
{
	if(g_theGoalDB == NULL)
		return;

	Cleanup();

	m_pruned_goals_count.resize(g_theGoalDB->NumRecords(),0);   // Not needed
	m_goals_of_type.resize(g_theGoalDB->NumRecords());
	m_pruned_goals_of_type.resize(g_theGoalDB->NumRecords());   // Maybe needed, can maybe replaced by priority == BAD_PRIORITY
	m_committed_agents = 0;
	m_total_agents = 0;
	m_goals.clear();

	for(size_t i = 0; i < m_goals_of_type.size(); ++i)
	{
		m_pruned_goals_of_type[i] = m_goals_of_type[i].end();
	}
}

void Scheduler::SetPlayerId(const PLAYER_INDEX &player_index)
{
	m_playerId = player_index;
}

void Scheduler::Planning_Status_Reset()
{
}

//////////////////////////////////////////////////////////////////////////
//
//  Process_Squad_Changes
//
//  When: Squads Change
//
//  Iterate: m_squads
//
//  1. Remove any empty squads and any matches that reference them.
//
//  2. Recompute squad class for all squads with changed/killed agents.
//
//  3. If squad class of squad changes, Add_New_Matches_For_Squad
//
//
//  4. Create new squads from new agents, add to squads_of_class <= where does the m_new_squads list come from
//     list and create new matches from pruned_goals_list.
//
//  5. Count up total number of agents available to match
//
//////////////////////////////////////////////////////////////////////////
Scheduler::TIME_SLICE_STATE Scheduler::Process_Squad_Changes()
{
	sint16 committed_agents = 0;

	m_total_agents = 0;

	Squad_List::iterator squad_ptr_iter = m_squads.begin();
	while (squad_ptr_iter != m_squads.end())
	{
		Squad* theSquad = (*squad_ptr_iter);

		committed_agents = theSquad->Remove_Dead_Agents();
		m_committed_agents -=  committed_agents;

		if (theSquad->Get_Num_Agents() <= 0)
		{
			Remove_Matches_For_Squad(theSquad);
			delete theSquad;
			squad_ptr_iter = m_squads.erase(squad_ptr_iter);
			continue;
		}

		m_total_agents             += theSquad->Get_Num_Agents();
		SQUAD_CLASS old_class       = theSquad->Get_Squad_Class();
		SQUAD_CLASS new_class       = theSquad->Compute_Squad_Class();

		if (old_class != new_class)
		{
			Remove_Matches_For_Squad(theSquad);
			Add_New_Matches_For_Squad(theSquad);
		}

		squad_ptr_iter++;
	}

	Squad_List::iterator new_squad_iter = m_new_squads.begin();
	while(new_squad_iter != m_new_squads.end())
	{
		Squad* newSquad = (*new_squad_iter);

		newSquad->Remove_Dead_Agents();

		if(newSquad->Get_Num_Agents() <= 0)
		{
			delete newSquad;
		}
		else
		{
			SQUAD_CLASS new_class       = newSquad->Compute_Squad_Class();
			squad_ptr_iter              = Add_Squad(newSquad);

			Add_New_Matches_For_Squad(newSquad);

			m_total_agents += newSquad->Get_Num_Agents();
		}

		new_squad_iter = m_new_squads.erase(new_squad_iter);
	}

	return TIME_SLICE_DONE;
}

//////////////////////////////////////////////////////////////////////////
//
//  Reset_Squad_Execution
//
//  When: After Squads Change
//
//  Iterate: m_squads
//
//  make squads available for goals
//
//////////////////////////////////////////////////////////////////////////
void Scheduler::Reset_Squad_Execution()
{
	Squad_List::iterator squad_ptr_iter = m_squads.begin();
	while(squad_ptr_iter != m_squads.end())
	{
		(*squad_ptr_iter)->Set_Can_Be_Executed(true);
		(*squad_ptr_iter)->Set_Needs_Transporter(false);
		squad_ptr_iter++;
	}
}

//////////////////////////////////////////////////////////////////////////
//
//  Process_Goal_Changes
//
//  When: Goals Change
//
//  Iterate: sorted_goals_of_class, pruned_goals_of_class
//
//  1. Prioritize_Goals
//
//  2. Prune_Goals
//
//////////////////////////////////////////////////////////////////////////
Scheduler::TIME_SLICE_STATE Scheduler::Process_Goal_Changes()
{
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, ("\n"));
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, ("\t//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, ("\t// PRIORITIZE GOALS\n"));
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, ("\t//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, ("\n"));

	SetContactCache(m_playerId);
	SetIsNeutralRegardCache(m_playerId);
	SetIsAllyRegardCache(m_playerId);

	Prioritize_Goals();

	SetContactCache(-1);
	SetIsNeutralRegardCache(-1);
	SetIsAllyRegardCache(-1);

	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\t//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\t// PRUNE GOALS\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\t//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));

	Prune_Goals();

	m_neededSquadStrength       = Squad_Strength(0);
	m_maxUndercommittedPriority = Goal::BAD_UTILITY;

	return TIME_SLICE_DONE;
}

//////////////////////////////////////////////////////////////////////////
//
//  Sort_Goals
//
//  When: Matches Change
//
//  Iterate: m_gaols Goal_List
//
//  1. For each gaol, compute the utility value between the
//     goal and each component agent in the squad.
//
//  2. Compute average match value from agent utility values and
//     goal raw priority.
//
//  3. Sort gaols list.
//
//////////////////////////////////////////////////////////////////////////
void Scheduler::Sort_Goals()
{
	Goal_List::iterator goal_iter;
/*
	bool first_turn_of_war = 
		Diplomat::GetDiplomat(m_playerId).FirstTurnOfWar();

	for
	(
	      goal_iter  = m_goals.begin();
	      goal_iter != m_goals.end();
	    ++goal_iter
	)
	{
		Goal_ptr theGoal = static_cast<Goal_ptr>(*goal_iter);

		if(first_turn_of_war
		|| m_playerId == 0
		|| theGoal->CanGoalBeReevaluated()
		|| theGoal->Commited_Agents_Need_Orders())
			m_committed_agents -= theGoal->Rollback_All_Agents();

//		theGoal->Compute_Matching_Value(); // Moved to Prioritize_Goals
	}
*/
	AI_DPRINTF(k_DBG_SCHEDULER_DETAIL, m_playerId, -1, -1, ("\n"));
	time_t t1 = GetTickCount();

#if defined(_DEBUG)
	sint32 size = m_goals.size();
#endif // _DEBUG

	m_goals.sort(std::greater<Goal_ptr>());

#if defined(_DEBUG)
	Assert(m_goals.size() == size);
	if(m_goals.size() != size)
	{
		c3errors_ErrorDialog("List Sort Error", "You compiled the game on MSVC++ 6.0 with the \ndefault standart library, please used the fixed version in your include directories from \n\\ctp2_code\\compiler\\msvc6\\stlfixes");
	}
#endif // _DEBUG

	time_t t2 = GetTickCount();
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1,
		("//  %d goals sorted = %d ms, Player %d\n\n\n", m_goals.size(), (t2 - t1), m_playerId));
	DPRINTF(k_DBG_AI,("//  %d goals sorted = %d ms, Player %d\n\n\n", m_goals.size(), (t2 - t1), m_playerId));

#if defined(_DEBUG) || defined(USE_LOGGING)

#ifdef _DEBUG_SCHEDULER

	// Looks like something Calvitix added
	for
	(
	    Squad_List::iterator squad_iter  = m_squads.begin();
	                         squad_iter != m_squads.end();
	                       ++squad_iter
	)
	{
		const Agent_List & agent_list = (*squad_iter)->Get_Agent_List();
		for
		(
		    Agent_List::const_iterator agent_iter  = agent_list.begin();
		                               agent_iter != agent_list.end();
		                             ++agent_iter
		)
		{
			if ((*agent_iter)->Get_Is_Used())
			{
				bool NOT_ALL_AGENTS_ROLLED_BACK = false;
				Assert(NOT_ALL_AGENTS_ROLLED_BACK);
			}
		}
	}
#endif // _DEBUG_SCHEDULER

	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("// SORTED GOALS\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));

	sint32 count = 0;
	for
	(
	      goal_iter  = m_goals.begin();
	      goal_iter != m_goals.end();
	    ++goal_iter
	)
	{
		CTPGoal_ptr goal = static_cast<CTPGoal_ptr>(*goal_iter);

		Utility value = goal->Get_Matching_Value();

		if (value > Goal::BAD_UTILITY)
		{
			GOAL_TYPE goal_type = goal->Get_Goal_Type();
			AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));
			AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1,
				("\t[%d] goal_prioriry=%d %s\n",
					count++, value, g_theGoalDB->Get(goal_type)->GetNameText()));

			// Match and squad go inside goal log
			goal->Log_Debug_Info(k_DBG_SCHEDULER_ALL);
		}
		else
		{
			GOAL_TYPE goal_type = goal->Get_Goal_Type();
			AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));
			AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1,
				("\t[%d] goal_bad_prioriry=%d %s, %d\n",
					count++, value, g_theGoalDB->Get(goal_type)->GetNameText(), Goal::BAD_UTILITY));

			// Match and squad go inside goal log
			goal->Log_Debug_Info(k_DBG_SCHEDULER_ALL);
		}
	}

	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("// SORTED GOALS END\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("//\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));
	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\n"));

#endif
}

//////////////////////////////////////////////////////////////////////////
//
//  Match_Resources
//
//  When: Goals need to be executed (CtpAi_ProcessMatchesEvent)
//
//  Iterate: matches
//
//  1. For each match, move agents from donor squad to goal.
//
//  2. If goal is in progress, execute goal and check status.
//
//  3. If goal is completed, create a new squad from agents that
//     completed the goal.
//
//  4. If goal failed, rollback agents to donor squads.
//     Rollback marks agents in matches as invalid for the goal.
//
//  5. When all agents have been committed, check all goals on
//     pruned_goals_class list.  If under committed, rollback
//     all agents to donor squads. If over committed, rollback
//     excess agents to donor squads.
//
//////////////////////////////////////////////////////////////////////////
void Scheduler::Match_Resources(const bool move_armies)
{
	bool out_of_transports = false; // this tells us if we have run out of available transports or not
#if defined(_DEBUG) || defined(USE_LOGGING)
	sint32 count = 0;
#endif

	for
	(
	    Goal_List::iterator goal_iter  = m_goals.begin();
	                        goal_iter != m_goals.end();
	                      ++goal_iter
	)
	{
		if (m_committed_agents >= m_total_agents)
			break;

		CTPGoal_ptr goal_ptr = static_cast<CTPGoal_ptr>(*goal_iter);
		Utility oldMatchValue = goal_ptr->Get_Matching_Value();

#if defined(_DEBUG) || defined(USE_LOGGING)
		MapPoint pos = goal_ptr->Get_Target_Pos();
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, ("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, ("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
				("[%d] Starting to match resources to %s: %x (x=%d,y=%d), match %d, %s\n",
					count, g_theGoalDB->Get(goal_ptr->Get_Goal_Type())->GetNameText(), goal_ptr, pos.x, pos.y, oldMatchValue, (g_theWorld->HasCity(pos) ? g_theWorld->GetCity(pos).GetName() : "field")));
		count++;
#endif

		if(oldMatchValue == Goal::BAD_UTILITY)
		{
			AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
					("\t\tGOAL (goal: %x) -- First goal with bad utility - stop matching\n",
						goal_ptr));

			AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, ("\n"));
			AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, ("\n"));
			// Assuming that the list is still sorted,
			// and the following has only Goal::BAD_UTILITY
			break;
		}

		Utility newMatchValue = goal_ptr->Recompute_Matching_Value(false, false);


		if(newMatchValue == Goal::BAD_UTILITY)
		{
			// Move to the end
			Goal_List::iterator tmp_goal_iter = goal_iter;
			++tmp_goal_iter;

			AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
				("\t\tGOAL (goal: %x)(agent count: %d) -- Goal with bad utility, trying agian in next cycle.\n",
						goal_ptr, goal_ptr->Get_Agent_Count()));

	//		Assert(goal_ptr->Get_Agent_Count() == 0); // Is still ok

			/*
			m_goals.splice
			              (
			               m_goals.end(),
			               m_goals,
			               tmp_goal_iter
			              );
			*/

			continue;
		}

		if(newMatchValue != oldMatchValue)
		{
			goal_ptr->Set_Matching_Value(newMatchValue);

			Goal_List::iterator tmp_goal_iter = goal_iter;
			++tmp_goal_iter;

			if(tmp_goal_iter != m_goals.end())
			{
				Utility nextMatchValue = static_cast<Goal_ptr>(*tmp_goal_iter)->Get_Matching_Value();
				if(newMatchValue < nextMatchValue)
				{
					// http://www.cplusplus.com/reference/stl/list/splice.html
					//or use a decrement
					// Sort the goal list, move iterator increment herein back
					tmp_goal_iter = goal_iter;
					--goal_iter;
					Reprioritize_Goal(tmp_goal_iter);
					continue;
				}
			}
		}

		// Needs to be reconsidered
		if(goal_ptr->Needs_Transporter())
		{
			// Be careful here
			sint16 transNum = goal_ptr->Get_Transporters_Num();
			m_committed_agents += goal_ptr->Commit_Transport_Agents();

			if(goal_ptr->Get_Transporters_Num() < 1
			|| transNum == goal_ptr->Get_Transporters_Num()
			){
				// Has to be modified for partial transport
				AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
					("\t\tGOAL_FAILED Not enough transporters (goal: %x)\n", goal_ptr));

				Rollback_Matches_For_Goal(goal_ptr);
				continue;
			}
		}

		m_committed_agents += goal_ptr->Commit_Agents();

		if(goal_ptr->Get_Agent_Count() == 0)
		{
			AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
					("\t\tGOAL (goal: %x) -- No agents were committed, maybe next time. Continuing...\n",
						goal_ptr));
			continue;
		}

		GOAL_RESULT result = move_armies ? goal_ptr->Execute_Task() : GOAL_IN_PROGRESS;

		switch (result) {
		case GOAL_ALREADY_MOVED:
			
			AI_DPRINTF(k_DBG_SCHEDULER_DETAIL, m_playerId, goal_ptr->Get_Goal_Type(), -1,
				("\t\tGOAL_ALREADY_MOVED (goal: %x)\n", goal_ptr));

			break;

		case GOAL_IN_PROGRESS:

			AI_DPRINTF(k_DBG_SCHEDULER_DETAIL, m_playerId, goal_ptr->Get_Goal_Type(), -1,
				("\t\tGOAL_IN_PROGRESS (goal: %x)\n", goal_ptr));

			break;

		case GOAL_COMPLETE:

			AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1,
				("\t\tGOAL_COMPLETE (goal: %x squad: %x)\n", goal_ptr));

#if 0
			if(!goal_ptr->Is_Single_Squad())
			{
			}
#endif
			if(goal_ptr->Get_Removal_Time())
			{
					AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
						("\t\tGOAL_COMPLETE (goal: %x) -- Removing matches for goal.\n",
						goal_ptr));
					Remove_Matches_For_Goal(goal_ptr);
			}
			else
			{
				Rollback_Matches_For_Goal(goal_ptr);
			}

			break;

		case GOAL_NEEDS_TRANSPORT:

			// optimization: If we have previously failed to get a transport, then skip trying to get a transport now:
			if (!out_of_transports)
			{
				AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
					("\t\tGOAL_NEEDS_TRANSPORT (goal: %x)\n", goal_ptr));

				if(!Add_Transport_Matches_For_Goal(goal_ptr))
				{
					out_of_transports = true; // record the fact we could not find a transport
					AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
						("\t\t **NO transporters found. Failing.\n"));
				}
				else
				{
					AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
						("\t\t Transporters found.\n"));
					--goal_iter;
					break;
				}
			} // if out_of_transports is true, we just fail like in the original code

		case GOAL_FAILED:

			AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
				("\t\tGOAL_FAILED (goal: %x)\n", goal_ptr));

			Rollback_Matches_For_Goal(goal_ptr);

			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Add_New_Goal
//
//
// Add a new goal to the m_new_goals Goal_List
//
// New goals are primarily added in CtpAi:
//
// 1) by AddSettleTargets, AddExploreTargets, and AddMiscMapTargets.
//
// 2) by AddGoalsForArmy, which is called whenever a savegame is loaded or an army is created.
//
// 3) by AddForeignerGoalsForCity and AddOwnerGoalsForCity (when a city is created, changes hands,
//    or a savegame is loaded).
//
//    These add every goal : those that are not gamestate possible are filtered out.
//
// 4) Also called by CtpAi_KillCityEvent, CtpAi_NukeCityUnit, CtpAi_ImprovementComplete.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Scheduler::Add_New_Goal(const Goal_ptr & new_goal)
{
	m_new_goals.push_back(new_goal);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Add_New_Squad
//
//
// Add a new squad to the m_new_squads Squad_List
//
// New squads are created by AddGoalsForArmy, which is called whenever a savegame is loaded
// or an army is created.
//
/////////////////////////////////////////////////////////////////////////////////////////////////
void Scheduler::Add_New_Squad(const Squad_ptr & new_squad)
{
#ifdef _DEBUG_SCHEDULER

	Squad_List::iterator squad_iter = m_new_squads.begin();
	while (squad_iter != m_new_squads.end() && !(*squad_iter)->ContainsArmyIn(new_squad))
	{
		squad_iter++;
	}
	Assert(squad_iter == m_new_squads.end());

	squad_iter = m_squads.begin();
	while (squad_iter != m_squads.end() && !(*squad_iter)->ContainsArmyIn(new_squad))
	{
		squad_iter++;
	}
	
	Assert(squad_iter == m_squads.end());
#endif // _DEBUG_SCHEDULER

	m_new_squads.push_back(new_squad);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Add_Squad
//
//
// Add a new squad to the m_squads Squad_List
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////
Squad_List::iterator Scheduler::Add_Squad(const Squad_ptr & squad)
{
#ifdef _DEBUG_SCHEDULER

	Squad_List::iterator squad_iter = m_squads.begin();
	while (squad_iter != m_squads.end() && !(*squad_iter)->ContainsArmyIn(squad))
	{
		squad_iter++;
	}
	
	Assert(squad_iter == m_squads.end());

	squad_iter = m_transport_squads.begin();
	while (squad_iter != m_transport_squads.end() && !(*squad_iter)->ContainsArmyIn(squad))
	{
		squad_iter++;
	}
	
	Assert(squad_iter == m_transport_squads.end());
#endif // _DEBUG_SCHEDULER

	Squad_Strength strength;
	squad->Compute_Strength(strength);
	if(strength.Get_Transport() > 0)
	{
		m_transport_squads.push_back(squad);
	}

	return m_squads.insert(m_squads.end(), squad);
}

////////////////////////////////////////////////////////////
//
//  Remove_Goal
//
//  called by Scheduler::Prioritize_Goals() when
//
////////////////////////////////////////////////////////////
Scheduler::Sorted_Goal_Iter Scheduler::Remove_Goal(const Scheduler::Sorted_Goal_Iter & sorted_goal_iter)
{
	GOAL_TYPE goal_type = sorted_goal_iter->second->Get_Goal_Type();

	Sorted_Goal_List & list = m_goals_of_type[goal_type];

	Remove_Matches_For_Goal(sorted_goal_iter->second);

	delete sorted_goal_iter->second;

	bool deleteFirstPruned = (m_pruned_goals_of_type[goal_type] == sorted_goal_iter);

	Scheduler::Sorted_Goal_Iter next_iter = list.erase(sorted_goal_iter);

	if (deleteFirstPruned)
		m_pruned_goals_of_type[goal_type] = next_iter;

	return next_iter;
}

void Scheduler::Remove_Goals_Type(const GoalRecord *rec)
{
	Sorted_Goal_List & goalList = m_goals_of_type[rec->GetIndex()];
	for
	(
	    Sorted_Goal_Iter sorted_goal_iter  = goalList.begin();
	                     sorted_goal_iter != goalList.end();
	                     sorted_goal_iter = Remove_Goal(sorted_goal_iter)
	)
	{
		// Action in for
	}
}

bool Scheduler::Validate() const
{
#ifdef _DEBUG_SCHEDULER
	Sorted_Goal_List::const_iterator sorted_goal_iter;

	for(sint32 i = 0; i < g_theGoalDB->NumRecords(); i++)
	{
		sorted_goal_iter = m_goals_of_type[i].begin();

		while (sorted_goal_iter != m_goals_of_type[i].end())
		{
			if (!sorted_goal_iter->second->Validate())
			{
				bool GOAL_VALIDATION_FAILED = false;
				Assert(GOAL_VALIDATION_FAILED);
			}
			sorted_goal_iter++;
		}
	}
#endif // _DEBUG_SCHEDULER

	return true;
}

// Isn't used
Scheduler::Sorted_Goal_List Scheduler::Get_Top_Goals(const int &number) const
{
	const bool no_top_goals_available = false;
	Assert(no_top_goals_available);

	Sorted_Goal_List output_goals;

	return output_goals;
}

//----------------------------------------------------------------------------
//
// Name       : Scheduler::GetValueUnsatisfiedGoals
//
// Description: Get the total value of all unsatisfied goals of a given type.
//
// Parameters : type    : type of goal
//
// Globals    : -
//
// Returns    : sint32  : sum of value of the unsatisfied goals of type type.
//
// Remark(s)  : Used in ThreatenedCity_MotivationEvent to trigger MOTIVATION_FEAR_CITY_DEFENSE
//
//----------------------------------------------------------------------------
sint32 Scheduler::GetValueUnsatisfiedGoals(const GOAL_TYPE & type) const 
{
	sint32 total_value = 0;

	if(IsValid(type, m_goals_of_type))
	{
		for
		(
		    Sorted_Goal_List::const_iterator 
		        sorted_goal_iter  = m_goals_of_type[type].begin();
		        sorted_goal_iter != m_goals_of_type[type].end();
		      ++sorted_goal_iter
		)
		{
			CTPGoal_ptr const ctp_goal_ptr = 
				static_cast<CTPGoal_ptr const>(sorted_goal_iter->second);

			if(ctp_goal_ptr->Get_Invalid()		||
			   ctp_goal_ptr->Is_Satisfied()	||
			   ctp_goal_ptr->ArmiesAtGoal()
			  )
			{
				// Goal has become invalid or has been satisfied: try next.
			}
			else
			{
				total_value += ctp_goal_ptr->Get_Target_Value();
			}
		}
	}

	return total_value;
}

//----------------------------------------------------------------------------
//
// Name       : Scheduler::GetHighestPriorityGoal
//
// Description: Get the highest valued goal of a given type.
//
// Parameters : type        : type of goal
//              satisfied   : consider satisfied/unsatisfied goals only
//
// Globals    : -
//
// Returns    : sint32	: sum of value of the unsatisfied goals of type type.
//
// Remark(s)  : Returns the first found goal that matches the parameters.
//              The list m_goals_of_type[type] is ordered by raw priority.
//
//              Used in governor to give advice on what city to defend
//              and in ThreatenedCity_MotivationEvent to trigger
//              MOTIVATION_FEAR_CITY_DEFENSE
//
//----------------------------------------------------------------------------
Goal_ptr Scheduler::GetHighestPriorityGoal(const GOAL_TYPE & type, const bool satisfied) const 
{
	if(IsValid(type, m_goals_of_type)) 
	{
		for
		(
		    Sorted_Goal_List::const_iterator
		        sorted_goal_iter  = m_goals_of_type[type].begin();
		        sorted_goal_iter != m_goals_of_type[type].end(); 
		      ++sorted_goal_iter
		)
		{
			CTPGoal_ptr	const	ctp_goal_ptr = 
				static_cast<CTPGoal_ptr const>(sorted_goal_iter->second);

			if(ctp_goal_ptr->Get_Invalid()                  ||
			    (satisfied != ctp_goal_ptr->Is_Satisfied()) ||
			    ctp_goal_ptr->ArmiesAtGoal()
			   )
			{
				// Goal does not match: try next.
			}
			else
			{
				return ctp_goal_ptr;
			}
		}
	}

	return NULL; // No matching goal available.
}

//////////////////////////////////////////////////////////////////////////
//
// CountGoalsOfType
//
// Used in ctpai when adding Explore, Settle, and MiscMap targets for goals
//
///////////////////////////////////////////////////////////////////////////
sint16 Scheduler::CountGoalsOfType(const GOAL_TYPE & type) const
{
	return IsValid(type, m_goals_of_type) 
	       ? m_goals_of_type[type].size() 
	       : 0;
}

//////////////////////////////////////////////////////////////////////////
//
//  Prioritize_Goals
//
//  Called by Process_Goal_Changes
//
//
//  1. Add new_goals into appropriate goals_of_class list.
//
//  2. Remove all invalid/complete goals from goals_of_class list.
//
//  3. Recompute raw priority of all new/changed goals from
//     sorted_goals_of_class list.
//
//  4. Sort goals_of_class lists.
//
//////////////////////////////////////////////////////////////////////////
bool Scheduler::Prioritize_Goals()
{
	time_t t1 = GetTickCount();

	for
	(
	    Goal_List::iterator goal_ptr_iter  = m_new_goals.begin();
	                        goal_ptr_iter != m_new_goals.end();
	                      ++goal_ptr_iter
	)
	{
		sint32 goal_type    = (*goal_ptr_iter)->Get_Goal_Type();

		CTPGoal_ptr goal2 = (CTPGoal_ptr) *goal_ptr_iter;

		Sorted_Goal_Iter tmp_goal_iter = 
			m_goals_of_type[goal_type].begin();

		while (tmp_goal_iter != m_goals_of_type[goal_type].end())
		{
			CTPGoal_ptr goal1 = (CTPGoal_ptr) tmp_goal_iter->second;
			if ( *goal1 == *goal2)
			{
				break;
			}
			tmp_goal_iter++;
		}

		if (tmp_goal_iter != m_goals_of_type[goal_type].end())
		{
			delete goal2;
			continue;
		}

		m_goals_of_type[goal_type].
			push_back(Sorted_Goal_ptr(Goal::BAD_UTILITY, *goal_ptr_iter));

#if 0
		// For some reason this is shown even for k_DBG_SCHEDULER, so removed
		AI_DPRINTF
		          (
		               k_DBG_SCHEDULER_DETAIL,
		               m_playerId,
		               goal_type,
		               -1,
		               (
		                    "\tAdded New Goal: %x (%s) - (%3d,%3d)\n",
		                    goal2,
		                    g_theGoalDB->Get(goal_type)->GetNameText(),
		                    goal2->Get_Target_Pos().x,
		                    goal2->Get_Target_Pos().y
		               )
		          );
#endif
	}

	m_new_goals.clear();

	time_t t2 = GetTickCount();
	DPRINTF(k_DBG_AI, ("//  Add new goals to list:\n"));
	DPRINTF(k_DBG_AI, ("//  elapsed time = %d ms\n\n", (t2 - t1)  ));

	t1 = GetTickCount();

	sint16 committed_agents = 0;

	bool first_turn_of_war = Diplomat::GetDiplomat(m_playerId).FirstTurnOfWar();

	Sorted_Goal_Iter sorted_goal_iter;

	sint32 goal_type;

	for(goal_type = 0; goal_type < g_theGoalDB->NumRecords(); goal_type++)
	{
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("//\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("// Calculate raw priority for %s (%d)\n", g_theGoalDB->Get(goal_type)->GetNameText(), m_goals_of_type[goal_type].size()));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("//\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,
		("\t %9x,\tGOAL\t\t,\tRAW_PRIORITY,\tCOORDS\t,\tINIT_VALUE,\tLAST_VALUE,\tTHREAT,\t\tENEMYVAL,\tALLIEDVAL,\tMAXPOW,\t\tHOMEDIST\t(   )\t,\tENEMYDIST (    ),\t\tSETTLE,\t\tCHOKE,\t\tUNEXPLORED,\tNOT_VISIBLE,\tTHREATEN\n",
		this));

		      sorted_goal_iter  = m_goals_of_type[goal_type].begin();
		while(sorted_goal_iter != m_goals_of_type[goal_type].end())
		{
			Goal_ptr goal_ptr = sorted_goal_iter->second;
#if 0
			// Get_Totally_Complete also called in Compute_Raw_Priority
			if(goal_ptr->Get_Totally_Complete())
			{
				if(!goal_ptr->Is_Single_Squad())
				{
				}
			}
#endif

			if(goal_ptr->Get_Removal_Time())
			{
				AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_ptr->Get_Goal_Type(), -1, 
					("\tRemoving Invalid/Completed Goal: %x\n", goal_ptr));

				sorted_goal_iter = Remove_Goal(sorted_goal_iter);
			}
			else
			{
				goal_ptr->Set_Can_Be_Executed(true);
				goal_ptr->Set_Needs_Transporter(false);
				sorted_goal_iter->first = goal_ptr->Compute_Raw_Priority();

				if(sorted_goal_iter->first > Goal::BAD_UTILITY)
				{
					goal_ptr->Compute_Needed_Troop_Flow();

					if
					  (
					       first_turn_of_war
					    || m_playerId == 0
					    || goal_ptr->CanGoalBeReevaluated()
					    || goal_ptr->Commited_Agents_Need_Orders()
					  )
					{
						m_committed_agents -= goal_ptr->Rollback_All_Agents();
					}

					if(goal_ptr->Get_Matches_Num() == 0)
					{
						Add_New_Matches_For_Goal(goal_ptr, false);
					}
				}
				else
				{
					if(goal_ptr->Get_Matches_Num() > 0)
					{
						Remove_Matches_For_Goal(goal_ptr);
					}
				}

				sorted_goal_iter++;
			}
		}
	}

	for(goal_type = 0; goal_type < g_theGoalDB->NumRecords(); goal_type++)
	{
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("//\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("// Calculate priority for %s (%d)\n", g_theGoalDB->Get(goal_type)->GetNameText(), m_goals_of_type[goal_type].size()));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("//\n"));
		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,("\n"));
//		AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, goal_type, -1,
//		("\t %9x,\tGOAL\t\t,\tRAW_PRIORITY,\tCOORDS\t,\tINIT_VALUE,\tLAST_VALUE,\tTHREAT,\t\tENEMYVAL,\tALLIEDVAL,\tMAXPOW,\t\tHOMEDIST\t(   )\t,\tENEMYDIST (    ),\t\tSETTLE,\t\tCHOKE,\t\tUNEXPLORED,\tNOT_VISIBLE,\tTHREATEN\n",
//		this));

		for
		(
		      sorted_goal_iter  = m_goals_of_type[goal_type].begin();
		      sorted_goal_iter != m_goals_of_type[goal_type].end();
		    ++sorted_goal_iter
		)
		{
			Goal_ptr goal_ptr = sorted_goal_iter->second;

			if(sorted_goal_iter->first > Goal::BAD_UTILITY)
			{
				if(goal_ptr->Get_Matches_Num() == 0)
				{
					// In this case there is no need to calculate anything
					sorted_goal_iter->first = Goal::BAD_UTILITY;
				}
				else
				{
					sorted_goal_iter->first = goal_ptr->Compute_Matching_Value();

					if(sorted_goal_iter->first <= Goal::BAD_UTILITY)
					{
						if(goal_ptr->Get_Matches_Num() > 0)
						{
							Remove_Matches_For_Goal(goal_ptr);
						}
					}
				}
			}
		}

		m_goals_of_type[goal_type].sort(std::greater<Sorted_Goal_ptr>());

		AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\n"));
		AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\t//\n"));
		AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\t// SORTED GOALS of %s (%d)\n", g_theGoalDB->Get(goal_type)->GetNameText(), m_goals_of_type[goal_type].size()));
		AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\t//\n"));
		AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\n"));
		
#if defined(_DEBUG) || defined(USE_LOGGING)
		sint32 count = 0;
#endif
		
		for
		(
		      sorted_goal_iter  = m_goals_of_type[goal_type].begin();
		      sorted_goal_iter != m_goals_of_type[goal_type].end();
		    ++sorted_goal_iter
		)
		{
#if defined(_DEBUG) || defined(USE_LOGGING)
			if (sorted_goal_iter->first > Goal::BAD_UTILITY + 0.5)
			{
				AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
					("\t[%3d]", count++));
				sorted_goal_iter->second->Log_Debug_Info(k_DBG_SCHEDULER_ALL);
			}
#endif
			committed_agents += sorted_goal_iter->second->Get_Agent_Count();
		}
	}

	t2 = GetTickCount();
	DPRINTF(k_DBG_AI, ("//  Compute raw priorities and sort goal lists:\n"));
	DPRINTF(k_DBG_AI, ("//  elapsed time = %d ms\n\n", (t2 - t1)  ));

	if (committed_agents != m_committed_agents)
	{
		DPRINTF(k_DBG_AI, ("m_committed_agents out of sync (%d != %d)\n",
		                   committed_agents, m_committed_agents));

		Assert(false);

		m_committed_agents = committed_agents;
	}

	return true;
}

#if 0
// Some stuff for testing
bool Scheduler::Test_Syn_Of_Committed_Agents()
{
	sint32 committed_agents = 0;

	for(sint32 goal_type = 0; goal_type < g_theGoalDB->NumRecords(); goal_type++)
	{
		for
		(
		    Sorted_Goal_Iter sorted_goal_iter  = m_goals_of_type[goal_type].begin();
		                     sorted_goal_iter != m_goals_of_type[goal_type].end();
		                   ++sorted_goal_iter
		)
		{
			committed_agents += sorted_goal_iter->second->Get_Agent_Count();
		}
	}

	if(committed_agents != m_committed_agents)
	{
		Assert(false);
		return false;
	}

	return true;
}
#endif

//////////////////////////////////////////////////////////////////////////
//
//  Prune_Goals
//
//  Called by Process_Goals
//
//  IV. pruned_goals_of_class
//
//  1. Iterate over all (sorted) goals in each goal class
//
//  2. Count out maximum number of each goal type.
//
//  3. If pruned_goals_count for a particular goal exceedes allowed count,
//     or the goal is complete, then remove matches for that goal
//     and splice onto end of list.
//
//  4. Otherwise, if not matches exist for this goal, add them.
//
//////////////////////////////////////////////////////////////////////////
bool Scheduler::Prune_Goals()
{
	m_pruned_goals_count.assign(g_theGoalDB->NumRecords(), 0);

	sint16 max_eval;
	sint16 max_exec;

	const StrategyRecord &strategy = Diplomat::GetDiplomat(m_playerId).GetCurrentStrategy();

	time_t prune_time = 0;

	m_goals.clear(); // @ToDo: Optimize code, by setting the initial size.

	for(sint32 i = 0; i < strategy.GetNumGoalElement(); i++)
	{
		time_t t1 = GetTickCount();

		const StrategyRecord::GoalElement* goal_element_ptr = strategy.GetGoalElement(i);

		GOAL_TYPE goal_type = GetMaxEvalExec(goal_element_ptr, max_eval, max_exec);

		max_eval = m_goals_of_type[goal_type].size(); // Temporary, maybe permanetly

		Sorted_Goal_Iter pruned_goal_iter = m_goals_of_type[goal_type].end();
		Sorted_Goal_Iter goal_ptr_iter    = m_goals_of_type[goal_type].begin();

		while(goal_ptr_iter != pruned_goal_iter &&
		      goal_ptr_iter != m_goals_of_type[goal_type].end()
		){
			Goal_ptr goal_ptr     = goal_ptr_iter->second;
			Utility  raw_priority = goal_ptr_iter->first;

			bool ok_to_match_goal =
				(m_pruned_goals_count[goal_type] < max_eval);

			ok_to_match_goal &= (raw_priority != Goal::BAD_UTILITY);

			if(ok_to_match_goal)
			{
				if (goal_ptr->Get_Matches_Num() == 0)
				{
					// Not needed anymore
					Add_New_Matches_For_Goal(goal_ptr, false);
				}

				m_goals.push_back(goal_ptr);

				m_pruned_goals_count[goal_type]++;
				goal_ptr_iter++;
			}
			else
			{
				if(goal_ptr->Get_Matches_Num() > 0)
				{
					// Not needed anymore
					Remove_Matches_For_Goal(goal_ptr);
				}

				Sorted_Goal_Iter tmp_goal_iter = goal_ptr_iter;
				goal_ptr_iter++;

				m_goals_of_type[goal_type].splice(m_goals_of_type[goal_type].end(),
								  m_goals_of_type[goal_type],
								  tmp_goal_iter);

				if(pruned_goal_iter == m_goals_of_type[goal_type].end())
				{
					pruned_goal_iter--;
				}
			}
		}

		m_pruned_goals_of_type[goal_type] = pruned_goal_iter;

		time_t t2 = GetTickCount();
		prune_time += t2 - t1;

#if defined(_DEBUG) || defined(USE_LOGGING)
		sint32 count = 0;
		for
		(
		      goal_ptr_iter  = m_pruned_goals_of_type[goal_type];
		      goal_ptr_iter != m_goals_of_type[goal_type].end();
		    ++goal_ptr_iter
		){
			if(count == 0)
			{
				AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\n\n"));
				AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\t//\n"));
				AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1, ("\t// PRUNED GOALS: %s (type %d)\n",
					g_theGoalDB->Get(goal_type)->GetNameText(),
					goal_type));
				AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
					("\t// max eval = %3.2f, max_exec = %3.2f",
					goal_element_ptr->GetMaxEval(),
					goal_element_ptr->GetMaxExec()));
				if(goal_element_ptr->GetExecPerCity())
					AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
					(" (ExecPerCity)"));
				if(goal_element_ptr->GetEvalPerCity())
					AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
					(" (EvalPerCity)"));
				if(goal_element_ptr->GetPerCity())
					AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
					(" (PerCity)"));
				AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
					("\n"));
				AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
					("\t//\n\n"));
			}

			if(goal_ptr_iter->first > Goal::BAD_UTILITY + 0.5)
			{
					AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, goal_type, -1,
						("\t%3d: [%x]", count, goal_ptr_iter->second));
					CTPGoal_ptr ctpgoal_ptr = (CTPGoal_ptr) goal_ptr_iter->second;
					ctpgoal_ptr->Log_Debug_Info(k_DBG_SCHEDULER_ALL);
			}
			count++;
		}
#endif

	}

	DPRINTF(k_DBG_AI, ("//  PRUNE goals based on max eval and max exec:\n"));
	DPRINTF(k_DBG_AI, ("//  elapsed time = %d ms\n\n", prune_time  ));

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Add_New_Matches_For_Goal
//
//   called by Scheduler::Prune_Goals() when iterating through the Sorted_Goal (by raw priority)
//   list m_goals_of_type[goal_type]
//
//   If it's ok to match the goal (because so far there's less than maxeval of them, and
//   it's raw_priority != Goal::BAD_UTILITY), it iterates through the Squad_List m_squads
//   and calls Add_New_Match_For_Goal_And_Squad to try and add a 3-tuple <goal,squad,matching value>,
//   for each squad that qualifies, to the plan
//
///////////////////////////////////////////////////////////////////////////////////////////////
sint32 Scheduler::Add_New_Matches_For_Goal
(
    const Goal_ptr & goal_ptr,
    const bool       update_match_value
)
{
	if (goal_ptr->Get_Invalid())
		return 0;

	sint32      count            = 0;
	GOAL_TYPE   type             = goal_ptr->Get_Goal_Type();
	SQUAD_CLASS goal_squad_class = g_theGoalDB->Get(type)->GetSquadClass();

	for
	(
	    Squad_List::iterator squad_iter  = m_squads.begin();
	                         squad_iter != m_squads.end();
	                       ++squad_iter
	)
	{
		Squad* squad = (*squad_iter);
		if((goal_squad_class & squad->Get_Squad_Class()) != goal_squad_class)
			continue;

		if(goal_ptr->Add_Match(squad, update_match_value))
		{
			count++;
		}
	}

	return count;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//   Add_New_Matches_For_Squad
//
//   called by Process_Squad_Changes
//
//////////////////////////////////////////////////////////////////////////////////////////////
sint32 Scheduler::Add_New_Matches_For_Squad
(
    const Squad_ptr & squad
)
{
	if(squad->Get_Num_Agents() <= 0)
		return 0;

	sint32 count = 0;

	SQUAD_CLASS squad_class = squad->Get_Squad_Class();

	for(sint32 i = 0; i < g_theGoalDB->NumRecords(); i++)
	{
		Sorted_Goal_List & goal_list = m_goals_of_type[i];

		SQUAD_CLASS goal_squad_class = 
				  g_theGoalDB->Get(i)->GetSquadClass();

		for
		(
		    Sorted_Goal_Iter goal_iter  = goal_list.begin();
		                     goal_iter != goal_list.end() &&
		                     goal_iter != m_pruned_goals_of_type[i];
		                   ++goal_iter
		){
			if(goal_iter->second->Get_Invalid())
				continue;

			if( (goal_squad_class & squad_class) != goal_squad_class)
				continue;

			if(goal_iter->second->Add_Match(squad))
			{
				count++;
			}
		}
	}

	return count;
}

void Scheduler::Remove_Matches_For_Goal
(
    const Goal_ptr & goal_ptr
)
{
	m_committed_agents -= goal_ptr->Remove_Matches();
}

void Scheduler::Remove_Matches_For_Squad
(
    const Squad_ptr & squad
)
{
	std::list<Plan_List::iterator> & match_refs = squad->Get_Match_References();

	for
	(
	    std::list<Plan_List::iterator>::iterator
	        plan_ref_iter  = match_refs.begin();
	        plan_ref_iter != match_refs.end();
	      ++plan_ref_iter
	){
		Assert((*plan_ref_iter)->Get_Squad() == squad);

		m_committed_agents -= (*plan_ref_iter)->Rollback_All_Agents();

		Goal_ptr goal_ptr = (*plan_ref_iter)->Get_Goal();
		m_committed_agents -= goal_ptr->Remove_Match(*plan_ref_iter);
	}

	match_refs.clear();
}

sint32 Scheduler::Rollback_Matches_For_Goal
(
    const Goal_ptr & goal
)
{
#if defined(_DEBUG) || defined(USE_LOGGING)
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, ("ROLLBACK_MATCHES_FOR_GOAL\n"));
#endif

	CTPGoal_ptr ctpgoal_ptr = (CTPGoal_ptr) goal;

#if defined(_DEBUG) || defined(USE_LOGGING)
	AI_DPRINTF(k_DBG_SCHEDULER,  m_playerId, -1, -1, ("\t"));
	ctpgoal_ptr->Log_Debug_Info(k_DBG_SCHEDULER);
	AI_DPRINTF(k_DBG_SCHEDULER,  m_playerId, -1, -1, ("\n"));
#endif

	Squad_Strength needed_strength = 
		ctpgoal_ptr->Get_Strength_Needed();

#if defined(_DEBUG) || defined(USE_LOGGING)
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, 
		("\t\tMissing attack = %3.0f\n",needed_strength.Get_Attack()));
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, 
		("\t\tMissing transport = %d\n",needed_strength.Get_Transport()));
	AI_DPRINTF(k_DBG_SCHEDULER, m_playerId, -1, -1, 
		("\t\tMissing defense = %3.0f\n",needed_strength.Get_Defense()));

#endif

	if(goal->Get_Raw_Priority() > m_maxUndercommittedPriority)
	{
		m_maxUndercommittedPriority = goal->Get_Raw_Priority();
	}

	m_neededSquadStrength.Set_To_The_Maximum(needed_strength);

	sint32 count = goal->Rollback_All_Agents();
	m_committed_agents -= count;

	AI_DPRINTF(k_DBG_SCHEDULER,  m_playerId, -1, -1, ("\t%d agents rolled back for Goal %x, %s.\n", count, goal, g_theGoalDB->Get(goal->Get_Goal_Type())->GetNameText()));

	return count;
}

bool Scheduler::Add_Transport_Matches_For_Goal
(
    const Goal_ptr & goal_ptr
)
{
	Assert(goal_ptr->Needs_Transporter());

	bool match_added = false;

	for
	(
	    Squad_List::iterator squad_iter  = m_squads.begin();
	                         squad_iter != m_squads.end();
	                       ++squad_iter
	)
	{
		Squad* squad = (*squad_iter);
		if ( (k_Goal_SquadClass_CanTransport_Bit & squad->Get_Squad_Class()) !=
			  k_Goal_SquadClass_CanTransport_Bit )
			  continue;

		bool hasMatch  = goal_ptr->Has_Squad(squad);
		match_added   |= hasMatch;

		if(hasMatch)
		{
			continue;
		}

		sint32 transports;
		sint32 max;
		sint32 empty;
		sint32 freeTransportCapacity = 0;

		CTPAgent_ptr agent_ptr = static_cast<CTPAgent_ptr>(squad->Get_Agent());

		if(!agent_ptr->Has_Goal())
		{
			agent_ptr->Get_Army()->GetCargo(transports, max, empty);
			freeTransportCapacity += empty;
		}

		if(freeTransportCapacity > 0
		&& goal_ptr->Add_Transport_Match(squad)
		){
			match_added = true;
		}
	}

	AI_DPRINTF(k_DBG_SCHEDULER_ALL, m_playerId, -1, -1, ("\t\tRecomputing matches for transport\n"));
	goal_ptr->Compute_Matching_Value(false);

	return match_added;
}

void Scheduler::Reprioritize_Goal(Goal_List::iterator &goal_iter)
{
	Goal_List::iterator goal_ptr_iter = goal_iter;
	Utility matchValue = static_cast<Goal_ptr>(*goal_ptr_iter)->Get_Matching_Value();

	++goal_ptr_iter;

	Goal_List tmp_list;
	tmp_list.splice(tmp_list.begin(), m_goals, goal_iter);


	while(goal_ptr_iter != m_goals.end())
	{
		Utility tmpValue = static_cast<Goal_ptr>(*goal_ptr_iter)->Get_Matching_Value();
		if(matchValue >= tmpValue)
		{
			m_goals.splice(goal_ptr_iter, tmp_list);
			break;
		}
		else
		{
			++goal_ptr_iter;
		}
	}
}

GOAL_TYPE Scheduler::GetMaxEvalExec(const StrategyRecord::GoalElement *goal_element_ptr, sint16 & max_eval, sint16 & max_exec)
{
	GOAL_TYPE goal_type = goal_element_ptr->GetGoalIndex();
	Assert(goal_type >= 0);
	Assert(goal_type < g_theGoalDB->NumRecords());

	
	double tmp_eval = goal_element_ptr->GetMaxEval();
	double tmp_exec = goal_element_ptr->GetMaxExec();
	
	if (goal_element_ptr->GetEvalPerCity() ||
		goal_element_ptr->GetPerCity())
		tmp_eval *= g_player[m_playerId]->GetNumCities();

	
	if (goal_element_ptr->GetExecPerCity() ||
		goal_element_ptr->GetPerCity())
		tmp_exec *= g_player[m_playerId]->GetNumCities();

	max_eval = (sint16) floor(tmp_eval);
	max_exec = (sint16) floor(tmp_exec);

	return goal_type;
}


void Scheduler::DisbandObsoleteArmies(const sint16 max_count)
{
	sint32 count = 0;

	Squad_List::iterator squad_ptr_iter = m_squads.begin();
	while (squad_ptr_iter != m_squads.end() && count < max_count)
	{
		if ((*squad_ptr_iter)->DisbandObsoleteArmies() > 0)
			count++;
		squad_ptr_iter++;
	}
}

Squad_Strength Scheduler::GetMostNeededStrength() const
{
	return m_neededSquadStrength;
}

void Scheduler::SetArmyDetachState(const Army & army, const bool detach)
{
	Squad_List::iterator squad_ptr_iter = m_squads.begin();
	bool found = false;
	while(squad_ptr_iter != m_squads.end() && !found)
	{
		CTPAgent_ptr ctp_agent = static_cast<CTPAgent_ptr>((*squad_ptr_iter)->Get_Agent());
		if(ctp_agent->Get_Army().m_id == army.m_id)
		{
			ctp_agent->Set_Detached(detach);
			found = true;
			break;
		}

		squad_ptr_iter++;
	}
}

bool Scheduler::GetArmyDetachState(const Army & army) const
{
	Squad_List::const_iterator squad_ptr_iter = m_squads.begin();

	while(squad_ptr_iter != m_squads.end())
	{
		const CTPAgent_ptr ctp_agent = static_cast<const CTPAgent_ptr>((*squad_ptr_iter)->Get_Agent());
		if (ctp_agent->Get_Army().m_id == army.m_id)
		{
			return ctp_agent->Get_Detached();
		}

		squad_ptr_iter++;
	}
	return false;
}

void Scheduler::SetContactCache(sint32 player)
{
	m_contactCachedPlayer = player;

	if (player < 0) return;

	m_contactCache        = 0;

	for(sint32 i = 0; i < k_MAX_PLAYERS; ++i)
	{
		if(i==player) continue;

		if(g_player[player]->HasContactWith(i))
		{
			m_contactCache |= (1<<i);
		}
	}
}

bool Scheduler::CachedHasContactWithExceptSelf(sint32 player1, sint32 player2)
{
	if (player1 == m_contactCachedPlayer)
	{

#ifdef _DEBUG

		int test1 = g_player[player1]->HasContactWith(player2) && (player1!=player2);
		int test2 = ((m_contactCache>>player2) & 1) != 0;
		Assert(test1==test2);
#endif

		return ((m_contactCache>>player2)&1) != 0;
	}

	if (g_player[player1] == NULL)
		return false;

	if (player1==player2) return false;
	return g_player[player1]->HasContactWith(player2);
}

void Scheduler::SetIsNeutralRegardCache(sint32 player)
{
	m_neutralRegardCachedPlayer = player;

	if (player < 0) return;

	m_neutralRegardCache        = 0;

	Diplomat & diplomat = Diplomat::GetDiplomat(player);

	for(sint32 i = 0; i < AgreementMatrix::s_agreements.GetMaxPlayers(); ++i)
	{
		if(diplomat.TestEffectiveRegard(i, NEUTRAL_REGARD))
		{
			m_neutralRegardCache |= (1<<i);
		}
	}
}

bool Scheduler::CachedIsNeutralRegard(sint32 player, sint32 opponent)
{
	if (player == m_neutralRegardCachedPlayer)
	{

#ifdef _DEBUG

		Diplomat & diplomat = Diplomat::GetDiplomat(player);
		int test1 = diplomat.TestEffectiveRegard(opponent, NEUTRAL_REGARD);
		int test2 = ((m_neutralRegardCache>>opponent) & 1) != 0;
		Assert(test1==test2);
#endif
		return ((m_neutralRegardCache>>opponent)&1) != 0;
	}

	Diplomat & diplomat = Diplomat::GetDiplomat(player);
	return diplomat.TestEffectiveRegard(opponent, NEUTRAL_REGARD);
}

void Scheduler::SetIsAllyRegardCache(sint32 player)
{
	m_allyRegardCachedPlayer = player;

	if (player < 0) return;

	m_allyRegardCache        = 0;

	Diplomat & diplomat = Diplomat::GetDiplomat(player);

	for(sint32 i = 0; i < AgreementMatrix::s_agreements.GetMaxPlayers(); ++i)
	{
		if(diplomat.TestAlliedRegard(i))
		{
			m_allyRegardCache |= (1<<i);
		}
	}
}

bool Scheduler::CachedIsAllyRegard(sint32 player, sint32 ally)
{
	if (player == m_allyRegardCachedPlayer)
	{

#ifdef _DEBUG
		
		Diplomat & diplomat = Diplomat::GetDiplomat(player);
		int test1 = diplomat.TestAlliedRegard(ally);
		int test2 = ((m_allyRegardCache>>ally) & 1) != 0;
		Assert(test1==test2);
#endif
		return ((m_allyRegardCache>>ally)&1) != 0;
	}

	Diplomat & diplomat = Diplomat::GetDiplomat(player);
	return diplomat.TestAlliedRegard(ally);
}

void Scheduler::Recompute_Goal_Strength()
{
	for
	(
	    Goal_List::iterator goal_iter  = m_goals.begin();
	                        goal_iter != m_goals.end();
	                      ++goal_iter
	)
	{
		Goal_ptr theGoal = static_cast<Goal_ptr>(*goal_iter);

		theGoal->Recompute_Current_Attacking_Strength();
	}
}

void Scheduler::Compute_Squad_Strength()
{
	for
	(
	    Squad_List::iterator squad_iter  = m_squads.begin();
	                         squad_iter != m_squads.end();
	                       ++squad_iter
	)
	{
		Squad_Strength strength;
		Squad* squad = (*squad_iter);
		squad->Compute_Strength(strength);
	}
}

void Scheduler::Rollback_Emptied_Transporters()
{
	for
	(
	    Goal_List::iterator goal_iter  = m_goals.begin();
	                        goal_iter != m_goals.end();
	                      ++goal_iter
	)
	{
		Goal_ptr theGoal = static_cast<Goal_ptr>(*goal_iter);

		m_committed_agents -= theGoal->Rollback_Emptied_Transporters();
	}
}

void Scheduler::Sort_Goal_Matches_If_Necessary()
{
	for
	(
	    Goal_List::iterator goal_iter  = m_goals.begin();
	                        goal_iter != m_goals.end();
	                      ++goal_iter
	)
	{
		Goal_ptr theGoal = static_cast<Goal_ptr>(*goal_iter);

		theGoal->Sort_Matches_If_Necessary();
	}
}
