
 //
/// Include
//
#include <portaudio.h>
#include "AudioCapture.hpp"
#include "SoundBuffer.hpp"
using namespace aqua;


 //
/// Source
//
/*
**	音取得用コールバック関数
*/
int aqua::recordStream(		
			const void *input, 
			void *output, 
			unsigned long frameCount, 
			const PaStreamCallbackTimeInfo* timeInfo, 
			PaStreamCallbackFlags statusFlags, 
			void *userData )
{
	((SoundBuffer<float>*)userData)->write( (float*)input, frameCount );
	return 0;
}


