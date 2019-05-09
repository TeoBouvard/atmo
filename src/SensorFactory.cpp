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
static const char DELIMITER = ';';
static const char DATE_DELIM = '-';
static const char TIME_DELIM = ':';
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type SensorFactory::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

vector<Sensor> SensorFactory::GetSensors()
{
  return listeCapteurs;
}

Sensor &SensorFactory::GetSensorByID(int ID)
{
  for (Sensor &s : listeCapteurs)
  {
    if (s.GetID() == ID)
      return s;
  }
#ifdef MAP
  cout << "Mesure erronée : aucun capteur associé à l'ID" << ID << endl;
#endif
  exit(0);
}

date_t make_date(string str)
{
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

void SensorFactory::ParseSensor(string sensorLine)
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

  listeCapteurs.emplace_back(id,latitude,longitude,description);
}

void SensorFactory::ParseMesure(string sensorLine)
{
  //parse date
  string date_token = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);
  date_t date = make_date(date_token);

  //parse ID
  string id_token = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);
  size_t last_index = id_token.find_first_of("0123456789");
  int id = stoi(id_token.substr(last_index));

  //parse polluant
  string polluant = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);

  //parse valeur
  string valeur_token = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);
  double valeur = strtod(valeur_token.c_str(), NULL);

  Mesure mesure(date, polluant, valeur);
  Sensor sensor = GetSensorByID(id);
  sensor.AjouterMesure(mesure);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

SensorFactory::SensorFactory(string pathToFile)
{
  ifstream dataFile(pathToFile);
  string dataLine;

  if (dataFile)
  {
    const string sensorHeader = "SensorID;Latitude;Longitude;Description;";
    regex sensorLine("A FAIRE");
    const string mesureHeader = "Timestamp;SensorID;AttributeID;Value;";
    regex mesureLine("\\d\\d\\d\\d-\\d\\d-\\d\\dT\\d\\d:\\d\\d:\\d\\d.\\d+;.*"); //ne marcha

    //read file header
    getline(dataFile, dataLine);

    //read sensor data / TODO : while(regex_match(data_line,sensorLine))
    cout << "Importation des capteurs ... " << flush;
    if(dataLine.find(mesureHeader) != string::npos)
    {
      cout << "Header valide" << endl;
    }

    //read sensor data / TODO : while(regex_match(dataLine,sensorLine))

    cout << "Importation des capteurs ... " << endl;

    while (getline(dataFile, dataLine))
    {
      if (dataLine.find(mesureHeader) != string::npos)
      {
        //cout << mesureHeader.compare(dataLine)<<endl;
        break;
      }
      ParseSensor(dataLine);
    }
    cout << listeCapteurs.size() << " capteur importes" << endl;
    //read mesure data_file until end of file / TODO : while(regex_match)

    //read data_file until end of file / TODO : while(regex_match)
    cout << "Importation des mesures ... " << flush;
    int nbMesures = 0;
    while (getline(dataFile, dataLine))
    {
      if (regex_match(dataLine, mesureLine)) 
      {
        ParseMesure(dataLine);
        nbMesures++;
      }
    }
    cout << nbMesures << " mesures importées" << endl;
  }
  else
  {
    cout << "Erreur ouverture du fichier " << pathToFile << endl;
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
