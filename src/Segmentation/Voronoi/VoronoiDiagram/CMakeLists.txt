cmake_minimum_required(VERSION 3.10.2)

project(VoronoiDiagram)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(VoronoiDiagram Code.cxx)
target_link_libraries(VoronoiDiagram ${ITK_LIBRARIES})

install(TARGETS VoronoiDiagram
  DESTINATION bin/ITKExamples/Segmentation/Voronoi
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/Voronoi/VoronoiDiagram/
  COMPONENT Code
  )


enable_testing()
add_test(NAME VoronoiDiagramTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VoronoiDiagram)

