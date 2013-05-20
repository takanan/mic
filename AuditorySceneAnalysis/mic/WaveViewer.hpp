#pragma once
/*
**	WaveViewer
**	”gŒ`‚ðOpenGL‚ðŽg‚Á‚Ä•`‰æ
*/


 //
/// Include
//
#include <vector>
#include "../Render/Render.hpp"
#include "SoundBuffer.hpp"


 //
/// Source
//
namespace aqua
{
	class WaveViewer
	{
	private:
		float** buf;
		int len;
		std::vector< SoundBuffer<float>* > sb;


	public:
		WaveViewer( std::vector< SoundBuffer<float>* >& buffer, int length )
			: sb	( buffer )
			, len	( length )
			, buf	( new float*[ buffer.size() ] )
		{
			for ( int i=0; i<buffer.size(); i++ )
			{
				buf[i] = new float[ len ];
			}
		}


		~WaveViewer()
		{
			for ( int i=0; i<sb.size(); i++ ) delete[] buf[i];
			delete[] buf;
		}


		void update()
		{
			for ( int i=0; i<sb.size(); i++ ) sb[i]->read( buf[i], len );
		}


		void render( int x, int y, int w, int h )
		{
			glBegin( GL_LINES );
				glColor3f( 0, 0, 0 );
				glVertex2f( x, y );
				glVertex2f( x, y+h ); 

				glEnable( GL_LINE_STIPPLE );
				glLineStipple( 1 ,0x5555 );
				glColor3f( 0.9, 0.9, 0.9 );
				glVertex2f( x, y + h/2 );
				glVertex2f( x+w, y + h/2 ); 
				glDisable( GL_LINE_STIPPLE );
			glEnd();

			for ( int j=0; j<sb.size(); j++ )
			{
				Color c = Color::hsv2rgb( 220 + 360.0*j/sb.size(), 0.7, 1.0 );

				glBegin( GL_LINE_STRIP );
				const int half = h/2;
				const int yofs = y + half;
				w = w > len ? len : w;
				for ( int i=0; i<w; i++ )
				{
					float value = -half * buf[j][i];
					glColor3f( c.r, c.g, c.b );
					glVertex2f( x+i, value + yofs );
				}
				glEnd();
			}
		}

	};
}