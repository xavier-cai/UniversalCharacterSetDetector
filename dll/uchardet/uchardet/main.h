#ifdef UCHARDET_API
#else
#define UCHARDET_API extern "C" _declspec(dllimport)
#endif

UCHARDET_API void __stdcall Reset();
UCHARDET_API void __stdcall HandleData(char* buffer, unsigned int size);
UCHARDET_API void __stdcall HandleDataEnd();
UCHARDET_API void __stdcall GetCharSet(char* out, unsigned int size);
