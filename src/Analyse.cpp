/*************************************************************************
                           Analyse  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Analyse> (fichier Analyse.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <math.h>
#include <float.h>
#include <algorithm>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analyse.h"
#include "SensorFactory.h"
#include "Sensor.h"
#include "Mesure.h"
#include "Geo.h"
#include "Result.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Result Analyse::valeurIntervalle(SensorFactory &sensorFactory)
{
    //récupérer les capteurs de la SensorFactory
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();
    vector<Sensor> capteursSurZone;
    vector<double> distancesAuCentre;

    if (rayon > 0)
    {
        //identification des capteurs dans la zone
        for (Sensor s : listeCapteurs)
        {
            double distanceCapteurCentre = Geo::CalculDistance(s.GetLatitude(), s.GetLongitude(), this->latitude, this->longitude);
            if (distanceCapteurCentre < rayon)
            {
                capteursSurZone.push_back(s);
                distancesAuCentre.push_back(distanceCapteurCentre);
            }
        }
    }
    else
    {
        //identification du capteur le plus proche
        double distanceMin = DBL_MAX;
        for (Sensor s : listeCapteurs)
        {
            double distanceCapteurCentre = Geo::CalculDistance(s.GetLatitude(), s.GetLongitude(), this->latitude, this->longitude);
            if (distanceCapteurCentre < distanceMin)
            {
                distanceMin = distanceCapteurCentre;
                capteursSurZone.clear();
                distancesAuCentre.clear();
                capteursSurZone.push_back(s);
                distancesAuCentre.push_back(distanceCapteurCentre);
            }
        }
    }

    if (capteursSurZone.size() == 0)
    {
        return Result();
    }

    else
    {
        double totO3 = 0;
        int nbO3 = 0;
        double totNO2 = 0;
        int nbNO2 = 0;
        double totSO2 = 0;
        int nbSO2 = 0;
        double totPM10 = 0;
        int nbPM10 = 0;

        for (Sensor s : capteursSurZone)
        {
            for (auto mesure : s.GetListeMesure())
            {
                if (comparerDebut(mesure.GetDate()) && comparerFin(mesure.GetDate()))
                {
                    string polluant = mesure.GetPolluant();
                    if (polluant.compare("O3") == 0)
                    {
                        totO3 += mesure.GetValeur();
                        nbO3++;
                    }
                    else if (polluant.compare("NO2") == 0)
                    {
                        totNO2 += mesure.GetValeur();
                        nbNO2++;
                    }
                    else if (polluant.compare("SO2") == 0)
                    {
                        totSO2 += mesure.GetValeur();
                        nbSO2++;
                    }
                    else if (polluant.compare("PM10") == 0)
                    {
                        totPM10 += mesure.GetValeur();
                        nbPM10++;
                    }
                }
            }
        }

        double moyO3 = (totO3 / nbO3);
        double moyNO2 = (totNO2 / nbNO2);
        double moySO2 = (totSO2 / nbSO2);
        double moyPM10 = (totPM10 / nbPM10);

        vector<double> moyennes = {moyO3, moyNO2, moySO2, moyPM10};
        vector<int> indicesAtmo = CalculIndicesAtmo(moyennes);

        int nbMesures = nbNO2 + nbO3 + nbPM10 + nbPM10;

        return Result(capteursSurZone, moyennes, indicesAtmo, nbMesures, distancesAuCentre);
    }
}

Result Analyse::computeSimiarity(SensorFactory &sensorFactory, string polluant)
{
    vector<vector<double>> similarityMatrix;
    vector<double> distances;

    //récupérer les capteurs de la SensorFactory
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();
    vector<double> listeMesureA;
    vector<double> listeMesureB;
    int nbMesures = 0;

    for (Sensor s1 : listeCapteurs)
    {
        for (auto mesure : s1.GetListeMesure())
        {
            if (comparerDebut(mesure.GetDate()) && comparerFin(mesure.GetDate()))
            {
                if (mesure.GetPolluant() == polluant)
                {
                    listeMesureA.push_back(mesure.GetValeur());
                }
            }
        }

        for (Sensor s2 : listeCapteurs)
        {
            for (auto mesure : s2.GetListeMesure())
            {
                if (comparerDebut(mesure.GetDate()) && comparerFin(mesure.GetDate()))
                {
                    if (mesure.GetPolluant() == polluant)
                    {
                        listeMesureB.push_back(mesure.GetValeur());
                        if (s1.GetID() < s2.GetID())
                        {
                            nbMesures++;
                        }
                    }
                }
            }
            distances.push_back(distanceEuclidienne(listeMesureA, listeMesureB));
            listeMesureB.clear();
        }
        similarityMatrix.push_back(distances);

        distances.clear();
        listeMesureA.clear();
    }

    normalizeMatrix(similarityMatrix);
    return Result(listeCapteurs, similarityMatrix, nbMesures / 2);
}

Result Analyse::identifyBrokenSensors(SensorFactory &sensorFactory)
{
    vector<Sensor> sensors = sensorFactory.GetBrokenSensors();
    vector<Sensor> brokenSensors;

    for (Sensor s : sensors)
    {
        if (!s.GetListeMesure().empty())
        {
            brokenSensors.push_back(s);
        }
    }
    return Result(brokenSensors);
}

double Analyse::distanceEuclidienne(vector<double> A, vector<double> B)
{
    double dist = 0.0;

    int nbElements = min(A.size(), B.size());
    for (int i = 0; i < nbElements; i++)
    {
        dist += (A[i] - B[i]) * (A[i] - B[i]);
    }
    return sqrt(dist);
}

matrice_t &Analyse::normalizeMatrix(matrice_t &mat)
{
    double maxElement = 0;
    for (vector<double> line : mat)
    {
        double maxLine = *max_element(line.begin(), line.end());
        if (maxLine > maxElement)
        {
            maxElement = maxLine;
        }
    }

    double norm = 1.0 / maxElement;

    for (int i = 0; i < mat.size(); i++)
    {
        transform(mat[i].begin(), mat[i].end(), mat[i].begin(), [norm](double d) { return 100.0 * (1 - (d * norm)); });
    }

    return mat;
}

bool Analyse::comparerDebut(date_t date)
{
    if (date.year != debut.year)
    {
        return (date.year >= debut.year);
    }
    else if (date.month != debut.month)
    {
        return (date.month >= debut.month);
    }
    else if (date.day != debut.day)
    {
        return (date.day >= debut.day);
    }
    return true;
}

bool Analyse::comparerFin(date_t date)
{
    if (date.year != fin.year)
    {
        return (date.year <= fin.year);
    }
    else if (date.month != fin.month)
    {
        return (date.month <= fin.month);
    }
    else if (date.day != fin.day)
    {
        return (date.day <= fin.day);
    }
    return true;
}

vector<int> Analyse::CalculIndicesAtmo(vector<double> moyennes)
{
    int moyenneO3 = (int)moyennes[0];
    int moyenneNO2 = (int)moyennes[1];
    int moyenneSO2 = (int)moyennes[2];
    int moyennePM10 = (int)moyennes[3];
    int atmoO3, atmoNO2, atmoSO2, atmoPM10, atmoGlobal = 0;

    if (moyenneO3 >= 0 && moyenneO3 <= 29)
    {
        atmoO3 = 1;
    }
    else if (moyenneO3 >= 30 && moyenneO3 <= 54)
    {
        atmoO3 = 2;
    }
    else if (moyenneO3 >= 55 && moyenneO3 <= 79)
    {
        atmoO3 = 3;
    }
    else if (moyenneO3 >= 80 && moyenneO3 <= 104)
    {
        atmoO3 = 4;
    }
    else if (moyenneO3 >= 105 && moyenneO3 <= 129)
    {
        atmoO3 = 5;
    }
    else if (moyenneO3 >= 130 && moyenneO3 <= 149)
    {
        atmoO3 = 6;
    }
    else if (moyenneO3 >= 150 && moyenneO3 <= 179)
    {
        atmoO3 = 7;
    }
    else if (moyenneO3 >= 180 && moyenneO3 <= 209)
    {
        atmoO3 = 8;
    }
    else if (moyenneO3 >= 210 && moyenneO3 <= 239)
    {
        atmoO3 = 9;
    }
    else
    {
        atmoO3 = 10;
    }

    if (moyenneNO2 >= 0 && moyenneNO2 <= 29)
    {
        atmoNO2 = 1;
    }
    else if (moyenneNO2 >= 30 && moyenneNO2 <= 54)
    {
        atmoNO2 = 2;
    }
    else if (moyenneNO2 >= 55 && moyenneNO2 <= 84)
    {
        atmoNO2 = 3;
    }
    else if (moyenneNO2 >= 85 && moyenneNO2 <= 109)
    {
        atmoNO2 = 4;
    }
    else if (moyenneNO2 >= 110 && moyenneNO2 <= 134)
    {
        atmoNO2 = 5;
    }
    else if (moyenneNO2 >= 135 && moyenneNO2 <= 164)
    {
        atmoNO2 = 6;
    }
    else if (moyenneNO2 >= 165 && moyenneNO2 <= 199)
    {
        atmoNO2 = 7;
    }
    else if (moyenneNO2 >= 200 && moyenneNO2 <= 274)
    {
        atmoNO2 = 8;
    }
    else if (moyenneNO2 >= 275 && moyenneNO2 <= 399)
    {
        atmoNO2 = 9;
    }
    else
    {
        atmoNO2 = 10;
    }

    if (moyenneSO2 >= 0 && moyenneSO2 <= 39)
    {
        atmoSO2 = 1;
    }
    else if (moyenneSO2 >= 40 && moyenneSO2 <= 79)
    {
        atmoSO2 = 2;
    }
    else if (moyenneSO2 >= 80 && moyenneSO2 <= 119)
    {
        atmoSO2 = 3;
    }
    else if (moyenneSO2 >= 120 && moyenneSO2 <= 159)
    {
        atmoSO2 = 4;
    }
    else if (moyenneSO2 >= 160 && moyenneSO2 <= 199)
    {
        atmoSO2 = 5;
    }
    else if (moyenneSO2 >= 200 && moyenneSO2 <= 249)
    {
        atmoSO2 = 6;
    }
    else if (moyenneSO2 >= 250 && moyenneSO2 <= 299)
    {
        atmoSO2 = 7;
    }
    else if (moyenneSO2 >= 300 && moyenneSO2 <= 399)
    {
        atmoSO2 = 8;
    }
    else if (moyenneSO2 >= 400 && moyenneSO2 <= 499)
    {
        atmoSO2 = 9;
    }
    else
    {
        atmoSO2 = 10;
    }

    if (moyennePM10 >= 0 && moyennePM10 <= 6)
    {
        atmoPM10 = 1;
    }
    else if (moyennePM10 >= 7 && moyennePM10 <= 13)
    {
        atmoPM10 = 2;
    }
    else if (moyennePM10 >= 14 && moyennePM10 <= 20)
    {
        atmoPM10 = 3;
    }
    else if (moyennePM10 >= 21 && moyennePM10 <= 27)
    {
        atmoPM10 = 4;
    }
    else if (moyennePM10 >= 28 && moyennePM10 <= 34)
    {
        atmoPM10 = 5;
    }
    else if (moyennePM10 >= 35 && moyennePM10 <= 41)
    {
        atmoPM10 = 6;
    }
    else if (moyennePM10 >= 42 && moyennePM10 <= 49)
    {
        atmoPM10 = 7;
    }
    else if (moyennePM10 >= 50 && moyennePM10 <= 64)
    {
        atmoPM10 = 8;
    }
    else if (moyennePM10 >= 65 && moyennePM10 <= 79)
    {
        atmoPM10 = 9;
    }
    else
    {
        atmoPM10 = 10;
    }

    atmoGlobal = max(max(atmoO3, atmoNO2), max(atmoSO2, atmoPM10));

    vector<int> indicesAtmo = {atmoO3, atmoNO2, atmoSO2, atmoPM10, atmoGlobal};
    return indicesAtmo;
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Analyse::Analyse(double latitude, double longitude, double rayon, date_t debut, date_t fin)
{
    this->latitude = latitude;
    this->longitude = longitude;
    this->rayon = rayon;
    this->debut = debut;
    this->fin = fin;

#ifdef MAP
    cout << "Appel au constructeur de <Analyse>" << endl;
#endif
} //----- Fin de Analyse

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
