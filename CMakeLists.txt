
cmake_minimum_required(VERSION 3.10)
project(f1-race)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# threads
find_package(Threads REQUIRED)

set(SRC src/main.cpp src/Engineer.cpp src/Bolide.cpp src/UI.cpp src/PitstopManager.cpp src/Random.cpp src/TrackManager.cpp src/Road.cpp src/Pitstop.cpp src/Storekeeper.cpp)

add_executable(f1-race ${SRC})
target_compile_options(f1-race PRIVATE -Wall -Wextra -Wpedantic -O3)
target_link_libraries(f1-race ${CURSES_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT})
