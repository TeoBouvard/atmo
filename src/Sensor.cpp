/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Sensor.h"
#include "Mesure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Sensor::AjouterMesure(date_t date, string polluant, double valeur)
{
    listeMesure.emplace_back(date, polluant, valeur);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Sensor::Sensor(int sID, double sLatitude, double sLongitude, string sDescription)
{
    sensorID = sID;
    latitude = sLatitude;
    longitude = sLongitude;
    description = sDescription;
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
} //----- Fin de Sensor

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
