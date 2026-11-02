add_executable(test_utmatrix
    test_main.cpp
    test_tmatrix.cpp
    test_tvector.cpp
)

target_link_libraries(test_utmatrix PRIVATE gtest matrix)

add_test(NAME MyTests COMMAND test_utmatrix)
