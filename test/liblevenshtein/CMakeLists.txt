list(APPEND CMAKE_MODULE_PATH
  /usr/lib/cmake/GTest
  /usr/share/rapidcheck/cmake
  /usr/lib/cmake/yaml-cpp)

include(GTestConfig)
include(rapidcheckConfig)
include(yaml-cpp-config)

add_subdirectory(config)
add_subdirectory(utils)
add_subdirectory(collection)
add_subdirectory(distance)
add_subdirectory(transducer)
add_subdirectory(serialization)
