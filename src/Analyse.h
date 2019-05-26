/*************************************************************************
                           Analyse  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Analyse> (fichier Analyse.h) ----------------
#if !defined(ANALYSE_H)
#define ANALYSE_H

//--------------------------------------------------- Interfaces utilisées
#include <vector>

#include "Mesure.h"
#include "SensorFactory.h"
#include "Sensor.h"
#include "Geo.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Analyse>
//
//
//------------------------------------------------------------------------

class Analyse
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    void ValeurIntervalle(SensorFactory &sensorFactory);

    void CapteursSimilaires(SensorFactory &sensorFactory);

    void CalculValeurAtmo(double O3, double NO2, double SO2, double PM10);

    bool comparerDebut(date_t date);
    bool comparerFin(date_t date);

    vector<vector<double>> computeSimiarity(SensorFactory &sensorFactory, string polluant);
    double distanceEuclidienne(vector<double> A, vector<double> B);
    vector<double> &normalizeVector(vector<double> &vec);

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    Analyse(double latitude, double longitude, double rayon, date_t debut, date_t fin);
    // Mode d'emploi :
    //
    // Contrat :
    //
    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    double latitude;
    double longitude;
    double rayon;
    date_t debut;
    date_t fin;
};

//-------------------------------- Autres définitions dépendantes de <Analyse>

#endif // ANALYSE_H
