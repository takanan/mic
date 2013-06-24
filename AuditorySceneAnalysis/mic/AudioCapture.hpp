#pragma once
/*
**	AudioCapture
**	PortAudioによって音を取得してくるクラス
**
**	2013/4/12
*/


 //
/// Include
//
#include <portaudio.h>
#include "AudioCapture.hpp"
#include "SoundBuffer.hpp"


 //
/// Source
//
namespace aqua
{
	extern int recordStream(		
			const void *input, 
			void *output, 
			unsigned long frameCount, 
			const PaStreamCallbackTimeInfo* timeInfo, 
			PaStreamCallbackFlags statusFlags, 
			void *userData );


	template < class T >
	class AudioCapture
	{
	private:
		PaError res;
		PaStream* stream;
		SoundBuffer<T>* buffer;
		int interval;


	public:
		AudioCapture( SoundBuffer<T>* buffer );
		~AudioCapture(void);


	public:
		bool init( int interval );
		bool release();
		bool start();
		bool isActive();
	};


	/*
	**	コンストラクタ
	*/
	template< class T >
	AudioCapture<T>::AudioCapture( SoundBuffer<T>* buffer )
		: stream	( NULL )
		, buffer	( buffer )
		, interval	( -1 )
	{}


	/*
	**	デストラクタ
	*/
	template< class T >
	AudioCapture<T>::~AudioCapture(void)
	{
		release();
	}


	/*
	**	初期化
	*/	
	template< class T >
	bool 
		AudioCapture<T>::init( int interval )
	{
		res = Pa_Initialize();
		if ( res != paNoError )
		{
			std::cerr << "PortAudioの初期化に失敗: " << Pa_GetErrorText( res ) <<  std::endl;
			return false;
		}

		this->interval = interval;
	}


	/*
	**	あとしまつ
	*/
	template< class T >
	bool 
		AudioCapture<T>::release()
	{
		if ( stream )
		{
			res = Pa_CloseStream( stream );
			if ( res != paNoError )
			{
				std::cerr << "ストリームを閉じれませんでした: " << Pa_GetErrorText( res ) << std::endl;
				return false;
			}
			stream = NULL;
		}

		res = Pa_Terminate();
		if ( res != paNoError )
		{
			std::cerr << "PortAudioの解放に失敗: " << Pa_GetErrorText( res ) <<  std::endl;
			return false;
		}
	}


	/*
	**	取得を開始
	*/
	template < class T >
	bool
		AudioCapture<T>::start()
	{
		res = Pa_OpenDefaultStream(
							&stream,
							1,
							0,
							paFloat32,
							44100,
							interval,
							recordStream,
							(void*) buffer );


		if ( res != paNoError )
		{
			std::cerr << "ストリームを開くのに失敗: " << Pa_GetErrorText( res ) << std::endl;
			return false;
		}


		res = Pa_StartStream( stream );
		if ( res != paNoError )
		{
			std::cerr << "ストリームの開けませんでした: " << Pa_GetErrorText( res ) << std::endl;
			return false;
		}
	}


	/*
	**	ストリームが継続中かどうか
	*/
	template < class T >
	bool
		AudioCapture<T>::isActive()
	{
		if ( stream )
		{
			return Pa_IsStreamActive( stream );
		}
	}
}

