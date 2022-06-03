add_library(
  collections
  src/graph.c
  src/list.c
  src/node.c
  src/tree.c
)

target_include_directories(collections PUBLIC "${LIBRARY_SOURCE_DIR}")

# Any projec that wants to include this library will now automatically include this interface directory
target_include_directories(collections
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

install(TARGETS collections DESTINATION lib)
install(FILES collections/common.h DESTINATION include)
