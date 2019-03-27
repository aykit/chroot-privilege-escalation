#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
    const char *chroot_path = realpath("chroot", NULL);
    if (chroot_path == NULL) {
        perror("realpath");
        return EXIT_FAILURE;
    }

    if (chdir("/") != 0) {
        perror("chdir");
        return EXIT_FAILURE;
    }

    if (chroot(chroot_path) != 0) {
        perror("chroot");
        exit(EXIT_FAILURE);
    }

    if (setenv("run_cmd", "sh", 1) != 0) {
        perror("setenv");
        exit(EXIT_FAILURE);
    }

    const char *path = "./bin/su";
    execl(path, path, NULL);

    perror("exec");
    return EXIT_FAILURE;
}
