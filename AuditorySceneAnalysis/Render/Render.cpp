
 //
/// Include
//
#include "Render.hpp"
using namespace aqua;


 //
///	Source
//
/*
**	“_‚ğ•`‰æ
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
**	ü‚ğ•`‰æ
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
**	‹éŒ`‚ğ•`‰æ
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
**	^‰~‚ğ•`‰æ
*/
void 
	Render::drawCircle( int x, int y, float r, const Color& c )
{}


/*
**	‹éŒ`‚ğ“h‚è‚Â‚Ô‚µ‚Ä•`‰æ
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
**	^‰~‚ğ“h‚è‚Â‚Ô‚µ‚Ä•`‰æ
*/
void 
	Render::fillCircle( int x, int y, float r, const Color& inner, const Color& outer )
{}
