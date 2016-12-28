find_program(CLANG_FORMAT NAMES clang-format
	clang-format39 clang-format-3.9
	clang-format38 clang-format-3.8
	clang-format37 clang-format-3.7
	clang-format36 clang-format-3.6
	clang-format35 clang-format-3.5
	clang-format34 clang-format-3.4
)

if (CLANG_FORMAT)
	message("Found clang-format: ${CLANG_FORMAT}")
	add_custom_target(
		format
		COMMAND ${CLANG_FORMAT}
		-style=Chromium
		-i
		${game_SOURCES}
	)
endif()
