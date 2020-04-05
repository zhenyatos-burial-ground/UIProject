# CMakeList.txt: проект CMake для UIProject; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

include_directories(Error Integer)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (UIProject "main.cpp" 
"Error/Error.h" "Error/Error.cpp"
"Integer/Integer.h" "Integer/Integer.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
