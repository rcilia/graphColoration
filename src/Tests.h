/*
 * Tests.h
 *
 *  Created on: 20 déc. 2012
 *      Author: zorro
 */

#ifndef TESTS_H_
#define TESTS_H_

#include <string>
#include <sstream>
#include "Graph.h"
#include "ColorationEngine.h"
#include <sys/time.h>
#include <fstream>

class Tests {
public:
	Tests();
	virtual ~Tests();
	void testGreedyAlgorithmWithGivenData();
	void testGreedyAlgorithmWithGeneratedGraph();
	void testBacktrackAlgorithmWithGivenData();
	void testBacktrackAlgorithmWithGeneratedGraph();
	void testNoChoiceAlgorithmWithGivenData();
	void testNoChoiceAlgorithmWithGeneratedGraph();
	void testSatReductionWithGivenData();
	void testSatReductionWithGeneratedGraph();
private:


};

#endif /* TESTS_H_ */
