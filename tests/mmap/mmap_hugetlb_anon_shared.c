#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#define LENGTH (2*1024*1024)

int main(void)
{
	char *ptr;

	ptr = mmap(NULL, LENGTH, PROT_READ | PROT_WRITE | PROT_EXEC,
		   MAP_SHARED | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
	if (ptr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	exit(0);
}
