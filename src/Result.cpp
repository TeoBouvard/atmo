/*************************************************************************
                           Result  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Result> (fichier Result.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include <math.h>
#include <iomanip>
#include "Result.h"
#include "Sensor.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs
ostream &operator<<(ostream &os, const Result &r)
{
    if (r.type == "indices")
    {
        if (r.capteurs.empty())
        {
            cout << endl
                 << "Aucun capteur présent dans la zone sélectionnée" << endl;
        }
        else if (isnan(r.concentrationsMoyennes.front()))
        {
            cout << endl
                 << "Nombre de capteurs dans la zone : " << r.capteurs.size() << endl
                 << endl
                 << "Aucune mesure sur cet intervalle de temps" << endl;
        }
        else
        {
            cout << endl
                 << "Nombre de capteurs dans la zone : " << r.capteurs.size() << endl
                 << endl;
            cout << "Moyenne 03 : " << r.concentrationsMoyennes.at(0) << " µg/m3 "
                 << "| Sous indice 03 : " << r.indices.at(0) << endl;
            cout << "Moyenne NO2 : " << r.concentrationsMoyennes.at(1) << " µg/m3 "
                 << "| Sous indice NO2 : " << r.indices.at(1) << endl;
            cout << "Moyenne SO2 : " << r.concentrationsMoyennes.at(2) << " µg/m3 "
                 << "| Sous indice SO2 : " << r.indices.at(2) << endl;
            cout << "Moyenne PM10 : " << r.concentrationsMoyennes.at(3) << " µg/m3 "
                 << "| Sous indice PM10 : " << r.indices.at(3) << endl;
            cout << endl
                 << "Indice ATMO : " << r.indices.back() << endl;
        }
    }

    else if (r.type == "similarite") //FINIR AFFICHAGE (titres colonnes et lignes)
    {
        for (int i = 0; i < r.similarityMatrix.size(); i++)
        {
            for (int j = 0; j < r.similarityMatrix[i].size() && j <= i; j++)
                cout << setw(10) << r.similarityMatrix[i][j] << " ";
            cout << endl;
        }
    }

    return os;
}

//-------------------------------------------- Constructeurs - destructeur

Result::Result(vector<Sensor> capteursSurZone, vector<double> moyennes, vector<int> indicesAtmo)
{
    this->type = "indices";
    this->capteurs = capteursSurZone;
    this->concentrationsMoyennes = moyennes;
    this->indices = indicesAtmo;
#ifdef MAP
    cout << "Appel au constructeur de <Result>" << endl;
#endif
} //----- Fin de Result

Result::Result(vector<Sensor> capteursSurZone, matrice_t similarityMatrix)
{
    this->type = "similarite";
    this->capteurs = capteursSurZone;
    this->similarityMatrix = similarityMatrix;

#ifdef MAP
    cout << "Appel au constructeur de <Result>" << endl;
#endif
} //----- Fin de Result

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
