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

void Controleur::LectureFichier(const string path)
{
    ifstream file(path);

    if (file)
    {
        SensorFactory&& sensorFactoryTemp = SensorFactory(file);
		sensorFactory = std::move(sensorFactoryTemp);
    }
    else
    {
        cerr << "Erreur lors de l'ouverture du fichier " << path << endl;
        exit(PATH_ERROR);
    }
}

void Controleur::ValeurIntervalle(double latitude, double longitude, double rayon, date_t debut, date_t fin)
{
    Analyse analyse(latitude, longitude, rayon, debut, fin);
    analyse.ValeurIntervalle(sensorFactory);
}


void Controleur::CapteursSimilaires(date_t debut, date_t fin)
{
	Analyse analyse(0, 0, 0 ,debut, fin);
	analyse.CapteursSimilaires(sensorFactory);
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Controleur::Controleur()
{
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
