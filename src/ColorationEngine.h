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
	void backtrackAlgorithm(unsigned int nbColors);
	void nochoiceAlgorithm(int nbColors);
	void satReduc(unsigned int nbColors);
	void colorFromSat(unsigned int nbColors, std::string filePath);
	std::vector<Vertex*> searchClique();
	void colorCliqueAndNeighbors(std::vector<Vertex*> clique);
	void coloringOneColorLeftVertices();
	Vertex* getHighestDegreeVertex(std::vector<Vertex*> vertices);
	int getNextColor();
	bool vertexStackContains(std::stack<Vertex*> s, Vertex* v);
};

#endif /* COLORATIONENGINE_H_ */
