cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Añade todos los archivos fuente aquí
set(SOURCES
    main.cpp
    src/Page.cpp
    src/BufferManager.cpp
    src/Buffer_Pool.cpp
    src/Frame.cpp
)

# Establece el directorio de salida para los archivos compilados
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compila el ejecutable
add_executable(main ${SOURCES})
