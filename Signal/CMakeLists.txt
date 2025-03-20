#add_subdirectory(doc)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*.hxx")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(Signal)
target_sources(Signal PRIVATE ${_HDRS} ${_SRCS})
target_include_directories(Signal PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
set_target_properties(Signal PROPERTIES
  PUBLIC_HEADER "${_HDRS}"
  LINKER_LANGUAGE CXX
)
#target_link_libraries(Signal PRIVATE ...)
add_library(${PROJECT_NAMESPACE}::Signal ALIAS Signal)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

install(TARGETS Signal
  EXPORT Match3Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Signal
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
