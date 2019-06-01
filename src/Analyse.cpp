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

    if (rayon > 0)
    {
        for (Sensor s : listeCapteurs)
        {
            //si le capteur et dans la zone choisie
            if (Geo::CalculDistance(s.GetLatitude(), s.GetLongitude(), this->latitude, this->longitude) < rayon)
            {
                capteursSurZone.push_back(s);
            }
        }
    }
    else
    {
        double distanceMin = DBL_MAX;
        for (Sensor s : listeCapteurs)
        {
            double distanceS = Geo::CalculDistance(s.GetLatitude(), s.GetLongitude(), this->latitude, this->longitude);
            if (distanceS < distanceMin)
            {
                distanceMin = distanceS;
                capteursSurZone.clear();
                capteursSurZone.push_back(s);
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
                    string type = mesure.GetPolluant();
                    if (type.compare("O3") == 0)
                    {
                        totO3 += mesure.GetValeur();
                        nbO3++;
                    }
                    else if (type.compare("NO2") == 0)
                    {
                        totNO2 += mesure.GetValeur();
                        nbNO2++;
                    }
                    else if (type.compare("SO2") == 0)
                    {
                        totSO2 += mesure.GetValeur();
                        nbSO2++;
                    }
                    else if (type.compare("PM10") == 0)
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

        return Result(capteursSurZone, moyennes, indicesAtmo, nbMesures);
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
                        nbMesures++;
                        listeMesureB.push_back(mesure.GetValeur());
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
    return Result(listeCapteurs, similarityMatrix, nbMesures);
}


Result Analyse::identifyBrokenSensors(SensorFactory &sensorFactory)
{
    vector<Sensor> brokenSensorsTmp = sensorFactory.GetBrokenSensors();
    vector<Sensor> brokenSensors;

    for(Sensor s : brokenSensorsTmp)
    {
        if(!s.GetListeMesure().empty()){
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
    int atmoO3, atmoNO2, atmoSO2, atmoPM10, atmoGlobal = 0;
	if ((int)moyennes.at(0) >= 0 && (int)moyennes.at(0) <= 29)
	{
		atmoO3 = 1;
	}
	else if ((int)moyennes.at(0) >= 30 && (int)moyennes.at(0) <= 54)
	{
		atmoO3 = 2;
	}
	else if ((int)moyennes.at(0) >= 55 && (int)moyennes.at(0) <= 79)
	{
		atmoO3 = 3;
	}
	else if ((int)moyennes.at(0) >= 80 && (int)moyennes.at(0) <= 104)
	{
		atmoO3 = 4;
	}
	else if ((int)moyennes.at(0) >= 105 && (int)moyennes.at(0) <= 129)
	{
		atmoO3 = 5;
	}
	else if ((int)moyennes.at(0) >= 130 && (int)moyennes.at(0) <= 149)
	{
		atmoO3 = 6;
	}
	else if ((int)moyennes.at(0) >= 150 && (int)moyennes.at(0) <= 179)
	{
		atmoO3 = 7;
	}
	else if ((int)moyennes.at(0) >= 180 && (int)moyennes.at(0) <= 209)
	{
		atmoO3 = 8;
	}
	else if ((int)moyennes.at(0) >= 210 && (int)moyennes.at(0) <= 239)
	{
		atmoO3 = 9;
	}
	else
	{
		atmoO3 = 10;
	}

	if ((int)moyennes.at(1) >= 0 && (int)moyennes.at(1) <= 29)
	{
		atmoNO2 = 1;
	}
	else if ((int)moyennes.at(1) >= 30 && (int)moyennes.at(1) <= 54)
	{
		atmoNO2 = 2;
	}
	else if ((int)moyennes.at(1) >= 55 && (int)moyennes.at(1) <= 84)
	{
		atmoNO2 = 3;
	}
	else if ((int)moyennes.at(1) >= 85 && (int)moyennes.at(1) <= 109)
	{
		atmoNO2 = 4;
	}
	else if ((int)moyennes.at(1) >= 110 && (int)moyennes.at(1) <= 134)
	{
		atmoNO2 = 5;
	}
	else if ((int)moyennes.at(1) >= 135 && (int)moyennes.at(1) <= 164)
	{
		atmoNO2 = 6;
	}
	else if ((int)moyennes.at(1) >= 165 && (int)moyennes.at(1) <= 199)
	{
		atmoNO2 = 7;
	}
	else if ((int)moyennes.at(1) >= 200 && (int)moyennes.at(1) <= 274)
	{
		atmoNO2 = 8;
	}
	else if ((int)moyennes.at(1) >= 275 && (int)moyennes.at(1) <= 399)
	{
		atmoNO2 = 9;
	}
	else
	{
		atmoNO2 = 10;
	}

	if ((int)moyennes.at(2) >= 0 && (int)moyennes.at(2) <= 39)
	{
		atmoSO2 = 1;
	}
	else if ((int)moyennes.at(2) >= 40 && (int)moyennes.at(2) <= 79)
	{
		atmoSO2 = 2;
	}
	else if ((int)moyennes.at(2) >= 80 && (int)moyennes.at(2) <= 119)
	{
		atmoSO2 = 3;
	}
	else if ((int)moyennes.at(2) >= 120 && (int)moyennes.at(2) <= 159)
	{
		atmoSO2 = 4;
	}
	else if ((int)moyennes.at(2) >= 160 && (int)moyennes.at(2) <= 199)
	{
		atmoSO2 = 5;
	}
	else if ((int)moyennes.at(2) >= 200 && (int)moyennes.at(2) <= 249)
	{
		atmoSO2 = 6;
	}
	else if ((int)moyennes.at(2) >= 250 && (int)moyennes.at(2) <= 299)
	{
		atmoSO2 = 7;
	}
	else if ((int)moyennes.at(2) >= 300 && (int)moyennes.at(2) <= 399)
	{
		atmoSO2 = 8;
	}
	else if ((int)moyennes.at(2) >= 400 && (int)moyennes.at(2) <= 499)
	{
		atmoSO2 = 9;
	}
	else
	{
		atmoSO2 = 10;
	}

	
	if ((int)moyennes.at(3) >= 0 && (int)moyennes.at(3) <= 6)
	{
		atmoPM10 = 1;
	}
	else if ((int)moyennes.at(3) >= 7 && (int)moyennes.at(3) <= 13)
	{
		atmoPM10 = 2;
	}
	else if ((int)moyennes.at(3) >= 14 && (int)moyennes.at(3) <= 20)
	{
		atmoPM10 = 3;
	}
	else if ((int)moyennes.at(3) >= 21 && (int)moyennes.at(3) <= 27)
	{
		atmoPM10 = 4;
	}
	else if ((int)moyennes.at(3) >= 28 && (int)moyennes.at(3) <= 34)
	{
		atmoPM10 = 5;
	}
	else if ((int)moyennes.at(3) >= 35 && (int)moyennes.at(3) <= 41)
	{
		atmoPM10 = 6;
	}
	else if ((int)moyennes.at(3) >= 42 && (int)moyennes.at(3) <= 49)
	{
		atmoPM10 = 7;
	}
	else if ((int)moyennes.at(3) >= 50 && (int)moyennes.at(3) <= 64)
	{
		atmoPM10 = 8;
	}
	else if ((int)moyennes.at(3) >= 65 && (int)moyennes.at(3) <= 79)
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
