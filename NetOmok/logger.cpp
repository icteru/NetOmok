#include "logger.h"

// thread safe print
#include <mutex>

// time
#include <ctime>

// static logger
omok::logging::Logger omok::logging::logger;



using namespace omok::logging;

// time
std::clock_t start_time = std::clock();

float _getTickTime()
{
	std::clock_t current = std::clock();
	float delta = (float)(current - start_time) / CLOCKS_PER_SEC;
	if (delta >= 10000.0f)
	{
		start_time = current;
		delta -= 10000.0f;
	}

	return delta;
}

// log level
inline wchar_t _getLevel(Logger::LogLevel level)
{
	switch (level)
	{
	case Logger::LogLevel::Debug:
		return 'D';
	case Logger::LogLevel::Info:
		return 'I';
	case Logger::LogLevel::Warning:
		return 'W';
	case Logger::LogLevel::Error:
		return 'E';
	default:
		return '?';

	}
}

// mutex
std::mutex mtx;

void omok::logging::Logger::add(FILE * fout)
{ 
	flist.insert(fout); 
}

bool omok::logging::Logger::has(FILE * fout)
{ 
	return flist.count(fout) != 0;
}

void omok::logging::Logger::remove(FILE * fout)
{
	flist.erase(fout);
}

//void omok::logging::Logger::printwln(LogLevel level, const wchar_t* format, va_list& args)
//{
//	mtx.lock();
//	float time = _getTickTime();
//	for (auto fit : flist)
//	{
//		fwprintf_s(fit, L"[%8.3f | %c] : ", time, _getLevel(level));
//		vfwprintf_s(fit, format, args);
//		fwprintf_s(fit, L"\n");
//	}
//	mtx.unlock();
//}


void omok::logging::Logger::println(LogLevel level, const char* format, va_list& args)
{
	mtx.lock();
	float time = _getTickTime();
	for (auto fit : flist)
	{
		fprintf_s(fit, "[%8.3f | %c] : ", time, _getLevel(level));
		vfprintf_s(fit, format, args);
		fprintf_s(fit, "\n");
	}
	mtx.unlock();
}
