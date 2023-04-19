

#pragma once

#include <iostream>
#include <set>
#include "Tools/Module/Module.h"
#include "Tools/Math/Transformation.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Perception/BallPercepts/BallPercept.h"
#include "Representations/Modeling/ObstacleModel.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Infrastructure/RobotInfo.h"
#include "Representations/Infrastructure/GameInfo.h"
#include "Representations/Infrastructure/TeamInfo.h"
#include "Representations/Sensing/FallDownState.h"
#include "Representations/Communication/TeamData.h"
#include "Representations/spqr_representations/ConfigurationParameters.h"
#include "Representations/spqr_representations/OurDefinitions.h"
#include "Representations/spqr_representations/UtilityShare.h"
#include "Representations/BehaviorControl/Libraries/LibCodeRelease.h"
#include "Representations/Modeling/TeamPlayersModel.h"
#include "Representations/Modeling/TeamBallModel.h"
 
#include "Platform/SystemCall.h"
#include "Platform/Time.h"
#include <mutex>

MODULE(UtilityShareProvider, 
{,
 REQUIRES(GameInfo),
 REQUIRES(OpponentTeamInfo),
 REQUIRES(OwnTeamInfo),
 REQUIRES(ObstacleModel),
 REQUIRES(RobotInfo),
 REQUIRES(LibCodeRelease),
 REQUIRES(RobotPose),
 REQUIRES(BallModel),
 REQUIRES(BallPercept),
 REQUIRES(FrameInfo),
 REQUIRES(FallDownState),
 REQUIRES(TeamData),
 REQUIRES(TeamBallModel),
 REQUIRES(TeamPlayersModel),
 REQUIRES(FieldDimensions),
 PROVIDES(UtilityShare),
});

class UtilityShareProvider : public UtilityShareProviderBase
{
private:
    int risultatoPartita();   
    int numeroPenalizzati();   
public:
    void update(UtilityShare& us);
    int status = 0;
    UtilityShareProvider();
};

