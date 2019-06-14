/*************************************************************************
                           Result  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Result> (fichier Result.h) ----------------
#if !defined(RESULT_H)
#define RESULT_H

//--------------------------------------------------- Interfaces utilisées
#include <vector>
#include <string>
#include "Sensor.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef vector<vector<double>> matrice_t;
//------------------------------------------------------------------------
// Rôle de la classe <Result>
//
//
//------------------------------------------------------------------------

class Result
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    //------------------------------------------------- Surcharge d'opérateurs

    friend ostream &operator<<(ostream &os, const Result &r);

    //-------------------------------------------- Constructeurs - destructeur

    Result(vector<Sensor const*> capteursSurZone, vector<double> moyennes, vector<int> indicesAtmo, int nbMesures, vector<double> distancesAuCentre);
    Result(vector<Sensor const*> capteursSurZone, matrice_t similarityMatrix, int nbMesures);
    Result(vector<Sensor const*> capteursSurZone);
	Result() {};

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string type; // ! serait beaucoup mieux avec de l'héritage
    matrice_t similarityMatrix;
    int nbMesures;
    vector<int> indices;
    vector<Sensor const*> capteurs;
    vector<double> concentrationsMoyennes;
    vector<double> distancesAuCentre;
};

//-------------------------------- Autres définitions dépendantes de <Result>

#endif // RESULT_H
