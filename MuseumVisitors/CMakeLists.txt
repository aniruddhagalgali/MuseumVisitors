# CMakeList.txt : CMake project for MuseumVisitors, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (MuseumVisitors "src/MuseumVisitors.cpp"  "src/Logger.cxx"  "src/VisitorCounterArray.cxx" "src/VisitorCounterMap.cxx")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MuseumVisitors PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
