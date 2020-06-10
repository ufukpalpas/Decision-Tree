/**
* Author : Ufuk Palpas
* ID: 21702958
* Section : 3
* Assignment : 2
*/
#include "DecisionTree.h"
#include "calculate.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;


DecisionTree::DecisionTree(DecisionTreeNode *left, DecisionTreeNode *right){ // Constructor
    root = new DecisionTreeNode(left, right);
    cur = root;
}

DecisionTree::~DecisionTree(){ // Destructor
    destroyTree(root);
}

void DecisionTree::destroyTree(DecisionTreeNode *&treePtr){ //part of destructor
    if(treePtr != NULL){
        destroyTree(treePtr->leftChildPtr);
        destroyTree(treePtr->rightChildPtr);
        delete treePtr;
        treePtr = NULL;
    }
}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures) { //create tree
    double maxGain = -10; // first value of max gain among features
    double gain; // features gain to compare with maxGain
    int whichFea; // selected feature for that node
    bool featureUsed = false; // to avoid the usage of past features
    numOfFeatures = numFeatures; // get the numFeatures (21 for now)
    bool* usedSamples; // to access the used samples array of node (I selected 0 as used ones and 1's will be passed)
    double entropy;
    int arrlabels[numSamples]; // an array contains the labels in the position which is also the value of the label


    if(cur->arrsize == 0) // for only first time create used samples array of the node
        cur->createUsedSamplesArray(numSamples);

    usedSamples = cur->usedSamples; // access the used samples array of the node

    for (int t = 0; t < numSamples; t++) // make all 0
        arrlabels[t] = 0;

    for(int i = 0; i < numSamples; i++) {
        if(usedSamples[i] == 1) {
            arrlabels[labels[i]]++; // increase the number in the position which is also value of the label for example num of the repetition of the class "2" will be in arrlabels[2]
        }
    }

    entropy = calculateEntropy(arrlabels, numSamples); // calculate entropy

    for(int i = 0; i < numFeatures; i++) { // to select the feature that we want to use
        for(int a = 0; a < cur->arrsize; a++) { // a loop checks whether the feature is used before in that path or not
            if(i == cur->featuresSoFar[a]) {
                featureUsed = true;
                break;
            }
        }
        if (!featureUsed) { // calculate all information gains and compare.
            gain = calculateInformationGain( (const bool**) data,(const int*) labels, numSamples, numFeatures, usedSamples, (const int) i);
            if (gain > maxGain) {
                maxGain = gain;
                whichFea = i;
            }
        }
        featureUsed = false;
    }

    cur->addFeature(whichFea); // add the feature to used features
    cur->indexOfFeature = whichFea; //keeps feature index for its decision (split)

    if(entropy == 0) { //(all labels are same) (if PURE)
        cur->isLeaf = true; // keeps track of whether or not the node is a leaf
        for(int a = 0; a < numSamples; a++) { // find the label that is available (used nodes = 1)
            if(usedSamples[a]){
                cur->destroyUsedSamplesArray();
                cur->classDecision = labels[a]; // get the class decision
                return;
            }
        }
    }

    if(maxGain == -10) { //if there is no more feature to look
        cur->isLeaf = true;
        int maxLabel = 0; // to compare the repetition number of different
        int decision = 0; // to get the class decision of the most repeated one
        for(int r = 0; r < numSamples; r++) { // Note that it there are more than one class it will find the most repeated one. If all are same gets first one.
            if(arrlabels[r] > maxLabel){
                maxLabel = arrlabels[r];
                decision = r;
            }
        }
        cur->destroyUsedSamplesArray();
        cur->classDecision = decision;
        return;
    }

    cur->leftChildPtr = new DecisionTreeNode(); // create the left branch
    for(int i = 0; i < cur->arrsize; i++) { // add the feature list until this node to the feature list inside new node
        (cur->leftChildPtr)->addFeature(cur->featuresSoFar[i]);
    }
    cur->rightChildPtr = new DecisionTreeNode(); // create the right branch
    for(int i = 0; i < cur->arrsize; i++) { // add the feature list until this node to the feature list inside new node
        (cur->rightChildPtr)->addFeature(cur->featuresSoFar[i]);
    }

    (cur->rightChildPtr)->createUsedSamplesArray(numSamples); // create the used samples array of right child
    (cur->leftChildPtr)->createUsedSamplesArray(numSamples); // create the used samples array of left child

    for(int k = 0; k < numSamples; k++) {// copy the current node's usedSamples array to the children
        (cur->rightChildPtr)->usedSamples[k] = usedSamples[k];
        (cur->leftChildPtr)->usedSamples[k] = usedSamples[k];
    }

    for(int k = 0; k < numSamples; k++) { // create new data for branches (NOTE THAT IT MAY BE REVERSE WHAT U THING "used" word is misleading)
        if(data[k][whichFea] == 0)// for right (take only ones) // if it is 0 don't take to the right child
            (cur->rightChildPtr)->usedSamples[k] = false;
        else // for left (take only zeros)
            (cur->leftChildPtr)->usedSamples[k] = false;
    }

    cur->destroyUsedSamplesArray(); // we used it until here so now we can deallocate
    DecisionTreeNode* temp2 = cur; // protect the first address of the cur
    cur = cur->rightChildPtr; // go right side of the tree (to create)
    train( (const bool**) data, (const int*) labels, numSamples, numFeatures); // go for right child
    cur = temp2;
    cur = cur->leftChildPtr; // go left side of the tree (to create)
    train( (const bool**) data, (const int*) labels, numSamples, numFeatures); // go for left child
    cur = temp2;
    cur = root;
}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures) {
    ifstream inFile(fileName.c_str());
    //inFile.open(fileName); //.c_str());
    bool** data = new bool*[numSamples];

    for(int y = 0; y < numSamples; y++) //create arrays
        data[y] = new bool[numFeatures];

    int* labels = new int[numSamples];
    int value;

    for(int i = 0; i < numSamples; i++) {
        for (int k = 0; k < numFeatures; k++) {
            inFile >> value; // read from file (data)
            if(value == 1)
                data[i][k] =  true;
            else
                data[i][k] = false;
        }
        inFile >> value; // read from file (label) (last element of the value)
        labels[i] = value;
    }
    inFile.close();
    train((const bool**)data, (const int*)labels, numSamples, numFeatures); //call the train to create hte tree

    for(int y = 0; y < numSamples; y++) // delete arrays.
        delete [] data[y];
    delete [] data;
    delete [] labels;
}

