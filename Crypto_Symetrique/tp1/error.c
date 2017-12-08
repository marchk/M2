#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include "error.h"

#define BUFF_ERR_SIZE 256

static char buf_err[BUFF_ERR_SIZE];

/**
 * \fn void error_set(const char *func, const char *fmt, ...)
 * \brief prints formatted string error in a static buffer
 *
 * \param func name of function in which an error occured (usually \a __fun__)
 * \param fmt format (see \a printf() manual)
 * \param ... variable-length arguments (see \a printf() manual)
 */
void
error_set(const char *func, const char *fmt, ...)
{
    va_list ap;
    size_t offset = strlen(func) + 4;

    (void) snprintf(buf_err, BUFF_ERR_SIZE, "%s(): ", func);
    va_start(ap, fmt);
    (void) vsnprintf(buf_err + offset, BUFF_ERR_SIZE - offset, fmt, ap);
    va_end(ap);
}

/**
 * \fn void error_sys_set(const char *func, const char *func_sys)
 * \brief prints system call error in a static buffer (see \a errno and
 *        \a strerror())
 *
 * \param func name of function in which a system call failed
 *             (usually \a __fun__)
 * \param func_sys system call name (see parameter \a func above)
 */
void
error_sys_set(const char *func, const char *func_sys)
{
    (void) snprintf(
	buf_err, BUFF_ERR_SIZE, "%s(): %s(): (%d, %s)", func, func_sys,
	errno, strerror(errno)
	);
}

/**
 * \fn void error_print(FILE *os)
 * \brief prints on output stream \a os last error setted by \a error_set()
 *        or error_sys_set()
 *
 * \param os output stream
 */
void
error_print(FILE *os)
{
    (void) fprintf(os, "%s\n", buf_err);
}
