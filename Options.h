/** All option files that belong to the current behavior have to be included by this file. */

#include "Options/Soccer.h"

#include "Options/GameControl/HandleGameState.h"
#include "Options/GameControl/HandlePenaltyState.h"
#include "Options/GameControl/PlayingState.h"
#include "Options/GameControl/ReadyState.h"



#include "Options/HeadControl/LookForward.h"
#include "Options/HeadControl/LookAtBall.h"
#include "Options/HeadControl/LookAtGlobalBall.h"
#include "Options/HeadControl/LookAtLandmark.h"
#include "Options/HeadControl/LookLeftAndRight.h"
#include "Options/HeadControl/LookRightAndLeft.h"

#include "Options/Output/Activity.h"
#include "Options/Output/Annotation.h"
#include "Options/Output/HeadControlMode.h"
#include "Options/Output/HeadMotionRequest/SetHeadPanTilt.h"
#include "Options/Output/HeadMotionRequest/SetHeadTarget.h"
#include "Options/Output/HeadMotionRequest/SetHeadTargetOnGround.h"

#include "Options/Output/MotionRequest/InWalkKick.h"
#include "Options/Output/MotionRequest/SpecialAction.h"
#include "Options/Output/MotionRequest/Stand.h"
#include "Options/Output/MotionRequest/WalkAtAbsoluteSpeed.h"
#include "Options/Output/MotionRequest/WalkAtRelativeSpeed.h"
#include "Options/Output/MotionRequest/WalkToTarget.h"
#include "Options/Output/MotionRequest/GetUpEngine.h"
#include "Options/Output/MotionRequest/GetIntoReadyPosition.h"
#include "Options/Output/MotionRequest/Kicks.h"
#include "Options/Output/MotionRequest/StopBall.h"
#include "Options/Output/MotionRequest/WalkToTargetPathPlanner.h"
#include "Options/Output/MotionRequest/Approacher2020.h"
#include "Options/Output/MotionRequest/FastApproacher.h"


#include "Options/Output/MotionRequest/Goalie/goalieFastDiveLeft.h"
#include "Options/Output/MotionRequest/Goalie/goalieFastDiveRight.h"
#include "Options/Output/MotionRequest/Goalie/GoalieKickAway.h"

#include "Options/Roles/Goalie.h"
#include "Options/Roles/MUSUMECI_ALLCONTEXTS_DummyRole.h"

//PROJECT BEHAVIOURS
#include "Options/Roles/MUSUMECI_ALLCONTEXTS_DefensiveDefender.h"
#include "Options/Roles/MUSUMECI_ALLCONTEXTS_AggressiveDefender.h"
#include "Options/Roles/MUSUMECI_ALLCONTEXTS_Supporter.h"
#include "Options/Roles/MUSUMECI_ALLCONTEXTS_Striker.h"

//Aggiunto per usare vincitore
#include "Options/Roles/Saraceni_Default_Defender.h"
#include "Options/Roles/Saraceni_Default_Midfielder.h"
#include "Options/Roles/Saraceni_Default_Supporter.h"
#include "Options/Roles/Saraceni_Losing_Defender.h"
#include "Options/Roles/Saraceni_Losing_Midfielder.h"
#include "Options/Roles/Saraceni_Losing_Supporter.h"
#include "Options/Roles/Saraceni_Outnum_Defender.h"
#include "Options/Roles/Saraceni_Outnum_Midfielder.h"
#include "Options/Roles/Saraceni_Outnum_Supporter.h"

//ruoli Raffaele
#include "Options/Roles/AttaccanteRaf.h"
#include "Options/Roles/DifensoreRaf.h"
#include "Options/Roles/FantasistaRaf.h"
#include "Options/Roles/MedianoRaf.h"
#include "Options/Roles/PortiereRaf.h"

//********************TECHNICAL CHALLENGE********************
//#define DETECT_OBS_POSE
#ifdef DETECT_OBS_POSE
#include "Options/Roles/StrikerCornerKickChallenge.h"
#include "Options/Roles/ReceiverCornerKickChallenge.h"
#endif
//******************END TECHNICAL CHALLENGE********************





#include "Options/Output/PlaySound.h"





#include "Options/Skills/GetUp.h"

#include "Options/Tools/ButtonPressedAndReleased.h"
#include "Options/Tools/USBCheck.h"
