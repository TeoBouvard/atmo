/*************************************************************************
                           SensorFactory  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <SensorFactory> (fichier SensorFactory.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

//------------------------------------------------------ Include personnel
#include "SensorFactory.h"
#include "Sensor.h"

//------------------------------------------------------------- Constantes
static const char DELIMITER = ';';
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type SensorFactory::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

const Sensor SensorFactory::ParseSensor(string sensorLine)
{
  //parse ID
  string id_token = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);
  size_t last_index = id_token.find_first_of("0123456789");
  int id = stoi(id_token.substr(last_index));

  //parse latitude
  string latitude_token = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);
  double latitude = strtod(latitude_token.c_str(), NULL);

  //parse longitude
  string longitude_token = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);
  double longitude = strtod(longitude_token.c_str(), NULL);

  //parse descritpion
  string description = sensorLine.substr(0, sensorLine.find(DELIMITER));

  return Sensor(id, latitude, longitude, description);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
SensorFactory::SensorFactory(const SensorFactory &unSensorFactory)
{
  listeCapteurs = unSensorFactory.listeCapteurs;
#ifdef MAP
  cout << "Appel au constructeur de copie de <SensorFactory>" << endl;
#endif
} //----- Fin de SensorFactory (constructeur de copie)

SensorFactory::SensorFactory(string pathToFile)
{
  ifstream dataFile(pathToFile);
  if (dataFile)
  {

    string dataLine;

    string sensorHeader("SensorID;Latitude;Longitude;Description;");
    //regex sensorLine("A FAIRE");

    const string mesureHeader = "Timestamp;SensorID;AttributeID;Value;";
    //regex mesureLine("A FAIRE");

    //read file header
    getline(dataFile, dataLine);

    if (dataLine.find(sensorHeader) == string::npos)
    {
      cerr << "Erreur de header" << endl;
      clog << dataLine << endl;
    }
    else
    {
      cout << "Header valide";
      //read sensor data / TODO : while(regex_match(dataLine,sensorLine))

      cout << "Importation des capteurs ... ";

      while (dataLine.find(mesureHeader) == string::npos)
      {
        getline(dataFile, dataLine);
        //cout << mesureHeader.compare(data_line)<<endl;
        ParseSensor(dataLine);
        //listeCapteurs.push_back(sensor);
      }
      cout << listeCapteurs.size() << "capteur importés" << endl;

      //read mesure data_file until end of file / TODO : while(regex_match)
      while (getline(dataFile, dataLine))
      {
      }
    }
    
  }
  else
  {
    cerr << "Erreur ouverture du fichier " << pathToFile << endl;
  }

#ifdef MAP
  cout << "Appel au constructeur de <SensorFactory>" << endl;
#endif
} //----- Fin de SensorFactory

SensorFactory::~SensorFactory()
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au destructeur de <SensorFactory>" << endl;
#endif
} //----- Fin de ~SensorFactory

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
