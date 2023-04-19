#pragma once

#include <iostream>
#include <set>
#include "Tools/Module/Module.h"  // ok
#include "Tools/Math/Transformation.h"  // ok
#include "Representations/Modeling/RobotPose.h"  // ok
#include "Representations/Modeling/TeamBallModel.h"  // ok
#include "Representations/Infrastructure/FrameInfo.h" // ok
#include "Representations/Infrastructure/RobotInfo.h" // ok
#include "Representations/Infrastructure/GameInfo.h" // ok
#include "Representations/Infrastructure/TeamInfo.h" // ok
#include "Representations/Sensing/FallDownState.h" // ok
#include "Representations/Communication/TeamData.h"  // modificato
#include "Representations/spqr_representations/ConfigurationParameters.h" // ok
#include "Representations/spqr_representations/OurDefinitions.h" // ok
#include "Representations/spqr_representations/UtilityShare.h"
#include "Representations/BehaviorControl/Role.h" // ok nuovo
#include "Representations/BehaviorControl/Libraries/LibCodeRelease.h"
#include "Representations/Configuration/FieldDimensions.h"
#include "Representations/Perception/ObstaclesPercepts/ObstaclesFieldPercept.h"
#include "Representations/spqr_representations/GCData.h"



// #include "Timestamp.h" // nuovo ma non funge

// #include <SPQR-Libraries/PTracking/Core/Processors/Processor.h>
#include "Platform/SystemCall.h"
#include "Platform/Time.h"
#include <mutex>


MODULE(ContextCoordinator, //TODO need to change Forget and Change as streamable and sand to all also the role toghether with the timestamp.. byebye
{,
 REQUIRES(GameInfo),
 REQUIRES(LibCodeRelease),
 REQUIRES(OpponentTeamInfo),
 REQUIRES(OwnTeamInfo),
 REQUIRES(RobotInfo),
 REQUIRES(RobotPose),
 REQUIRES(BallModel),
 REQUIRES(FrameInfo),
 REQUIRES(FallDownState),
 REQUIRES(TeamData),
 REQUIRES(TeamBallModel),
 REQUIRES(FieldDimensions),
 REQUIRES(ObstaclesFieldPercept),
 USES(Role),
 USES(UtilityShare),
 USES(GCData),
 PROVIDES(Role),


       });

class ContextCoordinator: public ContextCoordinatorBase
{

private:
  
public:
    ContextCoordinator();
    void update(Role& role);
};
