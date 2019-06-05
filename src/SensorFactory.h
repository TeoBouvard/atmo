/*************************************************************************
                           SensorFactory  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <SensorFactory> (fichier SensorFactory.h) ----------------
#if !defined(SENSORFACTORY_H)
#define SENSORFACTORY_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Sensor.h"
#include "Mesure.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <SensorFactory>
//
//
//------------------------------------------------------------------------

class SensorFactory
{
  //----------------------------------------------------------------- PUBLIC

public:
  //----------------------------------------------------- Méthodes publiques

  //crée une date depuis une string
  //format : 2017-01-01T00:01:20.6090(+)
  static date_t make_date(string str);

  vector<Sensor const*> GetSensors();
  vector<Sensor const*> GetBrokenSensors();

  //crée un capteur et l'ajoute à listeCapteurs
  void ParseSensor(string sensor_line);

  //crée une mesure et l'ajoute à son capteur
  void ParseMesure(string mesure_line);

  //------------------------------------------------- Surcharge d'opérateurs

  //-------------------------------------------- Constructeurs - destructeur

  SensorFactory(ifstream &dataFile);
  // Mode d'emploi :
  //
  // Contrat :
  //
  SensorFactory();
  //------------------------------------------------------------------ PRIVE

protected:
  //----------------------------------------------------- Méthodes protégées

  //----------------------------------------------------- Attributs protégés
  map<int, Sensor> listeCapteurs;
  map<int, Sensor> capteursDefectueux;

  int nbLignesInvalides;
  int nbMesures;
};

//-------------------------------- Autres définitions dépendantes de <SensorFactory>

#endif // SENSORFACTORY_H
