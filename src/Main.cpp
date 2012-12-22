#include "Graph.h"
#include "ColorationEngine.h"
#include <stdlib.h>


void choixalgo(Graph graph)
{
	std::cout << std::endl;
	std::cout << "Graphe colorié : " << std::endl;
	std::cout << graph << std::endl;

	ColorationEngine ce = ColorationEngine(&graph);
	std::string algo;
	std::cout << "Veuillez choisir un algorithme de coloration " << std::endl;
	std::cout << "\t1 : Algorithme Glouton" << std::endl;
	std::cout << "\t2 : Algorithme Backtrack" << std::endl;
	std::cout << "\t3 : Algorithme no-choice " << std::endl;
	std::cout << "\t4 : Réduction vers SAT " << std::endl;
	std::cout << "Choix : ";
	std::cin >> algo;

	if(algo == "1")
	{
		int nbVertex = ce.greedyAlgorithm();
	}
	else if(algo == "2")
	{
		std::string nbColors;
		std::cout << "Veuillez définir le nombre de couleurs : ";
		std::cin >> nbColors;
		bool isDec = ce.backtrackAlgorithm(atoi(nbColors.c_str()));
	}
	else if(algo == "3")
	{
		std::string nbColors;
		std::cout << "Veuillez définir le nombre de couleurs : ";
		std::cin >> nbColors;
		bool isDec = ce.nochoiceAlgorithm(atoi(nbColors.c_str()));
	}
	else if(algo == "4")
	{
		std::string nbColors;
		std::cout << "Veuillez définir le nombre de couleurs : ";
		std::cin >> nbColors;
		ce.satReduc(atoi(nbColors.c_str()));

		std::string path;
		std::cout << "Veuillez indiquer le chemin vers le fichier généré par MiniSat contenant les évaluations des variables" << std::endl;
		std::cout << "Chemin du fichier :";
		std::cin >> path;

		ce.colorFromSat(atoi(nbColors.c_str()), path);

	}

	std::cout << "Graphe sans couleurs : " << std::endl;
	std::cout << graph << std::endl;

}

int main() {

	std::string choix_graphe;

	std::cout << "Veuillez choisir comment créer le graphe" << std::endl;
	std::cout << "\t1 : Générer un graphe aléatoire" << std::endl;
	std::cout << "\t2 : Générer un graphe aléatoire k-coloriable" << std::endl;
	std::cout << "\t3 : Générer un graphe à partir d'un fichier " << std::endl;
	std::cout << std::endl;
	std::cout << "Entrez le numéro correspondant : ";
	std::cin >> choix_graphe;;

	if(choix_graphe == "1")
	{
		std::string nbVertex;
		std::string proba;
		std::cout << "Veuillez renseigner le nombre de sommets : ";
		std::cin >> nbVertex;
		std::cout << "Veuillez renseigner le taux de probabilité des arêtes : ";
		std::cin >> proba;
		std::cout << std::endl;

		Graph graph = Graph();
		graph.generateRandomGraph(atoi(nbVertex.c_str()), atoi(proba.c_str()));
		choixalgo(graph);
	}
	else if(choix_graphe == "2")
	{
		std::string nbVertex;
		std::string proba;
		std::string nbColors;
		std::cout << "Veuillez renseigner le nombre de sommets : ";
		std::cin >> nbVertex;
		std::cout << "Veuillez renseigner le taux de probabilité des arêtes : ";
		std::cin >> proba;
		std::cout << "Veuillez renseigner le nombre de couleurs : ";
		std::cin >> nbColors;
		std::cout << std::endl;

		Graph graph = Graph();
		graph.generateRandomKcoloriableGraph(atoi(nbVertex.c_str()), atoi(proba.c_str()), atoi(nbColors.c_str()));
		choixalgo(graph);
	}
	else if(choix_graphe == "3")
	{
		std::string path;
		std::cout << "Veuillez renseigner le chemin du fichier contenant la définition du graphe : ";
		std::cin >> path;

		Graph graph = Graph(path);
		choixalgo(graph);
	}

	/*
	 * Tests
	 *
	Tests tests = Tests();

	tests.testGreedyAlgorithmWithGivenData();
	//tests.testGreedyAlgorithmWithGeneratedGraph();
	tests.testBacktrackAlgorithmWithGivenData();
	tests.testNoChoiceAlgorithmWithGivenData();

	std::cout << "fini ! " << std::endl ;*/

	//Graph graph = Graph("tests/graphe10");

	//Graph graph = Graph();
	//Graph graph = Graph("graph.txt");
	//graph.generateRandomKcoloriableGraph(14, 50, 10);

	//graph.exportGraph();

	//std::cout << "avant : " << std::endl;
	//std::cout << graph << std::endl;

	//ColorationEngine ce = ColorationEngine(&graph);

	//int coloredVertices = ce.nochoiceAlgorithm(4);

	//ce.satReduc(10);
	//ce.colorFromSat(10, "output.txt");

	//int usedColors = ce.greedyAlgorithm();
	//std::cout << "nombre de couleurs utilisées : " << usedColors << std::endl;

	//std::cout << "après : " << std::endl;
	//std::cout << graph << std::endl;

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
