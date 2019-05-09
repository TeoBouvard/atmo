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
#include "Mesure.h"
//------------------------------------------------------------- Constantes
#define DELIMITER ';'
#define DATE_DELIM '-'
#define TIME_DELIM ':'
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type SensorFactory::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

vector<Sensor> SensorFactory::getSensors(){
  return listeCapteurs;
}

Sensor& SensorFactory::getSensorByID(int ID){
  for(Sensor& s : listeCapteurs){
    if(s.getID() == ID)
      return s;
  }
  #ifdef MAP
  cout << "Mesure erronée : aucun capteur associé à l'ID" << ID <<  endl;
  #endif
  exit(0);
}

date_t make_date(string str){
  date_t date;

  string year_token = str.substr(0, str.find(DATE_DELIM));
  str.erase(0, str.find(DATE_DELIM) + 1);

  string month_token = str.substr(0, str.find(DATE_DELIM));
  str.erase(0, str.find(DATE_DELIM) + 1);

  string day_token = str.substr(0, str.find('T'));
  str.erase(0, str.find('T') + 1);

  string hour_token = str.substr(0, str.find(TIME_DELIM));
  str.erase(0, str.find(TIME_DELIM) + 1);

  string minute_token = str.substr(0, str.find(TIME_DELIM));
  str.erase(0, str.find(TIME_DELIM) + 1);

  string second_token = str.substr(0, str.find('.'));

  date.year = stoi(year_token);
  date.month = stoi(month_token);
  date.day = stoi(day_token);
  date.hour = stoi(hour_token);
  date.minute = stoi(minute_token);
  date.second = stoi(second_token);
  
  return date;
}

void SensorFactory::parse_sensor(string sensor_line){
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

  Sensor sensor(id,latitude,longitude,description);
  listeCapteurs.push_back(sensor);
}

void SensorFactory::parse_mesure(string sensor_line){
  //parse date
  string date_token = sensor_line.substr(0, sensor_line.find(DELIMITER));
  sensor_line.erase(0, sensor_line.find(DELIMITER) + 1);
  date_t date = make_date(date_token);

  //parse ID
  string id_token = sensor_line.substr(0, sensor_line.find(DELIMITER));
  sensor_line.erase(0, sensor_line.find(DELIMITER) + 1);
  size_t last_index = id_token.find_first_of("0123456789");
  int id = stoi(id_token.substr(last_index));

  //parse polluant
  string polluant = sensor_line.substr(0, sensor_line.find(DELIMITER));
  sensor_line.erase(0, sensor_line.find(DELIMITER) + 1);

  //parse valeur
  string valeur_token = sensor_line.substr(0, sensor_line.find(DELIMITER));
  sensor_line.erase(0, sensor_line.find(DELIMITER) + 1);
  double valeur = strtod(valeur_token.c_str(),NULL);

  Mesure mesure(date,polluant,valeur);
  Sensor sensor = getSensorByID(id);
  sensor.ajouterMesure(mesure);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

SensorFactory::SensorFactory(string path_to_file){
  ifstream data_file(path_to_file);
  string data_line;

  const string sensorHeader = "SensorID;Latitude;Longitude;Description;\r";
  regex sensorLine("A FAIRE");
  const string mesureHeader = "Timestamp;SensorID;AttributeID;Value;\r";
  regex mesureLine("\\d\\d\\d\\d-\\d\\d-\\d\\dT\\d\\d:\\d\\d:\\d\\d.\\d+;.*\\r");

  //read file header
  getline(data_file, data_line);
  assert(data_line == sensorHeader);

  //read sensor data / TODO : while(regex_match(data_line,sensorLine))
  cout << "Importation des capteurs ... " << flush;
  while(getline(data_file, data_line)){
    if(data_line != mesureHeader)
      parse_sensor(data_line); 
    else
      break;
  }
  cout << listeCapteurs.size() << " capteurs importés" << endl;

  //read data_file until end of file / TODO : while(regex_match)
  cout << "Importation des mesures ... " << flush;
  int nbMesures = 0;
  while(getline(data_file,data_line)){
    if(regex_match(data_line,mesureLine)){
      parse_mesure(data_line);
      nbMesures++;
    } 
  }
  cout << nbMesures << " mesures importées" << endl;
  
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
