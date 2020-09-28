/*
  ==============================================================================

    Sirene.cpp
    Created: 6 May 2020 10:49:23am
    Author:  guyot

  ==============================================================================
*/

#include "Sirene.h"
#include <iostream>

// see precision
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/string.hpp>


/*
#define MAX_Partiel 200
#define NOMBRE_DE_NOTE 80
#define MAX_TAB 1000
#define pourcentClapetOff 7


float tabAmp[NOMBRE_DE_NOTE][MAX_TAB][MAX_Partiel];
float tabFreq[NOMBRE_DE_NOTE][MAX_TAB][MAX_Partiel];
float dureTabs[NOMBRE_DE_NOTE][3];//0=dureTab en samples // 1=nombreMax de Tab // 2=FreqMoyenne
float vector_interval[392];
*/


enum {
	Montant			=0,
	Descandant		=1,
	TonUpBefore		=2,
	DemiUpBefore	=3,
	QuartUpBefore	=4,
	Boucle			=5,
	QuartDownAfter	=6,
	QuartDownBefore	=7,
	QuartUpAfter	=8,
	jesuisrest		=9,
};

//Timer myTimer;



Sirene::Sirene(const std::string& str): name(str)
{



    std::cout << "Lancement de la sirene " << name << "\n";


    //std::string dataFilePath = "/media/guyot/Data/_projets/mecanique_vivante/dataFiles_binary/";
    //std::string dataFilePath = "/Users/guyot/Documents/_projets/mecanique_vivante/dataFiles_binary/";
    //std::string dataFilePath = "BinaryData::";
    std::string dataFilePath = juce::File::getSpecialLocation (juce::File::currentApplicationFile).getChildFile ("Contents/Resources/").getFullPathName().toStdString() + '/';

		std::string sireneNameForData;
		if (name=="S2")
			sireneNameForData="S1"; // s2 has the same data files than s1
		else if (name=="S6")
			sireneNameForData="S5"; // s6 has the same data files than s5
		else
			sireneNameForData=name;
		readDataFromBinaryFile(dataFilePath, "dataAmp" + sireneNameForData, "dataFreq" + sireneNameForData, "datadureTabs" + sireneNameForData, "dataVectorInterval" + sireneNameForData);

	  std::cout << "tabFreq[46][20][3] : " << std::fixed << std::setprecision(7) <<tabFreq[46][20][3] << std::endl;


    if (name=="S1") {noteMidiCentMax=7200; pourcentClapetOff=7; noteMin=24; coeffPicolo=1.;}
    else if (name=="S2") {noteMidiCentMax=7200; pourcentClapetOff=7; noteMin=24; coeffPicolo=1.;}
    else if (name=="S3") {noteMidiCentMax=6400; pourcentClapetOff=7; noteMin=24; coeffPicolo=1.;}
    else if (name=="S4") {noteMidiCentMax=6500; pourcentClapetOff=15; noteMin=24; coeffPicolo=1.;}
    else if (name=="S5") {noteMidiCentMax=7900; pourcentClapetOff=7; noteMin=36; coeffPicolo=1.;}
    else if (name=="S6") {noteMidiCentMax=7900; pourcentClapetOff=7; noteMin=36; coeffPicolo=1.;}
    else if (name=="S7") {noteMidiCentMax=7900; pourcentClapetOff=7; noteMin=36; coeffPicolo=2.;}

	  vitesseClape=0.0002;
    countKInf=0;
    countKSup=0;
    midiCentVoulue=0;
    ancienNoteVoulue=0;
    qualite=30;
		//qualite = 10;

		anciennewaveInf=0.;
    eloignementfreq=0;
    noteInf=0;
    noteSup=0;
    ampvoulu=1.;
    ampvouluz=1.;
    isChangementdenote=false;

    ampMax=1.;
    is16Bit=false;
    count8bit=true;

    //pat
    /*
    interDepart=0;
    boutonveloONS1=false;
    isCrossfade=false;
    noteVoulueAvantSlide=0;
    noteEncour=0;
    ouJeSuis=0;
    */


}
Sirene::~Sirene(){

}

