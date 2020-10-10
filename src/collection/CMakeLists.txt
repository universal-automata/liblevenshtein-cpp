add_library(levenshtein-collection SHARED
  "symmetric_immutable_pair.cpp")

# set_target_properties(levenshtein-collection PROPERTIES
#   LINKER_LANGUAGE CXX)

target_link_libraries(levenshtein-collection
  levenshtein-utils)

# install(TARGETS levenshtein-collection DESTINATION lib)
# install(FILES "symmetric_immutable_pair.h"
#   DESTINATION include/liblevenshtein/collection)
