#define DO_TURN_THRESHOLD 1080.f //si girano quando si allontanano di un metro dalla posizione
#define TOLERANCE_DEGREES_FOR_TURN 10_deg
#define STATIC_THRESHOLD 400.f
#define NOT_MOVING_THRESHOLD -1000.f
#define TURN_TO_BALL_THRESHOLD 20.f

#define WAIT_TEAMMATES

float posizioneMediano = -750.f;

option(MedianoRaf){
    
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
        //Ho due mediani
        if(theUtilityShare.context == 2){
            //Sono il vero mediano
            if(theUtilityShare.role4_utility == 100){
                posizioneMediano = +750.f;
            }
            //Sono il fantasista adattato a mediano
            if(theUtilityShare.role3_utility == 100){
                posizioneMediano = -750.f;
            }
            HeadControlMode(HeadControl::lookForward);
            WalkToTargetPathPlanner(Pose2f(1.f,1.f,1.f), Pose2f(0,theFieldDimensions.xPosOwnGoal/2.5, theFieldDimensions.yPosCenterGoal + posizioneMediano));
        }else{
            HeadControlMode(HeadControl::lookForward);
            WalkToTargetPathPlanner(Pose2f(1.f,1.f,1.f), Pose2f(0,theFieldDimensions.xPosOwnGoal/2.5, theFieldDimensions.yPosCenterGoal));
        }
       
    }
    
  }
  
}