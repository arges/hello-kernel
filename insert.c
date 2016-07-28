#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MODPATH    "/snap/hello-kernel/current/hello.ko"

static inline int finit_module(int fd, const char *uargs, int flags)
{
    return syscall(__NR_finit_module, fd, uargs, flags);
}

static inline int delete_module(const char *name, int flags)
{
    return syscall(__NR_delete_module, name, flags);
}

int main(void)
{
    uid_t uid;
    long ret;
    int fd;

    /* Load module */
    fd = open(MODPATH, O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        perror("Unable to open module file");
        return -1;
    }
    ret = finit_module(fd, "", 0);
    if (ret != 0) {
        perror("Error when loading module");
        close(fd);
        return -1;
    }
    close(fd);

    /* Wait a bit for it to load */
    sleep(1);

    /* Unload module */
    ret = delete_module("hello", 0);
    if (ret != 0) {
        perror("Error when unloading module");
        close(fd);
        return -1;
    }

    return 0;
}
