// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2000-2001 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
/*
 *      mmap_fill
 * 
 *      use memory mapping to fill a filesystem! :)
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <strings.h>
#include <errno.h>


char * progname;
int	fd;      		/* file descriptor */
addr_t	ptr;			/* mapped pointers */
long long  junk[512];

main(int argc, char * argv[])
{
  printf("Sizeof junk = %d \n", junk);
  exit(0);

  if ((progname = strrchr(argv[0], '/')) == NULL)
    progname = argv[0];
  else
    progname++;
  
  if (argc < 2) {
    fprintf(stderr,"Usage: %s filename\n", progname);
    exit(1);
  }
  
  fd = open(argv[1], O_RDWR|O_CREAT, 0644);
  if (fd < 0) {
    fprintf(stderr,"%s: cannot open %s\n", progname, argv[1]);
    perror(argv[1]);
    exit(3);
  }
  
  ptr = mmap(NULL, len, PROT_WRITE, MAP_SHARED|MAP_AUTOGROW , fd, 0);
  if (ptr == MAP_FAILED) {
    fprintf(stderr,"%s: cannot mmap %s\n", progname, argv[1]);
    perror(argv[1]);
    exit(3);
  }
  
  while (1) {
    bcopy(junk, ptr, size_of(junk));
    ptr+=size_of(junk);
  }
  printf("%s complete.\n", progname);
  return 0;
}
