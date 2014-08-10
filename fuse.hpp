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
		rmdir	= fuse_rmdir;
		readdir	= fuse_readdir;

		/*
		 * File Operation Function
		 */
		access	= fuse_access;
		open	= fuse_open;
		create	= fuse_create;
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
	}

	/* ---------------------------------------------------------------------
	 *			File System Operation Functions
	 * ------------------------------------------------------------------ */
	static int fuse_readdir(const char *path, void *buff,
		fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {

		filler(buff, ".", NULL, 0);
		filler(buff, "..", NULL, 0);

		vector<string> directories = metadata.list_directory(path);
		vector<string>::iterator it = directories.begin();
		for (it = directories.begin(); it != directories.end(); it++) {
			cout << it->c_str() << "\t" << strcmp(it->c_str(), "/") << endl;
			if (strcmp(it->c_str(), "/") != 0)
				filler(buff, it->c_str(), NULL, 0);
		}

		return 0;
	}

	static int fuse_mkdir(const char *path, mode_t mode) {
		if (metadata.isExist(path) == false)
			metadata.make_directory(path);
		return 0;
	}

	static int fuse_rmdir(const char *path) {
		if (metadata.isExist(path) == true)
			metadata.remove_directory(path);
		return 0;
	}

	/* ---------------------------------------------------------------------
	 *			File Operation Functions
	 * ------------------------------------------------------------------ */
	static int fuse_access(const char *path, int val) {
		cout << "-ACCESS---------------------------------------" << endl;
		return 0;
	}

	static int fuse_open(const char *path, struct fuse_file_info *fi) {
		if (metadata.isExist(path) == false) return -ENOENT;;

		cout << "-OPEN---------------------------------------" << endl;
		return 0;
	}

	static int fuse_create(const char *path, mode_t mode, struct fuse_file_info *info) {
		cout << "-CREATE---------------------------------------" << endl;
		metadata.make_file(path);
		return fuse_open(path, info);
	}

	static int fuse_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
		return 0;
	}

	static int fuse_write(const char * path, const char *data, size_t size, off_t offset, struct fuse_file_info *fi) {
		return 0;
	}
};

/* -StaticAttribute---------------------------------------------------------- */
Metadata Fuse::metadata;

