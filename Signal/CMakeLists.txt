cmake_minimum_required(VERSION 3.2)
project(Signal VERSION 0.0.1 LANGUAGES CXX)

#add_subdirectory(doc)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*.hxx")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(${PROJECT_NAME} ${_HDRS} ${_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)

#find_program(CPPCHECK cppcheck)
#if(CPPCHECK)
#	add_custom_command(TARGET ${PROJECT_NAME}
#		POST_BUILD
#		COMMAND ${CPPCHECK} -q --enable=all --inconclusive --inline-suppr
#		-Iinclude src test
#		--template "{file}:{line}: warning: {severity}: {message} [{id}]"
#		VERBATIM
#		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#		COMMENT "Running cppcheck in ${CMAKE_CURRENT_SOURCE_DIR}"
#	)
#else()
#	message(WARNING "cppcheck not found !")
#endif()
