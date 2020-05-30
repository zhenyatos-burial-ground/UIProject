add_library(Numeric
Vector/IVector.cpp
Vector/VectorImpl.cpp
Set/ISet.cpp
Set/SetImpl.cpp
MyLogger.cpp)

target_include_directories(Numeric PUBLIC UI_lab)