/*************************************************************************
                           Analyse  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Analyse> (fichier Analyse.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <vector>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analyse.h"
#include "SensorFactory.h"
#include "Sensor.h"
#include "Geo.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Analyse::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
void Analyse::ValeurIntervalle(SensorFactory &sensorFactory)
{
    vector<string> polluants;
    //récupérer les capteurs de la SensorFactory
    vector<Sensor> listeCapteurs = sensorFactory.GetSensors();
    for (Sensor s : listeCapteurs)
    {
        //si le capteur et dans la zone choisie
        if (Geo::CalculDistance(s.GetLatitude(), s.GetLongitude(), this->latitude, this->longitude) < rayon)
        {
            for (Mesure m : s.GetListeMesure())
            {
                        }
        }
    }
}


void Analyse::CapteursSimilaires(SensorFactory &sensorFactory)
{
	vector<string> polluants;
	vector<Sensor> listeCapteurs = sensorFactory.GetSensors();

	double **matriceCapteurs = new double*[listeCapteurs.size()];
	for (int i = 0; i < listeCapteurs.size(); i++) {
		matriceCapteurs[i] = new double[listeCapteurs.size()];
	}

	double similitudeMesure = 0;
	int compteur = 0;
	for (int i = 0; i < listeCapteurs.size(); i++)
	{
		for (int j = i + 1; j < listeCapteurs.size(); j++)
		{
			for (Mesure m : listeCapteurs[i].GetListeMesure())
			{
				if ((this->debut < m.GetDate()) && (m.GetDate() < this->fin))
				{
					for (Mesure n : listeCapteurs[j].GetListeMesure())
					{
						if (m < n && m.GetPolluant() == n.GetPolluant())
						{
							similitudeMesure += 1 - (m.GetValeur() - n.GetValeur() / m.GetValeur());
							compteur++;
							break;
						}
					}
				}
			}
			matriceCapteurs[i][j] = similitudeMesure / compteur;
			cout << matriceCapteurs[i] << endl;
		}
	}

	for (int i = 0; i < listeCapteurs.size(); i++)
		delete[] matriceCapteurs[i];
	delete[] matriceCapteurs;
}



						




//------------------------------------------------- Surcharge d'opérateurs
/*Analyse & Analyse::operator = ( const Analyse & unAnalyse )
// Algorithme :
//
{
} //----- Fin de operator =*/

//-------------------------------------------- Constructeurs - destructeur
Analyse::Analyse(const Analyse &unAnalyse)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Analyse>" << endl;
#endif
} //----- Fin de Analyse (constructeur de copie)

Analyse::Analyse(double latitude, double longitude, double rayon, date_t debut, date_t fin)
{
    this->latitude = latitude;
    this->longitude = longitude;
    this->rayon = rayon;
    this->debut = debut;
    this->fin = fin;

#ifdef MAP
    cout << "Appel au constructeur de <Analyse>" << endl;
#endif
} //----- Fin de Analyse

Analyse::~Analyse()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Analyse>" << endl;
#endif
} //----- Fin de ~Analyse

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
