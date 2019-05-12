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
    void Run();

    void QualiteDeLAir();

    void QualiteSimilaire();

    void QualiteEnUnPoint();

    void CapteurDefectueux();

    void input(double &value);
    date_t input(string value);

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur
    Menu(const Menu &unMenu);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Menu();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Menu();
    // Mode d'emploi :
    //
    // Contrat :
    //

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
