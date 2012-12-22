/*
 * ColorationEngine.cpp
 *
 *  Created on: 14 nov. 2012
 *      Author: neoz
 */

#include "ColorationEngine.h"
#include <set>
#include <fstream>
#include <sstream>
#include <stdlib.h>

ColorationEngine::ColorationEngine(Graph* graph):
		verticesSet(graph->getVertices()),
		verticesStack(std::stack<Vertex*>()),
		nbColors(0),
		currentColor(0)
{}

ColorationEngine::~ColorationEngine()
{}

// Greedy Algorithm
int ColorationEngine::greedyAlgorithm()
{

	std::set<int> usedColors;

	// On commence par vider la pile, au cas où elle ne le serait pas déjà
	while (!this->verticesStack.empty())
	{
		this->verticesStack.pop();
	}

	// On remplit la pile avec les sommets (ordre quelconque)
	for (unsigned int i = 0; i < this->verticesSet.size() ; ++i)
	{
		this->verticesStack.push(this->verticesSet[i]);
	}

	int color = 1;
	// Tant que la pile n'est pas vide, on essaie de colorier les sommets
	while (!this->verticesStack.empty())
	{
		// Tant que ce sommet a des voisins de cette couleur,
		// On tente la couleur suivante
		while (this->verticesStack.top()->are_neighbors_colored(color))
		{
			++color;
		}

		// Ce sommet n'a pas de voisins de cette couleur,
		// On peut le colorier et le retirer de la pile
		this->verticesStack.top()->setColor(color);
		this->verticesStack.pop();
		usedColors.insert(color);

		color = 1;
	}

	return usedColors.size();
}

// Backtrack Algorithm
bool ColorationEngine::backtrackAlgorithm(unsigned int nbColors)
{
	// On commence par vider la pile, au cas où elle ne le serait pas déjà
	while (!this->verticesStack.empty())
	{
		this->verticesStack.pop();
	}


	// Liste de toutes les couleurs dispo
	std::set<unsigned int> colors;
	for (unsigned int i = 1; i <= nbColors; ++i)
	{
		colors.insert(i);
	}

	// Initialisation du domaine de couleurs de chaque sommet
	// puis ajout des sommets dans la pile (ordre quelconque)
	for (unsigned int i = 0; i < this->verticesSet.size() ; ++i)
	{
		verticesSet[i]->setAvailableColors(colors);
		this->verticesStack.push(this->verticesSet[i]);
	}

	// Liste des sommets traités
	std::stack<Vertex*> result = std::stack<Vertex*>();

	int currentColor = 0;

	Vertex* currentVertex = verticesStack.top();
	verticesStack.pop();
	currentColor = currentVertex->getNextAvailableColor();
	currentVertex->setColor(currentColor);
	result.push(currentVertex);

	bool test = true;

	currentVertex = verticesStack.top();
	std::set<unsigned int> currentColors = currentVertex->getAvailableColors();

	while (test) {

		currentColor = currentVertex->getNextAvailableColor();
		if (currentColor != 0)
		{
			if (!currentVertex->are_neighbors_colored(currentColor))
			{
				verticesStack.pop();
				currentVertex->setColor(currentColor);
				result.push(currentVertex);
				currentVertex->setAvailableColors(currentColors);

				if (verticesStack.empty())
				{
					test = false; // solution trouvée
				}
				else
				{
					currentVertex = verticesStack.top();
					currentColors = currentVertex->getAvailableColors();
				}
			}
			else
			{
				currentColors.erase(currentColor);
				currentVertex->removeAvailableColor(currentColor);
			}
		}
		else
		{
			verticesStack.push(currentVertex);
			if (!result.empty()) {
				currentVertex = result.top();
				result.pop();
			} else {
				break;
			}

			currentVertex->removeAvailableColor(currentVertex->getColor());
			currentColors = currentVertex->getAvailableColors();
			currentVertex->setColor(0);
		}
	}

	if (result.empty())
	{
		std::cout << "pas de solution" << std::endl;
		return false;
	}
	else
	{
		std::cout << "solution trouvée" << std::endl;
		return true;
	}
}

// No Choice Algorithm
int ColorationEngine::nochoiceAlgorithm(int nbColors)
{
	this->nbColors = nbColors;
	int coloredVertices = 0;

	// On commence par vider la pile, au cas où elle ne le serait pas déjà
	while (!this->verticesStack.empty())
	{
		this->verticesStack.pop();
	}

	// recherche de la plus grande clique
	std::vector<Vertex*> clique = searchClique();
	std::cout << "taille clique : " << clique.size() << std::endl;
	coloredVertices += colorCliqueAndNeighbors(clique);
	coloredVertices += coloringOneColorLeftVertices();

	return coloredVertices;
}

