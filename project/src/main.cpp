#include <cstring>
#include "Game.h"


int main(int argc, const char** argv) {
    if (argc != 3) {
        puts("Wrong number of arguments...");
        return 1;
    }
    if (strcmp(argv[1], "--map")) {
        puts("no keyword --map");
        return 2;
    }
    Game game(argv[2]);
    game.run();
    return 0;
}
