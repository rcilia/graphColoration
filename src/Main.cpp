#include "Graph.h"
#include "ColorationEngine.h"
#include <set>

int main() {

	//Graph graph = Graph("tests/graphe1");

	Graph graph = Graph();
	graph.generateRandomKcoloriableGraph(4, 50, 4);

	std::cout << "avant : " << std::endl;
	std::cout << graph << std::endl;

	ColorationEngine ce = ColorationEngine(&graph);

	//ce.nochoiceAlgorithm(4);
	ce.satReduc(3);


	//int usedColors = ce.greedyAlgorithm();
	//std::cout << "nombre de couleurs utilisées : " << usedColors << std::endl;

	std::cout << "après : " << std::endl;
	std::cout << graph << std::endl;

	/*Graph graph = Graph();
	graph.generateRandomKcoloriableGraph(4, 75, 4);
	std::cout << "avant : " << std::endl;
	std::cout << graph << std::endl;

	ColorationEngine ce = ColorationEngine(&graph);
	//int usedColors = ce.greedyAlgorithm();
	ce.backtrackAlgorithm(4);

	std::cout << "après : " << std::endl;
	std::cout << graph << std::endl;
	//std::cout << "nombre de couleurs utilisées : " << usedColors << std::endl;*/
	return 0;
}
