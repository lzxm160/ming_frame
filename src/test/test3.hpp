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
namespace test3_namespace
{
	using std::string;
	class foo;
	class observer:public boost::enable_shared_from_this<observer>
	{
	public:
		observer(boost::shared_ptr<foo> s);
		void observe();
		~observer();
		void update()
		{
			std::cout<<"observer update"<<std::endl;
		}
	private:
		boost::shared_ptr<foo> m_foo;
	};
	class foo
	{
	public:
		void register_observer(boost::weak_ptr<observer> s)
		{
			std::cout<<"foo::register_observer"<<std::endl;
			m_observers.push_back(s);
		}
		// void unregister_observer(boost::weak_ptr<observer> s)
		// {
		// 	for(auto i=m_observers.begin();i!=m_observers.end();++i)
		// 	{
		// 		boost::shared_ptr<observer> temp(i->lock());
		// 		if(temp)
		// 		{
		// 			m_observers.erase(i);
		// 			break;
		// 		}
				
		// 	}
			
		// }
		void test()
		{
			std::cout<<"foo::test"<<std::endl;
			auto i=m_observers.begin();
			 while (i != m_observers.end())
			{
				boost::shared_ptr<observer> temp(i->lock());
				if(temp)
				{
					temp->update();
					++i;
				}
				else
				{
					std::cout<<"foo::test::erase"<<std::endl;
					i = m_observers.erase(i);
				}
			}
		}
	private:
		std::vector<boost::weak_ptr<observer>> m_observers;
	};
	observer::observer(boost::shared_ptr<foo> s):m_foo(s)
	{
		std::cout<<"observer::observer"<<std::endl;
		//m_foo->register_observer(shared_from_this());
	}
	void observer::observe()
	{
		std::cout<<"observer::observe"<<std::endl;
		m_foo->register_observer(shared_from_this());
	}
	observer::~observer()
	{
		std::cout<<"observer::~observer"<<std::endl;
		// m_foo->unregister_observer(shared_from_this());
	}
	class stock
	{
	public:
		stock(const string& name):m_name(name)
		{
			std::cout<<"stock constructor"<<std::endl;
		}
		~stock()
		{
			std::cout<<"stock destructor"<<std::endl;
		}
		string get_name()const
		{
			return m_name;
		}
	private:
		string m_name;
	};
	class stock_factory:public boost::enable_shared_from_this<stock_factory>,boost::noncopyable
	{
	public:
		stock_factory()
		{
			std::cout<<"stock_factory constructor"<<std::endl;
		}
		~stock_factory()
		{
			std::cout<<"stock_factory destructor"<<std::endl;
		}
		boost::shared_ptr<stock> get_stock(const string& key)
		{
			boost::shared_ptr<stock> temp;
			//boost::weak_ptr<stock> temp_weak;
			
			muduo::MutexLockGuard lo(m_mutex);
			boost::weak_ptr<stock>& temp_weak=m_stocks[key];
			temp=temp_weak.lock();
			
			if(temp)
			{
				return temp;
			}
			else
			{
				temp.reset(new stock(key),boost::bind(&stock_factory::weak_delete_callback,boost::weak_ptr<stock_factory>(shared_from_this()),_1));
				temp_weak=temp;
			}
			return temp;
		}
	private:
		static void weak_delete_callback(const boost::weak_ptr<stock_factory>& ptr_self,stock* s)
		{
			if(ptr_self.lock())
			{
				std::cout<<"weak_delete_callback::remove"<<std::endl;
				ptr_self.lock()->remove_stock(s);
			}
			else
			{
				std::cout<<"weak_delete_callback::stock_factory die"<<std::endl;
			}
			delete s;
		}
		void remove_stock(stock* s)
		{
			if(s)
			{
				muduo::MutexLockGuard lo(m_mutex);
				m_stocks.erase(s->get_name());
			}
		}
	private:
		std::map<string,boost::weak_ptr<stock>> m_stocks;
		mutable muduo::MutexLock m_mutex;

	};
	class test_self_lock
	{
	public:
		test_self_lock()
		{}
		~test_self_lock()
		{}
		void process()__attribute__((noinline))
		{
			muduo::MutexLockGuard lo(m_mutex);
			std::cout<<"process"<<std::endl;
			print();
		}
		void print()__attribute__((noinline))
		{
			muduo::MutexLockGuard lo(m_mutex);
			std::cout<<"print"<<std::endl;
		}
	private:
		mutable muduo::MutexLock m_mutex;
	};
	class request
	{
	public:
		//request();
		~request();
		void process();
		void print();
	private:
		mutable muduo::MutexLock m_mutex;
	};
	class inventory
	{
	public:
		inventory(){}
		~inventory(){}
		void add(request* r)
		{
			muduo::MutexLockGuard lo(m_mutex);
			m_requests.insert(r);
		}
		void remove(request* r)
		{
			muduo::MutexLockGuard lo(m_mutex);
			m_requests.erase(r);
		}
		void print_all()const
		{
			muduo::MutexLockGuard lo(m_mutex);
			std::cout<<"void print_all()const"<<std::endl;

			for(auto i=m_requests.begin();i!=m_requests.end();++i)
			{
				std::cout<<"void print_all()const::for"<<std::endl;
				sleep(5);
				(*i)->print();
			}
			std::cout<<"void print_all()const::finish"<<std::endl;
		}
	private:
		std::set<request*> m_requests;
		mutable muduo::MutexLock m_mutex;
	};
	inventory g_inventory;
	
