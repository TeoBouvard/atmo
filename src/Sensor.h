/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if !defined(SENSOR_H)
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <set>
#include "Mesure.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    int GetID() { return sensorID; }
    int GetLatitude() { return latitude; }
    int GetLongitude() { return longitude; }
    set<Mesure>& GetListeMesure() { return listeMesure; }
    void AjouterMesure(Mesure &mesure);

    //------------------------------------------------- Surcharge d'opérateurs
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Sensor();
    // Mode d'emploi :
    //
    // Contrat :
    //

    Sensor(int ID, double sLatitude, double sLongitude, string sDescription);
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    int sensorID;
    double latitude;
    double longitude;
    string description;
    set<Mesure> listeMesure;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // SENSOR_H
