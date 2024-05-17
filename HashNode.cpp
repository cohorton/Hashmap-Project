// Name: Chase Horton

#include "HashMap.hpp"


#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


hashNode::hashNode(string s) {
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}

hashNode::hashNode() {
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}

hashNode::hashNode(string s, string v) {
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}

hashNode::~hashNode() {
	delete [] values;
}

void hashNode::addValue(string v) {
	if (currSize >=valuesSize) {
        dblArray();
    }
    values[currSize++] = v;
}

void hashNode::dblArray() {
	int newSize = valuesSize * 2;
    string* newArray = new string[newSize];

    for (int i = 0; i < currSize; i++) {
        newArray[i] = values[i];
    }
    delete[] values;

    values = newArray;
    valuesSize = newSize;
}

string hashNode::getRandValue() {
	int randomIndex = rand() % currSize;
    return values[randomIndex];
}
