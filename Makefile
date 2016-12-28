WATCH_FILES= find . -type f -not -path '*/\.*' -and -not -path '*/build/*' | grep -i '.*[.][cc,cpp,c,h,hh]\|CMakeLists.txt$$' 2> /dev/null

entr_warn:
	@echo "----------------------------------------------------------"
	@echo "     ! File watching functionality non-operational !      "
	@echo "                                                          "
	@echo "Install entr(1) to automatically run tasks on file change."
	@echo "See http://entrproject.org/                               "
	@echo "----------------------------------------------------------"

all: build

mkdir_build:
	[[ -d ./build ]] || mkdir -p build

build: mkdir_build
	cd build; cmake ..
	make -C build

build_ninja: mkdir_build
	cd build; cmake -GNinja ..
	ninja -C build

debug: mkdir_build
	cd build; cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -C build

debug_ninja: mkdir_build
	cd build; cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
	ninja -C build

format:
	clang-format -style=Chromium src/* -i || clang-format38 -style=Chromium src/* -i

cpplint:
	cpplint.py --filter=-build/include src/*

cppcheck:
	cppcheck --quiet --enable=all --inconclusive --std=c11 src/*

run:
	./build/game

watch_cpplint:
	if command -v entr > /dev/null; then ${WATCH_FILES} | entr -c $(MAKE) cpplint; else $(MAKE) cpplint entr_warn; fi

watch_cppcheck:
	if command -v entr > /dev/null; then ${WATCH_FILES} | entr -c $(MAKE) cppcheck; else $(MAKE) cppcheck entr_warn; fi

watch_debug:
	if command -v entr > /dev/null; then ${WATCH_FILES} | entr -c $(MAKE) debug_ninja; else $(MAKE) debug_ninja entr_warn; fi

watch_run:
	if command -v entr > /dev/null; then ${WATCH_FILES} | entr -c $(MAKE) debug run; else $(MAKE) debug run entr_warn; fi

install_osx_deps:
	brew install cmake ninja sdl2 sdl2_image sdl2_ttf entr

.PHONY: mkdir_build
