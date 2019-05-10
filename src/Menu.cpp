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
#include <codecvt>
#include <fstream>
#include <cstring>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Menu.h"
#include "SensorFactory.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
/*static void utf16_utf8(string path_to_file){ // Au pire on convertit juste le fichier en UTF 8 pas besoin d'une methode complique
  ofstream myfile;
  string new_name = "log/data_10sensors_1year_utf8.csv"; //path_to_file - ".csv" + "_utf8" + ".csv";
  myfile.open(new_name);
  ifstream fin("log/data_10sensors_1year.csv", ios::binary);
  fin.seekg(0, ios::end);
  size_t size = (size_t)fin.tellg();

  //skip BOM
  fin.seekg(2, ios::beg);
  size -= 2;

  u16string u16((size / 2) + 1, '\0');
  fin.read((char*)&u16[0], size);

  string utf8 = std::wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
  myfile << utf8;
}*/
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Menu::Run()
{
  string lecture("");
  currentMenu = SelectionMenu::M_MENU;

	bool modif = false;

	while (strcmp(lecture.c_str(), "bye") != 0) //On entre dans le menu
	{
		modif = true;

		if (currentMenu == SelectionMenu::M_MENU) // Selection du premier sous menu
		{
			if(strcmp(lecture.c_str(),"5") == 0)
      {
        break;
      }
      else if(strcmp(lecture.c_str(),"1") == 0)
      {
        //put code here
      }
      else if(strcmp(lecture.c_str(),"2") == 0)
      {
        
      }
      else if(strcmp(lecture.c_str(),"3") == 0)
      {
        
      }
      else if(strcmp(lecture.c_str(),"4") == 0)
      {
        
      }
			else
			{
				modif = false;
				cout << endl << "Menu :\n 1 : Connaître la qualité de l’air sur une zone donnée\n 2 : Identifier les zones ayant une qualité de l’air similaire\n 3 : Connaître la qualité de l\'air en un point donné\n 4 : Identifier les capteurs défectueux\n 5 : Quitter\n" << endl;
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

int main(int argc, char* argv[]){
  //utf16_utf8("log/data_10sensors_1year.csv");

  SensorFactory sensorFactory("log/data_10sensors_1year.csv");
  vector<Sensor> capteurs = sensorFactory.GetSensors();
  cout << "Nombre de capteurs effectifs : " << capteurs.size() << endl;
  
  Menu menu;
  menu.Run();

  return 0;
}

