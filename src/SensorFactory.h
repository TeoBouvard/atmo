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
  // type Méthode ( liste des paramètres );
  // Mode d'emploi :
  //
  // Contrat :
  //

  //crée une date depuis une string
  //format : 2017-01-01T00:01:20.6090(+)
  date_t make_date(string str);

  vector<Sensor> GetSensors();

  //crée un capteur et l'ajoute à listeCapteurs
  void ParseSensor(string sensor_line);

  //crée une mesure et l'ajoute à son capteur
  void ParseMesure(string mesure_line);

  //retourne le capteur correspondant à l'ID
  Sensor &GetSensorByID(int ID);

  //------------------------------------------------- Surcharge d'opérateurs

  //-------------------------------------------- Constructeurs - destructeur

  SensorFactory(string path_to_file);
  // Mode d'emploi :
  //
  // Contrat :
  //

  virtual ~SensorFactory();
  // Mode d'emploi :
  //
  // Contrat :
  //

  //------------------------------------------------------------------ PRIVE

protected:
  //----------------------------------------------------- Méthodes protégées

  //----------------------------------------------------- Attributs protégés
  vector<Sensor> listeCapteurs;
};

//-------------------------------- Autres définitions dépendantes de <SensorFactory>

#endif // SENSORFACTORY_H
