#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

__BEGIN_DECLS

void
error_set(const char *, const char *, ...);
void 
error_sys_set(const char *, const char *);
void
error_print(FILE *);

__END_DECLS

#endif /* ERROR_H */
