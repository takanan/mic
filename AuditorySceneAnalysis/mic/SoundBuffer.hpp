#pragma once
/*
**	SoundBuffer.hpp
**	�ʃX���b�h�̃R�[���o�b�N�֐�����擾�������f�[�^���i�[���郊���O�o�b�t�@
**
**	version : 1.0
**	2013/4/12	�쐬
**	2013/4/17	���X�i�@�\�ǉ�
*/


 //
/// Include
//
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <algorithm>
#include <vector>
#include "Audio.h"


 //
/// Source
//
namespace aqua
{
	template < class T >
	class SoundBuffer
	{
	public:
		typedef boost::mutex::scoped_lock Lock;
		typedef boost::shared_lock< boost::shared_mutex > ReadLock;
		typedef boost::unique_lock< boost::shared_mutex > WriteLock;
		typedef std::vector<IAudioListener<T>*> ListenerList;

	private:
		T* ringBuf;
		unsigned len;
		int index;
		unsigned recvCnt;
		boost::shared_mutex rmu;
		boost::shared_mutex cmu;
		boost::mutex vmu;
		std::vector< IAudioListener<T>* > listeners;

	public:
		SoundBuffer();
		void init( int length );
		void write( T* dat, int length );
		void read( T* buffer, int length );
		unsigned getCounter();
		void addListener( IAudioListener<T>* listener );
		void removeListener( IAudioListener<T>* listener );
	};


	/*
	**	�R���X�g���N�^
	*/
	template < class T >
	SoundBuffer<T>::SoundBuffer()
		: ringBuf	( NULL )
		, len		( 0 )
		, index		( 0 )
		, recvCnt	( 0 )
	{}


	/*
	**	������
	*/
	template < class T >
	void 
		SoundBuffer<T>::init( int length )
	{
		len = length;
		ringBuf = new T[ len ];
		memset( ringBuf, 0, sizeof( T ) * len );
		recvCnt = 0;
	}


	/*
	**	�o�b�t�@�ɏ�������
	*/
	template < class T >
	void 
		SoundBuffer<T>::write( T* dat, int length )
	{
		assert( length < len && "SoundBuffer::write(): �������ރT�C�Y���傫�����܂� " && __LINE__ );

		{
			WriteLock lock( rmu );
			unsigned capacity = len - index;
			if ( capacity < length )
			{
				memcpy( ringBuf + index, dat, sizeof( T ) * capacity );

				int offset = length - capacity;
				memcpy( ringBuf, dat, sizeof( T ) * offset );
				index = offset;
			}
			else
			{
				memcpy( ringBuf + index, dat, sizeof( T ) * length );
				index += length;
			}
		}

		{
			WriteLock lock( cmu );
			recvCnt++;
		}

		{
			Lock lock( vmu );
			for ( ListenerList::iterator itr = listeners.begin(); itr != listeners.end(); itr++ )
			{
				(*itr)->receiveData( dat, length );
			}
		}
	}

		
	/*
	**	�o�b�t�@����ǂݍ���
	*/
	template < class T >
	void 
		SoundBuffer<T>::read( T* buffer, int length )
	{
		assert( length < len && "SoundBuffer::read(): �ǂݍ��ރT�C�Y���傫�����܂� " && __LINE__ );
		ReadLock lock( rmu );

		if ( index < length )
		{
			int begin = len + index - length;
			memcpy( buffer, ringBuf + begin, sizeof( T ) * ( length - index ) );
			memcpy( buffer, ringBuf, sizeof( T ) * index );
		}
		else
		{
			memcpy( buffer, ringBuf + index - length, sizeof( T ) * length );
		}
	}


	/*
	**	���݂̃J�E���^���擾
	*/
	template < class T >
	unsigned 
		SoundBuffer<T>::getCounter()
	{
		ReadLock lock( cmu );
		return recvCnt;
	}


	/*
	**	���X�i�[��ǉ�
	*/
	template < class T >
	void 
		aqua::SoundBuffer<T>::addListener( IAudioListener<T>* listener )
	{
		Lock lock( vmu );
		listeners.push_back( listener );
	}


	/*
	**	���X�i�[���폜
	*/
	template < class T >
	void 
		SoundBuffer<T>::removeListener( IAudioListener<T>* listener )
	{
		Lock lock( vmu );
		ListenerList::iterator itr = std::find( listeners.begin(), listeners.end(), listener );

		if ( itr != listeners.end() )
		{
			listeners.erase( itr );
		}
	}
}