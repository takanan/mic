
 //
/// Include
//
#include "Render.hpp"
using namespace aqua;


 //
///	Source
//
/*
**	点を描画
*/
void 
	Render::drawPixel( int x, int y, const Color& c )
{
	glColor4f( c.r, c.g, c.b, c.a );
	glBegin( GL_POINTS );
	glVertex2f( x, y );
	glEnd();
}


/*
**	線を描画
*/
void 
	Render::drawLine( int x1, int y1, int x2, int y2, const Color& c )
{
	glColor4f( c.r, c.g, c.b, c.a );
	glBegin( GL_LINES );
	glVertex2f( x1, y1 );
	glVertex2f( x2, y2 );
	glEnd();
}


/*
**	矩形を描画
*/
void 
	Render::drawRect( int x, int y, int w, int h, const Color& c )
{
	glColor4f( c.r, c.g, c.b, c.a );
	glBegin( GL_LINE_LOOP );
	glVertex2f( x, y );
	glVertex2f( x, y+h );
	glVertex2f( x+w, y+h );
	glVertex2f( x+w, y );
	glEnd();	
}


/*
**	真円を描画
*/
void 
	Render::drawCircle( int x, int y, float r, const Color& c )
{}


/*
**	矩形を塗りつぶして描画
*/
void 
	Render::fillRect( int x, int y, int w, int h, const Color& inner, const Color& outer )
{
	glColor4f( inner.r, inner.g, inner.b, inner.a );
	glBegin( GL_TRIANGLE_STRIP );
	glVertex2f( x, y );
	glVertex2f( x, y+h );
	glVertex2f( x+w, y );
	glVertex2f( x+w, y+h );
	glEnd();	

	drawRect( x, y, w, h, outer );
}


/*
**	真円を塗りつぶして描画
*/
void 
	Render::fillCircle( int x, int y, float r, const Color& inner, const Color& outer )
{}
