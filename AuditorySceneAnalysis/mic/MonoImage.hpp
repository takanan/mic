#pragma once
/*
**	MonoImage.hpp
**	1チャンネルな画像
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
	**	コンストラクタ
	*/
	MonoImage::MonoImage()
		: w		( -1 )
		, h		( -1 )
		, img	( NULL )
	{}


	/*
	**	デストラクタ
	*/
	MonoImage::~MonoImage()
	{
		release();
	}


	/*
	**	初期化
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
	**	解放
	*/
	bool 
		MonoImage::release()
	{
		if ( img ) delete[] img;
		img = NULL;

		return true;
	}


	/*
	**	描画
	*/
	void
		MonoImage::render()
	{}


	/*
	**	ピクセルに値をセット
	*/
	void  
		MonoImage::setPixel( int x, int y, bool pix )
	{
		img[ y*w + x ] = pix;
	}


	/*
	**	ピクセルの値を取得
	**		有		(1)
	**		無		(0)
	**		範囲外	(-1)
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
	**	幅取得
	*/
	int  
		MonoImage::getWidth()
	{
		return w;
	}


	/*
	**	高さ取得
	*/
	int  
		MonoImage::getHeight()
	{
		return h;
	}
}