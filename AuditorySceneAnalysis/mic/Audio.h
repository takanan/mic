#pragma once
/*
**	Audio.hpp
**	オーディオ周りの雑多なもの
**
**	version : 0.0
**	2013/4/17 インターフェイス追加
*/


 //
/// Include
//
#include "type.h"


 //
/// 
//
namespace aqua
{
	enum Frequency
	{ F48K = 48000, F32K = 32000, F16K = 16000, F8K = 8000, F44K = 44100, F22K = 22050, F11K = 11025 };


	/*
	**	IAudioIn
	**		オーディオ入力イベントによって呼び出されるリスナーインターフェース
	*/
	template < class T >
	class IAudioListener
	{
	public:
		virtual void receiveData( const T* const dat, uint samp_size ) = 0;
	};
}