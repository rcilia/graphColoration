/*
 * Tests.cpp
 *
 *  Created on: 20 déc. 2012
 *      Author: zorro
 */

#include "Tests.h"

#define TIME_DIFF(t1, t2) \
	((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))
struct timeval t1, t2;

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

// Tests utilisant les 12 graphes donnés
void Tests::testGreedyAlgorithmWithGivenData(){
	unsigned long time;
	int nbColors=0 ;

	std::cout << std::endl << "Test de l'algorithme glouton avec les graphes fournis :" << std::endl ;

	for (int i = 1 ; i <=12 ; ++i){
		std::ostringstream stm ;
		stm << i ;
		std::string filePath = "graphe" + stm.str() ;

		Graph graph = Graph("tests/"+filePath);
		ColorationEngine ce = ColorationEngine(&graph);


		 gettimeofday(&t1,NULL);
		 nbColors = ce.greedyAlgorithm();
		 gettimeofday(&t2,NULL);
		 time = TIME_DIFF(t1,t2);

		std::cout << filePath << " : " << nbColors << " colors / execution time : " << time << " us"<< std::endl ;
	}
}

// Tests utilisant des graphes aleatoires k-coloriables
void Tests::testGreedyAlgorithmWithGeneratedGraph(){
	unsigned long time;
	Graph graph = Graph();

	ColorationEngine ce = ColorationEngine(&graph);
	//std::cout << ce.greedyAlgorithm() << std::endl ;

	std::ofstream outFile("tests/data", std::ios::out | std::ios::trunc);
	if ( outFile ) {

		for (int i=10 ; i<=150 ; i+=5) {
			time = 0.;
			for (int j=0 ; j<10 ; ++j){
				graph.generateRandomKcoloriableGraph(i, 50 , 5);
				ColorationEngine ce = ColorationEngine(&graph);
				gettimeofday(&t1,NULL);
				ce.greedyAlgorithm();
				gettimeofday(&t2,NULL);
				time += TIME_DIFF(t1,t2);
			}

			outFile << i << " " << time/10 << std::endl ;

		}

		outFile.close();
	}
}

// Tests utilisant les 12 graphes donnés
void Tests::testBacktrackAlgorithmWithGivenData(){
	unsigned long time;

	std::cout << std::endl << "Test de l'algorithme de backtracking avec les graphes fournis :" << std::endl ;

	for (int i = 1 ; i <=12 ; ++i){
		std::ostringstream stm ;
		stm << i ;
		std::string filePath = "graphe" + stm.str() ;

		Graph graph = Graph("tests/"+filePath);
		ColorationEngine ce = ColorationEngine(&graph);

		for (int j = 3 ; j <= 10 ; ++j){

			std::cout <<  filePath << " avec une " << j << "-coloration : " ;
			 gettimeofday(&t1,NULL);
			 ce.backtrackAlgorithm(j) ;
			 gettimeofday(&t2,NULL);
			 time = TIME_DIFF(t1,t2);

			std::cout << " / execution time : " << time << " us"<< std::endl ;
		}

		std::cout << std::endl ;
	}
}

void Tests::testBacktrackAlgorithmWithGeneratedGraph(){


}

// Tests utilisant les 12 graphes donnés
void Tests::testNoChoiceAlgorithmWithGivenData(){
	unsigned long time;

	std::cout << std::endl << "Test de l'algorithme \"no choice \" avec les graphes fournis :" << std::endl ;

	for (int i = 1 ; i <=12 ; ++i){
		std::ostringstream stm ;
		stm << i ;
		std::string filePath = "graphe" + stm.str() ;

		Graph graph = Graph("tests/"+filePath);
		ColorationEngine ce = ColorationEngine(&graph);

		for (int j = 4 ; j <= 10 ; ++j){
			std::cout <<  filePath << " avec une " << j << "-coloration : " ;
			 gettimeofday(&t1,NULL);
			 ce.nochoiceAlgorithm(j);
			 gettimeofday(&t2,NULL);
			 time = TIME_DIFF(t1,t2);

			std::cout << " / execution time : " << time << " us"<< std::endl ;
		}

		std::cout << std::endl ;
	}
}

void Tests::testNoChoiceAlgorithmWithGeneratedGraph(){


}

// Tests utilisant les 12 graphes donnés
void Tests::testSatReductionWithGivenData(){


}

void Tests::testSatReductionWithGeneratedGraph(){


}
