#pragma once
#ifndef __ITF_BINARY_IMAGE__
#define __ITF_BINARY_IMAGE__

/*
**	IBinaryImage.hpp
**	２値画像用インターフェース
**	
**	update : 2013/4/5
*/


namespace aqua
{
	class IBinaryImage
	{
	public:

		/*
		**	ピクセルに値をセット
		*/
		virtual void setPixel( int x, int y, bool pix ) = 0;


		/*
		**	ピクセルの値を取得
		**		有		(1)
		**		無		(0)
		**		範囲外	(-1)
		*/
		virtual int getPixel( int x, int y ) = 0;


		/*
		**	幅取得
		*/
		virtual int getWidth() = 0;


		/*
		**	高さ取得
		*/
		virtual int getHeight() = 0;
	};
}

#endif // __ITF_BINARY_IMAGE__