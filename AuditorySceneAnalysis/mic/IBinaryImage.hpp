#pragma once
#ifndef __ITF_BINARY_IMAGE__
#define __ITF_BINARY_IMAGE__

/*
**	IBinaryImage.hpp
**	�Q�l�摜�p�C���^�[�t�F�[�X
**	
**	update : 2013/4/5
*/


namespace aqua
{
	class IBinaryImage
	{
	public:

		/*
		**	�s�N�Z���ɒl���Z�b�g
		*/
		virtual void setPixel( int x, int y, bool pix ) = 0;


		/*
		**	�s�N�Z���̒l���擾
		**		�L		(1)
		**		��		(0)
		**		�͈͊O	(-1)
		*/
		virtual int getPixel( int x, int y ) = 0;


		/*
		**	���擾
		*/
		virtual int getWidth() = 0;


		/*
		**	�����擾
		*/
		virtual int getHeight() = 0;
	};
}

#endif // __ITF_BINARY_IMAGE__