#ifndef PMASSERT_H

#define PMASSERT_H

#endif // !PMASSERT_H
#include <assert.h>
#include <string>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", __VA_ARGS__))

class PMassert
{
public:
	template<typename T>
	/**
	*Katsoo onko kaksi arvoa samoja: a == b,
	*jos ei katkaisee sovelluksen suorittamisen
	*viel‰ pit‰isi lis‰t‰ lis‰‰ informaatiota, jota k‰ytt‰j‰ saa.
	*/
	static void AssertEquals(T const& a, T const& b, char* s)
	{
		if (a == b)
			;
		else
			LOGI("%s", s);
			
			assert(a == b);

	};
	


	template<typename T>
	/**
	*Katsoo onko kaksi arvoa eri arvoja: a != b,
	*jos ei katkaisee sovelluksen suorittamisen
	*viel‰ pit‰isi lis‰t‰ lis‰‰ informaatiota, jota k‰ytt‰j‰ saa.
	*/
	static void AssertNotEquals(T const& a, T const& b, char* s)
	{
		if (a == b)
			;
		else
			LOGI("%s", s);

			assert(a != b);
	}; 
	


	template<typename T>
	/**
	*Katsoo onko arvo min ja max arvojen v‰liss‰: min < x < max,
	*jos ei katkaisee sovelluksen suorittamisen
	*viel‰ pit‰isi lis‰t‰ lis‰‰ informaatiota, jota k‰ytt‰j‰ saa.
	*/
	static void AssertInBetween(T const& min, T const& max, T const& x, char* s)
	{
		if (min < x && x < max)
			;
		else
			LOGI("%s", s);

			assert(min < x && x < max);
	};
	


private:

};