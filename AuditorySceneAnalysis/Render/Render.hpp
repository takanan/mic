#pragma once
/*
**	Render.hpp
**	OpenGLを使って描画を行うクラス
**
**	2013/4/8
*/


 //
/// Include
//
#include <SDL_opengl.h>
#include <math.h>


 //
///	Source
//
namespace aqua
{
	struct Color
	{
		float r, g, b, a;

		Color( float r, float g, float b, float a = 1.0 )
			: r ( r ), g ( g ), b ( b ), a ( a )
		{}

		static Color hsv2rgb( float h, float s, float v )
		{
			h = fmod( h, 360 );
			int hi = ((int)floor( h/60 ))%6;
			float f = h/60 - hi;
			float p = v*(1-s);
			float q = v*(1-f*s);
			float t = v*(1-(1-f)*s);

			switch ( hi )
			{	
				case 0: return Color( v, t, p );
				case 1: return Color( q, v, p );
				case 2: return Color( p, v, t );
				case 3: return Color( p, q, v );
				case 4:	return Color( t, p, v );
				case 5: return Color( v, p, q );
			}
			return Color(0,0,0);
		}
	};

	class Render
	{
	public:
		static void viewPers(){}
		static void viewIso(){}

		static void drawPixel( int x, int y, const Color& c );
		static void drawLine( int x1, int y1, int x2, int y2, const Color& c );
		static void drawRect( int x, int y, int w, int h, const Color& c );
		static void drawCircle( int x, int y, float r, const Color& c );
		static void fillRect( int x, int y, int w, int h, const Color& inner, const Color& outer );
		static void fillCircle( int x, int y, float r, const Color& inner, const Color& outer );
	};
}