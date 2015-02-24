#include "globals.h"

#include <stdarg.h>

void write_log(uint8_t type, const char *format, ...)
{
	char string[256];

	// TODO: Type enum.
	switch(type)
	{
		case 0:
			strcpy(string, "OK: ");
		break;

		case 1:
			strcpy(string, "ERROR: ");
		break;

		case 2:
			strcpy(string, "WARNING: ");
		break;
	}

	va_list args;
	va_start(args, format);
	vsnprintf(&string[strlen(string)], 256, format, args);
	va_end(args);

	puts(string);

	// TODO: Open file only once.
	FILE *file = fopen("theseus.log", "a");

	if(file != NULL)
	{
		fprintf(file, "%s\n", string);
		fclose(file);
	}
}
