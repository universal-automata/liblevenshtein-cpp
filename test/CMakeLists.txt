list(APPEND CMAKE_MODULE_PATH
  /usr/lib/cmake/GTest
  /usr/share/rapidcheck/cmake)

include(GTestConfig)
include(rapidcheckConfig)

add_subdirectory(utils)
add_subdirectory(collection)
add_subdirectory(distance)
add_subdirectory(transducer)
add_subdirectory(serialization)