	request::~request()
	{
		muduo::MutexLockGuard lo(m_mutex);
		std::cout<<"request::~request()"<<std::endl;
		sleep(3);
		//usleep(500*1000);
		g_inventory.remove(this);
	}
	void request::process()
	{
		muduo::MutexLockGuard lo(m_mutex);
		std::cout<<"request::process()"<<std::endl;
		g_inventory.add(this);
	}
	void request::print()
	{
		muduo::MutexLockGuard lo(m_mutex);
		std::cout<<"print"<<std::endl;
	}
	muduo::MutexLock mutex;
	muduo::Condition cond(mutex);
	std::deque<int> test_queue;
	int dequeue()
	{
		muduo::MutexLockGuard lo(mutex);
		while(test_queue.empty())
		{
			std::cout<<"before wait"<<std::endl;
			cond.wait();
			std::cout<<"after wait"<<std::endl;
		}
		int top=test_queue.front();
		test_queue.pop_front();
		return top;
	}
	void enqueue(int x)
	{
		muduo::MutexLockGuard lo(mutex);
		test_queue.push_back(x);
		cond.notify();
	}
	class my_mutex
	{
	public:
		my_mutex():m_owner_thread_id(0)
		{
			pthread_mutex_init(&m_mutex,NULL);
			pthread_mutexattr_t mattr;
			pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_NORMAL);
		}
		~my_mutex()
		{
			pthread_mutex_destroy(&m_mutex);
		}
		void lock()
		{
			pthread_mutex_lock(&m_mutex);
			m_owner_thread_id=1;
		}
		void unlock()
		{
			m_owner_thread_id=0;
			pthread_mutex_unlock(&m_mutex);
		}
	private:
		pthread_mutex_t m_mutex;
		pid_t m_owner_thread_id;
	};
	void test_out()
	{
		my_mutex test_mutex;
		test_mutex.lock();
		test_mutex.unlock();
		// muduo::Thread t1([]()
		// 	{
		// 		std::cout<<dequeue()<<std::endl;
		// 	});
		// t1.start();

		// muduo::Thread t2([]()
		// 	{
		// 		enqueue(3);
		// 	});
		// t2.start();
		// t2.join();
		// t1.join();
		
		// muduo::Thread t([]()
		// 	{
		// 		request* r=new request();
		// 		r->process();
		// 		delete r;
		// 	});
		// t.start();
		// //usleep(500*1000);
		// sleep(1);
		// g_inventory.print_all();
		// t.join();
		
		// test_self_lock t;
		// t.process();
		// {
		// 	boost::shared_ptr<stock_factory> sf(new stock_factory());
		// 	{
		// 		boost::shared_ptr<stock> s1=sf->get_stock("us");
		// 		boost::shared_ptr<stock> s2=sf->get_stock("uk");
		// 	}
		// }
		// std::cout<<"------------------------------"<<std::endl;
		// {
		// 	boost::shared_ptr<stock> s;
		// 	{
		// 		boost::shared_ptr<stock_factory> sf(new stock_factory());
		// 		s=sf->get_stock("ll");
		// 	}
		// 	std::cout<<s->get_name()<<std::endl;
		// }
	}
}