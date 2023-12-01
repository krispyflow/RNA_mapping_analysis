//  Functions.h
//  SequenceMod
//
//  Created 2023/9/8.
// !!!This script is NOT yet finished!!!

// idea is to make a class or hierachy of classes that handle DNA seq
// modification/manipulation

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
using namespace std;

class SeqMod {
public:
    SeqMod();
    SeqMod (string seqFront, string seqBack, string input, string output);
    ~SeqMod();
    void addingFront(string &seqFront, string &input);
private:
    string seqFront;
    string seqBack;
    string input;
    string output;
};

#endif /* Functions_h */
