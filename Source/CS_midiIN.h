/*
  ==============================================================================

    CS_midiIN.h
    Created: 6 May 2020 10:48:30am
    Author:  guyot

  ==============================================================================
*/

#pragma once


#include <math.h>
#include "synth.h"



#define constescursion 10					// valeur maxi de l'amplitude VFO en % de la vitesse correspondant ‡ une note


class MidiIn
{
public:
  MidiIn();
  ~MidiIn();

  void definiMuteEthernet(bool ismuted, int Ch);
  //id initWithControleur(id Controleurdelegate) ;//remplace par le constructeur
  void handleMIDIMessage2(int Ch, int value1, int value2);

  void RealTimeStartNote(int Ch, int value1, int value2);
  void RealTimeStopNote(int Ch, int note);
  void HandleControlChange(int Ch, int value1, int value2);
  void HandlePitchWheel(int Ch, int value1, int value2);

  float tabledecorresponcanceMidinote(float note, int Ch);

  void sendVolCh(int message, int Ch);
  void sendVariaCh(int Ch);



  void JouerClic(int value);
  void isWithSound(bool is);
  void changingvolumeclic(int VolumeClic);


  void STOffVariateurCh(int Ch);
  void STOnVariateurCh(int Ch);

  void createRampeCh(int Ch);
  void createReleaseCh(int Ch);

  void resetSireneCh(int Ch);

  void incrementeVibrato(int Ch);

  void timerAudio();
  void sirenium_in(unsigned char *buf);

  Synth* mySynth;

private:

  float ChangevolumegeneralCh[17];

  float noteonCh[17] ;
  float velociteCh[17];
  float pitchbendCh[17];
  float ControlCh[127][17];
  float Control1FinalCh[17];
  float noteonfinalCh[17] ;
  float volumefinalCh[17] ;
  float tourmoteurCh[17];
  int LSBCh[17];
  int MSBCh[17];
  float varvfoCh[17];
  float vartremoloCh[17];
  int isEnVeilleCh[17];
  float vitesseCh[17];
  float tremoloCh[17];
  int veloFinal[17];
  float incrementationVibrato;


  bool isWithSoundON;
  int VolumeDuClic;

  float vitesseClapetCh[17];
  int ancienVeloCh[17];

  bool isWithSynth;

  int AncienVolFinalCh[17];
  int isMuteEthernetCh[17];

  int countcreaterelease[17];
  int countcreateattac[17];

  int isAttacVibrato[9];
  int countTimerAudio ;
  int isRampeCh[9];
  int isReleaseCh[9];

  int countvibra;
  int pitch_bend;

  //Synth* mySynth;

};
