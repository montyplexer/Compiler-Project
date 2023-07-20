 # Compiler written in C++ for new language

There are multiple phases of a compiler. In this project, I seek to break down the compiler into seperate modules that include:
1. Lexer/Scanner/Tokenizer (Lexical Analysis)
2. Parser (Syntax And Semantic Analysis)
3. Intermediate Code Generator 
4. Code Optimizer
5. Target Code Generator

The exact division of the phases is subject to change based on implementation. As of now, the lexer is essentially complete (but may change as the language evolves). Work is beginning on the parser.

To build the code, download the repo, and from the main folder run `./build.sh`. This will build the project using CMake. Feel free to remove CMake leftovers, like caches, using `./clean.sh`.

To build and launch the expression evaluator, enter `./run.sh`. If you only want to launch the expression evaluator, run `exe/expr_eval.exe`.

__TODO__
- [x] Lexer 
    - [x] Implementation of key token types: operators, keywords, punctuals, identifiers, various literals
    - [x] Ignore whitespace and single- and multi-line comments
    - [x] Generate list of tokens for parser
    - [x] Write unit tests for lexer that tests for correct token generation using 'source code' files
- [ ] Parser
    - [x] Decide on type of parser to implement (will start by implementing an LL(k) parser)
    - [ ] Formalize a simple grammar
    - [ ] Implementation of key syntax node types
    - [ ] Calculate First and Follow sets
    - [ ] Implement procedure for each grammar rule
- [ ] Intermediate code generation
- [ ] Code optimizer
- [ ] Target code generation
