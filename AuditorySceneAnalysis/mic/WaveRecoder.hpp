/*
**	WaveRecorder
**	受け取ったデータをwaveデータとして保存する
**
**	version	: 0.0
**	2013/4/16 作成
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
	**	コンストラクタ
	*/
	WaveRecorder::WaveRecorder( SoundBuffer<float>* buffer )
		: sb		( buffer )
		, samples	( 0 )
	{}


	/*
	**	デストラクタ
	*/
	WaveRecorder::~WaveRecorder()
	{}


	/*
	**	レコーディング開始
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
		ofs.write( (char*)&bi, 4 ); // バイト数（１６）

		bs = 1;
		ofs.write( (char*)&bs, 2 );	// フォーマットID（１）

		bs = 1;
		ofs.write( (char*)&bs, 2 ); // チャンネル数（モノラル）

		bi = 44100;//(int)freq;
		ofs.write( (char*)&bi, 4 ); // サンプリングレート(44100)

		bi = 44100;//(int)freq * 2;
		ofs.write( (char*)&bi, 4 ); // データ速度(44100*2 byte/s)

		bs = 2;
		ofs.write( (char*)&bs, 2 ); // ブロックサイズ（2byte）

		bs = 16;
		ofs.write( (char*)&bs, 2 ); // ビット数（16bit=2byte）

		ofs.write( "data", 4 );
		ofs.write( "\xFF\xFF\xFF\xFF", 4 );		

		sb->addListener( this );
	}


	/*
	**	ファイルにwaveデータを書き出し
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
	**	レコーディングを停止
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