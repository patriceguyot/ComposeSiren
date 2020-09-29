/*
  ==============================================================================

    synth.h
    Created: 7 May 2020 10:56:48am
    Author:  guyot

  ==============================================================================
*/

#pragma once

#include "Sirene.h"



class Synth
{
public:
    Synth();
    ~Synth();

    void chooseOutputFile();
    void record(bool isrecord);
    //id initWithControleur(id Controleurdelegate); // traduire id par auto ?
    void initAudio();
    void clauseAudio();
    void setnote(int sirene, int note);
    void setVelocite(int sirene, int velo);
    void setPan(int sirene, float value);
    void jouerunenotePiano(int note, int, int chanal);
    void changeQualite(int qualt);
    void set16ou8Bit(bool is);
    void setReverbe(bool isreverbe);
    void setStereoHan(float wide);
    //void clauseSynth(NSTimer theTimer);
    void setRoomSizeRev(float value);
    void setwetRev(float value);
    void setdampRev(float value);
    void setwidthRev(float value);
    void setVitesse(int chanal, float vitesse);
    void setisWithSynth(bool iswith);
    void setisWithClic(bool iswith);
    //void jouerclic1();
    //void jouerclic2();
    void setVolumeSynthe(int vol);
    void setVolumeClic(int vol);
    void setMuteShynthe(int Sirene, bool isMute);
    void setisCrossfade(int is);
    void timer512();

    Sirene* s1;
    Sirene* s2;
    Sirene* s3;
    Sirene* s4;
    Sirene* s5;
    Sirene* s6;
    Sirene* s7;



private:

    //float volumeSynth;//1.;
    float PanS1;//0.25;
    float PanS2;//0.75;
    float PanS3;//0.4;
    float PanS4;//0.6;
    float PanS5;//0.1;
    float PanS6;//0.9;
    float PanS7;//0.65;
    //float Volsynthz;
    //AudioComponentDescription cd1;
    //AudioComponentDescription cdmix;
    //AudioComponentDescription cdout;
    //AudioComponentDescription desc;
    //AUNode synthNode,outNode,mixerNode;
    //AUGraph Graph ;
    //AppDelegate  *appDelegate;
    //AudioUnit	gOutputUnit,SynthUnit,MixerUnit;
    float fpourcentreverbe;
    float froomsize;
    float fDamp;
    float fwidth;


    //OSStatus err;
    //NSURL *outputFile;
    //ExtAudioFileRef extAudioFileRef;
    bool isRecordingAudio;
    bool isWithSynthe;//0;
    bool isWithClic;//1;

    //float volumeClic;//1.;
    //int SizeBufClic1 ;// sizeof(clic1);
    //int SizeBufClic2 ;// sizeof(clic2);
    //short *ptrClic1;//(short*)clic1;
    //short *ptrClic2;//(short*)clic2;
    //int countWherWeAreClic1;//0;
    //int countWherWeAreClic2;//0;
    //bool jouerclic1;//0;
    //bool jouerclic2;//0;

    //float VolClicz;
    float WideCoeff;//1.5;
    //bool fOnOffReverbe;//YES; pat : pas besoin

    bool muteS1;//NO;
    //float mIntervalFromAudio; // pat : pas besoin je crois

    //S1 *s1;



};
