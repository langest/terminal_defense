file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${HelloCMake_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "*.cpp")

add_library(terminal_defense_lib ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(terminal_defense_lib PUBLIC ../include)
target_compile_features(terminal_defense_lib PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
