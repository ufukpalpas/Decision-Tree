/**
* Author : Ufuk Palpas
* ID: 21702958
* Section : 3
* Assignment : 2
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
