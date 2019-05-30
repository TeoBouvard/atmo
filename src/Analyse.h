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
#include "Result.h"
//------------------------------------------------------------- Constantes
const date_t DEBUT = SensorFactory::make_date("1970-01-01T00:00:00");
const date_t FIN = SensorFactory::make_date("1970-01-01T00:00:00");
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
    Result valeurIntervalle(SensorFactory &sensorFactory);
    Result computeSimiarity(SensorFactory &sensorFactory, string polluant);
    Result identifyBrokenSensors(SensorFactory &sensorFactory);

    vector<int> CalculIndicesAtmo(vector<double> moyennes);
    bool comparerDebut(date_t date);
    bool comparerFin(date_t date);
    double distanceEuclidienne(vector<double> A, vector<double> B);
    matrice_t &normalizeMatrix(matrice_t &mat);

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    Analyse(double latitude = 0, double longitude = 0, double rayon = 0, date_t debut = DEBUT, date_t fin = FIN);

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
