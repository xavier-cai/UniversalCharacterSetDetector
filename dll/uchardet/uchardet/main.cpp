#include "uchardet.h"

#define UCHARDET_API extern "C" _declspec(dllexport)
#include "main.h"

//#define LOGGER_ENABLE

#ifdef LOGGER_ENABLE
#include <fstream>
#include <iostream>

namespace logger {

class Logger;
class LoggerHandle
{
protected:
	virtual void HandleLogger(Logger& logger) const = 0;
	friend class Logger;
};

class Logger
{
private:
	std::string m_path;
	std::ofstream m_ofs;
	
public:
	Logger(const char* path)
		: m_path(path), m_ofs(path)
	{ }
	~Logger()
	{
		Dispose();
	}
	void Dispose()
	{
		if(m_ofs.is_open())
		{
			m_ofs.flush();
			m_ofs.close();
		}
	}
	
	template <typename T>
	Logger& operator << (const T* content)
	{
		if(!m_ofs.is_open())
			m_ofs.open(m_path, std::ios::app);
		if(m_ofs.is_open())
			m_ofs << content;
		return *this;
	}
	
	Logger& operator << (const LoggerHandle& handler)
	{
		handler.HandleLogger(*this);
		return *this;
	}
};

class LoggerEndl : public LoggerHandle
{
protected:
	virtual void HandleLogger(Logger& logger) const override
	{
		logger << "\n";
		logger.Dispose();
	}
};

const char* logpath = "uchardet.log";
Logger log(logpath);
const LoggerEndl endl;
};

#include <exception>
#define FUNCTION_START \
	logger::log << "function start : " << __FUNCTION__ << "\n"; \
	logger::log << "instance : " << &instance << "\n"; \
	try { \

#define FUNCTION_END \
	logger::log << "function end : " << __FUNCTION__ << "\n"; \
	logger::log << "instance : " << &instance << logger::endl; \
} catch(std::exception &e) { \
	logger::log << "error " << e.what() << logger::endl; \
}
#else
#define FUNCTION_START
#define FUNCTION_END
#endif //#ifdef LOGGER_ENABLE

auto instance = uchardet_new();

void __stdcall Reset()
{
	FUNCTION_START
	uchardet_reset(instance);
	FUNCTION_END
}

void __stdcall HandleData(char* buffer, unsigned int size)
{
	FUNCTION_START
	uchardet_handle_data(instance, buffer, size);
	FUNCTION_END
}

void __stdcall HandleDataEnd()
{
	FUNCTION_START
	uchardet_data_end(instance);
	FUNCTION_END
}

void __stdcall GetCharSet(char* out, unsigned int size)
{
	FUNCTION_START
	const char* charset = uchardet_get_charset(instance);
	unsigned int index = 0;
	while(index < size && (out[index] = charset[index])) index++;
	out[size - 1] = '\0';
	FUNCTION_END
}
