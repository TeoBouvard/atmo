/*************************************************************************
                           Menu  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Menu> (fichier Menu.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Menu.h"
#include "SensorFactory.h"
#include "Mesure.h"
#include "Controleur.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Menu::Run(Controleur &controleur)
{
  string lecture("");
  currentMenu = SelectionMenu::M_MENU;

  bool modif = false;

  while (strcmp(lecture.c_str(), "5") != 0) //On entre dans le menu
  {
    modif = true;

    if (currentMenu == SelectionMenu::M_MENU) // Selection du premier sous menu
    {
      if (strcmp(lecture.c_str(), "1") == 0)
      {
        QualiteDeLAir(controleur);
      }
      else if (strcmp(lecture.c_str(), "2") == 0)
      {
        QualiteSimilaire(controleur);
      }
      else if (strcmp(lecture.c_str(), "3") == 0)
      {
        QualiteEnUnPoint(controleur);
      }
      else if (strcmp(lecture.c_str(), "4") == 0)
      {
        CapteurDefectueux(controleur);
      }
      else
      {
        modif = false;
        cout << endl
             << "Menu :\n 1 : Connaître la qualité de l’air sur une zone donnée\n 2 : Identifier les zones ayant une qualité de l’air similaire\n 3 : Connaître la qualité de l\'air en un point donné\n 4 : Identifier les capteurs défectueux\n 5 : Quitter\n"
             << endl;
      }
    }

    lecture = "";

    if (!modif)
    {
      cin >> lecture;
      cout << endl;
    }
  }
}

void Menu::input(double &value)
{
  while (!(cin >> value))
  {
    cerr << "Saisie erronnée, merci de saisir un nombre entier ou décimal : ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

date_t Menu::input(string value)
{
  regex dateFormat("\\d\\d\\d\\d-\\d\\d-\\d\\d");
  while (!(cin >> value) || !regex_match(value, dateFormat))
  {
    cerr << "Saisie erronnée, merci de saisir une date au format YYYY-MM-DD : ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  string convertedDate = value + "T00:00:00.00";
  return SensorFactory::make_date(convertedDate);
}

void Menu::QualiteDeLAir(Controleur &controleur)
{
  double latitude, longitude, rayon;
  string debut_str = "";
  string fin_str = "";
  date_t debut, fin;

  cout << "Latitude : ";
  input(latitude);
  cout << "Longitude : ";
  input(longitude);
  cout << "Rayon : ";
  input(rayon);
  cout << "Date de début au format YYYY-MM-DD : ";
  debut = input(debut_str);
  cout << "Date de fin au format YYYY-MM-DD : ";
  fin = input(fin_str);

  controleur.ValeurIntervalle(latitude, longitude, rayon, debut, fin);
}

void Menu::QualiteSimilaire(Controleur &controleur)
{
  string debut_str = "";
  string fin_str = "";
  date_t debut, fin;
  cout << "Date de début au format YYYY-MM-DD : ";
  debut = input(debut_str);
  cout << "Date de fin au format YYYY-MM-DD : ";
  fin = input(fin_str);

  controleur.CapteursSimilaires(debut, fin);
}

void Menu::QualiteEnUnPoint(Controleur &controleur)
{
  double latitude, longitude;
  string debut_str = "";
  string fin_str = "";
  date_t debut, fin;

  cout << "Latitude : ";
  input(latitude);
  cout << "Longitude : ";
  input(longitude);
  cout << "Date de début au format YYYY-MM-DD : ";
  debut = input(debut_str);
  cout << "Date de fin au format YYYY-MM-DD : ";
  fin = input(fin_str);

  controleur.ValeurIntervalle(latitude, longitude, 0, debut, fin);
}

void Menu::CapteurDefectueux(Controleur &controleur)
{
}

int main(int argc, char *argv[])
{
  Controleur controleur;

  controleur.LectureFichier(argv[1]);

  Menu menu;
  menu.Run(controleur);

  return 0;
}