//  main.cpp
//  SequenceMod
//
//  Created by Rui Huang on 2023/9/8.
// Right Now I will just use this main.cpp to add sequence in the front

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// In the future I will prompt command line input.
//For now let's stick with changing the const variable or 'macro'
//input ur seqeunce to be added to the front.
const string ADDFRONT = "TTCTAATACGACTCACTATA";
//input ur I/O file name
const string INPUT_FILE_NAME = "DefaultLib.fasta";//"DefaultLib.fasta";
const string OUTPUT_FILE_NAME = "DefaultMut.fasta";//"DefaultMutDNA.fasta";

//cat strings:
string adding(string ADDFRONT, string current) {
    string output = ADDFRONT + current;
    return output;
}

//change U to T if any
string replaceUwithT(const string& input) {
    string output = input;
    for (char& c : output) {
        if (c == 'U') {
            c = 'T';
        }
    }
    return output;
}


int main() {
    ifstream input(INPUT_FILE_NAME);
    ofstream output(OUTPUT_FILE_NAME);
    
    if (!input.is_open() || !output.is_open()) {
        cerr << "Failed to open input or output file." << endl;
        exit(1);
    }
    
    string line;
    vector<string> sequences;
    string current_sequence;

    while (getline(input, line)) {
        if (line.empty()) {
            continue; // Skip empty lines
        }

        if (line[0] == '>') {
            // If it's a header line, save the previous sequence and start a new one
            if (!current_sequence.empty()) {
                // Add seq to the beginning and write the modified sequence
                string modified_seq = ADDFRONT + replaceUwithT(current_sequence);
                output << modified_seq << endl;
                current_sequence.clear();
            }
            // Write the header to the output
            output << line << endl;
        } else {
            // If it's not a header, append the sequence line to the current sequence
            current_sequence += line;
        }
    }

    // Don't forget the last sequence
    if (!current_sequence.empty()) {
        // Add seq to the beginning and write the modified sequence
        string modified_seq = ADDFRONT + replaceUwithT(current_sequence);
        output << modified_seq << endl;
    }

    input.close();
    output.close();

    cout << "Sequences Added" << endl;

    return 0;
}
