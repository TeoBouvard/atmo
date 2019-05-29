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
#include <vector>
#include <string>
#include <math.h>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analyse.h"
#include "SensorFactory.h"
#include "Sensor.h"
#include "Geo.h"
#include "Result.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Result Analyse::ValeurIntervalle(SensorFactory &sensorFactory)
{
    //récupérer les capteurs de la SensorFactory
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();
    vector<Sensor> capteursSurZone;

    double totO3 = 0;
    int nbO3 = 0;
    double totNO2 = 0;
    int nbNO2 = 0;
    double totSO2 = 0;
    int nbSO2 = 0;
    double totPM10 = 0;
    int nbPM10 = 0;

    for (Sensor s : listeCapteurs)
    {
        //si le capteur et dans la zone choisie
        if (Geo::CalculDistance(s.GetLatitude(), s.GetLongitude(), this->latitude, this->longitude) < rayon)
        {
            capteursSurZone.push_back(s);
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
    }
    if (capteursSurZone.size() == 0)
    {
        return Result();
    }

    else
    {
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
    switch ((int)moyennes.at(0))
    {
    case 0 ... 29:
        atmoO3 = 1;
        break;
    case 30 ... 54:
        atmoO3 = 2;
        break;
    case 55 ... 79:
        atmoO3 = 3;
        break;
    case 80 ... 104:
        atmoO3 = 4;
        break;
    case 105 ... 129:
        atmoO3 = 5;
        break;
    case 130 ... 149:
        atmoO3 = 6;
        break;
    case 150 ... 179:
        atmoO3 = 7;
        break;
    case 180 ... 209:
        atmoO3 = 8;
        break;
    case 210 ... 239:
        atmoO3 = 9;
        break;
    default:
        atmoO3 = 10;
        break;
    }

    switch ((int)moyennes.at(1))
    {
    case 0 ... 29:
        atmoNO2 = 1;
        break;
    case 30 ... 54:
        atmoNO2 = 2;
        break;
    case 55 ... 84:
        atmoNO2 = 3;
        break;
    case 85 ... 109:
        atmoNO2 = 4;
        break;
    case 110 ... 134:
        atmoNO2 = 5;
        break;
    case 135 ... 164:
        atmoNO2 = 6;
        break;
    case 165 ... 199:
        atmoNO2 = 7;
        break;
    case 200 ... 274:
        atmoNO2 = 8;
        break;
    case 275 ... 399:
        atmoNO2 = 9;
        break;
    default:
        atmoNO2 = 10;
        break;
    }

    switch ((int)moyennes.at(2))
    {
    case 0 ... 39:
        atmoSO2 = 1;
        break;
    case 40 ... 79:
        atmoSO2 = 2;
        break;
    case 80 ... 119:
        atmoSO2 = 3;
        break;
    case 120 ... 159:
        atmoSO2 = 4;
        break;
    case 160 ... 199:
        atmoSO2 = 5;
        break;
    case 200 ... 249:
        atmoSO2 = 6;
        break;
    case 250 ... 299:
        atmoSO2 = 7;
        break;
    case 300 ... 399:
        atmoSO2 = 8;
        break;
    case 400 ... 499:
        atmoSO2 = 9;
        break;
    default:
        atmoSO2 = 10;
        break;
    }

    switch ((int)moyennes.at(3))
    {
    case 0 ... 6:
        atmoPM10 = 1;
        break;
    case 7 ... 13:
        atmoPM10 = 2;
        break;
    case 14 ... 20:
        atmoPM10 = 3;
        break;
    case 21 ... 27:
        atmoPM10 = 4;
        break;
    case 28 ... 34:
        atmoPM10 = 5;
        break;
    case 35 ... 41:
        atmoPM10 = 6;
        break;
    case 42 ... 49:
        atmoPM10 = 7;
        break;
    case 50 ... 64:
        atmoPM10 = 8;
        break;
    case 65 ... 79:
        atmoPM10 = 9;
        break;
    default:
        atmoPM10 = 10;
        break;
    }

    atmoGlobal = max(max(atmoO3, atmoNO2), max(atmoSO2, atmoPM10));

    vector<int> indicesAtmo = {atmoO3, atmoNO2, atmoSO2, atmoPM10, atmoGlobal};
    return indicesAtmo;
}

/*void Analyse::CapteursSimilaires(SensorFactory &sensorFactory)
{
    vector<string> polluants;
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();

    double **matriceCapteurs = new double *[listeCapteurs.size()];
    for (unsigned int i = 0; i < listeCapteurs.size(); i++)
    {
        matriceCapteurs[i] = new double[listeCapteurs.size()];
    }

    double similitudeMesure = 0;
    int compteur = 0;
    int nbmesure = 0;

    for (unsigned int i = 0; i < listeCapteurs.size(); i++)
    {
        for (unsigned int j = i + 1; j < listeCapteurs.size(); j++)
        {
            set<Mesure> listeMesure = listeCapteurs[j].GetListeMesure();
            auto it = listeMesure.begin();
            for (Mesure mesure : listeCapteurs[i].GetListeMesure())
            {
                if ((this->debut < mesure.GetDate()) && (mesure.GetDate() < this->fin))
                {
                    ++it;
                    similitudeMesure += 1 - (mesure.GetValeur() - it->GetValeur() / mesure.GetValeur());
                    compteur++;
                    break;
                }
                nbmesure++;
            }
            matriceCapteurs[i][j] = similitudeMesure / compteur;
            cout << matriceCapteurs[i][j] << endl;
        }
    }

    for (unsigned int i = 0; i < listeCapteurs.size(); i++)
    {
        delete[] matriceCapteurs[i];
    }
    delete[] matriceCapteurs;
}*/

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

double Analyse::distanceEuclidienne(vector<double> A, vector<double> B)
{
    double dist = 0.0;

    int nbElements = min(A.size(), B.size());
    for (int i = 0; i < nbElements; i++)
    {
        dist += (A[i]-B[i]) * (A[i]-B[i]);
    }
    return sqrt(dist);
}

matrice_t &Analyse::normalizeMatrix(matrice_t &mat)
{
    double maxElement = 0;
    for(vector<double> line : mat){
        double maxLine = *max_element(line.begin(), line.end());
        if (maxLine > maxElement){
            maxElement = maxLine;
        }    
    }
    
    double norm = 1.0 / maxElement;

    for(int i = 0; i < mat.size(); i++)
    {
        transform(mat[i].begin(), mat[i].end(), mat[i].begin(), [norm](double d) { return 100.0 * (1-(d * norm)); });
    }

    return mat;
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
