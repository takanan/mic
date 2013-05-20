#pragma once
/*
**	FFTViewer
**	”gŒ`‚ðOpenGL‚ðŽg‚Á‚Ä•`‰æ
*/


 //
/// Include
//
#include <boost/circular_buffer.hpp>
#include "../Render/Render.hpp"
#include "FFTAnalyzer.hpp"


 //
/// Source
//
namespace aqua
{
	class FFTViewer
	{
	private:
		FFTAnalyzer* ffta;


	public:
		FFTViewer( FFTAnalyzer* fftAnalyzer )
			: ffta	( fftAnalyzer )
		{}


		~FFTViewer()
		{}


		void update()
		{}


		void render( int x, int y, int w, int h )
		{
			int N = ffta->getN();
			
			float ratio = 1.0f;
			if ( h < ffta->getFreqSize() )
			{
				ratio = (float)ffta->getFreqSize()/h;
			}
			else
			{
				h = ffta->getFreqSize();
			}

			w = w > ffta->getLength() ? ffta->getLength() : w;

			glBegin( GL_POINTS );
			for ( int i=0; i<w; i++ )
			{
				const float* const power = ffta->getPowerSpectrum( i );
				int prevIdx = 0;

				for ( int j=0; j<h; j++ )
				{
					float alpha;
					if ( ratio != 1.0f )
					{
						const int idx = (int)(ratio*j);
						float max = 0;

						for ( int k=prevIdx; k<idx; k++ )
						{
							if ( max < power[k] ) max = power[k];
						}

						alpha = max / (float)N;
						prevIdx = idx;
					}
					else
					{
						alpha = power[j]/(float)N;
					}

					if ( alpha > 0.005 )
					{
						glColor4f( 0.07, 0.75, 0.8, alpha );
						glVertex2f( x + i, y + j );
					}
				}
			}
			glEnd();
		}

	};
}