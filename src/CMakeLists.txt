add_library(compiler_src
    
    # Main
    expression_evaluator.cpp
    
    # Token Struct and Enum
    tokens.h

    # Lexer Phase
    lexer.h
    lexer.cpp

    # Syntax Node Struct and Enum
    syntax_nodes.h

    # Parser Phase
    parser.h
    parser.cpp

    )

install(
    TARGETS compiler_src
    DESTINATION .
    )





