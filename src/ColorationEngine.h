/*
 * ColorationEngine.h
 *
 *  Created on: 14 nov. 2012
 *      Author: neoz
 */

#ifndef COLORATIONENGINE_H_
#define COLORATIONENGINE_H_

#include <stack>
#include <vector>
#include "Graph.h"
#include "Vertex.h"

class ColorationEngine {

private:
	std::vector<Vertex*> verticesSet;
	std::stack<Vertex*> verticesStack;
	int nbColors;
	int currentColor;

public:
	ColorationEngine(Graph* graph);
	virtual ~ColorationEngine();

	int greedyAlgorithm();
	bool backtrackAlgorithm(unsigned int nbColors);
	int nochoiceAlgorithm(int nbColors);
	void satReduc(unsigned int nbColors);
	std::vector<Vertex*> searchClique();
	int colorCliqueAndNeighbors(std::vector<Vertex*> clique);
	int coloringOneColorLeftVertices();
	Vertex* getHighestDegreeVertex(std::vector<Vertex*> vertices);
	int getNextColor();
	bool vertexStackContains(std::stack<Vertex*> s, Vertex* v);
	bool vertexVectorContains(std::vector<Vertex*> vector, Vertex* v);
	void retainAll(std::vector<Vertex*>& vector, std::vector<Vertex*> toRetain);
	void removeAll(std::vector<Vertex*>& vector, std::vector<Vertex*> toRemove);
};

#endif /* COLORATIONENGINE_H_ */
