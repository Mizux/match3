option(ENABLE_DOC "Compile doxygen documentation" OFF)

###########
##  DOC  ##
###########
if(${ENABLE_DOC})
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    # Find all specific doxygen files
    file(GLOB_RECURSE _SRCS "*.dox" "*.dot" "*.md" "*.pu")
    #but remove anything from build dir
    file(GLOB_RECURSE RM_SRCS "${CMAKE_BINARY_DIR}/*")
    list(REMOVE_ITEM _SRCS ${RM_SRCS})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(Match3_doc ALL
      SOURCES Doxyfile.in ${_SRCS}
      DEPENDS Match3_doc_cmd
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating Documentation for Match3 with Doxygen" VERBATIM)
    add_custom_command(OUTPUT Match3_doc_cmd ${CMAKE_BINARY_DIR}/doc
      COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/doc"
      COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()
endif()

#############
##  BUILD  ##
#############
file(GLOB_RECURSE _HDRS "include/*.hpp")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(Match3)
target_sources(Match3 PRIVATE ${_HDRS} ${_SRCS})
target_include_directories(Match3 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
set_target_properties(Match3 PROPERTIES
  PUBLIC_HEADER "${_HDRS}"
)
target_link_libraries(Match3 PUBLIC ${PROJECT_NAMESPACE}::Signal)
add_library(${PROJECT_NAMESPACE}::Match3 ALIAS Match3)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

install(TARGETS Match3
  EXPORT Match3Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Match3
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
