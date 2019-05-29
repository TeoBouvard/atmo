/*************************************************************************
                           Controleur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Controleur> (fichier Controleur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include <string>
#include "Controleur.h"
#include "SensorFactory.h"
#include "Mesure.h"
#include "Analyse.h"
#include "Geo.h"

//------------------------------------------------------------- Constantes
#define PATH_ERROR 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Controleur::LectureFichier(const string path)
{
    ifstream file(path);

    if (file)
    {
        SensorFactory &&sensorFactoryTemp = SensorFactory(file);
        this->sensorFactory = std::move(sensorFactoryTemp);
    }
    else
    {
        cerr << "Erreur lors de l'ouverture du fichier " << path << endl;
        exit(PATH_ERROR);
    }
}

Result Controleur::ValeurIntervalle(double latitude, double longitude, double rayon, date_t debut, date_t fin)
{
    Analyse analyse(latitude, longitude, rayon, debut, fin);
    return (analyse.ValeurIntervalle(sensorFactory));
}

Result Controleur::CapteursSimilaires(date_t debut, date_t fin, string polluant)
{
    Analyse analyse(0, 0, 0, debut, fin);
    return (analyse.computeSimiarity(sensorFactory, polluant));
}

void Controleur::CapteursDefectueux(date_t debut, date_t fin)
{
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
