/*
**	HoughLine.hpp
**	ハフ変換を実装するクラス
**
**	update : 2013/4/5
*/

#pragma once
#ifndef __HOUGH_LINE_HPP__
#define __HOUGH_LINE_HPP__


 //
/// Include
//
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Algebra.hpp"
#include "IBinaryImage.hpp"
 

namespace aqua
{

	class HoughLine
	{
	public:
		struct VotingLine
		{
			VotingLine( int vote, int r, int t ) : vote ( vote ), r ( r ), t ( t ) {}
			int vote;
			int r;
			int t;
		};
		typedef std::vector<VotingLine> LineList;

	private:
		Vec2 rhoRng;
		int rhoPart;
		int thetaPart;
		unsigned** votingPool;
		double* thetaTable;
		double* cosTable;
		double* sinTable;
		double rhoStribe;
		double thetaStribe;
		int threshold;
		int minDist;

	public:
		HoughLine( Vec2 rhoRange, int rhoPartitions, int thetaPartitions, int voteThreshold, int minDistance );

	public:
		void vote( IBinaryImage* img );
		void vote( int x, int y );
		void clearVoting();
		LineList pickup();

	private:
		void voteToPool( int r, int t );
		VotingLine pickupFromPool();
		double clip( double max, double x, double min );
	};


	/*
	**	コンストラクタ
	*/
	HoughLine::HoughLine( Vec2 rhoRange, int rhoPartitions, int thetaPartitions, int voteThreshold, int minDistance )
		:	rhoRng			( rhoRange )
		,	rhoPart			( rhoPartitions )
		,	thetaPart		( thetaPartitions )
		,	threshold		( voteThreshold )
		,	minDist			( minDistance )
	{
		rhoStribe = ( ( rhoRng[0] - rhoRng[1] ) / (double)rhoPart );
		thetaStribe = 2*M_PI / (double) thetaPart;
		votingPool = new unsigned*[rhoPart];
		cosTable = new double[thetaPart];
		sinTable = new double[thetaPart];

		for ( int i=0; i<thetaPart; i++ )
		{
			votingPool[i] = new unsigned[thetaPart];

			const double theta = thetaStribe * i;
			cosTable[i] = cos( theta );
			sinTable[i] = sin( theta );
		}
	}


	/*
	**	デストラクタ
	*/
	HoughLine::~HoughLine()
	{
		for ( int i=0; i<thetaPart; i++ )
		{
			delete[] votingPool[i];
		}
		delete[] votingPool;
		delete[] cosTable;
		delete[] sinTable;
	}


	/*
	**	２値画像で投票
	*/
	void 
		HoughLine::vote( IBinaryImage* img )
	{
		const int width = img->getWidth();
		const int height = img->getHeight();

		for ( int x=0; x<width; x++ )
		{
			for ( int y=0; y<height; y++ )
			{
				if ( img->getPixel(x,y) == 1 ) vote( x, y );
			}
		}
	}


	/*
	**	(x,y)を通る直線をすべて投票
	*/
	void
		HoughLine::vote( int x, int y )
	{
		for ( int t=0; t<thetaPart; t++ )
		{
			const double rho = x*cosTable[t] + y*sinTable[t];
			const int r = static_cast<int>( ( rho - rhoRng[1] ) / rhoStribe );

			voteToPool( r, t );
		}
	}


	/*
	**	投票空間から有意な直線をピックアップ
	*/
	HoughLine::LineList
		HoughLine::pickup()
	{
		LineList lineList;

		while ( 1 )
		{
			VotingLine line = pickupFromPool();
			if ( line.vote < threshold ) break;

			line.r = line.r * rhoStribe + rhoRng[1];
			line.t = line.t * thetaStribe;
			lineList.push_back( line );

			const int half = minDist/2;
			for ( int x=-half; x<half; x++ )
			{
				for ( int y=-half; y<half; y++ )
				{
					const int zx = line.r + x;
					const int zy = line.t + y;

					if ( zx < 0 || zx > rhoPart || zy < 0 || zy > thetaPart ) continue;
					votingPool[zx][zy] = 0;
				}
			}
		}

		return lineList;
	}


	/*
	**	投票空間をクリア
	*/
	void 
		HoughLine::clearVoting()
	{
		for ( int i=0; i<rhoPart; i++ )
		{
			for ( int j=0; j<thetaPart; j++ )
			{
				votingPool[i][j] = 0;
			}
		}
	}


	/*
	**	指定インデックスの場所に投票する
	*/
	void 
		HoughLine::voteToPool( int r, int t )
	{
		votingPool[r][t]++;
	}


	/*
	**	最大要素をピックアップ
	*/
	HoughLine::VotingLine
		HoughLine::pickupFromPool()
	{
		VotingLine v( 0, 0, 0 );

		for ( int i=0; i<rhoPart; i++ )
		{
			for ( int j=0; j<thetaPart; j++ )
			{
				if ( v.vote < votingPool[i][j] )
				{
					v.vote = votingPool[i][j];
					v.r = i;
					v.t = j;
				}
			}
		}

		return v;
	}


	/*
	**	xをmaxとminの範囲に収める
	*/
	double
		HoughLine::clip( double max, double x, double min )
	{
		if ( x > max ) return max;
		if ( x < min ) return min;
		return x;
	}
}


#endif // __HOUGH_LINE_HPP__