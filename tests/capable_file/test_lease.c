#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/posix_types.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Test the fcntl F_SETLEASE operation on a file whose name is given as 
 * the first argument.
 */
int main(int argc, char **argv) {

  int fd;
  int rc;

  if( argc != 2 ) {
    printf("usage: %s filename\n", argv[0]);
    exit(2);
  }

  fd = open(argv[1], O_RDONLY, 0);
  
  if(fd == -1) {
    perror("test_lease:open");
    exit(2);
  }

  rc = fcntl(fd, F_SETLEASE, 0);
  if( rc == -1 ) {
    perror("test_lease:F_SETLEASE");
    close(fd);
    exit(1);
  }

  close(fd);
  exit(0);

}
