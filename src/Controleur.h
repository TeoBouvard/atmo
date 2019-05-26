/*************************************************************************
                           Controleur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Controleur> (fichier Controleur.h) ----------------
#if !defined(CONTROLEUR_H)
#define CONTROLEUR_H

//--------------------------------------------------- Interfaces utilisées
#include "SensorFactory.h"
#include "Mesure.h"
#include "Result.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Controleur>
//
//
//------------------------------------------------------------------------

class Controleur
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    void LectureFichier(const string path);

    Result ValeurIntervalle(double latitude, double longitude, double rayon, date_t debut, date_t fin);
    Result CapteursSimilaires(date_t debut, date_t fin);

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur
    //------------------------------------------------------------------ PRIVE

protected:
    SensorFactory sensorFactory;
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <Controleur>

#endif // CONTROLEUR_H
