#ifndef MONTH_REPORT_HPP
#define	MONTH_REPORT_HPP
#include "mysql_connection.h"
#include "../config.hpp"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "../log.hpp"
struct report_data
 {
 	std::string quotation_id;
 	std::string quotation_detail_id;
 	std::string quotation_no;
 	std::string sales_full_name;
 	std::string sales_type;
 	std::string account_name;
 	std::string country_region;
 	std::string customer_countries;
 	std::string receiving_countries;
 	std::string product_classification;
 	std::string product_name;
 	double product_qty_pc;
 	double product_qty_w;
 	std::string price_condition;
 	std::string currency;
 	double unit_price;
 	std::string price_total_currency;
 	double price_total;
 	std::string guided_currency;
 	double price_total_guided;
 	std::string payment_term_desc;
 	std::string creat_at;
 	void print()
 	{
 		std::cout<<quotation_id
 			<<":"<<quotation_detail_id
 			<<":"<<quotation_no
 			<<":"<<sales_full_name<<":"
			<<":"<<sales_type<<":"
 			<<":"<<account_name<<":"
			<<":"<<country_region<<":"
			<<":"<<customer_countries<<":"
 			<<":"<<receiving_countries<<":"
 			<<":"<<product_classification<<":"
			<<":"<<product_name<<":"
 			<<":"<<product_qty_pc<<":"
			<<":"<<product_qty_w<<":"
			<<":"<<price_condition<<":"
 			<<":"<<currency<<":"
 			<<":"<<unit_price<<":"
			<<":"<<price_total_currency<<":"
 			<<":"<<price_total<<":"
			<<":"<<guided_currency<<":"
			<<":"<<price_total_guided<<":"
 			<<":"<<payment_term_desc<<":"
 			<<":"<<creat_at
 			<<std::endl;
 	}
 }; 
struct mysql_info_
 {
 	std::string ip;
 	std::string port;
 	std::string username;
 	std::string password;
 	std::string database;
 }; 
class month_report
{
public:
	month_report(boost::shared_ptr<mysql_info_> in);
	void start();
private:
	void query(const std::string& sql);
	boost::shared_ptr<sql::ResultSet> get_res()const;
	void insert_data();
private:
	std::vector<boost::shared_ptr<report_data>> m_report_datas;
	boost::shared_ptr<sql::ResultSet> m_res;
	boost::shared_ptr<sql::Statement> m_stmt;
	boost::shared_ptr<sql::PreparedStatement> m_pstmt;
	boost::shared_ptr<sql::Driver> m_drivers;
	boost::shared_ptr<sql::Connection> m_con;

	sql::Driver* m_driver;
};

void start_report();

#endif