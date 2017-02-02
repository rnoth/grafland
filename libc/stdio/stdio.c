#include "../stddef/stddef.h"

#include "stdio.h"



GFILE _iob[OPEN_MAX] = {
	{ 0, GNULL, GNULL, 1, 0, 0, 1, 0, 0},	/* stdin */
	{ 0, GNULL, GNULL, 1, 1, 1, 0, 0, 0},	/* stdout */
	{ 0, GNULL, GNULL, 1, 2, 1, 0, 0, 1}	/* stderr */ 
};

GFILE *gstdin = (&_iob[0]);
GFILE *gstdout = (&_iob[1]);
GFILE *gstderr = (&_iob[2]);
GFILE *gstdhold;


/* Function prototypes */
/* ------------------- */
int ggetc_inter(GFILE *);
int gputc_inter(int, GFILE *);
int ggetchar(void);
int gputchar(char);
int ggetc(GFILE *);
int gputc(int, GFILE *); 
ssize_t ggetline (char **, size_t *, GFILE *);
ssize_t ggetdelim(char **, size_t *, char, GFILE *);
int gprintf_inter(GFILE *, int, char *, size_t, int, char *, va_list);
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
size_t gfread(void *, size_t, size_t, GFILE *);
size_t gfwrite(const void *, size_t, size_t, GFILE *);
int gfeof(GFILE *);
int gferror(GFILE *);
int gfileno(GFILE *);



/* functions */
/* --------- */

/* single char io  */
int ggetc(GFILE *fp)
{
	return ggetc_inter(fp);
}

int gputc(int c, GFILE *fp)
{
	return gputc_inter(c, fp);
}

int ggetchar(void)
{
	return ggetc(gstdin);
}

int gputchar(char c)
{ 
	return gputc(c, gstdin);
}

int gfileno(GFILE *fp)
{
	return (fp)->fd;
}



/* Printf family (variadic and formatted) */
int gprintf_inter(GFILE *fp, int fd, char *str, size_t lim, int flag, char *fmt, va_list ap)
{
	char *p = NULL;
	char *out;
	size_t i = 0;
	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t zuval = 0; 
	int dval = 0; 
	long lval = 0;
	size_t bound = GBUFSIZ; 
#ifdef HASLIBM
	double fval = 0;
	char ftemp[GBUFSIZ]= { 0 };
#endif
	if ( flag == 2 ) 	/* snprintf */
		bound = lim;
	if (flag == 0)			/* printf, vprintf, dprintf etc */
		out = gmalloc(GBUFSIZ); 
	if (flag == 1 || flag == 2)	/* sprintf, snprintf etc */
		out = str;

	for (p = fmt; *p && i < bound; p++) 
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
				fltcase:
				fval = va_arg(ap, double); 
				if ( fval < 1 && fval > -1 )
				{ 
					gdtoa(ftemp, fval); 
					i += gsnprintf(out + i, 8, "%s", ftemp);
				} else {
					gdtoa(ftemp, fval - (long)fval); 
					i += gsprintf(out + i, "%ld", (long)fval);
					i += gsnprintf(out + i, 7, "%s", ftemp + 1);
				}
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
						goto fltcase;
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
	

	if ( flag == 2)  /* snprintf */ 
		i = bound; 

	out[i] = '\0'; 

	if (fp == NULL && flag == 0 )
		i = write(fd, out, i); /* if writing to an fd, then redefine the ret */
	else if ( fp != NULL )
		i = gfwrite(out, 1, i, fp);
	if ( flag == 0 )
		gfree(out);

	return i;
}

