/*
 * Graph.cpp
 *
 *  Created on: 8 nov. 2012
 *      Author: smoreau
 */

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

#include <stdlib.h>
#include <time.h>


using namespace std;

// Constructeurs / Destructeur
Graph::Graph()
{
	this->vertices = std::vector<Vertex*>();
}

Graph::Graph(std::vector<Vertex*> vertices):
		vertices(vertices)
{}

Graph::Graph(std::string filepath)
{
    ifstream fichier(filepath.c_str(), ios::in);

	if (fichier)
	{
		int nb_vertices = 0;
		int vertex_num = 0;

		string neighbor_num;
		string neighbors;

		string ligne;
		int i = 0;
		while(getline(fichier, ligne))
		{
			// Sur la première ligne, on récupère le nombre de sommets,
			// Puis on les ajoute au graphe
			if (i == 0)
			{
				nb_vertices = atoi(ligne.c_str());;

				for (int j = 0 ; j < nb_vertices ; ++j)
				{
					this->vertices.push_back(new Vertex(j));
				}
			}

			// Pour toutes les autres lignes...
			else
			{
				// On récupère le numéro du sommet courant
				vertex_num = atoi(ligne.substr(0, ligne.find_first_of(":")).c_str());

				// La liste des ses voisins
				neighbors = ligne.substr(ligne.find_first_of(":") + 1, ligne.size()).c_str();

				// On ajoute chaque élément de la liste aux voisins de ce sommet
				stringstream stream(neighbors);
				while(getline(stream, neighbor_num, ' '))
				{
					if (neighbor_num != "")
					{
						this->vertices[vertex_num]->add_neighbor(this->vertices[atoi(neighbor_num.c_str())]);
						//cout << neighbor_num.c_str() << endl;
					}
				}
				//this->vertices[vertex_num]->add_neighbor();
			}
			++i;
		}

		fichier.close();
	}
	else
	{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
}

Graph::~Graph() {

}


// Accesseurs
const std::vector<Vertex*>& Graph::getVertices() const
{
	return vertices;
}

void Graph::setVertices(const std::vector<Vertex*>& vertices)
{
	this->vertices = vertices;
}


// Méthodes
void Graph::generateRandomGraph(int nb_vertices, int prob)
{
	srand(time(NULL));

	for(int i = 0; i < nb_vertices; ++i)
	{
		this->vertices.push_back(new Vertex(i));
	}

	for (unsigned int i = 0; i < this->vertices.size(); ++i)
	{
		for (unsigned int j = 0; j < this->vertices.size(); ++j)
		{
			if (i != j) {
				int p = rand() % 100;
				if (prob - p >= 0)
				{
					if (!this->vertices[i]->neighbors_contains(this->vertices[j]))
					{
						this->vertices[i]->add_neighbor(this->vertices[j]);
					}

					if (!this->vertices[j]->neighbors_contains(this->vertices[i]))
					{
						this->vertices[j]->add_neighbor(this->vertices[i]);
					}
				}

			}
		}
	}
}

void Graph::generateRandomKcoloriableGraph(int nb_vertices, int prob, int chrom)
{
	++chrom;
	srand(time(NULL));

	int colorRand = 0;/*rand() % (chrom-1) + 1;*/
	for(int i = 0; i < nb_vertices; ++i)
	{
		colorRand = rand() % (chrom-1) + 1;
		this->vertices.push_back(new Vertex(i, colorRand));
		//std::cout << "rand : " << colorRand << std::endl;
	}

	for (unsigned int i = 0; i < this->vertices.size(); ++i)
	{
		for (unsigned int j = 0; j < this->vertices.size(); ++j)
		{
			if (i != j && this->vertices[i]->getColor() != this->vertices[j]->getColor()) {
				int p = rand() % 100;
				if (prob - p >= 0)
				{
					if (!this->vertices[i]->neighbors_contains(this->vertices[j]))
					{
						this->vertices[i]->add_neighbor(this->vertices[j]);
					}

					if (!this->vertices[j]->neighbors_contains(this->vertices[i]))
					{
						this->vertices[j]->add_neighbor(this->vertices[i]);
					}
				}

			}
		}
	}

	for(int i = 0; i < nb_vertices; ++i)
	{
		this->vertices[i]->setColor(0);
	}
}


std::ostream& operator <<(std::ostream& stream, const Graph & obj)
{
	for (unsigned int i = 0; i < obj.vertices.size(); ++i)
	{
		obj.vertices[i]->show();
	}

    return stream;
}
