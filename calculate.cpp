/**
* Author : Ufuk Palpas
* ID: 21702958
* Section : 3
* Assignment : 2
*/
#include "calculate.h"
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

double calculateEntropy( const int* classCounts, const int numClasses) {
    int sum = 0; // the number of samples
    double result = 0; // return value

    for(int i = 0; i < numClasses; i++) // to find the number of samples
        sum += classCounts[i];

    for(int k = 0; k < numClasses; k++) { // to calculate for each class
        if(classCounts[k] == 0) // if zero don't add
            continue;
        double divof = (double) classCounts[k] / sum;
        double logof = log2(divof);
        result += (divof*logof);
    }
    result *= -1;
    return result;
}


double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId){
    int countEachLabel[numSamples]; // an array to keep the number of repeats of labels in the position which is also the value of label
    int countEachRight[numSamples]; // an array to keep the number of repeats of labels in right child
    int countEachLeft[numSamples]; // an array to keep the number of repeats of labels in left child
    double numOne = 0; // count the num of right child's labels
    double numZero = 0; // count the num of left child's labels
    double parentEnt, pleft, pright, result, hRightEnt, hLeftEnt;
    int notUsed = 0; // if usedSamples is 0 subtract this from all

    for(int a  = 0; a < numSamples; a++){ // set all to 0
        countEachLabel[a] = 0;
        countEachLeft[a] = 0;
        countEachRight[a] = 0;
    }

    for(int i = 1; i < numSamples; i++){
        if(usedSamples[i] == 1) {
            countEachLabel[labels[i]]++; //For labels

            if(data[i][featureId] == 1){ // right
                numOne++;
                countEachRight[labels[i]]++; // increase the count of the label placed in the labels value = position in array
            } else { // left
                numZero++;
                countEachLeft[labels[i]]++;
            }
        } else
            notUsed++;
    }

    parentEnt = calculateEntropy( countEachLabel, numSamples ); // calculate the parents entropy

    pleft = (double) (numZero / (numSamples - notUsed) ); // proportion of zeros
    pright = (double) (numOne / (numSamples - notUsed) ); // proportion of ones
    hRightEnt = calculateEntropy(countEachRight, numSamples); // calculate entropy of right child
    hLeftEnt = calculateEntropy(countEachLeft, numSamples); // calculate entropy of left child

    pleft *= hLeftEnt; // proportion * child's entropy
    pright *= hRightEnt;

    result = parentEnt - pleft - pright; // subtract children's entropy from the parent's entropy
    return result;
}
