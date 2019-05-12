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
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    SensorFactory LectureFichier(const string path);
    void ValeurIntervalle(double latitude, double longitude, double rayon, date_t debut, date_t fin, SensorFactory &sensorFactory);

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <Controleur>

#endif // CONTROLEUR_H
