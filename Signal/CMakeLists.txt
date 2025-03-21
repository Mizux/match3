add_library(Signal INTERFACE)
file(GLOB _HDRS "include/Signal/*.hpp")
file(GLOB _DETAILS_HDRS "include/Signal/details/*.hxx")
#target_sources(Signal INTERFACE ${_HDRS} ${_DETAILS_HDRS})
target_include_directories(Signal INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
set_target_properties(Signal PROPERTIES
  PUBLIC_HEADER "${_HDRS}"
  PRIVATE_HEADER "${_DETAILS_HDRS}"
)
#target_link_libraries(Signal INTERFACE ...)
add_library(${PROJECT_NAMESPACE}::Signal ALIAS Signal)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

install(TARGETS Signal
  EXPORT Match3Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Signal
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Signal/details
)