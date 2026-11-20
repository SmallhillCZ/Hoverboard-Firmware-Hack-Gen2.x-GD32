// this file will not be updated to github :-)

//#define CONFIG_DEBUG	// so robo can work on configDebug.h

#if defined(CONFIG_GOCART)
	#include "../Inc/configGocart.h"	// GoCart: TT-SD2.2 boards, MASTER/SLAVE chosen by -D flag in platformio.ini
#elif defined(CONFIG_DEBUG)
	#include "../Inc/configDebug.h"
#else
	#include "../Inc/config.h"
#endif
	
	
