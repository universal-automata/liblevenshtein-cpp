add_subdirectory(utils)
add_subdirectory(collection)

if(BUILD_BASELINE_METRICS)
  add_subdirectory(distance)
endif()

add_subdirectory(transducer)
add_subdirectory(serialization)
