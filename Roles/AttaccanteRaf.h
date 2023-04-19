#define DO_TURN_THRESHOLD 1080.f //si girano quando si allontanano di un metro dalla posizione
#define TOLERANCE_DEGREES_FOR_TURN 10_deg
#define STATIC_THRESHOLD 400.f
#define NOT_MOVING_THRESHOLD -1000.f
#define TURN_TO_BALL_THRESHOLD 20.f

#define WAIT_TEAMMATES


option(AttaccanteRaf){
    
  initial_state(start){
      
    transition{
      if(state_time > 1000)
       goto giraVersoPalla;
    }
    
    action{
      HeadControlMode(HeadControl::lookForward);
     Stand();
    }
  }

  state(giraVersoPalla){
      
    transition{
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto cercaPalla;
      if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
        goto versoLaPalla;
    }
    
    action{
      HeadControlMode(HeadControl::lookForward);
      WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
    }
  }

  state(versoLaPalla){

    transition{
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto cercaPalla;
      if(theBallModel.estimate.position.norm() < 500.f)
        goto allineamentoPorta;
    }
    
    action{
      HeadControlMode(HeadControl::lookForward);
      WalkToTarget(Pose2f(100.f, 100.f, 100.f), theBallModel.estimate.position);
    }
  }

  state(allineamentoPorta){
      
    transition{
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto cercaPalla;
      if(std::abs(theLibCodeRelease.angleToGoal) < 10_deg && std::abs(theBallModel.estimate.position.y()) < 100.f)
        goto dietroLaPalla;
    }
    
    action{
      HeadControlMode(HeadControl::lookForward);
      WalkToTarget(Pose2f(1.f, 1.f, 1.f), Pose2f(theLibCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 400.f, theBallModel.estimate.position.y()));
    }
  }

  state(dietroLaPalla){
      
    transition{
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto cercaPalla;
      if(theRobotPose.translation.x() > theFieldDimensions.xPosOpponentPenaltyMark - 250.f)
        goto avvicinatiTiro;
    }
    
    action{
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(0.5f, 0.5f, 0.5f), Pose2f(theLibCodeRelease.angleToGoal, theBallModel.estimate.position.x(), theBallModel.estimate.position.y()));
    }
  }
  
  state(avvicinatiTiro){
   
      transition{
            if(theBallModel.estimate.position.x() < 160.f)
              goto preparaCalcio;
      }
      
      action{
            theHeadControlMode = HeadControl::lookForward;
            WalkToTarget(Pose2f(0.3f, 0.3f, 0.3f), Pose2f(theLibCodeRelease.angleToGoal, theBallModel.estimate.position.x(), theBallModel.estimate.position.y()));
      }
  }
  
  state(preparaCalcio){
      
      transition{
          if(state_time > 500)
              goto calcia;
      }
      
      action{
          float angoloRotazione = 0.f;
          if((theFieldDimensions.yPosRightGoal+theFieldDimensions.yPosCenterGoal)/2 <= theRobotPose.translation.y() && theRobotPose.translation.y() < 0){
              angoloRotazione = 0.75f;
          }
          if((theFieldDimensions.yPosLeftGoal+theFieldDimensions.yPosCenterGoal)/2 >= theRobotPose.translation.y() && theRobotPose.translation.y() > 0){
              angoloRotazione = -0.75f;
          }
          if((theFieldDimensions.yPosRightGoal+theFieldDimensions.yPosCenterGoal)/2 > theRobotPose.translation.y() && theRobotPose.translation.y() > theFieldDimensions.yPosRightGoal){
              angoloRotazione = 1.f;
          }
          if((theFieldDimensions.yPosLeftGoal+theFieldDimensions.yPosCenterGoal)/2 < theRobotPose.translation.y() && theRobotPose.translation.y() < theFieldDimensions.yPosLeftGoal){
              angoloRotazione = -1.f;
          }
          HeadControlMode(HeadControl::lookForward);
          WalkAtRelativeSpeed(Pose2f(angoloRotazione, 0.f, 0.f));
      }
  }

  state(calcia){
      
    transition{
      if(state_time > 3000 || (state_time > 10 && action_done))
        goto start;
    }
    
    action{
      theHeadControlMode = HeadControl::lookForward;
      Kicks("veryFastForwardKick");
    }
  }

  state(cercaPalla){
      
    transition{
      if(theLibCodeRelease.timeSinceBallWasSeen < 300)
        goto giraVersoPalla;
    }
    
    action{
      HeadControlMode(HeadControl::lookForward);
      WalkAtRelativeSpeed(Pose2f(1.f, 0.f, 0.f));
    }
  }
}
