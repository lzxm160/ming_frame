#ifndef TEST_HPP
#define	TEST_HPP
#include "../log.hpp"
#include "../include.hpp"
namespace test1
{
	namespace test_model_design_factory
	{
		class isplitter_base
		{
		public:
			virtual void split()=0;
			virtual ~isplitter_base(){}
		};
		class binary_spitter:public isplitter_base
		{
		public:
			void split();
		};
		class factory_base
		{
		public:
			virtual boost::shared_ptr<isplitter_base> create()=0;
			virtual ~factory_base(){}
		};
		class binary_factory:public factory_base
		{
		public:
			boost::shared_ptr<isplitter_base> create();
		};
		class caller
		{	
		public:
			caller(boost::shared_ptr<factory_base> fb);
			void start();
		private:
			boost::shared_ptr<factory_base> m_ib;
		};
		void test();
	}
	void test();
}
#endif

