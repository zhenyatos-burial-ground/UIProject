add_executable(test tests.cpp vectortests.cpp Test.h vectortests.h settests.cpp settests.h)

target_link_libraries(test PUBLIC Numeric)