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
    cout << "debut analyse" << endl;
    //récupérer les capteurs de la SensorFactory
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();
    int nbSensor = 0;
/*
    double moyO3 = 0;
    double moyNO2 = 0;
    double moySO2 = 0;
    double moyPM10 = 0;
*/
    for (Sensor s : listeCapteurs)
    {
        cout << "sensor" << endl;
        //si le capteur et dans la zone choisie
        if (Geo::CalculDistance(s.GetLatitude(), s.GetLongitude(), this->latitude, this->longitude) < rayon)
        {
            cout << "sensor valide" << endl;
            set<Mesure> ms = s.GetListeMesure();
            cout << ms.size() << endl;
            nbSensor++;
            for (auto m : s.GetListeMesure())
            {
                string type = m.GetPolluant();
                cout << type << endl;
            }
        }
    }
    if(nbSensor)
    {

    }
    else
    {
        
    }
    
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
