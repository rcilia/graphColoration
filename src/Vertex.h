/*
 * Vertex.h
 *
 *  Created on: 8 nov. 2012
 *      Author: smoreau
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>
#include <iostream>
#include <set>

class Vertex {
	friend std::ostream& operator <<(std::ostream&, const Vertex&);

private:
	unsigned int id;
	std::vector<Vertex*> neighbors;
	unsigned int color;
	std::set<unsigned int> availableColors;

public:
	Vertex(unsigned int id);
	Vertex(unsigned int id, unsigned int color);
	Vertex(unsigned int id, std::vector<Vertex*> neighbors);
	Vertex(unsigned int id, std::vector<Vertex*> neighbors, unsigned int color);
	virtual ~Vertex();

	bool neighbors_contains(Vertex * v);
	bool are_neighbors_colored(unsigned int color);
	void add_neighbor(Vertex * vertex);
	void show();

	unsigned int getId() const;
	void setId(unsigned int id);
	const std::vector<Vertex*>& getNeighbors() const;
	void setNeighbors(const std::vector<Vertex*>& neighbors);
	unsigned int getColor();
	void setColor(unsigned int color);

	void setAvailableColors(std::set<unsigned int> colors);
	void addAvailableColor(unsigned int color);
	std::set<unsigned int> getAvailableColors();
	void removeAvailableColor(unsigned int color);
	unsigned int getNextAvailableColor();

};

std::ostream& operator <<(std::ostream& stream, const Vertex & obj);

#endif /* VERTEX_H_ */
