/* -fuse.cpp----------------------------------------------------------------- */
#include <iostream>
#include <map>
#include <fuse.h>
#include <errno.h>

/* -boost-------------------------------------------------------------------- */
#include <boost/filesystem/path.hpp>

/* -------------------------------------------------------------------------- */
#include "metadata.hpp"

using namespace std;

/* -Fuse--------------------------------------------------------------------- */
class Fuse: public fuse_operations {
private:
	static Metadata metadata;

public:
	Fuse() {
		/*
		 * Register Fuse Operation Function
		 */
		init	= fuse_init;
		getattr	= fuse_getattr;

		/*
		 * File System Operation
		 */
		mkdir	= fuse_mkdir;
		readdir	= fuse_readdir;

		/*
		 * File Operation Function
		 */
		open	= fuse_open;
		read	= fuse_read;
		write	= fuse_write;
	}

	static void* fuse_init(struct fuse_conn_info *conn) {
		//boost::filesystem::path file_system_path("/");
		//string file_path = file_system_path.string();

		//struct fuse_context *context =  fuse_get_context();
		//struct stat root;

		//root.st_mode = S_IFDIR | 0755;
		//root.st_nlink = 2;
		//root.st_uid = context->uid;
		//root.st_gid = context->gid;

		//root.st_uid = 1000;
		//root.st_gid = 1000;

		//file_system_map[file_path] = root;

		//cout << "uid = " << root.st_uid << endl;
		//cout << "gid = " << root.st_gid << endl;

		return NULL;
	}

	static int fuse_getattr(const char *path, struct stat *stbuf) {
		if (metadata.isExist(path) == false) return -ENOENT;;
		*stbuf = metadata.stat(path);
		return 0;

		//boost::filesystem::path file_system_path(path);
		//string file_path = file_system_path.string();

		//map<string, struct stat>::iterator file_system_map_iter = file_system_map.find(file_path);

		//if (file_system_map_iter != file_system_map.end()) {
		//	*stbuf = file_system_map_iter->second;
		//	cout << "Find Path" << endl;
		//} else {
		//	cout << "Not Found Path" << endl;
		//}

		//int res = 0;
		//struct fuse_context *context =  fuse_get_context();
		//memset(stbuf, 0, sizeof(struct stat));

		//if (strcmp(path, "/") == 0) {
		//	stbuf->st_mode = S_IFDIR | 0755;
		//	stbuf->st_nlink = 2;
		//	stbuf->st_uid = context->uid;
		//	stbuf->st_gid = context->gid;
		//} else if (strcmp(path, "/file") == 0) {
		//	stbuf->st_mode = S_IFREG | 0755;
		//	stbuf->st_nlink = 1;
		//	stbuf->st_size = 0;
		//	stbuf->st_uid = context->uid;
		//	stbuf->st_gid = context->gid;
		//} else {
		//	res = -ENOENT;
		//}

		//return res;
	}

	/* ---------------------------------------------------------------------
	 *			File System Operation Functions
	 * ------------------------------------------------------------------ */
	static int fuse_readdir(const char *path, void *buff,
		fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
		if (strcmp(path, "/") != 0) return -ENOENT;

		filler(buff, ".", NULL, 0);
		filler(buff, "..", NULL, 0);
		filler(buff, "test", NULL, 0);

		return 0;
	}

	static int fuse_mkdir(const char *path, mode_t mode) {
		cout << "Make Directory-----------------------------" << endl;
		if (metadata.isExist(path) == false)
			metadata.make_directory(path);
		cout << "Make Directory-----------------------------" << endl;
		return 0;
	}

	/* ---------------------------------------------------------------------
	 *			File Operation Functions
	 * ------------------------------------------------------------------ */
	static int fuse_open(const char *path, struct fuse_file_info *fi) {
		return 0;
	}

	static int fuse_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
		return 0;
	}

	static int fuse_write(const char * path, const char *data, size_t size, off_t offset, struct fuse_file_info *fi) {
		return 10;
	}
};

/* -StaticAttribute---------------------------------------------------------- */
Metadata Fuse::metadata;

