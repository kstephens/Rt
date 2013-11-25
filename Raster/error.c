//
// error.c - error functions
// KAS 91/06/12
//
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> /* write(), read() */
#include <string.h> /* strlen() */

static
void	writestring (int fd, const char* string) {
	write(fd, string, strlen(string));
}

static
void	writechar (int fd, char c ) {
	write (fd, &c, 1);
}

static
void	writeint (int fd, int i ) {
	int	place = 10000;

	if ( i < 0 ) {
		writechar(fd, '-');
		i = -i;
	}

	while ( place > 0 ) {
		int	digit = i / place;

		writechar(fd, '0' + (char) digit );
		i -= digit * place;
		place /= 10;
	}
}

static
char	readchar ( int fd ) {
	char 	c;

	read ( fd, &c, 1 );
	return c;
}

static
void	_print_line( int fd, const char* file, int line ) {
	int	filefd;

	writestring(fd, "in file ");
	writestring(fd, file);
	writestring(fd, " at line ");
	writeint(fd, line);
	writechar(fd, ':');

#ifndef O_TEXT
#define O_TEXT 0
#endif
	if ( (filefd = open(file, O_RDONLY | O_TEXT )) != -1 ) {
		char	c;

		for ( ; line > 1; line -- ) {
			while ( readchar(filefd) != '\n' )
				;
		}

		do {
			writechar(fd, c = readchar(filefd));
		} while ( c != '\n' );
	} else {
		writestring(2, "Couldn't open ");
		writestring(2, file);
		writechar(2, '\n');
	}
}

void	_warning( const char* file, int line ) {
	writestring(2, "WARNING: ");
	_print_line(2,file,line);
}

void	_fatal( const char* file, int line ) {
	writestring(2, "FATAL: ");
	_print_line(2, file, line);
	_exit(-1);
}

