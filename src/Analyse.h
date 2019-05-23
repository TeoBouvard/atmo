/*************************************************************************
                           Analyse  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Analyse> (fichier Analyse.h) ----------------
#if !defined(ANALYSE_H)
#define ANALYSE_H

//--------------------------------------------------- Interfaces utilisées
#include "Mesure.h"
#include "SensorFactory.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Analyse>
//
//
//------------------------------------------------------------------------

class Analyse
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    void ValeurIntervalle(SensorFactory &sensorFactory);

	void CapteursSimilaires(SensorFactory &sensorFactory);

    void CalculValeurAtmo(double O3, double NO2, double SO2, double PM10);

    //------------------------------------------------- Surcharge d'opérateurs
    Analyse &operator=(const Analyse &unAnalyse);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    Analyse(const Analyse &unAnalyse);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Analyse(double latitude, double longitude, double rayon, date_t debut, date_t fin);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Analyse();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    double latitude;
    double longitude;
    double rayon;
    date_t debut;
    date_t fin;
};

//-------------------------------- Autres définitions dépendantes de <Analyse>

#endif // ANALYSE_H
