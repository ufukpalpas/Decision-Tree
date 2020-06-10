/**
* Author : Ufuk Palpas
*/
#include "DecisionTreeNode.h"
#include <string>
using namespace std;

DecisionTreeNode::DecisionTreeNode( DecisionTreeNode *left, DecisionTreeNode *right): leftChildPtr(left), rightChildPtr(right) {
    isLeaf = false;
    indexOfFeature = -1; //feature index
    classDecision = -1;
    arrsize = 0; // size of the array that keeps used features
    for(int i = 0; i < 21; i++) // fill the array of used features with -1
        featuresSoFar[i] = -1;
}

void DecisionTreeNode::addFeature(const int featureIndex){
    featuresSoFar[arrsize] = featureIndex; // if you use a feature this method adds it to the array
    arrsize++;
}

void DecisionTreeNode::createUsedSamplesArray(const int size) { // create an used samples array full of trues (first node's) if 1 continue
    usedSamples = new bool[size];
    for(int i = 0; i < size; i++)
        usedSamples[i] = true;
}

void DecisionTreeNode::destroyUsedSamplesArray() { //delete used samples array
    delete [] usedSamples;
}

bool DecisionTreeNode::isLeafNode() {
    return isLeaf;
}

int DecisionTreeNode::getClassDecision() {
    return classDecision;
}
