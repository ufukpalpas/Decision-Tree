/**
* Author : Ufuk Palpas
*/
#ifndef __DECISION_TREE_H
#define __DECISION_TREE_H
#include <string>
#include "DecisionTreeNode.h"
using namespace std;

class DecisionTree {
public:
    DecisionTree(DecisionTreeNode *left = NULL, DecisionTreeNode *right = NULL);
    ~DecisionTree();
    void train(const bool**, const int*, const int, const int);
    void train(const string, const int, const int);
    int predict(const bool*);
    double test(const bool**, const int*, const int);
    double test(const string, const int);
    void print();
private:
    void destroyTree(DecisionTreeNode *&treePtr);

    DecisionTreeNode *root = NULL;
    DecisionTreeNode *cur = NULL;
    int numOfFeatures;
};
#endif
