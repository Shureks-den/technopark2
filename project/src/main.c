#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    int fdin;
    void *src;
    struct stat statbuf;
    const char *path_to_eml = argv[1];
    puts(path_to_eml);
    fdin = open(path_to_eml, O_RDONLY);
    if (fstat(fdin, &statbuf) < 0 ) {
        puts("Error");
    }
    if ( (src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED) {
        puts("error");
    }
    close(fdin);
    puts(src);
    printf("%ld", strlen(src));
    printf("%ld\n", sizeof(src));
    return 0;
}
