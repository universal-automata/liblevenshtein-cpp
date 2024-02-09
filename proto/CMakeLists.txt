# NOTE: There is a caveate that requires add_library to be invoked in the same
# CMakeLists.txt as protobuf_generate_cpp for the protobuf sources to be
# generated.
add_library(levenshtein SHARED "")

set(PROTO_BINARY_DIR "${CMAKE_BINARY_DIR}/generated/liblevenshtein/proto")
file(MAKE_DIRECTORY "${PROTO_BINARY_DIR}")

target_sources(levenshtein PUBLIC
  "liblevenshtein.proto")

target_include_directories(levenshtein PUBLIC
  "${Protobuf_INCLUDE_DIRS}"
  "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>")

target_link_libraries(levenshtein PUBLIC
  protobuf::libprotobuf)

find_package(Protobuf REQUIRED)
protobuf_generate(
  TARGET levenshtein
  LANGUAGE cpp
  OUT_VAR PROTO_HDRS
  PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

list(FILTER PROTO_HDRS INCLUDE REGEX "^.*\\.h(pp)?$")
install(FILES ${PROTO_HDRS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/liblevenshtein/proto")
