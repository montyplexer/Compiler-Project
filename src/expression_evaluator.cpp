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
    Lexer lexer = Lexer();

    while (is_running) {
        /* Query user */
        cout << "> ";
        getline(cin,user_input);
        
        /* Do stuff */
        lexer.set_text(user_input);
        while (lexer.is_lexing()) {
            cout << Lexer::print_token(lexer.next_token()) << " ";
        }
        cout << endl;

        /* Exit */
        if (user_input == "exit") {exit(0);}
    }
}