void Sirene::readDataFromBinaryFile(std::string dataFilePath, std::string tabAmpFile, std::string tabFreqFile, std::string dureTabFile, std::string vectorIntervalFile){

	std::ifstream myfile;

	// Read tabAmpFile
    myfile.open(dataFilePath + tabAmpFile, std::ios::binary);
    if (myfile.is_open())
    {
        myfile.read(reinterpret_cast<char *>(tabAmp), sizeof tabAmp); // todo: check that input.gcount() is the number of bytes expected
        myfile.close();
    }
    else std::cout <<  "Error. Binary file not found: " <<  dataFilePath + tabAmpFile << "\n";

	// Read dataFreqFile
    myfile.open(dataFilePath + tabFreqFile, std::ios::binary);
    if (myfile.is_open())
    {
        myfile.read(reinterpret_cast<char *>(tabFreq), sizeof tabFreq); // todo: check that input.gcount() is the number of bytes expected
        myfile.close();
    }
    else std::cout <<  "Error. Binary file not found.\n";

	// Read dureTabFile
    myfile.open(dataFilePath + dureTabFile, std::ios::binary);
    if (myfile.is_open())
    {
        myfile.read(reinterpret_cast<char *>(dureTabs), sizeof dureTabs); // todo: check that input.gcount() is the number of bytes expected
        myfile.close();
    }
    else std::cout <<  "Error. Binary file not found.\n";

	// Read vectorIntervalFile
    myfile.open(dataFilePath + vectorIntervalFile, std::ios::binary);
    if (myfile.is_open())
    {
        myfile.read(reinterpret_cast<char *>(vector_interval), sizeof vector_interval); // todo: check that input.gcount() is the number of bytes expected
        myfile.close();
    }
    else std::cout <<  "Error. Binary file not found.\n";
}



void Sirene::setMidicent(int note){
    midiCentVoulue=note;
    if (midiCentVoulue>=noteMidiCentMax) midiCentVoulue=noteMidiCentMax;
    else if (midiCentVoulue%100==99) midiCentVoulue++;
    noteInf=midiCentVoulue/100;
    //NSLog(@"midiCentVoulue %i",midiCentVoulue);
    noteSup=noteInf+1 ;
    pitchSchift[noteInf]=((440.0 * pow(2., ((midiCentVoulue/100.) - 69.) / 12.))  /  (440.0 * pow(2., ((noteInf) - 69.) / 12.)))  * DeuxPieSampleRate;
    pitchSchift[noteSup]=((440.0 * pow(2., ((midiCentVoulue/100.) - 69.) / 12.))  /   (440.0 * pow(2., ((noteSup) - 69.) / 12.)))  * DeuxPieSampleRate;
	//std::cout << "noteInf:" << noteInf << std::endl;
}

