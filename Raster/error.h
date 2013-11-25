//
// error.h - error functions and macros
// KAS 91/06/12
//
#ifndef	__error_h
#define	__error_h

#ifdef	__cplusplus
extern "C" {
#endif

extern 	void _fatal(const char*, int);
extern	void _warning(const char*, int);

#ifdef	__cplusplus
}
#endif

#define	FATAL		_fatal(__FILE__,__LINE__);
#define	WARNING		_warning(__FILE__,__LINE__);
#define	NOT_IMPLEMENTED FATAL

#endif

