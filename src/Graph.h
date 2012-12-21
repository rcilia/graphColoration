/*
 * Graph.h
 *
 *  Created on: 8 nov. 2012
 *      Author: smoreau
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>
#include "Vertex.h"

class Graph {
	friend std::ostream& operator <<(std::ostream&, const Graph&);

private:
	std::vector<Vertex*> vertices;

public:
	Graph();
	Graph(std::vector<Vertex*> vertices);
	Graph(std::string filepath);
	virtual ~Graph();

	void generateRandomGraph(int nb_vertices, int prob);
	void generateRandomKcoloriableGraph(int nb_vertices, int prob, int chrom);
	const std::vector<Vertex*>& getVertices() const;
	void setVertices(const std::vector<Vertex*>& vertices);
	void show();
};

std::ostream& operator <<(std::ostream& stream, const Graph & obj);

#endif /* GRAPH_H_ */
