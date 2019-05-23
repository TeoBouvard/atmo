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
    void CapteurDefectueux(Controleur &controleur);

    void input(double &value);
    date_t input(string value);

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