int DecisionTree::predict(const bool* data){ // right child is TRUE left child is FALSE
    if(cur->isLeafNode()) { // stop if it is a leaf node
        int result = cur->getClassDecision();
        cur = root;
        return result;
    }
    int feature = cur->indexOfFeature; // get the feature of the node
    if(data[feature] == 0) { // if that feature in the test data is 0 go left otherwise go write
        cur=cur->leftChildPtr;
        return predict( data );
    } else {
        cur = cur->rightChildPtr;
        return predict( data );
    }
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {
    double truePredict = 0;
    int retLabel; // the prediction
    bool* dataPass = new bool[numOfFeatures];

    for (int i = 0; i < numSamples; i++) {
        for(int k = 0; k < numOfFeatures; k++) {
            dataPass[k] = data[i][k]; // get the particular row of the test data
        }
        retLabel = predict( (const bool*) dataPass ); // make prediction
        if( retLabel == labels[i] ) // compare with the result
            truePredict++;
    }
    delete [] dataPass;
    return (double) truePredict / numSamples; // proportion
}

double DecisionTree::test(const string fileName, const int numSamples) {
    double result;
    ifstream inFile(fileName.c_str());
    //inFile.open(fileName);//.c_str(), ios::in);
    cur = root; // insurance if cur is not at root
    bool** data = new bool*[numSamples];

    for(int y = 0; y < numSamples; y++)
        data[y] = new bool[numOfFeatures];

    int* labels = new int[numSamples];
    int value;

    for(int i = 0; i < numSamples; i++) {
        for (int k = 0; k < numOfFeatures; k++) {
            inFile >> value; // read from the file (data)
            if(value == 1)
                data[i][k] =  true;
            else
                data[i][k] = false;
        }
        inFile >> value; // read the label at the end of the row
        labels[i] = value;
    }
    inFile.close();
    result = test((const bool**) data, labels, numSamples); // test it

    for(int y = 0; y < numSamples; y++) // delete arrays
        delete [] data[y];
    delete [] data;
    delete [] labels;
    return result; // return to the proportion
}

void DecisionTree::print() { // prints the tree (preorder traversal)
    if(root != NULL) {
        for(int i = 0; i < ( (root->arrsize) - 1 ); i++) // print the tab according to level (it gets the level from the number of used features)
            cout << "   ";
        if(!root->isLeafNode()) // if it is a leaf node print the class decision else feature index of that node
            cout << root->indexOfFeature<<endl;
        else
            cout << "class=" << root->getClassDecision() << endl;
        DecisionTreeNode* current = root;
        root = root->leftChildPtr; // to print left child
        print();
        root = current;
        root = root->rightChildPtr; // to print right child
        print();
        root = current; //protect the roots address
    }
}
