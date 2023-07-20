#include <iostream>
#include <string>
#include <vector>
#include "tokens.h"
#include "lexer.cpp"

using namespace std;

int main (int argc, char* argv[]) {
    string user_input;
    int eval_mode = 1;
    cout << "Entered basic expression evaluator." << endl;
    /* Lexer */
    Lexer lexer = Lexer();
    /* Tokens generated during lexing */
    vector<token_t> tokens = vector<token_t>();
    
    while (true) {
        while (true) {
            cout << endl << "=== MENU ===" << endl;
            cout << "What would you like to use?" << endl;
            cout << "1. Lexer: display generated tokens" << endl;
            cout << "2. Lexer > Parser: display abstract syntax tree" << endl << endl;

            getline(cin,user_input);

            if (user_input == "exit") {exit(0);}

            eval_mode = atoi(user_input.c_str());

            if (1 <= eval_mode && eval_mode <= 1) { 
                cout << "Entering mode " << eval_mode << "..." << endl << endl;
                break; 
            }
            else { cout << "Please type a number corresponding to a valid mode." << endl; }
        }
        while (true) {
            /* Clear token list */
            tokens.clear();
            
            /* Query user */
            cout << "> ";
            getline(cin,user_input);
            
            /* Exit */
            if (user_input == "exit") {exit(0);}
            if (user_input == "menu") {break;}

            /* Do stuff */
            lexer.set_text(user_input);
            while (lexer.is_lexing()) {
                token_t token = lexer.next_token();
                tokens.push_back(token);
                cout << Lexer::print_token(token) << " ";
            }
            cout << endl;
            cout << "Number of tokens created: " << tokens.size() << endl;

        }
    }

    

    
}