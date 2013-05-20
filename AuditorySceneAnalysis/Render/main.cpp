/*
**	main.cpp
**	2013/4/8
*/

 //
/// Include
//
#include <iostream>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include "SDLW.hpp"
#include "Render.hpp"
using namespace std;
using namespace aqua;


 //
/// Source
//
int main(int argc, char **argv)
{
	int width = 640;
	int height = 480;

	SDLW* sdl = new SDLW( width, height, SDL_OPENGL );
	sdl->init();

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
	//glOrtho( -width/2, width/2, -height/2, height/2, 0, 1000 );
	//glOrtho( -1, 1, -1, 1, -1, 1 );

	while ( sdl->processEvent() )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		Render::drawLine( 0.0, 0.0, 100.0, 100.0, Color( 1.0, 0.0, 1.0 ) );
		Render::fillRect( 20, 200, 100, 100, Color( 1.0, 0.0, 0.0, 0.3 ), Color( 1, 0, 0, 0.8 ) );
		Render::fillRect( 70, 250, 100, 100, Color( 1.0, 0.0, 0.0, 0.3 ), Color( 1, 0, 0, 0.8 ) );
		

		SDL_GL_SwapBuffers();
	}

	delete sdl;
	return 0;
}