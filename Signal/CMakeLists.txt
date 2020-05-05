#add_subdirectory(doc)

file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*.hxx")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")

add_library(Signal ${_HDRS} ${_SRCS})
target_include_directories(Signal PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)
set_target_properties(Signal PROPERTIES
	PUBLIC_HEADER "${_HDRS}"
  LINKER_LANGUAGE CXX
	)
add_library(match3::Signal ALIAS Signal)

if(BUILD_TESTING)
	add_subdirectory(test)
endif()

install(TARGETS Signal EXPORT Match3Targets)

#find_program(CPPCHECK cppcheck)
#if(CPPCHECK)
#	add_custom_command(TARGET Signal
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
