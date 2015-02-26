#ifndef PMASSERT_H
#define PMASSERT_H

#include <assert.h>
#include <android/log.h>
#include <string>
#include <cstdlib>

#define LOGA(...) ((void)__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", __VA_ARGS__))

#define ASSERT(expression) \
	!(expression) ? Assert(__FILE__, __LINE__) : (void)0 // !a

#define ASSERT_EQ(expression1, expression2) \
	expression1 != expression2 ? Assert_EQ(__FILE__, __LINE__) : (void)0 // a == b

#define ASSERT_NEQ(expression1, expression2) \
	expression1 == expression2 ? Assert_NEQ(__FILE__, __LINE__) : (void)0 // a != b

#define ASSERT_MINMAX(expression1, expression2, value) \
	expression1 < value && value < expression2 ? Assert_MINMAX(__FILE__, __LINE__) : (void)0 // min < x < max

void Assert(const char* file, const int line)
{
	// Log file and file
	__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", file, line);
	std::abort();
}

void Assert_EQ(const char* file, const int line)
{
	// Log file and file
	__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", file, line);
	std::abort();
}

void Assert_NEQ(const char* file, const int line)
{
	// Log file and file
	__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", file, line);
	std::abort();
}

void Assert_MINMAX(const char* file, const int line)
{
	// Log file and file
	__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", file, line);
	std::abort();
}

namespace pm
{
	class PMassert
	{
	public:
		template<typename T>
		/**
		*Katsoo onko kaksi arvoa samoja: a == b,
		*jos ei katkaisee sovelluksen suorittamisen
		*turmeltunut funktio käytä ASSERT_EQ
		*/
		static void AssertEquals(T const& a, T const& b, char* s)
		{
			if(a == b)
				;
			else
				LOGA("%s", s);

			__builtin_trap(); // break debugger
			assert(a == b);
		};


		template<typename T>
		/**
		*Katsoo onko kaksi arvoa eri arvoja: a != b,
		*jos ei katkaisee sovelluksen suorittamisen
		*turmeltunut funktio käytä ASSERT_NEQ
		*/
		static void AssertNotEquals(T const& a, T const& b, char* s)
		{
			if(a == b)
				;
			else
				LOGA("%s", s);

			assert(a != b);
		};

		template<typename T>
		/**
		*Katsoo onko arvo min ja max arvojen välissä: min < x < max,
		*jos ei katkaisee sovelluksen suorittamisen
		*turmeltunut funktio käytä mieluummin ASSERT_MINMAX
		*/
		static void AssertInBetween(T const& min, T const& max, T const& x, char* s)
		{
			if(min < x && x < max)
				;
			else
				LOGA("%s", s);

			assert(min < x && x < max);
		};
	};
}

#endif