#if defined WIN32
#include "WindowsContext.h"

using namespace PORT;

int main()
{
	Context testi;

	while (1)
		testi.update();

	return 0;
}


#elif defined ANDROID
#include "AndroidContext.h"

using namespace PORT;

void android_main(struct android_app* application)
{
	Context testi(application);
	
	while (1)
	{
		testi.update(application);
	}
}

#endif