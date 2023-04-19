/**
* @file ContextCoordinator.cpp
*   This file implements the team coordination module
* @author Francesco Riccio, Emanuele Borzi
*/

#include "ContextCoordinator.h"

#include <unistd.h>
#include <iostream>
#include "Representations/SPQR-Libraries/ConfigFile/ConfigFile.h"


//#include <fstream> // ofstream


#define NORM(x, y) sqrt(x*x + y*y)
//#define UM_VIEW

MAKE_MODULE(ContextCoordinator, behaviorControl)

ContextCoordinator::ContextCoordinator(){
    SPQR::ConfigurationParameters();
    
}


void ContextCoordinator::update(Role& role)
{ 
	
    if(theRobotInfo.number == 1){
		role.role = Role::RoleType::goalie;	
	}
	else{
        float ruoli[4] = {theUtilityShare.role2_utility,theUtilityShare.role3_utility,theUtilityShare.role4_utility,theUtilityShare.role5_utility};
        int utilitaMassima = 0;
        for(unsigned i = 0; i < 4;i++){
            if(ruoli[i] == 100){
                utilitaMassima = i;
                break;
            }
        }
                
        switch(utilitaMassima){
            case 0:
                role.role = Role::RoleType::striker;	
                break;
            case 1:
                if(theUtilityShare.context == 0){
                    role.role = Role::RoleType::fantasista;
                    break;
                }
                if(theUtilityShare.context == 1){
                    role.role = Role::RoleType::fantasista;
                    break;
                }
                if(theUtilityShare.context == 2){
                    role.role = Role::RoleType::centrocampista;
                    break;
                }
                
            case 2:
                if(theUtilityShare.context == 0){
                    role.role = Role::RoleType::centrocampista;
                    break;
                }
                if(theUtilityShare.context == 1){
                    role.role = Role::RoleType::fantasista;
                    break;
                }
                if(theUtilityShare.context == 2){
                    role.role = Role::RoleType::centrocampista;
                    break;
                }
            case 3:
                role.role = Role::RoleType::defender;	
                break;
        }
	}
	return;
}
