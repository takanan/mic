#pragma once
/*
**	FFTAnalyzer
**	高速フーリエ変換を行うクラス
**
**	2013/4/12
*/


 //
/// Include
//
#include <fftw3.h>
#include "SoundBuffer.hpp"


 //
/// Source
//
namespace aqua
{
	class FFTAnalyzer
	{
	private:
		const int N;
		const int flen;
		const int len;
		int index;
		int prevBufIdx;
		float* in;
		float** power;
		fftwf_plan plan;
		fftwf_complex* out;
		SoundBuffer<float>* buf;

	public:
		FFTAnalyzer( const int N, SoundBuffer<float>* buffer, int length )
			: N				( N )
			, buf			( buffer )
			, len			( length )
			, index			( 0 )
			, prevBufIdx	( -1 )
			, flen			( N/2+1 )
		{
			power = new float*[ length ];
			for ( int i=0; i<length; i++ ) power[i] = new float[ flen ];

			in = (float*)fftwf_alloc_real( N );
			out = (fftwf_complex*)fftwf_alloc_complex( flen );
			plan = fftwf_plan_dft_r2c_1d( N, in, out, FFTW_MEASURE );
		}

		~FFTAnalyzer()
		{
			fftwf_free( in );
			fftwf_free( out );
		
			for ( int i=0; i<len; i++ ) delete[] power[i];
			delete[] power;
		}


	public:
		void analyze()
		{
			if ( buf->getCounter() == prevBufIdx )
			{
				return;
			}
			prevBufIdx = buf->getCounter();

			buf->read( in, N );
			fftwf_execute( plan );

			for ( int i=0; i<flen; i++ )
			{
				float* elem = (float*)(out[i]);
				const float re = elem[0];
				const float im = elem[1];
				const float pow = re*re + im*im;
				power[index][i] = re*re + im*im;
			}

			index = ++index%len;
		}


		float* getPowerSpectrum( int i )
		{
			const int ofs = index-i-1;
			const int idx = ofs<0 ? len+ofs : ofs;
			return power[idx];
		}


		int getFreqSize()
		{
			return flen;
		}


		int getLength()
		{
			return len;
		}


		int getN()
		{
			return N;
		}
	};
}