cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME lab3-SoundProcessor)
set(SOURCE_DIR src)
set(MAIN ${SOURCE_DIR}/main.cpp)
set(CONV ${SOURCE_DIR}/Convert.cpp)
set(FACTORY ${SOURCE_DIR}/Factory.cpp)
set(PARSING ${SOURCE_DIR}/Parsing.cpp)
set(LIBRARY_NAME converters_lib)
set(LIBRARY_HEADERS_DIR includes)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} ${FACTORY} ${MAIN} ${CONV} ${PARSING})

add_library(${LIBRARY_NAME} STATIC includes/MixConverter.h
				   includes/MutingConverter.h
				   includes/ReverseSecConverter.h
				   includes/Factory.h
				   includes/Convert.h
				   includes/Parsing.h
				   includes/IConverter.h
				   converters/MixConverter.cpp
				   converters/MutingConverter.cpp
				   converters/ReverseSecConverter.cpp
				   )

target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARY_NAME})
