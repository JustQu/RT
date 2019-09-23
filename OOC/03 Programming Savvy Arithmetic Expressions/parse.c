#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#include "setjmp.h"
#include "parse.h"
#include "value.h"

static enum tokens	token;	/* current input symbol */

static double	number; /* if NUMBER: numerical value */

/*
In the main loop, once an input line has been read into buf[], it is passed to scan(),
which for each call places the next input symbol into the variable token. At the end
of a line token is zero
We call scan() with the address of an input line or with a null pointer to continue
work on the present line. White space is ignored and for a leading digit or decimal
point we extract a floating point number with the ANSI-C function strtod(). Any
other character is returned as is, and we do not advance past a null byte at the end
of the input buffer.
The result of scan() is stored in the global variable token — this simplifies the
recognizer. If we have detected a number, we return the unique value NUMBER
and we make the actual value available in the global variable number.
*/

static enum tokens	scan(const char *buf) /* return token = next input symbol */
{
	static const char	*bp;
	
	if (buf)
		bp = buf;
	while (isspace(*bp))
		++bp;
	if (isdigit(*bp) || *bp == '.')
	{
		errno = 0;
		token = NUMBER, number = strtod(bp, (char **)&bp);
		if (errno == ERANGE)
			error("bad value: %s", strerror(errno));
	}
	else
		token = *bp ? *bp++ : 0;
	return token;
}

static void	*sum(void);

static void	*factor(void)
{
	void	*result;

	switch (token)
	{
		case '+':
			scan(0);
			return factor();
		case '-':
			scan(0);
			return new(Minus, factor());
		default:
			error("bad factor: '%c' 0x%x", token, token);
		case NUMBER:
			result = new(Value, number);
			break;
		case '(':
			scan(0);
			result = sum();
			if (token != ')')
				error("expected )");
	}
	scan(0);
	return result;
}

static void *product(void)
{
	void *result = factor();
	const void *type;

	for(;;)
	{
		switch (token)
		{
			case '*':
				type = Mult;
				break;
			case '/':
				type = Div;
				break;
			default:
				return result;
		}
		scan(0);
		result = new(type, result, factor());
	}
}

/*
sum : product { +|- product } ...
*/
static void	*sum(void)
{
	void		*result = product();
	const void	*type;

	for (;;)
	{
		switch (token)
		{
			case '+':
				type = Add;
				break;
			case '-':
				type = Sub;
				break;
			default:
				return result;
		}
		scan(0);
		result = new(type, result, product());
	}
}

static jmp_buf onError;

int		main(void)
{
	volatile int	errors = 0;
	char			buf[BUFSIZ];

		if (setjmp(onError))
			++errors;
		
		while (gets(buf))
			if (scan(buf))
			{
				void	*e = sum();

				if (token)
					error("trash after sum");
				process(e);
				delete(e);
			}
	return errors > 0;
}

void	error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap), putc('\n', stderr);
	va_end(ap);
	longjmp(onError, 1);
}
