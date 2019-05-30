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
#define FILE_ERROR 101

static const char DELIMITER = ';';
static const char DATE_DELIM = '-';
static const char TIME_DELIM = ':';
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques

vector<Sensor> SensorFactory::GetSensors()
{
  vector<Sensor> capteurs;
  for (map<int, Sensor>::iterator it = listeCapteurs.begin(); it != listeCapteurs.end(); ++it)
  {
    capteurs.push_back(it->second);
  }
  return capteurs;
}

vector<Sensor> SensorFactory::GetBrokenSensors()
{
  vector<Sensor> capteurs;
  for (map<int, Sensor>::iterator it = capteursDefectueux.begin(); it != capteursDefectueux.end(); ++it)
  {
    capteurs.push_back(it->second);
  }
  return capteurs;
}

date_t SensorFactory::make_date(string str)
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
  double latitude = stod(latitude_token);

  //parse longitude
  string longitude_token = sensorLine.substr(0, sensorLine.find(DELIMITER));
  sensorLine.erase(0, sensorLine.find(DELIMITER) + 1);
  double longitude = stod(longitude_token);

  //parse descritpion
  string description = sensorLine.substr(0, sensorLine.find(DELIMITER));

  Sensor &&sensor = Sensor(id, latitude, longitude, description);
  listeCapteurs.insert(pair<int, Sensor>(id, sensor));
  capteursDefectueux.insert(pair<int, Sensor>(id, sensor));
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
  double valeur = stod(valeur_token.c_str());

  //ajouter la mesure dans tous les cas pour cohérence calcul similarite
  if (valeur == 0)
  {
    capteursDefectueux.find(id)->second.AjouterMesure(date, polluant, valeur);
  }
  listeCapteurs.find(id)->second.AjouterMesure(date, polluant, valeur);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

SensorFactory::SensorFactory(ifstream &dataFile)
{
  string dataLine;

  const string sensorHeader = "SensorID;Latitude;Longitude;Description;";
  const string mesureHeader = "Timestamp;SensorID;AttributeID;Value;";
  regex sensorLine("^SensorSensor\\d+;.\\d+.\\d+;.\\d+.\\d+;.*;$");
  regex mesureLine("^\\d\\d\\d\\d-\\d\\d-\\d\\dT\\d\\d:\\d\\d:\\d\\d.\\d+;.*;$");

  //read file header
  getline(dataFile, dataLine);
  if (dataLine.find(mesureHeader) != string::npos)
  {
    cerr << "Header invalide" << endl;
    exit(FILE_ERROR);
  }

  cout << "Importation des capteurs ... " << flush;
  while (getline(dataFile, dataLine))
  {
    //parse sensors first
    if (regex_match(dataLine, sensorLine))
    {
      ParseSensor(dataLine);
    }
    //but stop as soon as you encouter mesures header
    else if (dataLine.find(mesureHeader) != string::npos)
    {
      cout << listeCapteurs.size() << " capteurs importés" << endl;
      break;
    }
    else
    {
      cerr << "Ligne de capteur erronnée, merci de vérifier l'intégrité du fichier" << endl;
      cerr << dataLine << endl;
    }
  }

  //then read data_file until end of file
  cout << "Importation des mesures ... " << flush;
  int nbMesures = 0;
  while (getline(dataFile, dataLine))
  {
    if (true) //regex_match(dataLine, mesureLine)) //<- MULTIPLIE PAR 10 LE TEMPS DE CHARGEMENT MAIS PLUS SAFE
    {
      ParseMesure(dataLine);
      nbMesures++;
    }
    else
    {
      cerr << "Ligne de mesure erronnée, merci de vérifier l'intégrité du fichier" << endl;
      cerr << dataLine << endl;
    }
  }
  cout << nbMesures << " mesures importées" << endl;

#ifdef MAP
  cout << "Appel au constructeur de <SensorFactory>" << endl;
#endif
} //----- Fin de SensorFactory

SensorFactory::SensorFactory()
{
#ifdef MAP
  cout << "Appel au constructeur par défaut de <SensorFactory>" << endl;
#endif
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
