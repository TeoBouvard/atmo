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
#include <cstring>
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

void Menu::Run(Controleur &controleur, SensorFactory &sensorFactory)
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
        QualiteDeLAir(controleur, sensorFactory);
      }
      else if (strcmp(lecture.c_str(), "2") == 0)
      {
        QualiteSimilaire();
      }
      else if (strcmp(lecture.c_str(), "3") == 0)
      {
        QualiteEnUnPoint();
      }
      else if (strcmp(lecture.c_str(), "4") == 0)
      {
        CapteurDefectueux();
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

void Menu::QualiteDeLAir(Controleur &controleur, SensorFactory &sensorFactory)
{
  double latitude, longitude, rayon;
  string debut_str, fin_str;
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

  controleur.ValeurIntervalle(latitude, longitude, rayon, debut, fin, sensorFactory);
}

void Menu::QualiteSimilaire()
{
}

void Menu::QualiteEnUnPoint()
{
}

void Menu::CapteurDefectueux()
{
}

Menu::Menu()
{
#ifdef MAP
  cout << "Appel au constructeur de <Menu>" << endl;
#endif
}

Menu::~Menu()
{
#ifdef MAP
  cout << "Appel au destructeur de <Menu>" << endl;
#endif
}

int main(int argc, char *argv[])
{
  //création de la SensorFactory au début du programme afin de l'avoir en mémoire
  Controleur controleur;
  SensorFactory sensorFactory = controleur.LectureFichier(argv[1]);

  Menu menu;
  menu.Run(controleur, sensorFactory);

  return 0;
}