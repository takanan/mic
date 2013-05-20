/*
**	WaveRecorder
**	�󂯎�����f�[�^��wave�f�[�^�Ƃ��ĕۑ�����
**
**	version	: 0.0
**	2013/4/16 �쐬
*/


 //
/// Include
//
#include <iostream>
#include <fstream>
#include "type.h"
#include "Audio.h"
#include "SoundBuffer.hpp"


 //
/// Source
//
namespace aqua
{
	class WaveRecorder : IAudioListener<float>
	{
	private:
		SoundBuffer<float>* sb;
		std::ofstream ofs;
		unsigned samples;
		
	public:
		WaveRecorder( SoundBuffer<float>* buffer );
		~WaveRecorder();

	public:
		void startRecording( const char* filename, const Frequency freq );
		void stopRecording();
		void update();
		void receiveData( const float* const dat, uint samp_size );
	};


	/*
	**	�R���X�g���N�^
	*/
	WaveRecorder::WaveRecorder( SoundBuffer<float>* buffer )
		: sb		( buffer )
		, samples	( 0 )
	{}


	/*
	**	�f�X�g���N�^
	*/
	WaveRecorder::~WaveRecorder()
	{}


	/*
	**	���R�[�f�B���O�J�n
	*/
	void 
		WaveRecorder::startRecording( const char* filename, const Frequency freq )
	{
		if ( ofs.is_open() ) stopRecording();

		ofs.open( filename, std::ios::binary | std::ios::out | std::ios::trunc );

		ofs.write( "RIFF", 4 );
		ofs.write( "\xFF\xFF\xFF\xFF", 4 );
		ofs.write( "WAVE", 4 );
		ofs.write( "fmt ", 4 );

		unsigned bi;
		short bs;

		bi = 16;
		ofs.write( (char*)&bi, 4 ); // �o�C�g���i�P�U�j

		bs = 1;
		ofs.write( (char*)&bs, 2 );	// �t�H�[�}�b�gID�i�P�j

		bs = 1;
		ofs.write( (char*)&bs, 2 ); // �`�����l�����i���m�����j

		bi = 44100;//(int)freq;
		ofs.write( (char*)&bi, 4 ); // �T���v�����O���[�g(44100)

		bi = 44100;//(int)freq * 2;
		ofs.write( (char*)&bi, 4 ); // �f�[�^���x(44100*2 byte/s)

		bs = 2;
		ofs.write( (char*)&bs, 2 ); // �u���b�N�T�C�Y�i2byte�j

		bs = 16;
		ofs.write( (char*)&bs, 2 ); // �r�b�g���i16bit=2byte�j

		ofs.write( "data", 4 );
		ofs.write( "\xFF\xFF\xFF\xFF", 4 );		

		sb->addListener( this );
	}


	/*
	**	�t�@�C����wave�f�[�^�������o��
	*/
	void 
		WaveRecorder::receiveData( const float* const dat, uint samp_size )
	{
		for ( int i=0; i<samp_size; i++ )
		{
			short recv = static_cast<short>( 32767 * dat[i] );
			ofs.write( (char*)&recv, 2 );
		}
	}


	/*
	**	���R�[�f�B���O���~
	*/
	void 
		WaveRecorder::stopRecording()
	{
		if ( ofs.is_open() )
		{
			sb->removeListener( this );

			unsigned waveSize = samples * 2;

			ofs.seekp( 4, std::ios::beg );
			unsigned size = waveSize + 36;
			ofs.write( (char*)&size, 4 );

			ofs.seekp( 40, std::ios::beg );
			ofs.write( (char*)&waveSize, 4 );

			ofs.close();
		}
	}
}