/**
 * @file Representations/BehaviorControl/Role.h
 *
 * Declaration of the representation of a robot's behavior role
 *
 * @author Tim Laue, Andreas Stolpmann
 */

#pragma once

#include "RoleCheck.h"
#include "Tools/Streams/AutoStreamable.h"
#include "Tools/Streams/Enum.h"
#include "Tools/Math/Pose2f.h"
/**
 * @struct Role
 * Representation of a robot's behavior role
 */
STREAMABLE(Role,
{
  /** The different roles */
  ENUM(RoleType,
  {,
   undefined,
   taker,
   kicker,
   goalie,
   striker,
   defender,
   supporter,
   centrocampista,
   fantasista,
   jolly,
   searcher_1,
   searcher_2,
   searcher_3,
   searcher_4,
   penaltyStriker,
   penaltyKeeper,
   planStriker,
   planJolly,
   saraceni_striker,
   saraceni_supporter,
   saraceni_midfielder,
   saraceni_defender,
   saraceni_losing_supporter,
   saraceni_losing_midfielder,
   saraceni_losing_defender,
   saraceni_outnum_supporter,
   saraceni_outnum_midfielder,
   saraceni_outnum_defender,
   musumeci_role2, //16 //NB: ogni "role2" sarà associato da ora in poi ad Approacher2020.h
   musumeci_role3, //17
   musumeci_role4, //18
   musumeci_role5, //19
   musumeci_losing_role2, //20
   musumeci_losing_role3, //21
   musumeci_losing_role4, //22
   musumeci_losing_role5, //23
   musumeci_outnumbered_role2, //24
   musumeci_outnumbered_role3, //25
   musumeci_outnumbered_role4, //26
   musumeci_outnumbered_role5, //27
   none,

  });

  bool isGoalkeeper() const;
  
  ENUM(Context,
   {,
       no_context, //TODO CAPIRE COME SOSTITUIRE L' =1 che c'era
       playing,
       search_for_ball,
   });
   
  

  CHECK_OSCILLATION(role, RoleType, undefined, "Role", 5000)
  /** Draws the current role next to the robot on the field view (in local robot coordinates) */
  void draw() const,

  /** Instance of role */
  (RoleType)(undefined) role,
  (RoleType)(undefined) lastRole,
 //this is not the context you have to use, that is located in UtilityShare
  (Context)(no_context) current_context,
  (std::vector<int>)(5,0) utility_vector,
  (std::vector<Pose2f>)(std::vector<Pose2f>(5,Pose2f())) robots_poses,
});
