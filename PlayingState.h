#define MUSUMECI_ACTIVATE_STRIKER true
#define MUSUMECI_ACTIVATE_DEFENSIVE_DEFENDER true
#define MUSUMECI_ACTIVATE_AGGRESSIVE_DEFENDER true
#define MUSUMECI_ACTIVATE_Supporter true
#define MUSUMECI_ACTIVATE_RED true

#define PLAYING_STATE_DEBUG false

option(PlayingState)
{
    initial_state(demo)
    {
        action
        {
        
            if(theRole.role == Role::RoleType::goalie){
                Goalie();
            }
            if(theRole.role == Role::RoleType::striker){
                AttaccanteRaf();
            }
            if(theRole.role == Role::RoleType::defender){
                DifensoreRaf();
            }
            if(theRole.role == Role::RoleType::fantasista){
                FantasistaRaf();
            }
            if(theRole.role == Role::RoleType::centrocampista){
                MedianoRaf();
            }
        }
    }
}
