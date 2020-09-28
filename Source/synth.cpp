/*
  ==============================================================================

    synth.cpp
    Created: 7 May 2020 10:56:27am
    Author:  guyot

  ==============================================================================
*/

#include "synth.h"


#include <iostream>


//static const  char clic1[] =
//#include "clic1Wave_16_stereo_clip.h"
//;

//static const char clic2[] =
//#include "clic2Wave_16_stereo_clip.h"
//;





Synth::Synth(){

    //mIntervalFromAudio=512/44100;
    //ICI TOUT LE TRUC DE OBJECTIVE C
    //fOnOffReverbe=true;
    //PanS1=0.75;
    muteS1=false;
    isWithSynthe=true;
    isWithClic=false;
    //volumeSynth=1.;
    //volumeClic=1.;
    //SizeBufClic1 = sizeof(clic1);
    //SizeBufClic2 = sizeof(clic2);
    //ptrClic1=(short*)clic1;
    //ptrClic2=(short*)clic2;
    //countWherWeAreClic1=0;
    //countWherWeAreClic2=0;
    //jouerclic1=false;
    //jouerclic2=false;
    //Volsynthz = 1.;
    //VolClicz = 1.;
    WideCoeff=1.5;
    s1 = new Sirene("S1");
    s2 = new Sirene("S2");
    s3 = new Sirene("S3");
    s4 = new Sirene("S4");
    s5 = new Sirene("S5");
    s6 = new Sirene("S6");
    s7 = new Sirene("S7");

}

Synth::~Synth(){
    delete (s1);
    delete (s2);
    delete (s3);
    delete (s4);
    delete (s5);
    delete (s6);
    delete (s7);
}


void Synth::setnote(int sireneNumber, int note)
{
    //std::cout<< "Set note. sirene : " << sireneNumber << ", note : " << note << std::endl;
    if(isWithSynthe){
        switch (sireneNumber) {
            case 1:s1->setnoteFromExt(note);break;
            case 2:s2->setnoteFromExt(note);break;
            case 3:s3->setnoteFromExt(note);break;
            case 4:s4->setnoteFromExt(note);break;
            case 5:s5->setnoteFromExt(note);break;
            case 6:s6->setnoteFromExt(note);break;
            case 7:s7->setnoteFromExt(note);break;
            case 8: break;
            default:
                break;
        }
    }

}

void Synth::setVelocite(int sireneNumber, int velo){
    if(isWithSynthe){
        switch (sireneNumber) {
            case 1:s1->setVelocite(velo);break;
            case 2:s2->setVelocite(velo);break;
            case 3:s3->setVelocite(velo);break;
            case 4:s4->setVelocite(velo);break;
            case 5:s5->setVelocite(velo);break;
            case 6:s6->setVelocite(velo);break;
            case 7:s7->setVelocite(velo);break;
            case 8: break;
            default:
                break;
        }
    }
}

/*
void Synth::setPan(int sireneNumber, float value){
    if(isWithSynthe){
        switch (sireneNumber) {
            case 1:PanS1=value;  break;
            default:
                break;
        }
    }
}
*/

void Synth::changeQualite(int qualt){
    if(isWithSynthe){
        s1->changeQualite(qualt);
        s2->changeQualite(qualt);
        s3->changeQualite(qualt);
        s4->changeQualite(qualt);
        s5->changeQualite(qualt);
        s6->changeQualite(qualt);
        s7->changeQualite(qualt);

    }
}


void Synth::setVitesse(int chanal, float vitesse){
    //std::cout<< "Set Vitesse. chanal : " << chanal << ", vitesse : " << vitesse << std::endl;
    if(isWithSynthe){
        int midicent=0;
        switch (chanal) {
            case 1:
                midicent=(int)roundf((69+12.*log2f((vitesse/5.)/440.0))*100.);
                if (midicent<0) midicent=0;
                setnote(1, midicent);
                break;
            case 2:
                midicent=(int)roundf((69+12.*log2f((vitesse/5.)/440.0))*100.);
                if (midicent<0) midicent=0;
                setnote(2, midicent);
                break;
            case 3:
                midicent=(int)roundf((69+12.*log2f((vitesse/7.5)/440.0))*100.);
                if (midicent<0) midicent=0;
                setnote(3, midicent);
                break;
            case 4:
                midicent=(int)roundf((69+12.*log2f((vitesse/(20./3.))/440.0))*100.);
                if (midicent<0) midicent=0;
                setnote(4, midicent);
                break;
            case 5:
                midicent=(int)roundf((69+12.*log2f((vitesse/7.5)/440.0))*100.);
                if (midicent<0) midicent=0;
                setnote(5, midicent);
                break;
            case 6:
                midicent=(int)roundf((69+12.*log2f((vitesse/7.5)/440.0))*100.);
                if (midicent<0) midicent=0;
                setnote(6, midicent);
                break;
            case 7:
                midicent=(int)roundf((69+12.*log2f((vitesse/7.5)/440.0))*100.);
                if (midicent<0) midicent=0;
                setnote(7, midicent);
                break;


            default:
                break;
        }
    }
}
