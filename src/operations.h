#ifndef OPERATIONS_HEAD
#define OPERATIONS_HEAD

#include "fuse-impl.h"
#include "fuse.h"

class Proxy : public FUSE::Fuse<Proxy> {
public:
    Proxy() {}

    ~Proxy() {}

    static void *proxy_init(struct fuse_conn_info *, struct fuse_config *cfg);

    static int proxy_getattr(const char *, struct stat *, struct fuse_file_info *);

    static int proxy_access(const char *path, int mask);

    static int proxy_readdir(const char *           path,
                             void *                 buf,
                             fuse_fill_dir_t        filler,
                             off_t                  offset,
                             struct fuse_file_info *fi,
                             enum fuse_readdir_flags);

    static int proxy_open(const char *path, struct fuse_file_info *fi);

    static int proxy_read(const char *           path,
                          char *                 buf,
                          size_t                 size,
                          off_t                  offset,
                          struct fuse_file_info *fi);

    static int proxy_write(const char *           path,
                           const char *           buf,
                           size_t                 size,
                           off_t                  offset,
                           struct fuse_file_info *fi);

    static int proxy_symlink(const char *from, const char *to);

    static int proxy_readlink(const char *path, char *buf, size_t size);
};

#endif  //
