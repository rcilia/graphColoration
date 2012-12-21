/*
 * Vertex.cpp
 *
 *  Created on: 8 nov. 2012
 *      Author: smoreau
 */

#include "Vertex.h"
#include <iostream>

// Constructeurs / Destructeur
Vertex::Vertex(unsigned int id):
	id(id)
{
	this->neighbors = std::vector<Vertex*>();
	this->color = 0;
}

Vertex::Vertex(unsigned int id, std::vector<Vertex*> neighbors):
		id(id), neighbors(neighbors)
{
	this->color = 0;
}

Vertex::Vertex(unsigned int id, unsigned int color):
		id(id), color(color)
{
	this->neighbors = std::vector<Vertex*>();
}

Vertex::Vertex(unsigned int id,std::vector<Vertex*> neighbors, unsigned int color):
		id(id), neighbors(neighbors), color(color)
{}

Vertex::~Vertex()
{}


// Accesseurs
unsigned int Vertex::getId() const
{
	return id;
}

void Vertex::setId(unsigned int id)
{
	this->id = id;
}

const std::vector<Vertex*>& Vertex::getNeighbors() const
		{
	return neighbors;
}

void Vertex::setNeighbors(const std::vector<Vertex*>& neighbors)
{
	this->neighbors = neighbors;
}

unsigned int Vertex::getColor()
{
	return this->color;
}
void Vertex::setColor(unsigned int color)
{
	this->color = color;
}

void Vertex::setAvailableColors(std::set<unsigned int> colors)
{
	this->availableColors = colors;
}

void Vertex::addAvailableColor(unsigned int color)
{
	this->availableColors.insert(color);
}

std::set<unsigned int> Vertex::getAvailableColors()
{
	return this->availableColors;
}

void Vertex::removeAvailableColor(unsigned int color)
{
	this->availableColors.erase(color);
}

unsigned int Vertex::getNextAvailableColor()
{
	return *(this->availableColors.begin());
}

// Méthodes

void Vertex::add_neighbor(Vertex * vertex)
{
	neighbors.push_back(vertex);
}

bool Vertex::neighbors_contains(Vertex * v)
{
	bool exists = false;
	for (unsigned int i = 0; i < this->neighbors.size(); ++i)
	{
		if (this->neighbors[i] == v)
		{
			exists = true;
			break;
		}
	}

	return exists;
}

bool Vertex::are_neighbors_colored(unsigned int color)
{
	bool exists = false;
	for (unsigned int i = 0; i < this->neighbors.size(); ++i)
	{
		if (this->neighbors[i]->getColor() == color)
		{
			exists = true;
			break;
		}
	}

	return exists;
}


// Affichage des données

std::ostream& operator <<(std::ostream& stream, const Vertex & obj)
{
	stream << obj.id << " : ";
	for (unsigned int i = 0; i < obj.neighbors.size(); ++i)
	{
		stream << obj.neighbors[i]->id << "(" << obj.color << ")" << " ";
	}

	stream << std::endl;

	return stream;
}

void Vertex::show()
{
	std::cout << id << " (" << this->color << ")" << " : ";
	for (unsigned int i = 0; i < this->neighbors.size(); ++i)
	{
		std::cout << this->neighbors[i]->id << " ";
	}

	std::cout << std::endl;
}
