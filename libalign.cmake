project(align)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

# cmake_policy(SET CMP0028 OLD)
 #  cmake_policy(SET CMP0075 NEW)

find_package(dlib REQUIRED)
find_package(OpenCV REQUIRED)

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")
add_definitions(-fPIC  -fopenmp)

include_directories(${OpenCV_INCLUDE_DIRS}/align)

link_directories(${OpenCV_LIBRARY_DIRS})

file(GLOB ALIGNSRC ${CMAKE_CURRENT_LIST_DIR}/align/*.cpp)
# add_subdirectory(../native/dlib dlib_build)

#add_executable(pico ${SRC})
add_library(libalign SHARED ${ALIGNSRC})
# INSTALL(TARGETS libalign
# #        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION /usr/local/lib
# #        ARCHIVE DESTINATION libstatic
# )
target_link_libraries(libalign dlib::dlib ${OpenCV_LIBS})

# file(COPY ${CMAKE_CURRENT_LIST_DIR}/align/align.hpp DESTINATION /usr/local/include)
