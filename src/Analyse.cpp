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
#include <iomanip> // A VIRER QUAND AFFICHAGE DANS MENU
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analyse.h"
#include "SensorFactory.h"
#include "Sensor.h"
#include "Geo.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Analyse::ValeurIntervalle(SensorFactory &sensorFactory)
{
    //récupérer les capteurs de la SensorFactory
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();
    int nbSensor = 0;

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
            nbSensor++;
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
    if (nbSensor == 0)
    {
        cout << "Auncun capteur dans cette zone" << endl;
    }
    else
    {
        double moyO3 = (totO3 / nbO3);
        double moyNO2 = (totNO2 / nbNO2);
        double moySO2 = (totSO2 / nbSO2);
        double moyPM10 = (totPM10 / nbPM10);

        cout << "Nombre de capteurs dans la zone : " << nbSensor << endl;
        cout << "Moyenne 03 : " << moyO3 << "µg / m3" << endl;
        cout << "Moyenne NO2 : " << moyNO2 << "µg / m3" << endl;
        cout << "Moyenne SO2 : " << moySO2 << "µg / m3" << endl;
        cout << "Moyenne PM10 : " << moyPM10 << "µg / m3" << endl;

        CalculValeurAtmo(moyO3, moyNO2, moySO2, moyPM10);
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

void Analyse::CalculValeurAtmo(double O3, double NO2, double SO2, double PM10)
{
    int atmoO3, atmoNO2, atmoSO2, atmoPM10, atmoGlobal = 0;
    switch ((int)O3)
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

    switch ((int)NO2)
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

    switch ((int)SO2)
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

    switch ((int)PM10)
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

    cout << "Sous indice atmo O3 :" << atmoO3 << endl;
    cout << "Sous indice atmo NO2 :" << atmoNO2 << endl;
    cout << "Sous indice atmo SO2 :" << atmoSO2 << endl;
    cout << "Sous indice atmo PM10 :" << atmoPM10 << endl;
    cout << "Indice ATMO : " << atmoGlobal << endl;
}

void Analyse::CapteursSimilaires(SensorFactory &sensorFactory)
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
}

vector<vector<double>> Analyse::computeSimiarity(SensorFactory &sensorFactory, string polluant)
{
    vector<vector<double>> similarityMatrix;
    vector<double> distances;

    //récupérer les capteurs de la SensorFactory
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();
    vector<double> listeMesureA;
    vector<double> listeMesureB;

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
                    }
                }
            }

            distances.push_back(distanceEuclidienne(listeMesureA, listeMesureB));
            //cout << s1.GetID() << " | " << s2.GetID() << " : " << distance << endl;
            listeMesureB.clear();
        }
        normalizeVector(distances);
        similarityMatrix.push_back(distances);

        distances.clear();
        listeMesureA.clear();
    }

    for (int i = 0; i < similarityMatrix.size(); i++)
    {
        for (int j = 0; j < similarityMatrix[i].size(); j++)
            cout << setw(10) << similarityMatrix[i][j] << " ";
        cout << endl;
    }

    return similarityMatrix;
}

double Analyse::distanceEuclidienne(vector<double> A, vector<double> B)
{
    double dist = 0.0;

    int nbElements = min(A.size(), B.size());
    for (int i = 0; i < nbElements; i++)
    {
        dist += pow(A.at(i) - B.at(i), 2);
    }

    return sqrt(dist);
}

vector<double> &Analyse::normalizeVector(vector<double> &vec)
{
    double max = *max_element(vec.begin(), vec.end());
    double norm = 1.0 / max;
    transform(vec.begin(), vec.end(), vec.begin(), [norm](double d) { return 1 - (d * norm); });
    return vec;
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
