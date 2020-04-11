cmake_minimum_required(VERSION 3.2)
project(Match3 VERSION 0.0.1 LANGUAGES CXX)

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
		add_custom_target(${PROJECT_NAME}_doc ALL
			SOURCES Doxyfile.in ${_SRCS}
			DEPENDS ${PROJECT_NAME}_doc_cmd
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating Documentation for ${PROJECT_NAME} with Doxygen" VERBATIM)
		add_custom_command(OUTPUT ${PROJECT_NAME}_doc_cmd ${CMAKE_BINARY_DIR}/doc
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

add_library(${PROJECT_NAME} ${_HDRS} ${_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Signal)

add_subdirectory(test)
