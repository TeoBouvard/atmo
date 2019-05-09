/*************************************************************************
                           Geo  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Geo> (fichier Geo.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cmath>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Geo.h"

//------------------------------------------------------------- Constantes

constexpr double pi = 3.14159265358979323846;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
double Geo::CalculDistance(double lat1, double long1, double lat2, double long2)
{
    lat1 = ToRadians(lat1);
    long1 = ToRadians(long1);
    lat2 = ToRadians(lat2);
    long2 = ToRadians(long2);

    double dlong = long2 - long1;
    double dlat = lat2 - lat1;

    double ans = pow(sin(dlat/2),2) + cos(lat1)*cos(lat2)*pow(sin(dlong/2),2);
    ans = 2 * asin(sqrt(ans));

    double R = 6371;
    ans = ans * R;

    return ans;
}

double Geo::ToRadians(double degree)
{
    double one_deg = pi / 180; //La constante M_PI n'est pas présente sur toutes les installations de c++ (surtout les plus récentes c++ 11 il me semble)
    return degree*one_deg;
}

//-------------------------------------------- Constructeurs - destructeur
Geo::Geo ( const Geo & unGeo )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Geo>" << endl;
#endif
} //----- Fin de Geo (constructeur de copie)


Geo::Geo ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Geo>" << endl;
#endif
} //----- Fin de Geo


Geo::~Geo ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Geo>" << endl;
#endif
} //----- Fin de ~Geo


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

