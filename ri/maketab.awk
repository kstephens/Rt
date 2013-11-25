BEGIN {	len = 512;
	print "RiFloat randtable[" len "] = {";
	for ( i = 0; i < len; i ++ ) {
		printf( "%8g", rand() );
		if ( i != len - 1 ) printf( ",");
		if ( i % 8 == 0 ) printf("\n"); else printf(" ")
	}
	print "}"
}
