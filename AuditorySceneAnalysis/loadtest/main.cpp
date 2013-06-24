#pragma comment( lib, "winmm.lib" )
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <fftw3.h>
#include <fstream>
#include <iostream>
using namespace std;



int main( int argn, char** argv )
{
	ofstream ofs( "test.txt" );
	
	ofs << "12345";
	ofs.seekp( 2, ios::beg );
	ofs << "8";

	ofs.close();
	cout << "end";

	getchar();
	return 0;
}


void timer_test()
{
	int N = 100000;
	SDL_Init( SDL_INIT_TIMER );

	for ( int t=0; t<5; t++ )
	{
		unsigned start = timeGetTime();
		for ( int i=0; i<N; i++ )
		{
			for ( int k=0; k<12000; k++ )
			{
				int ta = k + i;
				int tb = ta + 1;
			}
		}
		int time = timeGetTime() - start;
		printf( "time(%5d)  avg(%fms)\n", time, (float)time/N );
	}
}


void fftw_test()
{
	int N = 100000;
	int F = 512;

	fftwf_complex* in = fftwf_alloc_complex( F );
	fftwf_complex* out = fftwf_alloc_complex( F );

	fftwf_plan plan = fftwf_plan_dft_r2c_1d( F, (float*)in, out, FFTW_MEASURE );
	//fftwf_plan_dft_1d( F, in, out, FFTW_FORWARD, FFTW_MEASURE );
	
	for ( int i=0; i<F*2; i++ )
	{
		((float*)in)[i] = (float)rand()/RAND_MAX;
	}


	for ( int t=0; t<10; t++ )
	{
		unsigned start = ::timeGetTime();
		for ( int i=0; i<N; i++ )
		{
			::fftwf_execute( plan );
		}
		int time = timeGetTime() - start;
		printf( "time(%5d)  avg(%fms)\n", time, (float)time/N );
	}

	getchar();
}