/* Copyright (C) 2019 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Giancarlo Frix <gfrix@rocketsoftware.com>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#if !defined _SYS_STAT_H && !defined _FCNTL_H
# error "Never include <bits/stat.h> directly; use <sys/stat.h> instead."
#endif

#ifndef _BITS_STAT_H
#define _BITS_STAT_H	1

/* #include <bits/wordsize.h> */

# define _STAT_VER_KERNEL	0
# define _STAT_VER_LINUX	_STAT_VER_KERNEL
# define _STAT_VER		_STAT_VER_LINUX

#define _MKNOD_VER_LINUX	0

/* Tell code we have these members.  */
#define	_STATBUF_ST_BLKSIZE
#define _STATBUF_ST_RDEV

/* Nanosecond resolution time values are not supported.	 */
#ifdef _STATBUF_ST_NSEC
# undef _STATBUF_ST_NSEC
#endif /* _STATBUF_ST_NSEC */

#include <bits/types.h>

/* Get struct stat and struct stat64, which are the same for us.  */
struct stat
{
#include <bits/bpxystat.h>
  /* Implementation defined additions. Any fields after this are
     untouched by the actual syscall, and must be initialized by libc
     after the syscall returns. These fields are added to add
     compatibility.  */
# ifdef __USE_XOPEN2K8
  /* Nanosecond resolution timestamps are stored in a format
     equivalent to 'struct timespec'.  This is the type used
     whenever possible but the Unix namespace rules do not allow the
     identifier 'timespec' to appear in the <sys/stat.h> header.
     Therefore we have to handle the use of this header in strictly
     standard-compliant sources special.  */
  struct timespec st_atim;		/* Time of last access.	 */
  struct timespec st_mtim;		/* Time of last modification.  */
  struct timespec st_ctim;		/* Time of last status change.	*/
#  define st_atime st_atim.tv_sec	/* Backward compatibility.  */
#  define st_mtime st_mtim.tv_sec
#  define st_ctime st_ctim.tv_sec
# else
  __time_t st_atime;			/* Time of last access.	 */
  unsigned long int st_atimensec;	/* Nscecs of last access.  */
  __time_t st_mtime;			/* Time of last modification.  */
  unsigned long int st_mtimensec;	/* Nsecs of last modification.	*/
  __time_t st_ctime;			/* Time of last status change.	*/
  unsigned long int st_ctimensec;	/* Nsecs of last status change.	 */
# endif /* __USE_XOPEN2K8  */
};

#ifdef __USE_LARGEFILE64
struct stat64
{
#include <bits/bpxystat.h>
  /* Implementation defined additions. Any fields after this are
     untouched by the actual syscall, and must be initialized by libc
     after the syscall returns. These fields are added to add
     compatibility.  */
# ifdef __USE_XOPEN2K8
  /* Nanosecond resolution timestamps are stored in a format
     equivalent to 'struct timespec'.  This is the type used
     whenever possible but the Unix namespace rules do not allow the
     identifier 'timespec' to appear in the <sys/stat.h> header.
     Therefore we have to handle the use of this header in strictly
     standard-compliant sources special.  */
  struct timespec st_atim;		/* Time of last access.	 */
  struct timespec st_mtim;		/* Time of last modification.  */
  struct timespec st_ctim;		/* Time of last status change.	*/
#  define st_atime st_atim.tv_sec	/* Backward compatibility.  */
#  define st_mtime st_mtim.tv_sec
#  define st_ctime st_ctim.tv_sec
# else
  __time_t st_atime;			/* Time of last access.	 */
  unsigned long int st_atimensec;	/* Nscecs of last access.  */
  __time_t st_mtime;			/* Time of last modification.  */
  unsigned long int st_mtimensec;	/* Nsecs of last modification.	*/
  __time_t st_ctime;			/* Time of last status change.	*/
  unsigned long int st_ctimensec;	/* Nsecs of last status change.	 */
# endif /* __USE_XOPEN2K8  */
};
#endif /* __USE_LARGEFILE64  */

/* TODO: define the __S_* constants */

/* Encoding of the file mode.  */

#define __S_IFMT	0xFF000000 /* These bits determine file type.  */

/* File types.	*/
#define __S_IFDIR	0x01000000 /* Directory.  */
#define __S_IFCHR	0x02000000 /* Character device.	 */
#define __S_IFBLK	0x06000000 /* Block device.  */
#define __S_IFREG	0x03000000 /* Regular file.  */
#define __S_IFIFO	0x04000000 /* FIFO.  */
#define __S_IFLNK	0x05000000 /* Symbolic link.  */
#define __S_IFSOCK	0x07000000 /* Socket.  */

/* POSIX.1b objects.  Note that these macros always evaluate to zero.  But
   they do it by enforcing the correct use of the macros.  */
#define __S_TYPEISMQ(buf)  ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSEM(buf) ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSHM(buf) ((buf)->st_mode - (buf)->st_mode)

/* Protection bits.  */

#define	__S_ISUID	04000	/* Set user ID on execution.  */
#define	__S_ISGID	02000	/* Set group ID on execution.  */
#define	__S_ISVTX	01000	/* Save swapped text after use (sticky).
				   NOTE: IBM has decided to add some
				   very incompatible behavior for
				   this flag.
				   TODO: figure out exactly what it
				   does. What is normal MVS search
				   order?  */
#define	__S_IREAD	0400	/* Read by owner.  */
#define	__S_IWRITE	0200	/* Write by owner.  */
#define	__S_IEXEC	0100	/* Execute by owner.  */

/* TODO: S_* macros for z/OS-specific filetypes?
   S_ISVMEXTL, etc.  */

/*
  TODO: The following:
#ifdef __USE_ATFILE
# define UTIME_NOW	((1l << 30) - 1l)
# define UTIME_OMIT	((1l << 30) - 2l)
#endif
*/

#endif	/* bits/stat.h */
