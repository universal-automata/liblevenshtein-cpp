# NOTE: There is a caveate that requires add_library to be invoked in the same
# CMakeLists.txt as protobuf_generate_cpp for the protobuf sources to be
# generated.
add_library(levenshtein SHARED)

set(PROTO_BINARY_DIR "${CMAKE_BINARY_DIR}/generated/liblevenshtein/proto")
file(MAKE_DIRECTORY "${PROTO_BINARY_DIR}")

target_sources(levenshtein
  PRIVATE
    "liblevenshtein.proto")

find_package(Protobuf REQUIRED)

find_package(absl REQUIRED) # workaround for protobuf linking bug

target_include_directories(levenshtein PUBLIC
  "${Protobuf_INCLUDE_DIRS}"
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(levenshtein
  PUBLIC
    protobuf::libprotobuf
  PRIVATE
    absl::log_internal_check_op # workaround for protobuf linking bug
)

protobuf_generate(
  TARGET levenshtein
  LANGUAGE cpp
  OUT_VAR PROTO_HDRS
  PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

list(FILTER PROTO_HDRS INCLUDE REGEX "^.*\\.h(pp)?$")
install(FILES ${PROTO_HDRS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/liblevenshtein/proto")
