set(NAME Match3_UT)

file(GLOB _SRCS "src/*.[hc]pp")

add_executable(${NAME} ${_SRCS})
# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(${NAME} PROPERTIES
		INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX AND NOT APPLE)
  set_target_properties(${NAME} PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
target_link_libraries(${NAME} PRIVATE
	match3::Match3 Catch2)
add_test(NAME ${NAME} COMMAND ${NAME})
add_test(NAME Match3::Types COMMAND ${NAME} \[Types\])
add_test(NAME Match3::Board COMMAND ${NAME} \[Board\])
add_test(NAME Match3::Game COMMAND ${NAME} \[Game\])
add_test(NAME Match3::Matrix COMMAND ${NAME} \[Matrix\])
add_test(NAME Match3::Vector COMMAND ${NAME} \[Vector\])
