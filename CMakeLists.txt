cmake_minimum_required (VERSION 2.6)
project (detector_face)

find_package( OpenCV REQUIRED )

add_executable (detector_face src/main.cpp)
target_link_libraries (detector_face tiobj ${OpenCV_LIBS})

