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
    /* Lexer */
    Lexer lexer = Lexer();
    /* Tokens generated during lexing */
    vector<token_t> tokens = vector<token_t>();
    /* Parser */

    while (is_running) {
        /* Clear token list */
        tokens.clear();
        
        /* Query user */
        cout << "> ";
        getline(cin,user_input);
        
        /* Do stuff */
        lexer.set_text(user_input);
        while (lexer.is_lexing()) {
            token_t token = lexer.next_token();
            tokens.push_back(token);
            cout << Lexer::print_token(token) << " ";
        }
        cout << endl;
        cout << "Number of tokens created: " << tokens.size() << endl;

        /* Exit */
        if (user_input == "exit") {exit(0);}
    }
}