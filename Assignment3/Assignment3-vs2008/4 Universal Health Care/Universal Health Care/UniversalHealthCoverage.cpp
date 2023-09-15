/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);
/* prototype */
bool coversAllCities(Set<string> cities, Vector< Set<string> > locations);


int main() {
    return 0;
}

/* recursion */	
bool canOfferUniversalCoverageRec(Set<string>& cities,
								  Vector< Set<string> >& locations,
								  int numHospitals,
								  Vector< Set<string> >& result,
								  Vector< Set<string> > curRes,
								  int index){
	//base case
	if(curRes.size() <= numHospitals){
		if(coversAllCities(cities, curRes)){
			result = curRes;
			return true;
		}
	}

	if(index >= locations.size() - 1) return false;
	index++;
	bool a = canOfferUniversalCoverageRec(cities, locations, numHospitals, result, curRes, index);
	curRes.add(locations.get(index));
	bool b = canOfferUniversalCoverageRec(cities, locations, numHospitals, result, curRes, index);
	return b||a;
}

/* wrapper function */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result){
	int index = -1;
	Vector< Set<string> > curRes = result;
	return canOfferUniversalCoverageRec(cities, locations, numHospitals, result, curRes, index);
}

/* checks if possible location of hospitals covers all cities */
bool coversAllCities(Set<string> cities, Vector< Set<string> > locations){
	for(int i = 0; i < locations.size(); i++){
		Set<string> temp = locations.get(i);
		while(!temp.isEmpty()) {
			if(cities.contains(temp.first())) cities.remove(temp.first());
			temp.remove(temp.first());
		}
	}
	if(cities.isEmpty()) return true;
	return false;
}