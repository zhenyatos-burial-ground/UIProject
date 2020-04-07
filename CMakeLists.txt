# CMakeList.txt: проект CMake для UIProject; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

include_directories(Error Integer Rational Real UI_lab Vector)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (UIProject "main.cpp" 
"Error/Error.h" "Error/Error.cpp" "Error/MyLogger.cpp"
"Integer/Integer.h" "Integer/Integer.cpp"
"Rational/Rational.h" "Rational/Rational.cpp"
"Real/Real.h" "Real/Real.cpp"
"UI_lab/ICompact.h" "UI_lab/ILogger.h" "UI_lab/ISet.h" "UI_lab/IVector.h" "UI_lab/RC.h"
"Vector/IVector.cpp" "Vector/VectorImpl.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
