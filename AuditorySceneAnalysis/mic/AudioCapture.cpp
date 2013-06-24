
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
**	���擾�p�R�[���o�b�N�֐�
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


