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
void ColorationEngine::backtrackAlgorithm(unsigned int nbColors)
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

			/*std::set<unsigned int>::iterator it = currentColors.begin() ;
			for (it ; it != currentColors.end() ; it ++)
			{
				std::cout << *it << std::endl;
			}
			std::cout << std::endl;*/



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
	}
	else
	{
		std::cout << "solution trouvée" << std::endl;
	}
}

// No Choice Algorithm
void ColorationEngine::nochoiceAlgorithm(int nbColors)
{
	this->nbColors = nbColors;

	// On commence par vider la pile, au cas où elle ne le serait pas déjà
	while (!this->verticesStack.empty())
	{
		this->verticesStack.pop();
	}

	// recherche de la plus grande clique
	std::vector<Vertex*> clique = searchClique();
	colorCliqueAndNeighbors(clique);
	coloringOneColorLeftVertices();
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
		clique.push_back(highestDegreeVertex);

		// On supprime de la liste des sommets tous ceux qui ne sont pas voisin
		// du sommet de plus haut degrès
		neighbors = std::vector<Vertex*>(highestDegreeVertex->getNeighbors());
		for (std::vector<Vertex*>::iterator it = neighbors.begin() ; it != neighbors.end() ; ++it)
		{
			for (std::vector<Vertex*>::iterator it2 = vertices.begin() ; it2 != vertices.end() ; ++it2)
			{
				if ((*it)->getId() != (*it2)->getId())
				{
					vertices.erase(it2);
					break;
				}
			}
		}
	}

	return clique;
}

void ColorationEngine::colorCliqueAndNeighbors(std::vector<Vertex*> clique)
{
	std::vector<Vertex*> vertices = std::vector<Vertex*>(this->verticesSet);

	// On colorie chaque sommet de la clique d'une couleur différente
	for (std::vector<Vertex*>::iterator it = clique.begin() ; it != clique.end() ; ++it)
	{
		(*it)->setColor(this->getNextColor());
	}

	// On supprime de la liste des sommets tous ceux qui sont dans la clique
	for (std::vector<Vertex*>::iterator it = clique.begin() ; it != clique.end() ; ++it)
	{
		for (std::vector<Vertex*>::iterator it2 = vertices.begin() ; it2 != vertices.end() ; ++it2)
		{
			if ((*it)->getId() == (*it2)->getId())
			{
				vertices.erase(it2);
				break;
			}
		}
	}

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


	for (std::vector<Vertex*>::iterator it = clique.begin() ; it != clique.end() ; ++it)
	{
		std::vector<Vertex*> adj = std::vector<Vertex*>((*it)->getNeighbors());

		// On supprime de la liste des voisins tous ceux qui sont dans la clique
		for (std::vector<Vertex*>::iterator itClique = clique.begin() ; itClique != clique.end() ; ++itClique)
		{
			for (std::vector<Vertex*>::iterator it2 = adj.begin() ; it2 != adj.end() ; ++it2)
			{
				if ((*itClique)->getId() == (*it2)->getId())
				{
					adj.erase(it2);
					break;
				}
			}
		}

		for (std::vector<Vertex*>::iterator itAdj = adj.begin() ; itAdj != adj.end() ; ++itAdj)
		{
			(*itAdj)->removeAvailableColor((*it)->getColor());

			if ((*itAdj)->getAvailableColors().size() == 1 && !vertexStackContains(verticesStack, (*itAdj)))
			{
				verticesStack.push((*itAdj));
			}
		}

	}
}

void ColorationEngine::coloringOneColorLeftVertices()
{
	Vertex * currentVertex = NULL;

	while (!verticesStack.empty())
	{
		currentVertex = verticesStack.top();
		verticesStack.pop();
		currentVertex->setColor(*(currentVertex->getAvailableColors().begin()));
		currentVertex->getAvailableColors().clear();

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
			if ((vertices[i]->getNeighbors().size() > toReturn->getNeighbors().size()))
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


std::string toString(const int nb)
{
   std::ostringstream oss;
   oss << nb;
   return oss.str();
}

void ColorationEngine::satReduc(unsigned int nbColors)
{


	// Variable : num_color + num_vertex

	std::ofstream fichier("test.txt", std::ios::out | std::ios::trunc);

	if(fichier)
	{
			fichier << "p cnf" << std::endl;

			//Chaque sommet a au moins une couleur
			for (unsigned int i = 0; i < this->verticesSet.size() ; ++i)
			{
				std::string clause;
				for(unsigned int j = 1; j <= nbColors; ++j)
				{
					clause += toString(j) + toString(this->verticesSet[i]->getId()) + " ";
				}

				fichier << clause << "0" << std::endl;
			}

			//Chaque sommet a au plus une couleur
			for (unsigned int i = 0; i < this->verticesSet.size(); ++i)
			{
				unsigned int colorExept = 1;
				for(unsigned int j = 1; j <= nbColors; ++j)
				{
					std::string clause;
					for(unsigned int k = 1; k <= nbColors; ++k)
					{
						if(k != colorExept)
						{
							clause += "-" + toString(k) + toString(this->verticesSet[i]->getId()) + " ";
						}
					}
					fichier << clause << "0" << std::endl;
					++colorExept;
				}
			}

			//Deux sommets voisins ne comportent pas la même couleur
			for (unsigned int i = 0; i < this->verticesSet.size(); ++i)
			{
				for(unsigned int j = 0; j < this->verticesSet[i]->getNeighbors().size(); ++j)
				{
					for(unsigned int k = 1; k <= nbColors; ++k)
					{
						std::string clause = "-" + toString(k) + toString(this->verticesSet[i]->getId()) +
								" -" + toString(k) + toString(this->verticesSet[i]->getNeighbors()[j]->getId()) + " 0";
						fichier << clause << std::endl;
					}
				}
			}

			fichier.close();
	}
	else
		std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;

}

