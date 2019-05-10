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


//------------------------------------------------- Surcharge d'opérateurs
Mesure & Mesure::operator = ( const Mesure & uneMesure )
// Algorithme :
//
{
    date = uneMesure.date;
    polluant = uneMesure.polluant;
    valeur = uneMesure.valeur;
    return *this;
} //----- Fin de operator =

bool operator<(const Mesure& m1, const Mesure& m2){
    if(m1.polluant != m2.polluant)
    {
        return m1.polluant < m2.polluant;
    }
    else if(m1.date.year != m2.date.year)
    {
        return m1.date.year < m2.date.year;
    }
    else if(m1.date.month != m2.date.month)
    {
        return m1.date.month < m2.date.month;
    }
    else if(m1.date.day != m2.date.day)
    {
        return m1.date.day < m2.date.day;
    }
    else if(m1.date.hour != m2.date.hour)
    {
        return m1.date.hour < m2.date.hour;
    }
    else if(m1.date.minute != m2.date.minute)
    {
        return m1.date.minute < m2.date.minute;
    }
    return false;
}

//-------------------------------------------- Constructeurs - destructeur
Mesure::Mesure ( const Mesure & uneMesure )
// Algorithme :
//
{
    date = uneMesure.date;
    polluant = uneMesure.polluant;
    valeur = uneMesure.valeur;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Mesure>" << endl;
#endif
} //----- Fin de Mesure (constructeur de copie)


Mesure::Mesure (const date_t dateMesure, const string polluantMesure, const double valeurMesure)
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


Mesure::~Mesure ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Mesure>" << endl;
#endif
} //----- Fin de ~Mesure

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

