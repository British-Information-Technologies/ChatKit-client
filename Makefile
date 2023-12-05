.PHONY: prepare_release make_release build_release full_release prepare_debug make_debug build_debug full_debug

prepare_release:
	rm -rf build_release
	mkdir build_release

make_release:
	cd build_release && cmake .. -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release -G Ninja
	ln -sf build_release/compile_commands.json .

build_release:
	cd build_release && cmake --build .

full_release: prepare_release make_release build_release

prepare_debug:
	rm -rf build_debug
	mkdir build_debug

make_debug:
	cd build_debug && cmake .. -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug -G Ninja
	ln -sf build_debug/compile_commands.json .

build_debug:
	cd build_debug && cmake --build .

full_debug: prepare_debug make_debug build_debug

format_src:
	find src/ -regex '.*\.\(cpp\|hpp\|h\|cc\|cxx\)' -exec clang-format -style=file:"./.clang-format" -i {} \;

format_include:
	find include/ -regex '.*\.\(cpp\|hpp\|h\|cc\|cxx\)' -exec clang-format -style=file:"./.clang-format" -i {} \;

format_all: format_include format_src
