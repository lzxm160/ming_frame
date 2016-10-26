#include "../log.hpp"
#include "../include.hpp"
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/inspect/Inspector.h>
#include <muduo/net/Connector.h>
#include <boost/unordered_map.hpp>
#include <boost/make_shared.hpp>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <muduo/base/LogStream.h>
#include <execinfo.h>
#include <queue>
#include <vector>
namespace test4_namespace
{
	using std::string;
	typedef struct linknode
	{
		int value;
		linknode* next;
		linknode(int val):value(val),next(nullptr){}
	}node;
	void print(node* phead)
	{
		node* p=phead->next;
		while(p!=nullptr)
		{
			std::cout<<p->value<<"-->";
			p=p->next;
		}	
		std::cout<<"end"<<std::endl;
	}
	void destroy(node* phead)
	{
		node* p;
		while(phead!=nullptr)
		{
			std::cout<<"destroy:"<<phead->value<<std::endl;
			p=phead->next;
			delete phead;
			phead=p;
		}
	}
	void reverse(node* phead,int start,int end)
	{
		node* prev;
		for(int i=0;i<start-1;++i)
		{	
			prev=phead->next;
			phead=prev;
		}
		node* pstart=prev;
		prev=prev->next;
		node* pcur=prev->next;
		for(int i=start;i<end;++i)
		{	
			node* temp=pstart->next;
			pstart->next=pcur;
			prev->next=pcur->next;
			pcur->next=temp;
			pcur=prev->next;
		}
	}
	void test()
	{
		node* phead=new node(0);
		node* pindex=phead;
		for(int i=0;i<10;++i)
		{
			node* p=new node(rand()%100);
			pindex->next=p;
			pindex=pindex->next;
		}
		print(phead);
		reverse(phead,3,5);
		print(phead);
		destroy(phead);
	}
	void deleteDuplicate2(node* phead)
	{
		node* prev=phead;
		node* p=phead->next->next;
		phead=phead->next;
		
		while(p)
		{
			if(p->value==phead->value)
			{
				int temp=p->value;
				while(p->value==temp)
				{
					phead->next=p->next;
					delete p;
					p=phead->next;
				}
				prev->next=p;
				std::cout<<"delete:"<<phead->value<<std::endl;
				delete phead;
				phead=p;
				p=p->next;
				std::cout<<"::"<<prev->value<<std::endl;
				std::cout<<"::"<<phead->value<<std::endl;
				std::cout<<"::"<<p->value<<std::endl;
			}
			else
			{
				p=p->next;
				phead=phead->next;
				prev=prev->next;
			}
		}
	}
	node* partition(node* phead,int value)
	{
		node* left=phead;
		node* right=new node(0);
		node* leftindex=phead;
		node* rightindex=right;
		while(phead&&phead->next)
		{
			if(phead->next->value<value)
			{
				leftindex->next=phead->next;
				phead=phead->next;
				leftindex=leftindex->next;
				std::cout<<":"<<leftindex->value<<std::endl;
			}
			else
			{
				rightindex->next=phead->next;
				leftindex->next=phead->next->next;
				phead=leftindex;
				rightindex=rightindex->next;
				rightindex->next=nullptr;
				std::cout<<"::"<<rightindex->value<<std::endl;
			}
		}
		leftindex->next=right->next;
		return left;
	}
	void test2()
	{
		node* phead=new node(0);
		int digit[]={1,2,8,3,4,4,4,5,6};
		node* pindex=phead;
		for(int i=0;i<8;++i)
		{
			node* p=new node(digit[i]);
			pindex->next=p;
			pindex=pindex->next;
		}
		print(phead);
		//deleteDuplicate(phead);
		//deleteDuplicate2(phead);
		partition(phead,4);
		print(phead);
		destroy(phead);
	}
	void topologic(std::vector<int>& output,std::vector<std::vector<int>> graph)
	{
		const int cnt=13;
  		std::vector<int> indegree(cnt);
  		for(int i=0;i<cnt;++i)
  		{
  			for(int j=0;j<cnt;++j)
  			{
  				indegree[i]+=graph[j][i];
  			}
  		}
  		std::copy(indegree.begin(), indegree.end(), std::ostream_iterator<int>(std::cout, "->"));
  		std::cout<<std::endl;
  		while(output.size()<cnt)
  		{
  			std::queue<int> temp;
	  		for(int i=0;i<cnt;++i)
	  		{
	  			if(indegree[i]==0)
	  				temp.push(i);
	  		}
	  		while(!temp.empty())
	  		{
	  			int value=temp.front();
	  			temp.pop();
	  			output.push_back(value);
	  			std::cout<<output.size()<<std::endl;
	  			indegree[value]=-1;
	  			for(int i=0;i<cnt;++i)
	  			{
	  				if(graph[value][i]==1)
	  				{
	  					indegree[i]-=1;
	  				}
	  			}
	  		}
  		}
  				
	}
	void testtopologic()
	{
		std::vector<std::vector<int>> v
		{{0,1,0,0,0,1,1,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0},
		 {1,0,0,1,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,1,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,1,0,0,0,0,0,0,0,0},
		 {0,0,0,0,1,0,0,0,0,1,0,0,0},
		 {0,0,0,0,0,0,1,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,1,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,1,1,1},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,0,0,1},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		std::vector<int> output;
		topologic(output,v);
		std::copy(output.begin(), output.end(), std::ostream_iterator<int>(std::cout, "->"));
		std::cout<<std::endl;
	}
	int calcpath(const std::vector<std::vector<int>>& graph)
	{
		const int N=16;
		int step[N]={0};//how many step to i
		int path[N]={0};//how many path to i
		path[0]=1;
		std::queue<int> q;
		q.push(0);
		while(!q.empty())
		{
			int from=q.front();
			q.pop();
			for(int i=1;i<N;++i)
			{
				if(graph[from][i]==1)
				{
					if(step[i]==0||step[i]>step[from]+1)
					{
						step[i]=step[from]+1;
						path[i]=path[from];
						q.push(i);
					}
					else if(step[i]==step[from]+1)
					{
						path[i]+=path[from];
					}
				}
				
			}
		}
		return path[N-1];
	}
	void testshortpath()
	{
		const int N=16;
		std::vector<std::vector<int>> graph(N ,std::vector<int>(N,0));
		graph[0][1]=graph[0][4]=1;
		graph[1][5]=graph[1][0]=graph[1][2]=1;
		graph[2][1]=graph[2][6]=graph[2][3]=1;
		graph[3][2]=graph[3][7]=1;
		graph[4][0]=graph[4][5]=1;
		graph[5][1]=graph[5][4]=graph[5][6]=graph[5][9]=1;
		graph[6][2]=graph[6][5]=graph[6][7]=graph[6][10]=1;
		graph[7][3]=graph[7][6]=1;
		graph[8][9]=graph[8][12]=1;
		graph[9][8]=graph[9][13]=graph[9][10]=1;
		graph[10][9]=graph[10][14]=graph[10][11]=1;
		graph[11][10]=graph[11][15]=1;
		graph[12][8]=graph[12][13]=1;
		graph[13][9]=graph[13][12]=graph[13][14]=1;
		graph[14][10]=graph[14][13]=graph[14][15]=1;
		graph[15][11]=graph[15][14]=1;
		std::cout<<calcpath(graph)<<std::endl;
	}
	int get_ml(const string& p)
	{
		int len=p.length();
		std::queue<int> q;
		int ml=0;
		int start=0;
		for(int i=0;i<len;++i)
		{
			if(p[i]=='(')
			{
				q.push(i);
			}
			else
			{
				if(q.empty())
				{
					start=i;
				}
				else
				{
					q.pop();
					if(q.empty())
					{
						if(ml<i-start)
							ml=i-start;
					}
					else
					{
						if(ml<i-q.front())
							ml=i-q.front();
					}
				}
			}
		}
		return ml;
	}
	void test_parenthesis()
	{
		string parenthesis="(())()";
		int maxlength=get_ml(parenthesis);
		std::cout<<maxlength<<std::endl;
	}
	void test_out()
	{
		test_parenthesis();
		//testshortpath();
		//testtopologic();
	}
}