#pragma once
/*
**	MonoImage.hpp
**	1�`�����l���ȉ摜
*/


 //
/// Include
//
#include <iostream>
#include "IBinaryImage.hpp"


 //
/// Source
//
namespace aqua
{
	class MonoImage : public IBinaryImage
	{
	private:
		int w;
		int h;
		unsigned char* img;

	public:
		MonoImage();
		~MonoImage();

	public:
		bool init( int width, int height );
		bool release();

	public:
		void render();

	public:
		/* inherited */
		void setPixel( int x, int y, bool pix );
		int getPixel( int x, int y );
		int getWidth();
		int getHeight();

	};


	/*
	**	�R���X�g���N�^
	*/
	MonoImage::MonoImage()
		: w		( -1 )
		, h		( -1 )
		, img	( NULL )
	{}


	/*
	**	�f�X�g���N�^
	*/
	MonoImage::~MonoImage()
	{
		release();
	}


	/*
	**	������
	*/
	bool 
		MonoImage::init( int width, int height )
	{
		release();

		w = width;
		h = height;
		img = new unsigned char[ w * h ];

		return true;
	}


	/*
	**	���
	*/
	bool 
		MonoImage::release()
	{
		if ( img ) delete[] img;
		img = NULL;

		return true;
	}


	/*
	**	�`��
	*/
	void
		MonoImage::render()
	{}


	/*
	**	�s�N�Z���ɒl���Z�b�g
	*/
	void  
		MonoImage::setPixel( int x, int y, bool pix )
	{
		img[ y*w + x ] = pix;
	}


	/*
	**	�s�N�Z���̒l���擾
	**		�L		(1)
	**		��		(0)
	**		�͈͊O	(-1)
	*/
	int  
		MonoImage::getPixel( int x, int y )
	{
		if ( x < w && x >= 0 && y < h && y >= 0 )
		{
			return (bool)img[ y*w + x ];
		}
		
		return -1;
	}


	/*
	**	���擾
	*/
	int  
		MonoImage::getWidth()
	{
		return w;
	}


	/*
	**	�����擾
	*/
	int  
		MonoImage::getHeight()
	{
		return h;
	}
}