#pragma once
#pragma comment( lib, "winmm.lib" )
#ifndef __FrameRateChecker_h__
#define __FrameRateChecker_h__

#include <windows.h>
#include <mmsystem.h>

namespace aqua
{
	template < unsigned interval = 500 >
	class FrameRateChecker
	{
	public:
		FrameRateChecker(void)
			: counter	( 0 )
			, lastTime	( 0 )
			, fps		( 0 )
			, isUpdated	( false )
		{
			buffer[0] = '\0';
		}

		bool frame()
		{
			const DWORD nowTime = timeGetTime();
			if ( nowTime - lastTime > interval )
			{
				lastTime = nowTime;
				fps = counter/(interval/1000.0);
				counter = 0;
				isUpdated = true;
				return true;
			}
			counter++;
			isUpdated = false;
			return false;
		}

		const char* getFrameRateString()
		{
			sprintf( buffer, "%.2f", fps );
			return buffer;
		}

		const double getFrameRate() const { return fps; }
		const bool isUpdate() { return isUpdated; }

	private:
		DWORD lastTime;
		int counter;
		double fps;
		char buffer[128];
		bool isUpdated;
	};
};

#endif // __FrameRateChecker_h__
