#include "Graph.h"
#include "ColorationEngine.h"


int main() {

	/*
	 * Tests
	 *
	Tests tests = Tests();

<<<<<<< HEAD
	Graph graph = Graph();
	//Graph graph = Graph("graph.txt");
	graph.generateRandomKcoloriableGraph(15, 50, 10);
=======
	tests.testGreedyAlgorithmWithGivenData();
	//tests.testGreedyAlgorithmWithGeneratedGraph();
	tests.testBacktrackAlgorithmWithGivenData();
	tests.testNoChoiceAlgorithmWithGivenData();
>>>>>>> refs/remotes/origin/master

<<<<<<< HEAD
=======

	std::cout << "fini ! " << std::endl ;*/

	//Graph graph = Graph("tests/graphe10");

	//Graph graph = Graph();
	Graph graph = Graph("graph.txt");
	//graph.generateRandomKcoloriableGraph(14, 50, 10);

	//graph.exportGraph();

	std::cout << "avant : " << std::endl;
	std::cout << graph << std::endl;

	ColorationEngine ce = ColorationEngine(&graph);

	//int coloredVertices = ce.nochoiceAlgorithm(4);

	//ce.satReduc(10);
	ce.colorFromSat(10, "output.txt");

	//int usedColors = ce.greedyAlgorithm();
	//std::cout << "nombre de couleurs utilisées : " << usedColors << std::endl;

	std::cout << "après : " << std::endl;
	std::cout << graph << std::endl;

	//std::cout << "Sommets coloriés : " << coloredVertices << std::endl;

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
