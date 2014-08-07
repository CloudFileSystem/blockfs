/* -sunfile.hpp-------------------------------------------------------------- */
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <openssl/md5.h>

/* -SunFile------------------------------------------------------------------ */
class SunFile {
private:
	int chunk_size;
	std::string *base_path;
	std::string *file_name;
	unsigned char *file_hash;
	char *file_hash_string;

public:
	/*
	 * Sun File IO Class Constructor
	 */
	SunFile(char *fname, int default_chunk_size = 4096) {
		/*
		 * Setting up file name
		 * Setting up file hash
		 * Setting up default chunk size
		 */
		file_name = new std::string(fname);
		file_hash = new unsigned char[MD5_DIGEST_LENGTH];
		file_hash_string = new char[((2 * MD5_DIGEST_LENGTH) + 1)];
		chunk_size = default_chunk_size;

		/*
		 * Get File Name Hash Value
		 */
		MD5((unsigned char *)fname, std::strlen(fname), (unsigned char *)file_hash);

		/*
		 * Convert Hash Value to String
		 */
		for (int i = 0; i < 16; i++) {
			std::sprintf(&file_hash_string[i * 2], "%02x", (unsigned int)file_hash[i]);
		}
	}

	/*
	 * Sun File IO Class Destructor
	 */
	~SunFile() {
		/*
		 * Free file name
		 * Free file hash
		 * Free file hash_string
		 */
		delete file_name;
		delete file_hash;
		delete file_hash_string;
	}

	/*
	 * File Operation Of Write
	 */
	int write(char *data, int size) {
		int i;
		int n;
		int r;

		n = size / chunk_size;
		r = size % chunk_size;

		for (i = 0; i < n; i++) {
			write_chunk((data + i * chunk_size), chunk_size, i);
		}

		if (r != 0) {
			write_chunk((data + i * chunk_size), r, i);
		}

		return 0;
	}

	/*
	 * File Operation Of Read
	 */
	int read(char *data, int size) {
		int i;
		int n;
		int r;

		n = size / chunk_size;
		r = size % chunk_size;

		for (i = 0; i < n; i++) {
			read_chunk((data + i * chunk_size), chunk_size, i);
		}

		if (r != 0) {
			read_chunk((data + i * chunk_size), r, i);
		}

		return 0;
	}

protected:
	/*
	 * write_chunk
	 */
	int write_chunk(char *data, int size, int offset) {
		FILE *file;
		char filename[256];

		std::cout << size << std::endl;
		std::cout << offset << std::endl;
		std::cout << "write chunk" << std::endl;

		// ファイル名を作成(Hashの方がいいのかも知れない)
		sprintf(filename, "./block/%0200d.blk", offset);

		// ファイルを開いて書き込みを行う
		file = fopen(filename, "wb");
		fwrite(data, sizeof(char), size, file);

		fclose(file);

		return 0;
	}
	/*
	 * read_chunk
	 */
	int read_chunk(char *data, int size, int offset) {
		FILE *file;
		char filename[256];

		std::cout << size << std::endl;
		std::cout << offset << std::endl;
		std::cout << "read chunk" << std::endl;

		// ファイル名を作成(Hashの方がいいのかも知れない)
		sprintf(filename, "./block/%0200d.blk", offset);

		// ファイルを開いて読み込みを行う
		file = fopen(filename, "rb");
		fread(data, sizeof(char), size, file);

		fclose(file);
		return 0;
	}
};

