add_executable(terminal_defense Main.cpp)
target_compile_features(terminal_defense PRIVATE cxx_std_20)
target_link_libraries(
	terminal_defense PRIVATE
	terminal_defense_lib
	ncurses
	tinfo
)
