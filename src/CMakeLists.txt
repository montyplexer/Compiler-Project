add_library(compiler_src
    
    # Main
    expression_evaluator.cpp
    
    # Token Struct and Enum
    tokens.h

    # Lexer Phase
    lexer.h
    lexer.cpp

    )

install(
    TARGETS compiler_src
    DESTINATION .
    )