std::vector<Vertex*> ColorationEngine::searchClique()
{
	std::vector<Vertex*> clique = std::vector<Vertex*>();
	std::vector<Vertex*> vertices = std::vector<Vertex*>(this->verticesSet);
	std::vector<Vertex*> neighbors;

	Vertex * highestDegreeVertex = NULL;
	while(!vertices.empty())
	{
		// On récupère le sommet de plus haut degrès
		highestDegreeVertex = getHighestDegreeVertex(vertices);

		// On l'ajoute à la clique
		if (!vertexVectorContains(clique, highestDegreeVertex))
		{
			clique.push_back(highestDegreeVertex);
		}

		// On garde dans la liste seulement ceux qui sont voisins
		// avec le sommet de plus haut degrès
		retainAll(vertices, highestDegreeVertex->getNeighbors());
	}

	return clique;
}

int ColorationEngine::colorCliqueAndNeighbors(std::vector<Vertex*> clique)
{
	int coloredVertices = 0;

	std::vector<Vertex*> vertices = std::vector<Vertex*>(this->verticesSet);

	// On colorie chaque sommet de la clique d'une couleur différente
	for (std::vector<Vertex*>::iterator it = clique.begin() ; it != clique.end() ; ++it)
	{
		if ((*it)->getColor() == 0) {
			(*it)->setColor(this->getNextColor());
			++coloredVertices;
		}
	}

	// On supprime de la liste des sommets tous ceux qui sont dans la clique
	removeAll(vertices, clique);

	// On ajoute toutes les couleurs disponibles aux sommets restants dans la liste
	std::set<unsigned int> colors = std::set<unsigned int>();
	for (int i = 1; i <= nbColors ; ++i)
	{
		colors.insert(i);
	}
	for (std::vector<Vertex*>::iterator it = vertices.begin() ; it != vertices.end() ; ++it)
	{
		(*it)->setAvailableColors(colors);
	}

	// Pour chaque élément de la clique...
	for (std::vector<Vertex*>::iterator it = clique.begin() ; it != clique.end() ; ++it)
	{
		std::vector<Vertex*> adj = std::vector<Vertex*>((*it)->getNeighbors());

		// On supprime de la liste des voisins tous ceux qui sont dans la clique
		removeAll(adj, clique);

		for (std::vector<Vertex*>::iterator itAdj = adj.begin() ; itAdj != adj.end() ; ++itAdj)
		{
			(*itAdj)->removeAvailableColor((*it)->getColor());

			if ((*itAdj)->getAvailableColors().size() == 1 && !vertexStackContains(verticesStack, (*itAdj)))
			{
				verticesStack.push((*itAdj));
			}
		}

	}

	return coloredVertices;
}

int ColorationEngine::coloringOneColorLeftVertices()
{
	int coloredVertices = 0;
	Vertex * currentVertex = NULL;

	while (!verticesStack.empty())
	{
		currentVertex = verticesStack.top();
		verticesStack.pop();

		if (currentVertex->getColor() == 0) {
			currentVertex->setColor(*(currentVertex->getAvailableColors().begin()));
			++coloredVertices;
			currentVertex->getAvailableColors().clear();
		}

		// Pour chaque voisin du sommet qu'on vient de colorier,
		// On enlève la couleur de ce sommet à la liste des couleurs
		// disponibles pour le voisin
		// Si après ça, le voisin n'a plus qu'une couleur dispo,
		// On le rajoute à la pile pour le colorier
		std::vector<Vertex*> adj = std::vector<Vertex*>(currentVertex->getNeighbors());
		for (std::vector<Vertex*>::iterator itAdj = adj.begin() ; itAdj != adj.end() ; ++itAdj)
		{
			if ((*itAdj)->getColor() == 0)
			{
				(*itAdj)->removeAvailableColor(currentVertex->getColor());

				if ((*itAdj)->getAvailableColors().size() == 1 && !vertexStackContains(verticesStack, (*itAdj)))
				{
					verticesStack.push((*itAdj));
				}
			}
		}
	}

	return coloredVertices;
}

Vertex* ColorationEngine::getHighestDegreeVertex(std::vector<Vertex*> vertices)
{
	Vertex *toReturn = NULL;

	//std::set<Vertex>::iterator it = this->verticesSet.begin();
	for (unsigned int i = 0 ; i < vertices.size() ; ++i)
	{
		if (toReturn == NULL)
		{
			toReturn = vertices[i];
		}
		else
		{
			if ( vertices[i]->getNeighbors().size() > toReturn->getNeighbors().size() )
			{
				toReturn = vertices[i];
			}
		}
	}

	return toReturn;
}