void Sirene::setnoteFromExt(int note)
{
	//std::cout << "Note from ext: " << note << std::endl;
    noteVoulueAvantSlide=note;
    if (noteVoulueAvantSlide > noteMidiCentMax) noteVoulueAvantSlide=noteMidiCentMax;
    interDepart=(int)noteVoulueAvantSlide-noteEncour;
    if (noteEncour > noteVoulueAvantSlide)noteEncour=noteEncour-1;
    else if (noteEncour < noteVoulueAvantSlide)noteEncour=noteEncour+1;
}
void Sirene::setnote(){
	//std::cout << "Sirene::setnote()" << std::endl;
    oujesuis();
    int note=(int)((noteEncour-50)/100.);
    if (note <= noteMin) note=noteMin;
    if (ouJeSuis==Montant) {
        noteEncour=noteEncour+(100./(vector_interval[note-noteMin+294]*coeffPicolo));
        if(noteEncour > noteVoulueAvantSlide)noteEncour=noteVoulueAvantSlide;

    }
    else if(ouJeSuis==Descandant) {
        noteEncour=noteEncour-(100./(vector_interval[391-(note-noteMin)]*coeffPicolo));
        if(noteEncour < noteVoulueAvantSlide)noteEncour=noteVoulueAvantSlide;

    }
    else if(ouJeSuis==TonUpBefore) {
        noteEncour=noteEncour+(100./(vector_interval[((note-noteMin+2)*6)+1]*coeffPicolo));
    }
    else if(ouJeSuis==DemiUpBefore) {
        noteEncour=noteEncour+(100./(vector_interval[((note-noteMin+1)*6)+2]*coeffPicolo));
    }
    else if(ouJeSuis==QuartUpBefore) {
        noteEncour=noteEncour+(100./(vector_interval[((note-noteMin)*6)+3]*coeffPicolo));
        if(noteEncour > noteVoulueAvantSlide)noteEncour=noteVoulueAvantSlide;
    }
    else if(ouJeSuis==Boucle) {
    }
    else if(ouJeSuis==QuartDownAfter) {
        noteEncour=noteEncour-(100./(vector_interval[((note-noteMin)*6)+4]*coeffPicolo));
        if(noteEncour < noteVoulueAvantSlide)noteEncour=noteVoulueAvantSlide;

    }
    else if(ouJeSuis==QuartDownBefore) {
        noteEncour=noteEncour-(100./(vector_interval[((note-noteMin)*6)]*coeffPicolo));
        if(noteEncour < noteVoulueAvantSlide)noteEncour=noteVoulueAvantSlide;
    }
    else if(ouJeSuis==QuartUpAfter) {
        noteEncour=noteEncour+(100./(vector_interval[((note-noteMin)*6)+5]*coeffPicolo));
        if(noteEncour > noteVoulueAvantSlide)noteEncour=noteVoulueAvantSlide;

    }

    setMidicent(noteEncour);
}
void Sirene::oujesuis(){
    int inter=(int)noteVoulueAvantSlide-noteEncour;
    if (inter==0) ouJeSuis=Boucle;
    else if ((inter-interDepart) >0 && (inter-interDepart) < 50)ouJeSuis=QuartDownAfter;
    else if ((inter-interDepart) <0 && (inter-interDepart) > -50)ouJeSuis=QuartUpAfter;
    else if (inter >= -50 && inter < 0) ouJeSuis=QuartDownBefore;
    else if (inter > 250 && (inter-interDepart) <=-50 ) ouJeSuis=Montant;
    else if (inter < -50  && (inter-interDepart) >=50) ouJeSuis=Descandant;
    else if (inter >= 150 && inter < 250  ) ouJeSuis=TonUpBefore;
    else if (inter >= 50 && inter < 150 ) ouJeSuis=DemiUpBefore;
    else if (inter > 0 && inter < 50) ouJeSuis=QuartUpBefore;
    /* benoit
	switch (ouJeSuis) {
        case QuartDownBefore: printf("QuartDownBefore\n"); break;
            case QuartDownAfter: printf("QuartDownAfter\n"); break;
            case QuartUpAfter: printf("QuartUpAfter\n"); break;
            case Montant: printf("Montant\n"); break;
            case Descandant: printf("Descandant\n"); break;
            case TonUpBefore: printf("TonUpBefore\n"); break;
            case DemiUpBefore: printf("DemiUpBefore\n"); break;
            case QuartUpBefore: printf("QuartUpBefore\n"); break;

        default:
            break;
    }*/

}
void Sirene::changeQualite(int qualt){
    qualite =qualt;
}
void Sirene::set16ou8Bit(bool is){
    is16Bit=!is;
}
void Sirene::setVelocite(int velo){
   // printf("velo:%i\n",velo);
    ampMax=velo/500.;
    ampvoulu=(velo/500.)/(100./(100-pourcentClapetOff))+(pourcentClapetOff/100.);

}
void Sirene::setisCrossFade(int is){
    if(is==0)isCrossfade=false;
    else isCrossfade=true;
}
