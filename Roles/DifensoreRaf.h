#define DO_TURN_THRESHOLD 1080.f //si girano quando si allontanano di un metro dalla posizione
#define TOLERANCE_DEGREES_FOR_TURN 10_deg
#define STATIC_THRESHOLD 400.f
#define NOT_MOVING_THRESHOLD -1000.f
#define TURN_TO_BALL_THRESHOLD 20.f

#define WAIT_TEAMMATES

int casuale = 0;
int y = 0;

option(DifensoreRaf){
    
  initial_state(start){
      
    transition{
        if(state_time > 1500){
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
        if(state_time > 20000){
            casuale = rand()%1500;
            y = rand()%1;
            if(y == 0){
                casuale = casuale * -1;
            }
            goto camminaLateralmente;
        }
    }
    
    action{
        lookLeftAndRight();
        WalkToTargetPathPlanner(Pose2f(1.f,1.f,1.f), Pose2f(0,theFieldDimensions.xPosOwnGoal/1.5, theFieldDimensions.yPosCenterGoal));
    }
    
  }
  
  state(camminaLateralmente){
      
    transition{
       if(state_time > 20000){
          goto posizionati;
       }
    }
    
    action{
        HeadControlMode(HeadControl::lookForward);
        WalkToTargetPathPlanner(Pose2f(1.f,1.f,1.f), Pose2f(0,theFieldDimensions.xPosOwnGoal/1.5, theFieldDimensions.yPosCenterGoal + casuale));
    }
      
      
  }
  
}