int ColorationEngine::getNextColor()
{
	currentColor = (currentColor >= nbColors) ? 1 : currentColor + 1;

	return currentColor;
}

bool ColorationEngine::vertexStackContains(std::stack<Vertex*> s, Vertex* v)
{
	bool contains = false;
	std::stack<Vertex*> stack = std::stack<Vertex*>(s);

	Vertex* currentVertex;

	while (!stack.empty())
	{
		currentVertex = stack.top();
		stack.pop();

		if (currentVertex->getId() == v->getId())
		{
			contains = true;
			break;
		}
	}

	return contains;
}

bool ColorationEngine::vertexVectorContains(std::vector<Vertex*> vector, Vertex* v)
{
	bool contains = false;

	for (std::vector<Vertex*>::iterator it = vector.begin() ; it != vector.end() ; ++it)
	{
		if ((*it)->getId() == v->getId())
		{
			contains = true;
			break;
		}
	}

	return contains;
}

void ColorationEngine::retainAll(std::vector<Vertex*>& vector, std::vector<Vertex*> toRetain)
{
	for (std::vector<Vertex*>::iterator it = vector.begin() ; it != vector.end() ; ++it)
	{
		if (!vertexVectorContains(toRetain, (*it)))
		{
			vector.erase(it);
			break;
		}
	}
}

void ColorationEngine::removeAll(std::vector<Vertex*>& vector, std::vector<Vertex*> toRemove)
{
	for (std::vector<Vertex*>::iterator it = vector.begin() ; it != vector.end() ; ++it)
	{
		if (vertexVectorContains(toRemove, (*it)))
		{
			vector.erase(it);
			break;
		}
	}
}

std::string toString(const int nb)
{
   std::ostringstream oss;
   oss << nb;
   return oss.str();
}

void ColorationEngine::satReduc(unsigned int nbColors)
{
	// Une variable est composé du numéro de couleur et de l'identidiant du sommet
	// L'identifiant du sommet doit être compris entre 0 et 999 et est écrit sur 3 chiffres, ce qui permet
	// de pouvoir extraire le numéro de la couleur et l'identifiant du sommet simplement

	// La négation d'une variable est écrite avec le préfixe -

	// On crée le fichier test.txt qui comportera les formules
	std::ofstream fichier("input.txt", std::ios::out | std::ios::trunc);

	if(fichier)
	{
			fichier << "p cnf" << std::endl;
			fichier << std::endl;
			fichier << "c ************************************************" << std::endl;
			fichier << "c ***** Chaque sommet a au moins une couleur *****" << std::endl;
			fichier << "c ************************************************" << std::endl;

			// Formule 1 : Chaque sommet a au moins une couleur
			for (unsigned int i = 0; i < this->verticesSet.size() ; ++i)
			{
				fichier << "c ** Sommet " << this->verticesSet[i]->getId() << " **" << std::endl;
				std::string clause;
				for(unsigned int j = 1; j <= nbColors; ++j)
				{
					// chaque numéro de couleur doit être codé avec le même nombre de chiffres.
					// Si 0 < nbColors < 10 : la couleur numéro 3 sera codée 3
					// Si 10 < nbColors < 100 : la couleur numéro 3 sera codée 03
					// Si 100 < nbColors < 1000 : la couleur numéro 3 sera codée 003
					// ...
					std::string prefixNumColors;
					for(int k = 0; k < (toString(nbColors).length() - toString(j).length()); ++k)
					{
						prefixNumColors += "0";
					}

					// Chaque identifiant de sommet doit être codé avec 3 chiffres.
					// Le sommet 3 sera codé 003
					std::string prefixNumVertex;
					for(int k = 0; k < (3 - toString(this->verticesSet[i]->getId()).length()); ++k)
					{
						prefixNumVertex += "0";
					}

					clause += prefixNumColors + toString(j) + prefixNumVertex + toString(this->verticesSet[i]->getId()) + " ";

				}

				// Chaque clause doit se terminer par 0 pour Minisat
				fichier << clause << "0" << std::endl;
			}
			fichier << std::endl;
			fichier << "c ***********************************************" << std::endl;
			fichier << "c ***** Chaque sommet a au plus une couleur *****" << std::endl;
			fichier << "c ***********************************************" << std::endl;

			// Formule 2 : Chaque sommet a au plus une couleur
			for (unsigned int i = 0; i < this->verticesSet.size(); ++i)
			{
				fichier << "c ** Sommet " << this->verticesSet[i]->getId() << " **" << std::endl;

				unsigned int colorExept = 1;
				for(unsigned int j = 1; j <= nbColors; ++j)
				{
					std::string clause;
					for(unsigned int k = 1; k <= nbColors; ++k)
					{
						std::string prefixNumColors;
						for(int l = 0; l < (toString(nbColors).length() - toString(k).length()); ++l)
						{
							prefixNumColors += "0";
						}

						std::string prefixNumVertex;
						for(int l = 0; l < (3 - toString(this->verticesSet[i]->getId()).length()); ++l)
						{
							prefixNumVertex += "0";
						}

						if(k != colorExept)
						{
							clause += "-" + prefixNumColors + toString(k) + prefixNumVertex + toString(this->verticesSet[i]->getId()) + " ";
						}
					}
					fichier << clause << "0" << std::endl;
					++colorExept;
				}
			}
			fichier << std::endl;
			fichier << "c ******************************************************************" << std::endl;
			fichier << "c ***** Deux sommets voisins ne comportent pas la même couleur *****" << std::endl;
			fichier << "c ******************************************************************" << std::endl;

			//Formule 3 : Deux sommets voisins ne comportent pas la même couleur
			for (unsigned int i = 0; i < this->verticesSet.size(); ++i)
			{
				for(unsigned int j = 0; j < this->verticesSet[i]->getNeighbors().size(); ++j)
				{
					fichier << "c ** Arrête entre les sommets " << this->verticesSet[i]->getId() << " et " << this->verticesSet[i]->getNeighbors()[j]->getId() << " **" << std::endl;
					for(unsigned int k = 1; k <= nbColors; ++k)
					{
						std::string prefixNumColors;
						for(int l = 0; l < (toString(nbColors).length() - toString(k).length()); ++l)
						{
							prefixNumColors += "0";
						}

						std::string prefixNumVertex;
						for(int l = 0; l < (3 - toString(this->verticesSet[i]->getId()).length()); ++l)
						{
							prefixNumVertex += "0";
						}

						std::string clause = "-" + prefixNumColors + toString(k) + prefixNumVertex + toString(this->verticesSet[i]->getId()) +
								" -" + prefixNumColors +toString(k) + prefixNumVertex + toString(this->verticesSet[i]->getNeighbors()[j]->getId()) + " 0";
						fichier << clause << std::endl;
					}
				}
			}

			fichier.close();

			std::cout << "Le fichier input.txt a été créé. Il contient les formules de la réduction vers SAT" << std::endl;
			std::cout << "Vous devez utiliser MiniSat à partir de ce fichier afin de déterminer si le problème est satisfaisable" << std::endl;
	}
	else
		std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;

}

