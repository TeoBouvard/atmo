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
#include "Controleur.h"
#include "SensorFactory.h"
#include "Mesure.h"
#include "Analyse.h"
#include "Geo.h"

//------------------------------------------------------------- Constantes
#define PATH_ERROR 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

SensorFactory Controleur::LectureFichier(const string path)
{
    ifstream file(path);

    if (file)
    {
        return (SensorFactory(file));
    }
    else
    {
        cerr << "Erreur lors de l'ouverture du fichier " << path << endl;
        exit(PATH_ERROR);
    }
}

void Controleur::ValeurIntervalle(double latitude, double longitude, double rayon, date_t debut, date_t fin, SensorFactory &sensorFactory)
{
    Analyse analyse(latitude, longitude, rayon, debut, fin);
    analyse.ValeurIntervalle(sensorFactory);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
