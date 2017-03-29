# Game
A simple game framework and build system. Builds upon [engine](https://github.com/zerotri/engine).

# Usage
```
git clone http://github.com/zerotri/game
cd game
git submodule update --init --recursive
mkdir src/some-game

cat <<-EOF > src/some-game/main.c
#include <2d>

int main( int argc, char** argv ) {
	game_window *window = NULL;
	window_create("Testing", 640, 480, &window);
	while(1);
	return 0;
}
EOF

mkdir build
cd build
cmake ..
cmake --build .
```

