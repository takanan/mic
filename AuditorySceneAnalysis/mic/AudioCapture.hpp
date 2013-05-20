#pragma once
/*
**	AudioCapture
**	PortAudio�ɂ���ĉ����擾���Ă���N���X
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
	**	�R���X�g���N�^
	*/
	template< class T >
	AudioCapture<T>::AudioCapture( SoundBuffer<T>* buffer )
		: stream	( NULL )
		, buffer	( buffer )
		, interval	( -1 )
	{}


	/*
	**	�f�X�g���N�^
	*/
	template< class T >
	AudioCapture<T>::~AudioCapture(void)
	{
		release();
	}


	/*
	**	������
	*/	
	template< class T >
	bool 
		AudioCapture<T>::init( int interval )
	{
		res = Pa_Initialize();
		if ( res != paNoError )
		{
			std::cerr << "PortAudio�̏������Ɏ��s: " << Pa_GetErrorText( res ) <<  std::endl;
			return false;
		}

		this->interval = interval;
	}


	/*
	**	���Ƃ��܂�
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
				std::cerr << "�X�g���[�������܂���ł���: " << Pa_GetErrorText( res ) << std::endl;
				return false;
			}
			stream = NULL;
		}

		res = Pa_Terminate();
		if ( res != paNoError )
		{
			std::cerr << "PortAudio�̉���Ɏ��s: " << Pa_GetErrorText( res ) <<  std::endl;
			return false;
		}
	}


	/*
	**	�擾���J�n
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
			std::cerr << "�X�g���[�����J���̂Ɏ��s: " << Pa_GetErrorText( res ) << std::endl;
			return false;
		}


		res = Pa_StartStream( stream );
		if ( res != paNoError )
		{
			std::cerr << "�X�g���[���̊J���܂���ł���: " << Pa_GetErrorText( res ) << std::endl;
			return false;
		}
	}


	/*
	**	�X�g���[�����p�������ǂ���
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

