#include "uchardet.h"

#define UCHARDET_API extern "C" _declspec(dllexport)
#include "main.h"

auto instance = uchardet_new();

void __stdcall Reset()
{
	uchardet_reset(instance);
}

void __stdcall HandleData(char* buffer, unsigned int size)
{
	uchardet_handle_data(instance, buffer, size);
}

void __stdcall HandleDataEnd()
{
	uchardet_data_end(instance);
}

void __stdcall GetCharSet(char* out, unsigned int size)
{
	const char* charset = uchardet_get_charset(instance);
	unsigned int index = 0;
	while((out[index] = charset[index]) && index++ < size);
	out[size - 1] = '\0';
}
