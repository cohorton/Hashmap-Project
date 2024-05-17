// Name: Chase Horton

#include "HashMap.hpp"
#include "HashNode.hpp"
#include <iostream>
#include <cmath>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
    numKeys = 0;
    mapSize = 100;
    hashfn = hash1;
    collfn = coll1;
    collisions = 0;
    hashcoll = 0;

    map = new hashNode*[mapSize];

    for(int i = 0; i < mapSize; ++i) {
        map[i] = NULL;
    }

}

hashMap::~hashMap() {
	for(int i = 0; i < mapSize; ++i) {
		if(map[i] != NULL) {
			delete map[i];
			map[i] = NULL;
		}
	}
	delete [] map;
}

void hashMap::addKeyValue(string k, string v) {
    int index = getIndex(k);

    if (map[index] != nullptr) {
        map[index]->addValue(v);
    } else {
        hashNode* newNode = new hashNode(k, v);
        map[index] = newNode;
        numKeys++;

        float loadFactor = static_cast<float>(numKeys) / static_cast<float>(mapSize);
        if (loadFactor > 0.7) {
            reHash();
        }
    }
}

int hashMap::getIndex(string k) {
    int hashValue;
    if (hashfn) {
        hashValue = calcHash1(k);
    } else {
        hashValue = calcHash2(k);
    }

    int index = hashValue % mapSize;
    int i = 0;

    while (map[index] != nullptr && map[index]->keyword != k) {
        int offset;
        if (collfn) {
            offset = coll1(hashValue, i, k);
        } else {
            offset = coll2(hashValue, i, k);
        }
        index = (hashValue + offset) % mapSize;
        i++;
    }

    return index;
}

int hashMap::calcHash2(string k){
	unsigned long hash = 5381;
    const int prime = 31;

    for (char c:k) {
        hash = (hash * prime) + static_cast<unsigned long>(c);
    }
    return hash;
}

int hashMap::calcHash1(string k){
	int hash = 7;
    for (int i = 0; i < k.length(); i++) {
        hash = hash*13 + int(k[i]);
    }
    return hash;
}

void hashMap::getClosestPrime() {
    int newSize = mapSize * 2;

    const int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153
    };
    int low = 0;
    int high = sizeof(primes) / sizeof(primes[0]) - 1;
    int closestPrime = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (primes[mid] < newSize) {
            closestPrime = primes[mid];
            low = mid + 1;
        } else if (primes[mid] > newSize) {
            high = mid - 1;
        } else {
            closestPrime = primes[mid];
            break;
        }
    }
    mapSize = closestPrime;
}

void hashMap::reHash() {
	getClosestPrime();

    hashNode** newMap = new hashNode*[mapSize]();

    for (int i = 0; i < mapSize / 2; i++) {
        if (map[i] != NULL) {
            int newIndex = getIndex(map[i]->keyword);
            newMap[newIndex] = map[i];
        }
    }
    delete[] map;
    map = newMap;
}

int hashMap::coll1(int h, int i, string k) {
	return (h+i) % mapSize;
}

int hashMap::coll2(int h, int i, string k) {
	return (h + i * i) % mapSize;
}

void hashMap::printMap() {
	cout << "Hash Map:" << endl;
	for (int i = 0; i < mapSize; i++) {
		// print valid values
		if (map[i] != NULL) {
			printf("[%6d] ", i);
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
	cout << "Total Keys: " << numKeys << endl;
	cout << "Hash Map Array Size: " << mapSize << endl;
}


