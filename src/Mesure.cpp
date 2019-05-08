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

