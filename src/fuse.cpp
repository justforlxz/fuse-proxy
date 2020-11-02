//==================================================================
/**
 *  FuseApp -- A simple C++ wrapper for the FUSE filesystem
 *
 *  Copyright (C) 2017 by James A. Chappell (rlrrlrll@gmail.com)
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

#include "fuse.h"

template <class T>
FUSE::t_getattr FUSE::Fuse<T>::proxy_getattr = nullptr;
template <class T>
FUSE::t_readlink FUSE::Fuse<T>::proxy_readlink = nullptr;
template <class T>
FUSE::t_mknod FUSE::Fuse<T>::proxy_mknod = nullptr;
template <class T>
FUSE::t_mkdir FUSE::Fuse<T>::proxy_mkdir = nullptr;
template <class T>
FUSE::t_unlink FUSE::Fuse<T>::proxy_unlink = nullptr;
template <class T>
FUSE::t_rmdir FUSE::Fuse<T>::proxy_rmdir = nullptr;
template <class T>
FUSE::t_symlink FUSE::Fuse<T>::proxy_symlink = nullptr;
template <class T>
FUSE::t_rename FUSE::Fuse<T>::proxy_rename = nullptr;
template <class T>
FUSE::t_link FUSE::Fuse<T>::proxy_link = nullptr;
template <class T>
FUSE::t_chmod FUSE::Fuse<T>::proxy_chmod = nullptr;
template <class T>
FUSE::t_chown FUSE::Fuse<T>::proxy_chown = nullptr;
template <class T>
FUSE::t_truncate FUSE::Fuse<T>::proxy_truncate = nullptr;
template <class T>
FUSE::t_open FUSE::Fuse<T>::proxy_open = nullptr;
template <class T>
FUSE::t_read FUSE::Fuse<T>::proxy_read = nullptr;
template <class T>
FUSE::t_write FUSE::Fuse<T>::proxy_write = nullptr;
template <class T>
FUSE::t_statfs FUSE::Fuse<T>::proxy_statfs = nullptr;
template <class T>
FUSE::t_flush FUSE::Fuse<T>::proxy_flush = nullptr;
template <class T>
FUSE::t_release FUSE::Fuse<T>::proxy_release = nullptr;
template <class T>
FUSE::t_fsync FUSE::Fuse<T>::proxy_fsync = nullptr;
template <class T>
FUSE::t_setxattr FUSE::Fuse<T>::proxy_setxattr = nullptr;
template <class T>
FUSE::t_getxattr FUSE::Fuse<T>::proxy_getxattr = nullptr;
template <class T>
FUSE::t_listxattr FUSE::Fuse<T>::proxy_listxattr = nullptr;
template <class T>
FUSE::t_removexattr FUSE::Fuse<T>::proxy_removexattr = nullptr;
template <class T>
FUSE::t_opendir FUSE::Fuse<T>::proxy_opendir = nullptr;
template <class T>
FUSE::t_readdir FUSE::Fuse<T>::proxy_readdir = nullptr;
template <class T>
FUSE::t_releasedir FUSE::Fuse<T>::proxy_releasedir = nullptr;
template <class T>
FUSE::t_fsyncdir FUSE::Fuse<T>::proxy_fsyncdir = nullptr;
template <class T>
FUSE::t_init FUSE::Fuse<T>::proxy_init = nullptr;
template <class T>
FUSE::t_destroy FUSE::Fuse<T>::proxy_destroy = nullptr;
template <class T>
FUSE::t_access FUSE::Fuse<T>::proxy_access = nullptr;
template <class T>
FUSE::t_create FUSE::Fuse<T>::proxy_create = nullptr;
template <class T>
FUSE::t_lock FUSE::Fuse<T>::proxy_lock = nullptr;
template <class T>
FUSE::t_utimens FUSE::Fuse<T>::proxy_utimens = nullptr;
template <class T>
FUSE::t_bmap FUSE::Fuse<T>::proxy_bmap = nullptr;
template <class T>
FUSE::t_ioctl FUSE::Fuse<T>::proxy_ioctl = nullptr;
template <class T>
FUSE::t_poll FUSE::Fuse<T>::proxy_poll = nullptr;
template <class T>
FUSE::t_write_buf FUSE::Fuse<T>::proxy_write_buf = nullptr;
template <class T>
FUSE::t_read_buf FUSE::Fuse<T>::proxy_read_buf = nullptr;
template <class T>
FUSE::t_flock FUSE::Fuse<T>::proxy_flock = nullptr;
template <class T>
FUSE::t_fallocate FUSE::Fuse<T>::proxy_fallocate = nullptr;

template <class T>
struct fuse_operations FUSE::Fuse<T>::operations_;
