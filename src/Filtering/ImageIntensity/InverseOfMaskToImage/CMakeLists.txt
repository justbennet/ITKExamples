cmake_minimum_required(VERSION 3.10.2)

project(InverseOfMaskToImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(InverseOfMaskToImage Code.cxx)
target_link_libraries(InverseOfMaskToImage ${ITK_LIBRARIES})

install(TARGETS InverseOfMaskToImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/InverseOfMaskToImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME InverseOfMaskToImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/InverseOfMaskToImage)
