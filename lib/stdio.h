/* libraries */
/* --------- */ 
#include <stddef.h>
#include <stdarg.h>
#include <fcntl.h>

/* local libraries */
/* --------------- */
#include "itoa.h"
#ifdef HASLIBM
#include "dtoa.h"
#endif

/* defines */
/* ------- */
#define GNULL		0
#define EOF		(-1)
#define GBUFSIZ		1024
#define OPEN_MAX	20	/* max #files open at once */ 
#define gstdin		(&_iob[0])
#define gstdout		(&_iob[1])
#define gstderr		(&_iob[2]) 
#define feof(p)		((p)->flag & _EOF) != 0)
#define ferror(p)	((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)
#define ggetc(p)	(--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define gputc(x,p) 	(--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define ggetchar()	ggetc(gstdin)
#define gputchar(x)	gputc((x), gstdout)
#define PERMS		0666	/* RW for owner, group, others */

#define GBUFSIZEE 4096
#define IRCBUFSIZ GBUFSIZEE

typedef struct _iobuf {
	int cnt;		/* characters left */
	char *ptr;		/* next character position */
	char *base;		/* location of buffer */
	int flag;		/* mode of file access */
	int fd;			/* file descriptor */
} GFILE;

extern GFILE _iob[OPEN_MAX];

enum _flags {
	_READ	 =	01,	/* file open for reading  01 */	
	_WRITE	=	01,	/* file open for writing  02 */
	_UNBUF	=	01,	/* file is unbuffered  04 */
	_EOF	=	01,	/* EOF has occurred on this file 010 */
	_ERR	=	01	/* error occurred on this file 020 */
};

GFILE _iob[OPEN_MAX] = {	/* stdin, stdout, stderr */
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

/* Function prototypes */ 
/* ------------------- */ 
int _fillbuf(GFILE *);
int _flushbuf(int, GFILE *);
int gggetchar(void);
int ggputchar(char);
size_t ggetline(char [], int);
int gprintf_inter(int, char *, size_t, int, char *, va_list);
int gprintf(char *, ...);
int gsprintf(char *, char *, ...);
int gsnprintf(char *, size_t, char *, ...);
int gdprintf(int, char *, ...);
int gfprintf(GFILE *, char *, ...);
int gvprintf(char *, va_list);
int gvsprintf(char *, char *, va_list);
int gvsnprintf(char *, size_t, char *, va_list);
int gvdprintf(int, char *, va_list);
int gvfprintf(GFILE *, char *, va_list);


/* functions */
/* --------- */

/* single char io  */
int gggetchar(void)
{ 
	static char buf[GBUFSIZEE];
	static char *bufp = buf;
	static size_t i = 0;

        if (i >= (GBUFSIZEE - 1))
		return -1;
	
	if (i == 0) 
	{
		i = read(0, buf, 1);
		bufp = buf;
	}
	
        if ( i-- )
		return  *bufp++;

	return -1;
} 

int ggputchar(char c)
{ 
	char buf[1];
	buf[0] = c;
	return write(1, buf, 1);
}

/* line retrieval */
size_t ggetline(char s[], int lim)
{
        int c;
        size_t i = 0;
        while (--lim > 0 && (c=ggetchar()) != -1 && c != '\n')
                s[i++] = c;
        if (c == '\n')
                s[i++] = c;
        s[i] = '\0';
        return i;
}

/* printf family (variadic and formatted) */
int gprintf_inter(int fd, char *str, size_t lim, int flag, char *fmt, va_list ap)
{ 
	char *p = NULL;
	char *out;
	int i = 0;
	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t zuval = 0; 
	int dval = 0; 
	long lval = 0;
#ifdef HASLIBM
	double fval = 0;
	char ftemp[1025]= { 0 };
#endif

	if (flag == 0) /* printf */
		out = malloc(1025); 
	if (flag == 1 || flag == 2) /* sprintf, snprintf */
		out = str;

	for (p = fmt; *p; p++) 
	{
		if (*p != '%')
		{
			out[i++] = *p;
			continue;
		}
		switch (*++p)
		{
			case 'c':
				cval = va_arg(ap, int);
				out[i++] = cval;
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++) 
					out[i++] = *sval; 
				break;
			case 'd': 
				dval = va_arg(ap, int);
				i += intostrbase(out + i, dval, 10);
				break;
#ifdef HASLIBM
			case 'f':
				fval = va_arg(ap, double); 
				gdtoa(ftemp, fval - (long)fval); 
				i += gsprintf(out + i, "%ld", (long)fval);
				i += gsnprintf(out + i, 7, "%s", ftemp + 1);
				break;
#endif
			case 'l':
				switch (*++p)
				{ 
					case 'd':
						lval = va_arg(ap, long);
						i += intostrbase(out + i, lval, 10);
						break;
#ifdef HASLIBM
					case 'f':
						fval = va_arg(ap, double);
						gdtoa(ftemp, fval - (long)fval);
						i += gsprintf(out + i, "%ld", (long)fval);
						i += gsnprintf(out + i, 7, "%s", ftemp + 1);
						break;
#endif
					default:
						break;
				}
				break;
			case 'z':
				switch (*++p)
				{ 
					case 'u':
						zuval = va_arg(ap, size_t);
						i += uintostrbase(out + i, zuval, 10);
					default:
						break;
				}
				break;
			default:
				out[i++] = *p;
				break;
		}
	}

	
	if ( flag == 2) 
		i = lim;

	out[i + 1] = '\0';


	if ( flag == 0 )
		i = write(fd, out, i); /* if writing to an fd, then redefine the ret */

	return i;
}

