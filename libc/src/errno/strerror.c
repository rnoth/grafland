#include <gerrno.h>


/* x86 ( incomplete )  */
char _messages[1000][100] = { 
	"\0",					/* (not used)	0	*/
	"Operation not permitted.\0",		/* EPERM	1	*/
	"No such file or directory.\0",		/* ENOENT	2	*/
	"No such process.\0",			/* ESRCH	3	*/
	"Interrupted function.\0",		/* EINTR	4	*/
	"\0",					/* ?		5	*/
	"No such device or address.\0",		/* ENXTA	6	*/
	"Argument list too long.\0",		/* E2BIG	7	*/
	"Executable file format error.\0",	/* ENOEXEC	8	*/
	"\0",					/* ?		9	*/
	"No child processes.\0",		/* ECHILD	10	*/
	"Resource unavailable, try again.\0", 	/* EAGAIN	11	*/
	"Not enough space.\0", 			/* ENOMEM	12	*/
	"Permission denied.\0",			/* EACCESS	13	*/
	"Bad address.\0",			/* EFAULT	14	*/
	"\0",					/* ?		15	*/
	"Device or resource busy.\0",		/* EBUSY	16	*/
	"File exists.\0",			/* EEXIST	17	*/
	"Cross-device link.\0",			/* EXDEV	18	*/
	"No such device.\0",			/* ENODEV	19	*/
	"Not a directory.\0",			/* ENOTDIR	20	*/
	"Is a directory.\0",			/* EISDIR	21	*/
	"Invalid argument.\0",			/* EINVAL	22	*/
	"Too many files open in system.\0",	/* ENFILE	23	*/
	"Too many open files.\0",		/* EMFILE	24	*/
	"Inappropriate I/O control operation.\0",/*ENOTTY	25	*/
	"Text file busy.\0",			/* ETXTBSY	26	*/
	"File too large.\0",
	"No space left on device.\0",
	"Invalid seek.\0",
	"Read-only file system.\0",
	"Too many links.\0",
	"Broken pipe.\0",
	"Mathematics argument out of doma.\0",
	"Result too large.\0",
	"\0"
	"Filename too long.\0",
	"No locks available.\0",
	"Function not supported.\0",
	"Directory not empty.\0",
	"Too many levels of symbolic links.\0",
	"\0",
	"No message of the desired type.\0",
	"Identifier removed.\0",
	"\0",
	"\0",
	"\0",
	"\0",
	"\0",
	"\0",
	"\0",
	"\0",
};


char *gstrerror(int errnum)
{
	return _messages[errnum];
}
