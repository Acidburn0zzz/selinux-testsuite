#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/mman.h>
#include<selinux/selinux.h>

/*
 * Test the mmap file operation on a file whose name is given as the first
 * argument. The second argument must be the SID we are to use to test
 * the actual mmap() operation by changing the SID of the file we are
 * given.
 */

int main(int argc, char **argv)
{

	int fd;
	void *ptr;
	int rc;

	if( argc != 3 ) {
		printf("usage: %s filename context\n", argv[0]);
		exit(2);
	}

	fd = open(argv[1], O_RDWR, 0);

	if(fd == -1) {
		perror("test_mmap:open");
		exit(2);
	}

	rc = fsetfilecon(fd, argv[2]);
	if (rc < 0) {
		perror("test_mmap:fsetfilecon");
		exit(2);
	}

	ptr = mmap(0, 1024, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd,
		   getpagesize());
	if( ptr == MAP_FAILED ) {
		perror("test_mmap:mmap");
		close(fd);
		exit(1);
	}

	close(fd);
	exit(0);

}
