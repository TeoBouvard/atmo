/*************************************************************************
                           Geo  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Geo> (fichier Geo.h) ----------------
#if ! defined ( GEO_H )
#define GEO_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Geo>
//
//
//------------------------------------------------------------------------

class Geo
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    double CalculDistance(double lat1, double long1, double lat2, double long2);

    double ToRadians(double degree);


//-------------------------------------------- Constructeurs - destructeur
    Geo ( const Geo & unGeo );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Geo ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Geo ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Geo>

#endif // GEO_H

