/* -stat.hpp----------------------------------------------------------------- */
#include <fuse.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

/* -Stat--------------------------------------------------------------------- */
class Stat: public stat {
public:
	Stat() {
		st_mode		= 0;
		st_ino		= 0;
		st_dev		= 0;
		st_nlink	= 0;
		st_uid		= 0;
		st_gid		= 0;
		st_size		= 0;
		st_atime	= 0;
		st_mtime	= 0;
		st_ctime	= 0;
	}

	Stat& setFile() {
		st_mode		= (S_IFREG | 0644);
		return *this;
	}

	Stat& setDirectory() {
		st_mode		= (S_IFDIR | 0755);
		st_nlink	= 2;
		return *this;
	}

	Stat& setDefaultContext(int uid = 0, int gid = 0) {
		struct fuse_context *context;
		time_t timer;

		// get fuse context
		context =  fuse_get_context();
		if (uid == 0) uid = context->uid;
		if (gid == 0) gid = context->gid;

		// set user, group id
		st_uid = uid;
		st_gid = gid;

		// set create time
		time(&timer);
		st_ctime = timer;

		return *this;
	}
};

