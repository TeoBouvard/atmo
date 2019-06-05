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
#include "Result.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Menu::Run(Controleur &controleur)
{
  string lecture;
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
        CapteursDefectueux(controleur);
      }
      else
      {
        modif = false;
        cout << endl
             << "Menu :\n 1 : Connaître la qualité de l’air sur une zone donnée\n 2 : Identifier les zones ayant une qualité de l’air similaire\n 3 : Connaître la qualité de l\'air en un point donné\n 4 : Identifier les capteurs défectueux\n 5 : Quitter\n"
             << endl;
      }
    }

    lecture.clear();

    if (!modif)
    {
      cin >> lecture;
      cout << endl;
    }
  }
}

void Menu::inputDouble(double &value)
{
  while (!(cin >> value))
  {
    cerr << "Saisie erronnée, merci de saisir un nombre entier ou décimal : ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

void Menu::inputPolluant(string &polluant)
{
  regex polluantFormat("^O3$|^NO2$|^SO2$|^PM10$");
  while (!(cin >> polluant) || !regex_match(polluant, polluantFormat))
  {
    if (!regex_match(polluant, polluantFormat))
    {
      cerr << "Saisie erronnée, merci de saisir un polluant : ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

date_t Menu::inputDate(date_t borneInf)
{
  regex dateFormat("\\d\\d\\d\\d-(0[1-9]|1[012])-((0|1|2)[0-9]|3[01])");
  string value;
  getline(cin,value);
  while (!regex_match(value, dateFormat) || SensorFactory::make_date(value + "T00:00:00.00") < borneInf)
  {
    if(value == "")
    {
      if(borneInf.year == 0) {
        return SensorFactory::make_date("0001-00-00T00:00:00.00");
      }
      else {
        return SensorFactory::make_date("9999-00-00T00:00:00.00");
      }
    }
    else if (!regex_match(value, dateFormat))
    {
      cerr << "Saisie erronnée, merci de saisir une date au format YYYY-MM-DD : ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
      cerr << "Sasir une date de fin postérieure à l'heure de début : ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    getline(cin,value);
  }

  date_t date = SensorFactory::make_date(value + "T00:00:00.00");
  return date;
}

void Menu::QualiteDeLAir(Controleur &controleur)
{
  double latitude, longitude, rayon;
  date_t debut, fin;

  cout << "Latitude : ";
  inputDouble(latitude);
  cout << "Longitude : ";
  inputDouble(longitude);
  cout << "Rayon : ";
  inputDouble(rayon);
  cout << "Date de début au format YYYY-MM-DD : ";
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  debut = inputDate();
  cout << "Date de fin au format YYYY-MM-DD : ";
  fin = inputDate(debut);

  cout << endl
       << "Analyse en cours ... " << endl;

  Result result = controleur.ValeurIntervalle(latitude, longitude, rayon, debut, fin);
  cout << result << endl;

  cout << "Analyse terminée." << endl;
}

void Menu::QualiteSimilaire(Controleur &controleur)
{
  date_t debut, fin;
  string polluant;
  cout << "Choisir un polluant (O3 | NO2 | SO2 | PM10) : ";
  inputPolluant(polluant);
  cout << "Date de début au format YYYY-MM-DD : ";
  debut = inputDate();
  cout << "Date de fin au format YYYY-MM-DD : ";
  fin = inputDate(debut);

  cout << endl
       << "Analyse en cours ... " << endl;

  Result result = controleur.CapteursSimilaires(debut, fin, polluant);
  cout << result << endl;

  cout << "Analyse terminée." << endl;
}

void Menu::QualiteEnUnPoint(Controleur &controleur)
{
  double latitude, longitude;
  date_t debut, fin;

  cout << "Latitude : ";
  inputDouble(latitude);
  cout << "Longitude : ";
  inputDouble(longitude);
  cout << "Date de début au format YYYY-MM-DD : ";
  debut = inputDate();
  cout << "Date de fin au format YYYY-MM-DD : ";
  fin = inputDate(debut);

  cout << endl
       << "Analyse en cours ... " << endl;

  Result result = controleur.ValeurIntervalle(latitude, longitude, 0, debut, fin);
  cout << result << endl;

  cout << "Analyse terminée." << endl;
}

void Menu::CapteursDefectueux(Controleur &controleur)
{

  cout << endl
       << "Analyse en cours ... " << endl;

  Result result = controleur.CapteursDefectueux();
  cout << result << endl;

  cout << "Analyse terminée." << endl;
}

int main(int argc, char *argv[])
{
  Controleur controleur;

  controleur.LectureFichier(argv[1]);

  Menu menu;
  menu.Run(controleur);

  return 0;
}