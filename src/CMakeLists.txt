add_library(compiler_src
    
    # Main
    expression_evaluator.cpp
    
    )

install(
    TARGETS compiler_src
    DESTINATION .
    )





