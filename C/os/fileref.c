#include "csapp.h"

static char buf[256];

#define LINE1 49
#define LINE2 33
#define LINE3 78

static void do_read(int fd) {
  /* TODO: Spawn a child. Read from the file descriptor in both parent and
   * child. Check how file cursor value has changed in both processes. */
	pid_t pid;
	pid = Fork();
	if(pid==0)
	{
		printf("child, fork = %d  - pid: %d: ", pid, getpid());
		off_t off = lseek(fd,0,SEEK_CUR);
		printf("child offset %ld\n", off);
		if(read(fd, buf, 5))
			printf("Child - %s\n", buf);
	}
	else
	{
		printf("parent of %d - pid: %d: ", pid, getpid());
		off_t off = lseek(fd,0,SEEK_CUR);
		printf("parent offset %ld\n", off);
		if(read(fd, buf, 6))
			printf("Parent - %s\n", buf);
	}
  exit(0);
}

static void do_close(int fd) {
  /* TODO: In the child close file descriptor, in the parent wait for child to
   * die and check if the file descriptor is still accessible. */
	pid_t pid;
	pid = Fork();	
	if(pid == 0)
	{
		printf("Child %d - closing descriptor\n", pid);
		close(fd);
	}
	else
	{	
		printf("Parent %d - waiting\n", pid);
		int child_pid = wait(NULL);
		if(read(fd, buf, 20))
			printf("Parent %d - %s\n", child_pid, buf);
	}
  exit(0);
}

int main(int argc, char **argv) {
  if (argc != 2)
    app_error("Usage: %s [read|close]", argv[0]);

  int fd = Open("test.txt", O_RDONLY, 0);

  if (!strcmp(argv[1], "read"))
    do_read(fd);
  if (!strcmp(argv[1], "close"))
    do_close(fd);
  app_error("Unknown variant '%s'", argv[1]);
}
