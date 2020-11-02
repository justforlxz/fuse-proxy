#define FUSE_USE_VERSION 30

#include <fuse.h>
#include "operations.h"

int main(int argc, char* argv[]) {
    Proxy proxy;
    return proxy.run(argc, argv);
}
