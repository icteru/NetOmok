#pragma once

#include <cstdarg>
#include <set>
#include <iostream>


namespace omok
{
	namespace logging
	{
		class Logger
		{
		public:
			// outlist manipulate
			void add(FILE* fout);
			bool has(FILE* fout);
			void remove(FILE* fout);


			// log level
			enum LogLevel
			{
				Debug,
				Info,
				Warning,
				Error
			};


			// log functions
#ifndef NDEBUG
			// debug mode
			inline void d(const char* format, ...)
			{
				va_list arglist;
				va_start(arglist, format);
				println(Debug, format, arglist);
				va_end(arglist);
			}
#else
			// release mode
			inline void d(const char* format, ...) { }
#endif

			inline void i(const char* format, ...)
			{
				va_list arglist;
				va_start(arglist, format);
				println(Info, format, arglist);
				va_end(arglist);
			}

			inline void w(const char* format, ...)
			{
				va_list arglist;
				va_start(arglist, format);
				println(Warning, format, arglist);
				va_end(arglist);
			}

			inline void e(const char* format, ...)
			{
				va_list arglist;
				va_start(arglist, format);
				println(Error, format, arglist);
				va_end(arglist);
			}



		private:
			// actual printing function
			void println(LogLevel level, const char* format, va_list& args);

			std::set<FILE*> flist;
		};

		extern Logger logger;
	}
}

