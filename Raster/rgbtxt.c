/*
// rgbtxt.c - read routines for rgb.txt
// KAS 91/06/23
*/
#include <stdio.h>
#include <ctype.h>

#ifndef	SEEK_SET
#define	SEEK_SET	0
#endif

static	FILE*	rgb_txt = NULL;

static
char
convert (char c) {
	if ( isupper(c) )
		c = tolower(c);
	else if ( isspace(c) || c == '_' )
		c = ' ';

	return c;
}

static
int
match(const char* a, const char* b ) {
	while ( *a && *b ) {
		if ( convert(*a) != convert(*b) )
			return 0;
		a ++; b ++;
	}

	if ( *a || *b )
		return 0;
	else
		return 1;
}

int
rgbtxt( const char* name, int* r, int* g, int* b ) {
	if ( rgb_txt == NULL ) {
		rgb_txt = fopen("rgb.txt", "r");
	} else {
		fseek(rgb_txt, 0L, SEEK_SET);
	}

	while ( ! feof(rgb_txt) ) {
		char	color[80];
		int	R, G, B;

		fscanf(rgb_txt, "%s", color);

		if ( match(color, name) ) {
			fscanf(rgb_txt, "%d %d %d", r, g, b);
			return 1;
		}
		{
			int	c;
			while ( (c = getc( rgb_txt)) != '\n' && c != EOF )
				;
			ungetc(c, rgb_txt);
		}

	}
	return 0;
}