int gprintf(char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsprintf(char *str, char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsnprintf(char *str, size_t lim, char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gdprintf(int fd, char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gvprintf(char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsprintf(char *str, char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsnprintf(char *str, size_t lim, char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvdprintf(int fd, char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gfprintf(GFILE *stream, char *fmt, ...) /* not implemented */
{
	int ret  = 0;
	va_list argptr;
	(void) stream; // ................
	va_start(argptr, fmt);
	ret = gprintf_inter(1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvfprintf(GFILE *stream, char *fmt, va_list argptr) /* not implemented */
{
	int ret  = 0;
	(void) stream; // ................
	ret = gprintf_inter(1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

/* fopen family (not implemented) */
GFILE *gfopen(char *name, char *mode)
{
	int fd;
	GFILE *fp;
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return GNULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;		/* found free slot */
	if (fp >= _iob + OPEN_MAX)	 /* no free slots */
		return GNULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)		 /* couldn't access name */
		return GNULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = GNULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(GFILE *fp)
{
	int bufsize;
	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : GBUFSIZ;
	if (fp->base == GNULL)		/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == GNULL)
			 return EOF;		 /* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			 fp->flag |= _EOF;
		else
			 fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* _flushbuf */
int _flushbuf(int c, GFILE *f)
{
	int num_written, bufsize;
	unsigned char uc = c;	

	if ((f->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
		return EOF;
	if (f->base == GNULL && ((f->flag & _UNBUF) == 0)) {
		/* no buffer yet */
		if ((f->base = malloc(GBUFSIZ)) == GNULL) 
			/* couldn't allocate a buffer, so try unbuffered */
			f->flag |= _UNBUF;
		else {
			f->ptr = f->base;
			f->cnt = GBUFSIZ - 1;
		}
	}
	if (f->flag & _UNBUF) {
		/* unbuffered write */
		f->ptr = f->base = GNULL;
		f->cnt = 0;
		if (c == EOF)
			return EOF;
		num_written = write(f->fd, &uc, 1);
		bufsize = 1;
	} else {
		/* buffered write */
		if (c != EOF)
		{
			//f->ptr = uc;
			f->ptr++;
		}
		bufsize = (int)(f->ptr - f->base);
		num_written = write(f->fd, f->base, bufsize);
		f->ptr = f->base;
		f->cnt = GBUFSIZ - 1;
	}
	if (num_written == bufsize)
		return c;
	else {		 
		f->flag |= _ERR;
		return EOF;
	} 
}

int gfflush(GFILE *f)
{
	int retval;
	int i;

	retval = 0;
	if (f == GNULL) {
	/* flush all output streams */ 
		for (i = 0; i < OPEN_MAX; i++) {
			//if ((_iob[i]->flag & _WRITE) && (gfflush(EOF, _iob[i]) == -1))
			if ((gfflush(&_iob[i]) == -1))
				retval = -1;
		} 
	} else {
		if ((f->flag & _WRITE) == 0)
			return -1;
		_flushbuf(EOF, f);
		if (f->flag & _ERR)
			retval = -1;
	}
	return retval;
}

int gfclose(GFILE *f)
{
	int fd;
	
	if (f == GNULL)
		return -1;
	fd = f->fd;
	gfflush(f);
	f->cnt = 0;
	f->ptr = GNULL;
	if (f->base != GNULL)
		free(f->base);
	f->base = GNULL;
	f->flag = 0;
	f->fd = -1;
	return close(fd);
}




