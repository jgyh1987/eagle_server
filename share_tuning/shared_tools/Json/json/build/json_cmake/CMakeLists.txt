FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
ADD_LIBRARY(json STATIC ${SOURCES})


