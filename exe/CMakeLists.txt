include_directories(
    ../src
)

add_executable(expr_eval.exe ../src/expression_evaluator.cpp)

target_link_libraries(
    expr_eval.exe
    compiler_src
    )


install(
    TARGETS expr_eval.exe 
    DESTINATION .
    )