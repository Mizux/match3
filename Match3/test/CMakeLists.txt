set(NAME Match3_UT)

file(GLOB _SRCS "src/*.[hc]pp")

add_executable(${NAME} ${_SRCS})
target_link_libraries(${NAME} Catch Match3)
add_test(NAME ${NAME} COMMAND ${NAME})
add_test(NAME Match3::Types COMMAND ${NAME} \[Types\])
add_test(NAME Match3::Board COMMAND ${NAME} \[Board\])
add_test(NAME Match3::Game COMMAND ${NAME} \[Game\])
add_test(NAME Match3::Matrix COMMAND ${NAME} \[Matrix\])
add_test(NAME Match3::Vector COMMAND ${NAME} \[Vector\])
