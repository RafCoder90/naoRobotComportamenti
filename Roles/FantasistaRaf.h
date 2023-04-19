#define DO_TURN_THRESHOLD 1080.f //si girano quando si allontanano di un metro dalla posizione
#define TOLERANCE_DEGREES_FOR_TURN 10_deg
#define STATIC_THRESHOLD 400.f
#define NOT_MOVING_THRESHOLD -1000.f
#define TURN_TO_BALL_THRESHOLD 20.f

#define WAIT_TEAMMATES

option(FantasistaRaf){
    
    initial_state(start){
      
    transition{
        if(state_time > 3000){
            goto posizionati;
        }
    }
    
    action{
        lookLeftAndRight();
        Stand();
    }
    
  }
  
  state(posizionati){
      
    transition{
        if(theLibCodeRelease.timeSinceBallWasSeen > 20000)
          goto start;
    }
    
    action{
        float xStriker = 0.f;
        float yStriker = 0.f;
        for(unsigned i = 0; i < theTeamData.teammates.size(); i++){
                if(theTeamData.teammates.at(i).theUtilityShare.role2_utility == 100){
                    xStriker = theTeamData.teammates.at(i).theRobotPose.translation.x();
                    yStriker = theTeamData.teammates.at(i).theRobotPose.translation.y();
                    break;
                }
        }
        //Ho due fantasisti
        if(theUtilityShare.context == 1){
            float posizioneY = 0.f;
            //Sono il vero fantasista
            if(theUtilityShare.role3_utility == 100){
                posizioneY = yStriker + 550.f;
                if(posizioneY < theFieldDimensions.yPosLeftSideline){
                    posizioneY = theFieldDimensions.yPosLeftSideline + 300.f;
                }
                if(posizioneY > theFieldDimensions.yPosRightSideline){
                    posizioneY = theFieldDimensions.yPosLeftSideline - 300.f;                }
            }
            //Sono il mediano adattato a fantasista
            if(theUtilityShare.role4_utility == 100){
                posizioneY = yStriker - 550.f;
                if(posizioneY > theFieldDimensions.yPosLeftSideline){
                    posizioneY = theFieldDimensions.yPosLeftSideline - 300.f;
                }
                if(posizioneY < theFieldDimensions.yPosRightSideline){
                    posizioneY = theFieldDimensions.yPosLeftSideline + 300.f;
                }
            }
            HeadControlMode(HeadControl::lookForward);
            WalkToTargetPathPlanner(Pose2f(0.5f,0.5f,0.5f), Pose2f(0,xStriker, posizioneY));
        }else{
            HeadControlMode(HeadControl::lookForward);
            WalkToTargetPathPlanner(Pose2f(0.5f,0.5f,0.5f), Pose2f(0,xStriker - 500.f, yStriker));
        }
       
    }
    
  }
}

