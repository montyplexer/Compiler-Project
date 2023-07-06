add_library(compiler_src
    
    # Token Struct and Enum
    tokens.h

    # Lexer Phase
    lexer.h

    # Syntax Node Struct and Enum
    syntax_nodes.h

    # Parser Phase
    parser.h

    )

set_target_properties(compiler_src PROPERTIES LINKER_LANGUAGE CXX)

install(
    TARGETS compiler_src
    DESTINATION .
    )





