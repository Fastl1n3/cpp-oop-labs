cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME lab2-PrisonersDilemma)
set(SOURCE_DIR src)
set(MAIN ${SOURCE_DIR}/main.cpp)
set(GAME ${SOURCE_DIR}/Game.cpp)
set(FACTORY ${SOURCE_DIR}/Factory.cpp)
set(PARSING ${SOURCE_DIR}/Parsing.cpp)
set(LIBRARY_NAME strategys_lib)
set(LIBRARY_HEADERS_DIR includes)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} ${FACTORY} ${MAIN} ${GAME} ${PARSING})

add_library(${LIBRARY_NAME} STATIC includes/AlTitForTatStrategy.h
				   includes/BetrayalStrategy.h
				   includes/DefaultStrategy.h
 				   includes/EgTitForTatStrategy.h
				   includes/Factory.h
				   includes/Game.h
				   includes/Parsing.h
				   includes/IStrategy.h
				   includes/SilenceStrategy.h
				   includes/SmartStrategy.h
				   strategys/AlTitForTatStrategy.cpp
				   strategys/BetrayalStrategy.cpp
				   strategys/DefaultStrategy.cpp
				   strategys/EgTitForTatStrategy.cpp
				   strategys/SilenceStrategy.cpp
				   strategys/SmartStrategy.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARY_NAME})
