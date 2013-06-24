#pragma once
/*
**	SDLW.hpp
**	SDLラッパークラス
**
**	2013/4/8
*/


 //
/// Include
//
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>


 //
/// Source
//
namespace aqua
{
	class SDLW
	{
	private:
		int width;
		int height;
		int flags;

	public:
		SDLW( int width, int height, int flags );
		~SDLW();

	public:
		bool init();
		bool processEvent();
	};

	/*
	**	コンストラクタ
	*/
	SDLW::SDLW( int width, int height, int flags )
		: flags		( flags )
		, width		( width )
		, height	( height )
	{}


	/*
	**	デストラクタ
	*/
	SDLW::~SDLW()
	{
		SDL_Quit();
	}


	/*
	**	イニシャライザ
	*/
	bool 
		SDLW::init()
	{
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			std::cerr << "ビデオシステムの初期化に失敗: " << SDL_GetError() << std::endl;
			return false;
		}

		const SDL_VideoInfo* info = SDL_GetVideoInfo();
		if ( !info )
		{
			std::cerr << "ビデオシステムの情報取得に失敗: " << SDL_GetError() << std::endl;
			return false;
		}

		int bpp = info->vfmt->BitsPerPixel;
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		if ( SDL_SetVideoMode( width, height, bpp, flags ) == 0 )
		{
			std::cerr << "ビデオモードの設定に失敗: " << SDL_GetError() << std::endl;
			return false;
		}	

		glShadeModel( GL_SMOOTH );

		glCullFace( GL_BACK );
		glFrontFace( GL_CCW );
		glEnable( GL_CULL_FACE );

		glClearColor( 1.0, 1.0, 1.0, 1.0 );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glViewport( 0, 0, width, height );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0, width, height, 0, 0, 1000 );

		return true;
	}


	/*
	**	イベントを処理する
	*/
	bool 
		SDLW::processEvent()
	{
		SDL_Event e;
		while ( SDL_PollEvent( &e ) )
		{
			switch ( e.type )
			{
			case SDL_KEYDOWN:
				break;
			case SDL_QUIT:
				return false;
			default:
				break;
			}
		}

		return true;
	}
}