find_program(CLANG_TIDY NAMES clang-tidy
	clang-tidy39 clang-tidy-3.9
	clang-tidy38 clang-tidy-3.8
	clang-tidy37 clang-tidy-3.7
	clang-tidy36 clang-tidy-3.6
	clang-tidy35 clang-tidy-3.5
	clang-tidy34 clang-tidy-3.4
)

if (CLANG_TIDY)
	message("Found clang-tidy: ${CLANG_TIDY}")
	add_custom_target(
		tidy
		COMMAND ${CLANG_TIDY}
		-fix -fix-errors -p=${CMAKE_BINARY_DIR}/compile_commands.json -header-filter=src/ 
		${game_SOURCES}
	)
endif()
