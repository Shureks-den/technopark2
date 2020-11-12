#include <cstring>
#include "Game.h"


int main(int argc, const char** argv) {
    bool stage2 = false;
    int map_argv;

    if (argc < 3) {
        puts("Wrong number of arguments...");
        return 1;
    }
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--map") == 0) {
            map_argv = i + 1;
        }
        if (strcmp(argv[i], "--view-armor") == 0) {
            stage2 = true;
        }
    }

    Game game(argv[map_argv], stage2);
    game.run();
    return 0;
}
