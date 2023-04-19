#include "UtilityShareProvider.h"

#include <unistd.h>
#include <iostream>
#include <math.h> 


UtilityShareProvider::UtilityShareProvider(){
    SPQR::ConfigurationParameters();
}

//Calcolo il risulato delle partita
int UtilityShareProvider::risultatoPartita(){
    //Valuto la situazione 0-0, 1-0 0-1 e vantaggi superiori di 2
    int golMiei = static_cast<int>(theOwnTeamInfo.score);
    int golAvversari = static_cast<int>(theOpponentTeamInfo.score);
    return golMiei - golAvversari;
}

//Calcolo se ho dei giocatori penalizzati
int UtilityShareProvider::numeroPenalizzati(){
    int numero = 0;
    for(unsigned i = 0; i < theTeamData.teammates.size(); i++){
        if(theTeamData.teammates.at(i).status == 0){
                numero++;
        }    
    }
    return numero;
}

void UtilityShareProvider::update(UtilityShare& us) {
    
    //Palla e distanza dalla palla
    float miaDistanzaDallaPalla = theBallModel.estimate.position.norm();
    
    //Porta e distanza dalla porta
    Pose2f miaPorta = Pose2f(theFieldDimensions.xPosOwnGoal,theFieldDimensions.yPosCenterGoal);
    float miaDistanzaDallaPorta = theLibCodeRelease.distance(theRobotPose,miaPorta);
    
    //Sono striker o meno
    bool sonoStriker = true;
    
    //Posizione Striker;
    Pose2f posizioneStriker = Pose2f(0,0);
    
    if(miaDistanzaDallaPalla == 0){
        miaDistanzaDallaPalla = 99999.f;
    }
    
    //Calcolo la validità come striker
    float distanzaMinima = 99999.f;
    for(unsigned i = 0; i < theTeamData.teammates.size(); i++){
        float distanzaIesimaPalla = theTeamData.teammates.at(i).theBallModel.estimate.position.norm();
		if(distanzaIesimaPalla == 0)continue;
		//if(miaDistanzaDallaPalla == 0)continue;
        if(distanzaIesimaPalla < miaDistanzaDallaPalla && theTeamData.teammates.at(i).number != 1){
            sonoStriker = false;
            if(distanzaIesimaPalla < distanzaMinima){
                distanzaMinima = distanzaIesimaPalla;
                posizioneStriker = theTeamData.teammates.at(i).theRobotPose;
            }
        }   
	}
    
        
    //Sono lo striker
    if(sonoStriker){
        us.role2_utility = 100;//Utile come striker
        us.role3_utility = 0;
        us.role4_utility = 0;
        us.role5_utility = 0;
        posizioneStriker = theRobotPose;
    }
    
    //Non utile come striker, trovo un altro ruolo
    if(sonoStriker == false){
        bool sonoDefender = true;
        for(unsigned i = 0; i < theTeamData.teammates.size(); i++){
            float distanzaIesimaPorta = theLibCodeRelease.distance(theTeamData.teammates.at(i).theRobotPose,miaPorta);
            if(theTeamData.teammates.at(i).theUtilityShare.role2_utility == 100){
                distanzaIesimaPorta = 99999.f;
            }
            if(distanzaIesimaPorta < miaDistanzaDallaPorta && theTeamData.teammates.at(i).number != 1){
                    sonoDefender = false;
            }   
        }
        if(sonoDefender){
            us.role2_utility = 0;
            us.role3_utility = 0;
            us.role4_utility = 0;
            us.role5_utility = 100;//Utile come defender
        }
        
        if(sonoDefender == false){
            
            bool sonoSupporter = true;
            float distanzaDaStriker = theLibCodeRelease.distance(theRobotPose,posizioneStriker);
            for(unsigned i = 0; i < theTeamData.teammates.size(); i++){
                float distanzaIesimaDaStriker = theLibCodeRelease.distance(theTeamData.teammates.at(i).theRobotPose,posizioneStriker);
                if(theTeamData.teammates.at(i).theUtilityShare.role2_utility == 100)continue;
                if(theTeamData.teammates.at(i).theUtilityShare.role5_utility == 100)continue;
                if(distanzaDaStriker > distanzaIesimaDaStriker && theTeamData.teammates.at(i).number != 1){
                        sonoSupporter = false;
                }   
            }
            
            if(sonoSupporter){
                us.role2_utility = 0;
                us.role3_utility = 100;//Utile come fantasista
                us.role4_utility = 0;
                us.role5_utility = 0;
            }
            if(sonoSupporter == false){
                us.role2_utility = 0;
                us.role3_utility = 0;
                us.role4_utility = 100;//Utile come mediano
                us.role5_utility = 0;
            }
        }
    }
    
    int giocatoriPenalizzati = numeroPenalizzati();
    int differenzaRisultato = risultatoPartita();

    //Sto pareggiando o perdendo di misura
    if(differenzaRisultato == 0 || differenzaRisultato == -1){
        if(giocatoriPenalizzati == 0){
            us.context = 0;
        }
        if(giocatoriPenalizzati > 0){
            us.context = 1;
        }
    }
    
    //Sto vincendo di misura
    if(differenzaRisultato == 1){
        if(giocatoriPenalizzati == 0){
            us.context = 0;
        }
        if(giocatoriPenalizzati > 0){
            us.context = 2;
        }
    }
        
    //Sto vincendo con uno scarto buono
    if(differenzaRisultato > 1){
            us.context = 2;
    }
    
    //Sto perdendo di brutto
    if(differenzaRisultato < -1){
        us.context = 1;
    }
	
}

MAKE_MODULE(UtilityShareProvider, modeling)
