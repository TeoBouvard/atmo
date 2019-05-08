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
#define DELIMITER ';'
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type SensorFactory::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

const Sensor SensorFactory::parse_sensor(string sensor_line){
  //parse ID
  string id_token = sensor_line.substr(0, sensor_line.find(DELIMITER));
  sensor_line.erase(0, sensor_line.find(DELIMITER) + 1);
  size_t last_index = id_token.find_first_of("0123456789");
  int id = stoi(id_token.substr(last_index));

  //parse latitude
  string latitude_token = sensor_line.substr(0, sensor_line.find(DELIMITER));
  sensor_line.erase(0, sensor_line.find(DELIMITER) + 1);
  double latitude = strtod(latitude_token.c_str(),NULL);

  //parse longitude
  string longitude_token = sensor_line.substr(0, sensor_line.find(DELIMITER));
  sensor_line.erase(0, sensor_line.find(DELIMITER) + 1);
  double longitude = strtod(longitude_token.c_str(),NULL);

  //parse descritpion
  string description = sensor_line.substr(0, sensor_line.find(DELIMITER));

  return Sensor(id,latitude,longitude,description);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
SensorFactory::SensorFactory(const SensorFactory &unSensorFactory){
  listeCapteurs = unSensorFactory.listeCapteurs;
#ifdef MAP
  cout << "Appel au constructeur de copie de <SensorFactory>" << endl;
#endif
} //----- Fin de SensorFactory (constructeur de copie)

SensorFactory::SensorFactory(string path_to_file){
  ifstream data_file(path_to_file);
  string data_line;

  string sensorHeader("SensorID;Latitude;Longitude;Description;\n");
  regex sensorLine("A FAIRE");
  const string mesureHeader = "Timestamp;SensorID;AttributeID;Value;";
  regex mesureLine("A FAIRE");

  //read file header
  getline(data_file, data_line);
  //assert(data_line == sensorHeader); --> carctères inconnus en début de fichier

  //read sensor data / TODO : while(regex_match(data_line,sensorLine))
  cout << "Importation des capteurs ... ";
  while(data_line != mesureHeader){
    getline(data_file, data_line);
    cout << data_line.length() << endl;
    cout << mesureHeader.length() << endl;

    //cout << mesureHeader.compare(data_line)<<endl;
    parse_sensor(data_line);

    //listeCapteurs.push_back(sensor);
    
    cout << mesureHeader << endl;
  }
  cout << listeCapteurs.size() << "capteur importés" << endl;


  //read mesure data_file until end of file / TODO : while(regex_match)
  while(getline(data_file,data_line)){

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
