

 //
/// Include
//
#include <iostream>
#include <SDL.h>
#include <boost/tuple/tuple_io.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include "SoundBuffer.hpp"
#include "AudioCapture.hpp"
#include "../Render/SDLW.hpp"
#include "../Render/Render.hpp"
#include "FFTAnalyzer.hpp"
#include "FFTViewer.h"
#include "WaveViewer.hpp"
#include "WaveRecoder.hpp"
#include "FrameRateChecker.h"
#include "MonoImage.hpp"
using namespace aqua;
using namespace std;


/*
**	エントリポイント
*/
int main( int argn, char* argv[] )
{
	const int width = 1260;
	const int height = 600;
	const int N = 8192;
	const int frameBufferSize = 512;
	const int fftLogSize = width/2;
	const int waveSize = width/2;


	/* システムモジュール生成 */
	SoundBuffer<float> buffer;
	vector< SoundBuffer<float>* > stream;
	AudioCapture<float> ac( &buffer );
	SDLW sdl( width, height, SDL_OPENGL | SDL_INIT_TIMER );
	FrameRateChecker<1000> frc;
	stream.push_back( &buffer );
	stream.push_back( &buffer );
	stream.push_back( &buffer );
	stream.push_back( &buffer );
	stream.push_back( &buffer );
	stream.push_back( &buffer );
	stream.push_back( &buffer );
	stream.push_back( &buffer );

	/* 初期化 */
	buffer.init( N*2 );
	ac.init( frameBufferSize );
	sdl.init();


	/* アナライザモジュール生成 */
	FFTAnalyzer fftAnalyzer( N, &buffer, fftLogSize );
	//WaveRecorder recorder( &buffer );
	//recorder.startRecording( "test.wav", F44K );


	/* ビューアモジュール生成 */
	WaveViewer waveViewer( stream, waveSize );
	FFTViewer fftViewer( &fftAnalyzer );


	ac.start();
	int time = timeGetTime();
	while ( sdl.processEvent() && ac.isActive() )
	{	
		waveViewer.update();
		fftAnalyzer.analyze();

		//if ( timeGetTime() - time > 7000 )
		//{
		//	recorder.stopRecording();
		//	cout << "end recording" << endl;
		//}

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		waveViewer.render( 20, 20, 260, 130 );
		fftViewer.render( width/2, 0, width/2, height );
		SDL_GL_SwapBuffers();

		if ( frc.frame() )
		{
			::SDL_WM_SetCaption( frc.getFrameRateString(), NULL );
		}
	}

	return 0;
}