/**
* Author : Ufuk Palpas
*/
#ifndef __CALCULATE_H
#define __CALCULATE_H
#include <string>
using namespace std;

double calculateEntropy( const int* classCounts, const int numClasses);
double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);


#endif
