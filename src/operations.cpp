#include "operations.h"

#include <fcntl.h>
#include <pwd.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <dirent.h>

// include in one .cpp file
#include "fuse-impl.h"

using namespace std;

static const string root_path = "/";

static const std::list<std::string> root_dir{
    "/Documents",
    "/Pictures",
    "/Downloads",
    "/Music",
    "/Videos"
};

static std::string username()
{
    const uid_t    uid = geteuid();
    struct passwd *pw  = getpwuid(uid);
    return pw ? pw->pw_name : std::string();
}

static std::string original_path(const std::string &realtive)
{
    return std::string("/home/") + username() + realtive;
}

void *Proxy::proxy_init(struct fuse_conn_info *conn, struct fuse_config *cfg)
{
    (void) conn;
    cfg->use_ino = 1;

    /* Pick up changes from lower filesystem right away. This is
	   also necessary for better hardlink support. When the kernel
	   calls the unlink() handler, it does not know the inode of
	   the to-be-removed entry and can therefore not invalidate
	   the cache of the associated inode - resulting in an
	   incorrect st_nlink value being reported for any remaining
	   hardlinks to this inode. */
    cfg->entry_timeout    = 0;
    cfg->attr_timeout     = 0;
    cfg->negative_timeout = 0;

    return nullptr;
}

int Proxy::proxy_getattr(const char *           path,
                         struct stat *          stbuf,
                         struct fuse_file_info *info)
{
    memset(stbuf, 0, sizeof(struct stat));

    const std::string path_{ original_path(path) };
    std::cout << "[getattr]: " << path_ << std::endl;
    int res = lstat(path_.c_str(), stbuf);
    if (res == -1) {
        return -errno;
    }

    return 0;
}

int Proxy::proxy_access(const char *path, int mask)
{
    std::cout << "[access]: " << original_path(path) << std::endl;
    const int res = access(original_path(path).c_str(), mask);
    return res == -1 ? -errno : 0;
}

int Proxy::proxy_readdir(const char *    path,
                         void *          buf,
                         fuse_fill_dir_t filler,
                         off_t,
                         struct fuse_file_info *,
                         enum fuse_readdir_flags)
{
    // need access control

    if (path == root_path) {
        filler(buf, ".", nullptr, 0, FUSE_FILL_DIR_PLUS);
        filler(buf, "..", nullptr, 0, FUSE_FILL_DIR_PLUS);
        for (const std::string& path : root_dir) {
            filler(buf, path.c_str() + 1, nullptr, 0, FUSE_FILL_DIR_PLUS);
        }
        return 0;
    }

    DIR *          dp;
    struct dirent *de;

    dp = opendir(original_path(path).c_str());
    if (dp == nullptr) {
        return -errno;
    }

    while ((de = readdir(dp)) != nullptr) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino  = de->d_ino;
        st.st_mode = de->d_type << 12;
        if (filler(buf, de->d_name, &st, 0, FUSE_FILL_DIR_PLUS)) break;
    }

    closedir(dp);
    return 0;
}

int Proxy::proxy_open(const char *path, struct fuse_file_info *fi)
{
    // need access control

    const int res = open(original_path(path).c_str(), fi->flags);
    if (res == -1) {
        return -errno;
    }

    fi->fh = res;

    return 0;
}

int Proxy::proxy_read(
    const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    int fd = fi ? open(original_path(path).c_str(), O_RDONLY) : fi->fh;

    if (fd == -1) return -errno;

    int res = pread(fd, buf, size, offset);

    if (res == -1) res = -errno;

    if (!fi) {
        close(fd);
    }

    return res;
}

int Proxy::proxy_write(const char *           path,
                           const char *           buf,
                           size_t                 size,
                           off_t                  offset,
                           struct fuse_file_info *fi)
{
    int fd = fi ? open(original_path(path).c_str(), O_WRONLY) : fi->fh;

    if (fd == -1) {
        return -errno;
    }

    int res = pwrite(fd, buf, size, offset);

    if (res == -1) {
        res = -errno;
    }

    if (!fi) {
        close(fd);
    }

    return res;
}

int Proxy::proxy_symlink(const char *from, const char *to)
{
    return symlink(from, to) == -1 ? -errno : 0;
}

int Proxy::proxy_readlink(const char *path, char *buf, size_t size)
{
    int res = readlink(original_path(path).c_str(), buf, size - 1);
    if (res == -1) return -errno;

    buf[res] = '\0';
    return 0;
}
