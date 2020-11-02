//==================================================================
/**
 *  FuseApp -- A simple C++ wrapper for the FUSE filesystem
 *
 *  Copyright (C) 2019 by James A. Chappell (rlrrlrll@gmail.com)
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  condition:
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __FUSE_APP_H__
#define __FUSE_APP_H__

#ifndef FUSE_USE_VERSION
#define FUSE_USE_VERSION 30
#endif

#include <fuse.h>
#include <cstring>

namespace FUSE {
typedef int (*t_getattr)(const char *, struct stat *, struct fuse_file_info *);
typedef int (*t_readlink)(const char *, char *, size_t);
typedef int (*t_mknod)(const char *, mode_t, dev_t);
typedef int (*t_mkdir)(const char *, mode_t);
typedef int (*t_unlink)(const char *);
typedef int (*t_rmdir)(const char *);
typedef int (*t_symlink)(const char *, const char *);
typedef int (*t_rename)(const char *, const char *, unsigned int);
typedef int (*t_link)(const char *, const char *);
typedef int (*t_chmod)(const char *, mode_t, struct fuse_file_info *);
typedef int (*t_chown)(const char *, uid_t, gid_t, fuse_file_info *);
typedef int (*t_truncate)(const char *, off_t, fuse_file_info *);
typedef int (*t_open)(const char *, struct fuse_file_info *);
typedef int (*t_read)(const char *, char *, size_t, off_t, struct fuse_file_info *);
typedef int (*t_write)(
    const char *, const char *, size_t, off_t, struct fuse_file_info *);
typedef int (*t_statfs)(const char *, struct statvfs *);
typedef int (*t_flush)(const char *, struct fuse_file_info *);
typedef int (*t_release)(const char *, struct fuse_file_info *);
typedef int (*t_fsync)(const char *, int, struct fuse_file_info *);
typedef int (*t_setxattr)(const char *, const char *, const char *, size_t, int);
typedef int (*t_getxattr)(const char *, const char *, char *, size_t);
typedef int (*t_listxattr)(const char *, char *, size_t);
typedef int (*t_removexattr)(const char *, const char *);
typedef int (*t_opendir)(const char *, struct fuse_file_info *);
typedef int (*t_readdir)(const char *,
                         void *,
                         fuse_fill_dir_t,
                         off_t,
                         struct fuse_file_info *,
                         enum fuse_readdir_flags);
typedef int (*t_releasedir)(const char *, struct fuse_file_info *);
typedef int (*t_fsyncdir)(const char *, int, struct fuse_file_info *);
typedef void *(*t_init)(struct fuse_conn_info *, struct fuse_config *cfg);
typedef void (*t_destroy)(void *);
typedef int (*t_access)(const char *, int);
typedef int (*t_create)(const char *, mode_t, struct fuse_file_info *);
typedef int (*t_lock)(const char *, struct fuse_file_info *, int cmd, struct flock *);
typedef int (*t_utimens)(const char *,
                         const struct timespec  tv[2],
                         struct fuse_file_info *fi);
typedef int (*t_bmap)(const char *, size_t blocksize, uint64_t *idx);

#if FUSE_USE_VERSION < 35
typedef int (*t_ioctl)(const char *,
                       int   cmd,
                       void *arg,
#else
typedef int (*t_ioctl)(const char *,
                       unsigned int cmd,
                       void *       arg,
#endif
                       struct fuse_file_info *,
                       unsigned int flags,
                       void *       data);
typedef int (*t_poll)(const char *,
                      struct fuse_file_info *,
                      struct fuse_pollhandle *ph,
                      unsigned *              reventsp);
typedef int (*t_write_buf)(const char *,
                           struct fuse_bufvec *buf,
                           off_t               off,
                           struct fuse_file_info *);
typedef int (*t_read_buf)(const char *,
                          struct fuse_bufvec **bufp,
                          size_t               size,
                          off_t                off,
                          struct fuse_file_info *);
typedef int (*t_flock)(const char *, struct fuse_file_info *, int op);
typedef int (*t_fallocate)(const char *, int, off_t, off_t, struct fuse_file_info *);

template <class T>
class Fuse {
public:
    Fuse()
    {
        memset(&T::operations_, 0, sizeof(struct fuse_operations));
        load_operations_();
    }

    // no copy
    Fuse(const Fuse &) = delete;
    Fuse &operator=(const Fuse &) = delete;

    ~Fuse() = default;

    auto run(int argc, char **argv)
    {
        return fuse_main(argc, argv, Operations(), this);
    }

    auto Operations()
    {
        return &operations_;
    }

    static auto this_()
    {
        return static_cast<T *>(fuse_get_context()->private_data);
    }

private:
    static void load_operations_()
    {
        operations_.getattr     = T::proxy_getattr;
        operations_.readlink    = T::proxy_readlink;
        operations_.mknod       = T::proxy_mknod;
        operations_.mkdir       = T::proxy_mkdir;
        operations_.unlink      = T::proxy_unlink;
        operations_.rmdir       = T::proxy_rmdir;
        operations_.symlink     = T::proxy_symlink;
        operations_.rename      = T::proxy_rename;
        operations_.link        = T::proxy_link;
        operations_.chmod       = T::proxy_chmod;
        operations_.chown       = T::proxy_chown;
        operations_.truncate    = T::proxy_truncate;
        operations_.open        = T::proxy_open;
        operations_.read        = T::proxy_read;
        operations_.write       = T::proxy_write;
        operations_.statfs      = T::proxy_statfs;
        operations_.flush       = T::proxy_flush;
        operations_.release     = T::proxy_release;
        operations_.fsync       = T::proxy_fsync;
        operations_.setxattr    = T::proxy_setxattr;
        operations_.getxattr    = T::proxy_getxattr;
        operations_.listxattr   = T::proxy_listxattr;
        operations_.removexattr = T::proxy_removexattr;
        operations_.opendir     = T::proxy_opendir;
        operations_.readdir     = T::proxy_readdir;
        operations_.releasedir  = T::proxy_releasedir;
        operations_.fsyncdir    = T::proxy_fsyncdir;
        operations_.init        = T::proxy_init;
        operations_.destroy     = T::proxy_destroy;
        operations_.access      = T::proxy_access;
        operations_.create      = T::proxy_create;
        operations_.lock        = T::proxy_lock;
        operations_.utimens     = T::proxy_utimens;
        operations_.bmap        = T::proxy_bmap;
        operations_.ioctl       = T::proxy_ioctl;
        operations_.poll        = T::proxy_poll;
        operations_.write_buf   = T::proxy_write_buf;
        operations_.read_buf    = T::proxy_read_buf;
        operations_.flock       = T::proxy_flock;
        operations_.fallocate   = T::proxy_fallocate;
    }

    static struct fuse_operations operations_;

    static t_getattr     proxy_getattr;
    static t_readlink    proxy_readlink;
    static t_mknod       proxy_mknod;
    static t_mkdir       proxy_mkdir;
    static t_unlink      proxy_unlink;
    static t_rmdir       proxy_rmdir;
    static t_symlink     proxy_symlink;
    static t_rename      proxy_rename;
    static t_link        proxy_link;
    static t_chmod       proxy_chmod;
    static t_chown       proxy_chown;
    static t_truncate    proxy_truncate;
    static t_open        proxy_open;
    static t_read        proxy_read;
    static t_write       proxy_write;
    static t_statfs      proxy_statfs;
    static t_flush       proxy_flush;
    static t_release     proxy_release;
    static t_fsync       proxy_fsync;
    static t_setxattr    proxy_setxattr;
    static t_getxattr    proxy_getxattr;
    static t_listxattr   proxy_listxattr;
    static t_removexattr proxy_removexattr;
    static t_opendir     proxy_opendir;
    static t_readdir     proxy_readdir;
    static t_releasedir  proxy_releasedir;
    static t_fsyncdir    proxy_fsyncdir;
    static t_init        proxy_init;
    static t_destroy     proxy_destroy;
    static t_access      proxy_access;
    static t_create      proxy_create;
    static t_lock        proxy_lock;
    static t_utimens     proxy_utimens;
    static t_bmap        proxy_bmap;
    static t_ioctl       proxy_ioctl;
    static t_poll        proxy_poll;
    static t_write_buf   proxy_write_buf;
    static t_read_buf    proxy_read_buf;
    static t_flock       proxy_flock;
    static t_fallocate   proxy_fallocate;
};
}  // namespace FUSE

#endif
