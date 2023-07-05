include_directories(
    ../src
)

add_executable(test_lexer.exe ../test/lexer/test_lexer.cpp)

target_link_libraries(
    test_lexer.exe
    compiler_src
    )

set_target_properties(test_lexer.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./lexer )

install(
    TARGETS test_lexer.exe
    DESTINATION .
    )

#add_subdirectory(lexer)