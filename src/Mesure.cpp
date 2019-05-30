/*************************************************************************
                           Mesure  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Mesure> (fichier Mesure.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Mesure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Mesure::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
bool operator<(const date_t &date1, const date_t &date2)
{
    if (date1.year != date2.year)
    {
        return (date1.year < date2.year);
    }
    else if (date1.month != date2.month)
    {
        return (date1.month < date2.month);
    }
    else if (date1.day != date2.day)
    {
        return (date1.day < date2.day);
    }
    else if (date1.hour != date2.hour)
    {
        return (date1.hour < date2.hour);
    }
    else if (date1.minute != date2.minute)
    {
        return (date1.minute < date2.minute);
    }
    else if (date1.second != date2.second)
    {
        return (date1.second < date2.second);
    }
    else
    {
        return true;
    }
}

//------------------------------------------------- Surcharge d'opérateurs

bool operator<(const Mesure &m1, const Mesure &m2)
{
    if (m1.polluant != m2.polluant)
    {
        return m1.polluant < m2.polluant;
    }
    else
    {
        return m1.date < m2.date;
    }
}

ostream &operator<<(ostream &os, const date_t &date)
{
    os << date.year << "-"
       << ((date.month < 10) ? "0" : "") << date.month << "-"
       << ((date.day < 10) ? "0" : "") << date.day;
    return os;
}

//-------------------------------------------- Constructeurs - destructeur

Mesure::Mesure(const date_t dateMesure, const string polluantMesure, const double valeurMesure)
// Algorithme :
//
{
    date = dateMesure;
    polluant = polluantMesure;
    valeur = valeurMesure;
#ifdef MAP
    cout << "Appel au constructeur de <Mesure>" << endl;
#endif
} //----- Fin de Mesure

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
