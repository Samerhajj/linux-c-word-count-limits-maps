#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit lim;
    getrlimit(RLIMIT_STACK,&lim);
    printf("Maximum Stack Size: %ld\n",lim.rlim_cur);
    getrlimit(RLIMIT_NPROC,&lim);
    printf("Maximum Number of Processes: %ld\n", lim.rlim_cur);
    getrlimit(RLIMIT_NOFILE,&lim);
    printf("Maximum Number of File Descriptors: %ld\n", lim.rlim_cur);
    return 0;
}
