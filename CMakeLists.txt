cmake_minimum_required(VERSION 3.10)

# Set the project Name
project(CWorkspace VERSION 1.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED)

option(USE_COLLECTIONS "Use the custom Collection library" ON)

# Configures a header file to pass some of the CMake settings to the source code
configure_file(CWorkspaceConfig.h.in CWorkspaceConfig.h)

if(USE_COLLECTIONS)
  add_subdirectory(collections_lib)
  list(APPEND EXTRA_LIBS collections)
endif()

# add the executable
add_executable(CWorkspace src/main.c)

target_link_libraries(CWorkspace PUBLIC ${EXTRA_LIBS})

target_include_directories(CWorkspace PUBLIC
  "${PROJECT_BINARY_DIR}"
  )

install(TARGETS CWorkspace DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/CWorkspaceConfig.h"
  DESTINATION include
)

# Simple Deployment tests
enable_testing()

# does the application run?
add_test(NAME Runs COMMAND CWorkspace)

# does hello world get printed
add_test(NAME Output COMMAND CWorkspace)
set_tests_properties(Output
PROPERTIES PASS_REGULAR_EXPRESSION "Hello world 0"
)

# Distribution Code for installing on various plaforms
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${CWORKSPACE_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CWORKSPACE_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
