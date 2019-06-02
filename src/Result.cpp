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
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */
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
                 << BOLDWHITE << "Aucun capteur présent dans la zone sélectionnée" << RESET << endl;
        }
        else if (isnan(r.concentrationsMoyennes.front()))
        {
            cout << endl
                 << BOLDWHITE << "Nombre de capteurs dans la zone : " << r.capteurs.size() << endl
                 << endl
                 << "Aucune mesure sur cet intervalle de temps" << RESET << endl;
        }
        else
        {
            cout << endl
                 << BOLDWHITE << "Capteur(s) selectionné(s) : " << endl
                 << endl;
            for (int i = 0; i < r.capteurs.size(); i++)
            {
                cout << "Sensor n°" << r.capteurs[i].GetID() << " | Distance au centre : " << r.distancesAuCentre[i] << "km" << endl;
            }
            cout << endl
                 << "Nombre de mesures sur cette période de temps : " << r.nbMesures << endl
                 << endl;
            cout << BOLDCYAN << "Moyenne 03 : " << r.concentrationsMoyennes.at(0) << " µg/m3 "
                 << "| Sous indice 03 : " << r.indices.at(0) << endl;
            cout << "Moyenne NO2 : " << r.concentrationsMoyennes.at(1) << " µg/m3 "
                 << "| Sous indice NO2 : " << r.indices.at(1) << endl;
            cout << "Moyenne SO2 : " << r.concentrationsMoyennes.at(2) << " µg/m3 "
                 << "| Sous indice SO2 : " << r.indices.at(2) << endl;
            cout << "Moyenne PM10 : " << r.concentrationsMoyennes.at(3) << " µg/m3 "
                 << "| Sous indice PM10 : " << r.indices.at(3) << endl;
            cout << endl
                 << BOLDRED << "Indice ATMO : " << r.indices.back() << RESET << endl;
        }
    }

    else if (r.type == "similarite")
    {
        if (r.capteurs.empty())
        {
            cout << endl
                 << BOLDWHITE << "Aucun capteur à comparer" << RESET << endl;
        }
        else if (isnan(r.similarityMatrix[0].front()))
        {
            cout << endl
                 << BOLDWHITE << "Nombre de capteurs comparés : " << r.capteurs.size() << endl
                 << endl
                 << "Aucune mesure sur cet intervalle de temps" << RESET << endl;
        }
        else
        {
            cout << endl
                 << BOLDWHITE << "Nombre de capteurs comparés : " << r.capteurs.size() << endl
                 << "Nombre de mesures sur cette période de temps : " << r.nbMesures << RESET << endl
                 << endl;

            cout << setw(12) << "|";
            for (Sensor s : r.capteurs)
            {
                cout << setw(4) << s.GetID() << setw(3) << "|";
            }
            cout << endl;

            for (int i = 0; i < r.similarityMatrix.size(); i++)
            {
                cout << "Sensor n°" << r.capteurs[i].GetID() << " | ";
                for (int j = 0; j < r.similarityMatrix[i].size(); j++)
                {
                    int similarite = (int)r.similarityMatrix[i][j];
                    cout << setw(9) << fixed << setprecision(2);
                    if (similarite < 33)
                    {
                        cout << BOLDRED;
                    }
                    else if (similarite < 66)
                    {
                        cout << BOLDYELLOW;
                    }
                    else if (similarite <= 100)
                    {
                        cout << BOLDGREEN;
                    }
                    cout << setw(3) << similarite << "%" << RESET << " | ";
                }
                cout << endl
                     << endl;
            }
        }
    }
    else if (r.type == "defectueux")
    {
        if (r.capteurs.empty())
        {
            cout << endl
                 << BOLDWHITE << "Aucun capteur défectueux" << RESET << endl;
        }
        else
        {
            cout << endl
                 << BOLDWHITE << "Nombre de capteurs défectueux : " << r.capteurs.size() << endl
                 << endl;

            for (Sensor s : r.capteurs)
            {
                cout << "Sensor n°" << s.GetID() << " | " << s.GetListeMesure().size() << " mesures erronées"
                     << " ["
                     << s.GetListeMesure().front().GetDate() << " -> "
                     << s.GetListeMesure().back().GetDate() << "]" << endl;
            }
            cout << RESET;
        }
    }

    return os;
}

//-------------------------------------------- Constructeurs - destructeur

Result::Result(vector<Sensor> capteursSurZone, vector<double> moyennes, vector<int> indicesAtmo, int nbMesures, vector<double> distancesAuCentre)
{
    this->type = "indices";
    this->capteurs = capteursSurZone;
    this->concentrationsMoyennes = moyennes;
    this->indices = indicesAtmo;
    this->nbMesures = nbMesures;
    this->distancesAuCentre = distancesAuCentre;
#ifdef MAP
    cout << "Appel au constructeur de <Result>" << endl;
#endif
} //----- Fin de Result

Result::Result(vector<Sensor> capteursSurZone, matrice_t similarityMatrix, int nbMesures)
{
    this->type = "similarite";
    this->capteurs = capteursSurZone;
    this->similarityMatrix = similarityMatrix;
    this->nbMesures = nbMesures;

#ifdef MAP
    cout << "Appel au constructeur de <Result>" << endl;
#endif
} //----- Fin de Result

Result::Result(vector<Sensor> capteursSurZone)
{
    this->type = "defectueux";
    this->capteurs = capteursSurZone;

#ifdef MAP
    cout << "Appel au constructeur de <Result>" << endl;
#endif
} //----- Fin de Result

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
