#pragma once
#include <boost/unordered_map.hpp>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <execinfo.h>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <set>
namespace test7_namespace
{
int getSqrt(int a)
{
	int x=(int)std::sqrt(a);
	std::cout<<x<<":"<<std::sqrt(a)<<std::endl;
	if(x*x>a)
	{
		return x-1;
	}
	return x;
}
int getSqrt2(double a)
{
	if(a==1)
		return 1;
	double x=a/2;
	double t=a;
	while(std::fabs(x-t)>1e-6)
	{
		t=x;
		x=(x+a/x)/2;
	}
	// if(x*x>a)
	// 	return (int)x-1;
	return x;
}
void squareSplit(int n)
{
	std::vector<int> dp(n+1);
	std::vector<int> pre(n+1);
	for(int i=0;i<n+1;++i)
	{
		dp[i]=i;
		pre[i]=i-1;
	}
	pre[0]=0;
	for(int i=1;i<n+1;++i)
	{
		int k=getSqrt2(i);
		if(k*k==i)
		{
			dp[i]=1;
			pre[i]=0;
			continue;
		}
		for(int j=1;j<=k;++j)
		{
			int t=i-j*j;
			if((dp[t]+1)<dp[i])
			{
				dp[i]=dp[t]+1;
				pre[i]=t;
			}
		}
	}
	std::cout<<dp[n]<<std::endl;
	{
		//get answer from pre
		int step=dp[n];
		while(step>0)
		{
			std::cout<<getSqrt2(n-pre[n])<<" ";
			n=pre[n];
			// if(n<0)
			// 	break;
			--step;
		}
		std::cout<<std::endl;
	}
}
int squareSplitRecursion(int n,int dp,int& step)
{
	// if(dp==1)
	// 	return 1;
	// int k=getSqrt2(dp);
	// for(int j=1;j<k;++j)
	// {
	// 	int t=dp-j*j;
	// 	if((dp[t]+1)<dp[i])
	// 	{
	// 		dp[i]=dp[t]+1;
	// 		pre[i]=t;
	// 	}
	// }
	// int temp=getSqrt2(n-dp);
	// if(temp*temp==(n-dp))
	// {
	// 	++step;
	// }
	// else
	// {
	// 	squareSplitRecursion(n,dp,step);
	// }
	
}
void test_squareSplit()
{
	const int N=201314;
	squareSplit(N);
}
void chargeChange(std::vector<int> dom,int n)
{
	std::vector<std::vector<int>> dp(dom.size(),std::vector<int>(n+1,0));
	 
	for(int i=0;i<=n;++i)
	{
		dp[0][i]=1;
	}
	for(int i=0;i<dom.size();++i)
	{
		dp[i][0]=1;
	}
	for(int i=1;i<dom.size();++i)
	{
		for(int j=0;j<=n;++j)
		{
			if(j>=dom[i])
			{
				dp[i][j]=dp[i-1][j]+dp[i][j-dom[i]];
			}
			else
				dp[i][j]=dp[i-1][j];
			
		}
	}
	std::cout<<dp[dom.size()-1][n]<<std::endl;
}
void chargeChange2(std::vector<int> dom,int n)
{
	std::vector<int> dp(n+1,1);
	std::vector<int> last(n+1,1);
	 
	for(int i=1;i<dom.size();++i)
	{
		for(int j=0;j<=n;++j)
		{
			if(j>=dom[i])
			{
				dp[j]=last[j]+dp[j-dom[i]];
				last[j]=dp[j];
			}
		}
	}
	std::cout<<dp[n]<<std::endl;
}
void test_chargeChange()
{
	std::vector<int> dom{1,2,5,10,20,50,100};
	const int N=5;
	chargeChange(dom,N);
	chargeChange2(dom,N);
}
bool isScramble(std::string one,std::string two)
{
	int oneLength=one.length();
	int twoLength=two.length();

	if(oneLength!=twoLength)
		return false;
	if(oneLength==0)
		return true;
	if(oneLength==1)
		return one[0]==two[0];
	for(int i=1;i<oneLength;++i)
	{
		bool oneWay=isScramble(one.substr(0,i),two.substr(0,i))&&isScramble(one.substr(i,oneLength-i),two.substr(i,oneLength-i));
		bool twoWay=isScramble(one.substr(0,i),two.substr(oneLength-i,i))&&isScramble(one.substr(i,oneLength-i),two.substr(0,oneLength-i));
		if(oneWay||twoWay)
			return true;
	}
	return false;
}
void test_isScramble()
{
	using std::string;
	string one="great";
	string two="rgeat";
	string three="rteac";
	std::cout<<isScramble(one,two)<<std::endl;
	std::cout<<isScramble(one,three)<<std::endl;
}
void test_out()
{
	test_isScramble();
	// test_chargeChange();
	// test_squareSplit();
	// 	std::cout<<getSqrt(10)<<std::endl;
	// 	std::cout<<getSqrt(15)<<std::endl;
	// 	std::cout<<getSqrt(16)<<std::endl;
	// std::cout<<getSqrt2(10)<<std::endl;
	// std::cout<<getSqrt2(15)<<std::endl;
	// std::cout<<getSqrt2(16)<<std::endl;
}
}
