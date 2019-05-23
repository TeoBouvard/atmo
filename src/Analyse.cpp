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
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analyse.h"
#include "SensorFactory.h"
#include "Sensor.h"
#include "Geo.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Analyse::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
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
            for (auto m : s.GetListeMesure())
            {
                string type = m.GetPolluant();
                if(type.compare("O3") == 0)
                {
                    totO3 += m.GetValeur();
                    nbO3++;
                }
                else if(type.compare("NO2") == 0)
                {
                    totNO2 += m.GetValeur();
                    nbNO2++;
                }
                else if(type.compare("SO2") == 0)
                {
                    totSO2 += m.GetValeur();
                    nbSO2++;
                }
                else if(type.compare("PM10") == 0)
                {
                    totPM10 += m.GetValeur();
                    nbPM10++;
                }
            }
        }
    }
    if(nbSensor == 0)
    {
        cout << "Auncun capteur dans cette zone" << endl;
    }
    else
    {
        double moyO3 = (totO3 / nbO3);;
        double moyNO2 = (totNO2 / nbNO2);
        double moySO2 = (totSO2 / nbSO2);
        double moyPM10 = (totPM10 / nbPM10);

        cout << "Nombre de capteurs etudiee : " << nbSensor << endl;
        cout << "Moyenne 03 : " << moyO3 << endl;
        cout << "Moyenne NO2 : " << moyNO2 << endl;
        cout << "Moyenne SO2 : " << moySO2 << endl;
        cout << "Moyenne PM10 : " << moyPM10 << endl;

        CalculValeurAtmo(moyO3, moyNO2, moySO2, moyPM10);
    }
    
}

void Analyse::CalculValeurAtmo(double O3, double NO2, double SO2, double PM10)
{
    int atmoO3, atmoNO2, atmoSO2, atmoPM10, atmoGene = 0;
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
    
    atmoGene = max(max(atmoO3, atmoNO2),max(atmoSO2,atmoPM10));

    cout << "Indice atmo : " << atmoGene << endl;
    
}

//------------------------------------------------- Surcharge d'opérateurs
/*Analyse & Analyse::operator = ( const Analyse & unAnalyse )
// Algorithme :
//
{
} //----- Fin de operator =*/

//-------------------------------------------- Constructeurs - destructeur
Analyse::Analyse(const Analyse &unAnalyse)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Analyse>" << endl;
#endif
} //----- Fin de Analyse (constructeur de copie)

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

Analyse::~Analyse()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Analyse>" << endl;
#endif
} //----- Fin de ~Analyse

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
