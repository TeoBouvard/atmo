/*************************************************************************
                           Menu  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Menu> (fichier Menu.h) ----------------
#if !defined(MENU_H)
#define MENU_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "Mesure.h"
#include "Controleur.h"
#include "SensorFactory.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
//------------------------------------------------------------------------
// Rôle de la classe <Menu>
//
//
//------------------------------------------------------------------------

class Menu
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    void Run(Controleur &controleur);

    void QualiteDeLAir(Controleur &controleur);
    void QualiteSimilaire(Controleur &controleur);
    void QualiteEnUnPoint(Controleur &controleur);
    void CapteursDefectueux(Controleur &controleur);

    void inputDouble(double &value);
    void inputPolluant(string &polluant);
    date_t inputDate(date_t borneInf = SensorFactory::make_date("0000-00-00T00:00:00.00"));

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    enum SelectionMenu
    {
        M_MENU
    };
    SelectionMenu currentMenu;
};

//-------------------------------- Autres définitions dépendantes de <Menu>

#endif // MENU_H
