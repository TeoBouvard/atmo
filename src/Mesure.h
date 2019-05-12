/*************************************************************************
                           Mesure  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Mesure> (fichier Mesure.h) ----------------
#if !defined(MESURE_H)
#define MESURE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef struct date_t
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} date_t;

bool operator<(const date_t &date1, const date_t &date2);

//------------------------------------------------------------------------
// Rôle de la classe <Mesure>
// Représente une unique mesure d'un capteur
//------------------------------------------------------------------------

class Mesure
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    //------------------------------------------------- Surcharge d'opérateurs
    Mesure &operator=(const Mesure &uneMesure);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //opérateur de comparaison nécéssaire à l'insertion dans un set
    friend bool operator<(const Mesure &m1, const Mesure &m2);

    //-------------------------------------------- Constructeurs - destructeur
    Mesure(const Mesure &uneMesure);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Mesure(const date_t dateMesure, const string polluantMesure, const double valeurMesure);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Mesure();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string polluant;
    double valeur;
    date_t date;
};

//-------------------------------- Autres définitions dépendantes de <Mesure>

#endif // MESURE_H
