add_subdirectory(utils)
add_subdirectory(collection)

if(BUILD_TESTS)
  add_subdirectory(distance)
endif()

add_subdirectory(transducer)
add_subdirectory(serialization)
