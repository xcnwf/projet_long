#define FUSE_USE_VERSION 31

#include <fuse.h>
#include <string.h>
#include <errno.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

static char base_folder[64];
#define RIT_FOLDER "/rit_fs"
static const char test_file[] = "/test";

static int init_filesystem(struct fuse_conn_info *conn,
			struct fuse_config *cfg)
{
	cfg->kernel_cache = 0;
	char* env_user = getenv("USER");
	if (env_user == NULL || strlen(env_user) > 32) //D'après le man de useradd, la taille max d'un username est de 32 caractères
		return -EINVAL;
	
	strcpy(base_folder,"/home/");
	strcat(base_folder,env_user);
	strcat(base_folder,RIT_FOLDER);

	return 0;
}

static int getattr_callback(const char *path, struct stat *stbuf)
{
	memset(stbuf, 0, sizeof(struct stat));

	if(strncmp(path, "/", 1) == 0) {
		stbuf->st_mode = __S_IFDIR | 0755;
		stbuf->st_nlink = 2;
		return 0;
	}

	if (strncmp(path,test_file,sizeof(test_file)) == 0) {
		char temp[ sizeof(base_folder) + sizeof(test_file) ]; //Possible de mettre -1 pour enlever le nullbyte de trop.
		memset(temp,0,sizeof(temp));
		strcpy(temp,base_folder);
		strcat(temp, test_file);
		strcat(temp,"_orginal");
		stat(temp,stbuf);
		return 0;
	}

	return -EINVAL;
}

static int readdir_callback(const char *path, void *buf, fuse_fill_dir_t filler,
	off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags)
{
	(void) offset;
	(void) fi;
	(void) flags;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0,0);
	filler(buf, "..", NULL, 0,0);

	filler(buf, test_file, NULL, 0,0);

	return 0;
}

static int open_callback(const char *path, struct fuse_file_info *fi)
{
	if (strcmp(path, test_file) != 0)
		return -ENOENT;

	if ((fi->flags & O_ACCMODE) != O_RDONLY)
		return -EACCES;

	return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;

	static int nbr_lectures = 0;
	static int fd = NULL;
	static char temp[128] = {0};

	if (fd == NULL && nbr_lectures == 0) {
		strcpy(temp,base_folder);
		strcat(temp,"/test_original");
		fd = open(temp,O_RDONLY);
	}
	
	if (nbr_lectures == 1 && offset == 0) {
		close(fd);
		strcpy(temp,base_folder);
		strcat(temp,"/test_modified");
		fd = open(temp,O_RDONLY);
	}
	
	lseek(fd,offset,SEEK_SET);
	size = read(fd,buf,size);


	nbr_lectures++;
	return size;
}

static const struct fuse_operations rit_fs = {
	.init       = init_filesystem,
	.getattr	= getattr_callback,
	.readdir	= readdir_callback,
	.open		= open_callback,
	.read		= read_callback,
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &rit_fs, NULL);
}