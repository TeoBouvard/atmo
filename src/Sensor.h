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
#include <vector>
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

    int GetID() const { return sensorID; }
    int GetLatitude() const { return latitude; }
    int GetLongitude() const { return longitude; }
    vector<Mesure> const& GetListeMesure() const { return listeMesure; }
    void AjouterMesure(date_t date, string polluant, double valeur);

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    Sensor(int ID, double sLatitude, double sLongitude, string sDescription);

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    int sensorID;
    double latitude;
    double longitude;
    string description;
    vector<Mesure> listeMesure;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // SENSOR_H