void ColorationEngine::colorFromSat(unsigned int nbColors, std::string filePath)
{
	// Le fichier donné en paramètre comporte la solution trouvée par Minisat
	//

	std::ifstream fichier(filePath.c_str(), std::ios::in);

	if (fichier)
	{
		std::string ligne;
		int i = 0;
		while(getline(fichier, ligne))
		{
			if (i == 1)
			{
				// On lit séparément chaque variable
				std::string val;
				std::stringstream stream(ligne);
				while(getline(stream, val, ' '))
				{
					if (val != "" && val[0] != '-' && val != "0")
					{
						// Une variable représentant le sommet 12 avec la couleur 5 peut être écrite 5012, 05012 ou encore  005012 ... (voir explications satReduc() )
						// Or MiniSat supprime les 0 au début de chaque variable, mais il est très important de garder le même nombre de chiffre codant une couleur
						// Nous comblons donc le les 0 supprimés par MiniSat
						for(int j = 0; j < ( (toString(nbColors).length() + 3) - val.length()); ++j)
						{
							val.insert(0, "0");
						}

						// on extrait le numéro de couleur et l'identifiant du sommet
						std::string color = val.substr(0, toString(nbColors).length());
						std::string idVertex = val.substr(toString(nbColors).length(), val.length());

						//std::cout << "vertex : " << idVertex << " , color : " << color << std::endl;

						// On supprime les zéros inutiles aux identifiants des sommets
						std::string vertex;
						if(idVertex[0] == '0' && idVertex[1] == '0')
						{
							 vertex = idVertex.substr(2, idVertex.length());
						}
						else if(idVertex[0] == '0' && idVertex[1] != '0')
						{
							vertex = idVertex.substr(1, idVertex.length());
						}
						else
						{
							vertex = idVertex;
						}

						// On assigne les couleurs aux sommets
						for (unsigned int i = 0; i < this->verticesSet.size(); ++i)
						{
							if(toString(this->verticesSet[i]->getId()) == vertex)
							{
								this->verticesSet[i]->setColor(atoi(color.c_str()));
							}
						}
					}
				}
			}
			++i;
		}

		fichier.close();
	}
	else
	{
		std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
	}
}