int gprintf(char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(gstdout, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsprintf(char *str, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(NULL, 1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsnprintf(char *str, size_t lim, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(NULL, 1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gdprintf(int fd, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(NULL, fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gvprintf(char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(gstdout, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsprintf(char *str, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(NULL, 1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsnprintf(char *str, size_t lim, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(NULL, 1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvdprintf(int fd, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(NULL, fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gfprintf(GFILE *stream, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(stream, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvfprintf(GFILE *stream, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(stream, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

/* fopen family */
GFILE *gfopen(char *file, char *mode)
{
	int fd = -1;
	GFILE *fp = GNULL;
	int oflags = 4242;
	int seek = -1;
	
	/* find a gfree slot */
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag == 0))
			break;

	/* no gfree slots */
	if (fp >= _iob + OPEN_MAX)
		return GNULL; 

	/* init */
	fp->unbuf = 0;
	fp->cnt = 0;
	fp->append = 0;
	fp->write = 0;
	fp->read = 0;

	/* fopen modes */
	switch (*mode)
	{ 
		case 'r':
			oflags = O_RDONLY;
			fp->read = 1;
			switch (*++mode) 
			{ 
				case '+':
					fp->write = 1;
					oflags = O_RDWR;
				default:
					break;
			}
			break;
		case 'w':
			oflags = O_TRUNC | O_CREAT;
			fp->read = 1;
			switch (*++mode) 
			{
				case '+': 
					oflags = O_TRUNC | O_CREAT | O_RDWR;
				default:
					break;
			}
			break; 
		case 'a':
			oflags = O_CREAT | O_APPEND;
			fp->append = 1;
			switch (*++mode)
			{
				case '+':
					oflags = O_CREAT | O_APPEND | O_RDWR;
				default:
					break;
			}
			seek = SEEK_END;
			break;
		default:
			if ( oflags == 4242 )
				return GNULL;
			break;
	}

	/* open the file */
	if ((fd = open(file, oflags, 0)) == -1)
		return GNULL;

	/* and lseek to the end of it if in append mode */
	if ( seek == SEEK_END)
		lseek(fd, 0L, seek);

	/* initialize the new GFILE */
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = GNULL;
	fp->flag = 1;
	return fp;
} 

int ggetc_inter(GFILE *fp)
{ 
	int len = 0;
	char c = 0;
	//int ret = 0; 
	//char *a;

	if (!(fp->base))
	{
		if ((fp->base = gmalloc(GBUFSIZ)) == GNULL) 
			fp->unbuf = 1;
		fp->ptr = fp->base;
	}
	
	if ( fp->cnt == 0 )
	{
		if ( fp->unbuf != 1 )
			len = read(fp->fd, fp->base, GBUFSIZ);
		else { 
			len = read(fp->fd, &c, 1);
		}
		
		fp->ptr = fp->base;
	
		gstdhold = fp;
		fp->cnt += len;
		
		if ( len == 0 || len == -1) 
		//if ( fp->cnt < 1 )
			return GEOF; 
		if ( fp->unbuf == 1 )
			return c;
		else
		
			return *(fp)->ptr; 
	}


	
	return *(fp)->ptr++; 
}


int gputc_inter(int c, GFILE *fp)
{ 
	if (c == GEOF)
		return GEOF;

	if(fp->unbuf == 1)
		gstdhold->cnt -= write(fp->fd, &c, 1);
	else
		gstdhold->cnt -= write(fp->fd, gstdhold->ptr, gstdhold->cnt);
	return c;
}

int gfflush(GFILE *fp)
{
	int ret = 0;
	int i; 
	
	if (fp == GNULL) 
		for (i = 0; i < OPEN_MAX; i++) 
			if ((gfflush(&_iob[i]) == -1))
				ret = -1; 
	else 
		gputc_inter(GEOF, fp);

	return ret;
}

int gfclose(GFILE *fp)
{
	int fd;
	if (fp == GNULL)
		return -1;
	fd = fp->fd;
	gfflush(fp);
	if (fp->base != GNULL)
		gfree(fp->base);
	fp->ptr = fp->base = GNULL;
	fp->fd = -1;
	fp->flag = fp->cnt = fp->append = fp->read = fp->write = fp->unbuf = 0;
	return close(fd);
} 

size_t gfread(void *ptr, size_t size, size_t nmemb, GFILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = read(fp->fd, ptr, request);
	return ret / size;
}

size_t gfwrite(const void *ptr, size_t size, size_t nmemb, GFILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = write(fp->fd, ptr, request);
	return ret / size;
} 

/* getline  */
ssize_t ggetdelim(char **lineptr, size_t *n, char delim, GFILE *fp)
{
	size_t len = 0;
	char *pos = GNULL;
	ssize_t ret = -1;
	size_t chunk = GBUFSIZ;
	int c = 0;

	if (!*lineptr) 
	{
		*n = chunk;
		if (!(*lineptr = gmalloc (chunk))) 
			return -1; 
	} 

	len = *n;
	pos = *lineptr;

	for ( ; c != delim ;len--, pos++)
	{
		read (fp->fd, &c, 1); 
		if (c == 0 || c == -1)
			c = GEOF;
		
		if (len == 0)
		{
			*n += chunk; 
			len = chunk; 
			if (!(*lineptr = grealloc (*lineptr, *n)))
				return ret;
			pos = *lineptr;
		}

		if (c == GEOF )
		{
			if (pos == *lineptr) 
				return ret;
			else
				break;
		}
		*pos = c;
	}

	*pos = '\0';

	ret = pos - (*lineptr);
	return ret;
}


ssize_t ggetline(char **lineptr, size_t *n, GFILE *fp)
{
	return ggetdelim(lineptr, n, '\n', fp);
}




#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../stddef/stddef.h"
#include "../fcntl/fcntl.h"

char * gdtoa(char *, double);
size_t uintostrbase(char *, size_t, int);
size_t intostrbase_inter(char *, int, int); 
	




