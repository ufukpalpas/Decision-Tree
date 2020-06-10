/**
* Author : Ufuk Palpas
*/
#ifndef __DECISION_TREE_NODE_H
#define __DECISION_TREE_NODE_H
#include <string>

using namespace std;

class DecisionTreeNode {
private:
    DecisionTreeNode(DecisionTreeNode *left = NULL, DecisionTreeNode *right = NULL);
    void addFeature(const int featureIndex);
    void createUsedSamplesArray(const int size);
    void destroyUsedSamplesArray();
    bool isLeafNode();
    int getClassDecision();

    DecisionTreeNode* leftChildPtr;
    DecisionTreeNode* rightChildPtr;
    int indexOfFeature;
    int classDecision;
    int arrsize; // used features array size
    bool isLeaf;
    bool* usedSamples;
    int featuresSoFar[21];
    friend class DecisionTree;
};
#endif
