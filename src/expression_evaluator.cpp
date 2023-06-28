#include <iostream>
#include <string>
#include <vector>
#include "tokens.h"
#include "lexer.cpp"

using namespace std;

int main (int argc, char* argv[]) {
    bool is_running = true;
    string user_input;
    cout << "Entered basic expression evaluator." << endl;

    while (is_running) {
        /* Query user */
        cout << "> ";
        getline(cin,user_input);
        
        /* Do stuff */
        cout << user_input;
        cout << endl;

        /* Exit */
        if (user_input == "exit") {exit(0);}
    }
}