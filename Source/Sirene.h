/*
  ==============================================================================

    S1.h
    Created: 6 May 2020 10:49:33am
    Author:  guyot

  ==============================================================================
*/

#pragma once

#include <iostream>

#include <JuceHeader.h>



//
//  S1.h
//  FourrerN
//
//  Created by Maria Isabella Hallberg Møller on 25/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include <math.h>
//#include "CoreFoundation/CoreFoundation.h"  // Pat: j'enleve CoreFoundation

#ifndef FourrerN_S1_h
#define FourrerN_S1_h
#define DeuxPieSampleRate 2.* M_PI /44100
#define MAX_Partiel 200
#define NOMBRE_DE_NOTE 80
#define MAX_TAB 1000
//#define pourcentClapetOff 7
#define constescursion 10	// valeur maxi de l'amplitude VFO en % de la vitesse correspondant ‡ une note

//pat see precision
#include <iomanip>



class Sirene
{
public:
		Sirene(const std::string& str);
		~Sirene();

    void setMidicent(int note);
    void setnoteFromExt(int note);
    void setnote();
    void oujesuis();
    void changeQualite(int qualt);
    void set16ou8Bit(bool is);
    void setVelocite(int velo);

    void setisCrossFade(int is);

	void readDataFromBinaryFile(std::string dataFilePath, std::string tabAmpFile, std::string tabFreqFile, std::string dureTabFile, std::string vectorIntervalFile);


    inline float calculwave(){

        //std::cout << "Je suis la 1" << std::endl;
        float wavefinal=0.;

        //std::cout << "Je suis la 5" << std::endl;

        isChangementdenote=false;
        //std::cout << "Je suis la 6" << std::endl;

        if (! (noteInf == ancienNoteVoulue))
        {
            //std::cout << "Je suis la 2" << std::endl;
            isChangementdenote=true;
            //std::cout << "isChangementdenote\n" << std::endl;
            ancienNoteVoulue=noteInf;
        }

        if (countKInf==(int)dureTabs[noteInf][0]) {
					  //cout << "Je suis la 3" << endl;
            countP[noteInf]++;
            if( countP[noteInf]==(int)dureTabs[noteInf][1]) countP[noteInf]=0;
            countKInf=0;
        }
        countKInf++;
        if (countKSup==(int)dureTabs[noteSup][0]) {
						//cout << "Je suis la 4" << endl;
            countP[noteSup]++;
            if( countP[noteSup]==(int)dureTabs[noteSup][1]) countP[noteSup]=0;
            countKSup=0;
        }
        countKSup++;



        if (ampvouluz < ampvoulu) ampvouluz += vitesseClape;
        if ((ampvouluz > ampvoulu) ) ampvouluz -= vitesseClape;

        float waveInf=0.;
        eloignementfreq=((noteSup)*100)-midiCentVoulue;
        count8bit= !count8bit;


        for (int i = 0;i < qualite ; i++){
            if (is16Bit || isChangementdenote || count8bit){
                if(isCrossfade){
									  //cout << "Je suis la 5" << endl;
                    phaseInf[i] += ((tabFreq[noteInf][countP[noteInf]][i]* pitchSchift[noteInf]
                                     *(eloignementfreq)/100.)
                                    + (tabFreq[noteSup][countP[noteSup]][i]* pitchSchift[noteSup]
                                       *(100-eloignementfreq)/100.)) ;

                    amp[i] = (tabAmp[noteInf][countP[noteInf]][i]
                            *((eloignementfreq)/100.))+
                    (tabAmp[noteSup][countP[noteSup]][i]*((100-eloignementfreq)/100.) );

                }else {
                    amp[i]=tabAmp[noteInf][countP[noteInf]][i];

										// tabAmp[NOMBRE_DE_NOTE=80][MAX_TAB=1000][MAX_Partiel=200];
										/*
										cout << "noteInf :" << noteInf << endl;
										cout << "countP[noteInf] :" << countP[noteInf] << endl;
										cout << "i :" << i << endl;
										cout << "tabAmp[noteInf][countP[noteInf]][i] :" << tabAmp[noteInf][countP[noteInf]][i] << endl;
										cout << "amp[i] :" << amp[i] << endl;
										*/

                    phaseInf[i] += (tabFreq[noteInf][countP[noteInf]][i]* pitchSchift[noteInf]);
                }
                ampz[i]  = 0.001 * amp[i]  + 0.999 * ampz[i] ;
                waveInf += sin(phaseInf[i])* ampz[i];
                anciennewaveInf=waveInf;
                if (phaseInf[i]==180.) phaseInf[i]=0.;

            } else {
                phaseInf[i] += (tabFreq[noteInf][countP[noteInf]][i]* pitchSchift[noteInf]);
            }
        }


        if(is16Bit)wavefinal=waveInf*ampvouluz;
        else wavefinal=anciennewaveInf*ampvouluz;
		//cout << "noteEncour :" << noteEncour << endl;
        if (noteEncour<=noteMin*100) wavefinal=0.;



        return wavefinal;
    }

private:
    //CFRunLoopTimerRef 			timerSetNoteS1; //pat
    //CFRunLoopRef		mRunLoopRef; //pat

    float tabAmp[NOMBRE_DE_NOTE][MAX_TAB][MAX_Partiel];
    float tabFreq[NOMBRE_DE_NOTE][MAX_TAB][MAX_Partiel];
    float dureTabs[NOMBRE_DE_NOTE][3];//0=dureTab en samples // 1=nombreMax de Tab // 2=FreqMoyenne
    float vector_interval[392];

    bool count8bit;
    double vitesseClape;
    int countKInf;
    int countKSup;
    int midiCentVoulue;
    int ancienNoteVoulue;
    int qualite;
    double phaseInf[MAX_Partiel];
    double phaseSup[MAX_Partiel];
    int countP[NOMBRE_DE_NOTE];
    float pitchSchift[NOMBRE_DE_NOTE];
    float anciennewaveInf;
    int eloignementfreq;
    int noteInf;
    int noteSup;
    float ampvoulu;
    float ampvouluz;
    bool isChangementdenote;
    float ampz[MAX_Partiel];
    float amp[MAX_Partiel];

    float ampMax;
    bool is16Bit;
    int noteVoulueAvantSlide;
    float noteEncour;
    int interDepart;
    int ouJeSuis;
    bool boutonveloONS1;
    bool isCrossfade;

		// Pat added ------------------
		std::string name;
		int noteMidiCentMax;
		int noteMin;
		int pourcentClapetOff;
		int noteEncourMax;
		int coeffPicolo;
};


#endif
