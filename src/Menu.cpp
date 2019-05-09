/*************************************************************************
                           Menu  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Menu> (fichier Menu.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <codecvt>
#include <fstream>

using namespace std;

//------------------------------------------------------ Include personnel
//#include "Menu.h"
#include "SensorFactory.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static void utf16_utf8(string path_to_file){
  ofstream myfile;
  string new_name = "log/data_10sensors_1year_utf8.csv"; //path_to_file - ".csv" + "_utf8" + ".csv";
  myfile.open(new_name);
  ifstream fin("log/data_10sensors_1year.csv", ios::binary);
  fin.seekg(0, ios::end);
  size_t size = (size_t)fin.tellg();

  //skip BOM
  fin.seekg(2, ios::beg);
  size -= 2;

  u16string u16((size / 2) + 1, '\0');
  fin.read((char*)&u16[0], size);

  string utf8 = std::wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
  myfile << utf8;
}
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main(){

  utf16_utf8("log/data_10sensors_1year.csv");
  SensorFactory sensorFactory("log/data_10sensors_1year_utf8.csv");
  vector<Sensor> capteurs = sensorFactory.getSensors();

  cout << "Nombre de capteurs effectifs : " << capteurs.size() << endl;

  return 0;
}

