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
  const Sensor ParseSensor(string sensorLine);
  Mesure &ParseMesure(string mesure_line);

  //------------------------------------------------- Surcharge d'opérateurs
  SensorFactory &operator=(const SensorFactory &unSensorFactory);
  // Mode d'emploi :
  //
  // Contrat :
  //

  //-------------------------------------------- Constructeurs - destructeur
  SensorFactory(const SensorFactory &unSensorFactory);
  // Mode d'emploi (constructeur de copie) :
  //
  // Contrat :
  //

  SensorFactory(string file);
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
