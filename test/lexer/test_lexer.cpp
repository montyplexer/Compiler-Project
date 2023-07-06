#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "../../src/lexer.cpp"
#include "../../src/tokens.h"

/* This is a utility file used to perform unit tests on the Lexer. 
 * */

using namespace std;

int main (int argc, char* argv[]) {
    ifstream source_file; string source_file_name;
    ofstream output_file; string output_file_name;
    Lexer lexer = Lexer();
    string source_text = string();
    stringstream source_buffer;

    // Check that command is formed correctly
    if (argc != 2) {
        cerr << "Wrong number of arguments!" << endl;
        cout << "usage: test_lexer <source_file>" << endl;
        exit(1);
    }

    // Open source file
    source_file_name = string(argv[1]);
    cout << "Opening \"" << source_file_name << "\" source file..." << endl;
    source_file.open(source_file_name);
    if (!source_file.is_open()) {
        cerr << "Error opening file!" << endl;
        cout << "Unable to open file." << endl;
        exit(1);
    }
    
    // Create token list file
    output_file_name = source_file_name.substr(0,source_file_name.length()-3) + "out";
    cout << "Creating \"" << output_file_name << "\" output file..." << endl;
    output_file.open(output_file_name);
    if (!source_file.is_open()) {
        cerr << "Error opening file!" << endl;
        cout << "Unable to open file." << endl;
        exit(1);
    }

    // Turn enter file buffer into a string
    source_buffer << source_file.rdbuf();
    source_text = source_buffer.str();

    // Begin scanning
    lexer.set_text(source_text);
    while(lexer.is_lexing()) {
        token_t token = lexer.next_token();
        output_file << Lexer::print_token(token) << endl;
    }
    
    // Finish up
    cout << "Closing files..." << endl;
    source_file.close();
    output_file.close();
    cout << "Done!" << endl;
}