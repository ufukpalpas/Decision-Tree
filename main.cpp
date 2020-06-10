/**
* Author : Ufuk Palpas
*/
#include "calculate.h"
#include "DecisionTree.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
    DecisionTree* decTree = new DecisionTree();
    decTree->train("train_data.txt", 498, 21 );
    cout << "Proportion =  " << decTree->test("test_data.txt", 473) << endl;
    decTree->print();
    delete decTree;
    return 0;
}
