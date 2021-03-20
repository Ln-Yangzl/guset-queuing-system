#include "top_head.h"
#include "table_queue.h"
#include "customer.h"
#include <fstream>
#include <iostream>

using std::cin;			using std::cout;
using std::endl;		using std::ifstream;
using std::ofstream;

typedef customer_node Node;
typedef customer_node* NodePtr;

/*
 * 此程序中的所有时间实际存储的都是从0开始的时间，且仅仅储存分钟数，不产生进位，
 * 只有在格式化输出的时候才会调整为11:00开始的，按常用时间格式的方式输出。这样保证了程序内部时间比较的方便性。
 */

int main() {
	ofstream customer_file("input_customer.txt"), output_data("output_data.txt");
	rand_data(customer_file);
	ifstream table_file("input_table.txt"), cust_file("input_customer.txt");
	customer customer_list(cust_file);
	table_queue table_list(table_file);
	int time = 0, last_leave_time = 0;
	NodePtr client(NULL);
	//控制模块，具体图解可参看实验报告
	//客人入店，出店的时间戳会在push和pop时被打上，具体实现方法可参看相应头文件
	do {
		if (table_list.full() || table_list.top_time() <= customer_list.top_time()) {		//桌位已满或者客人离店时间在前，让一组客人离店
			time = table_list.top_time();
			last_leave_time = last_leave_time > time ? last_leave_time : time;
			table_list.pop();
		}
		else {
			client = customer_list.fewer(table_list.max_empty_table());			//找一组能够符合当前空闲桌位的最前客人组，可能相等，也可能顾客人数小于桌位数
			if (client == NULL) {					//找不到这样的客人组
				if(table_list.empty()) break;		//没有新顾客且桌位已空
				time = table_list.top_time();
				last_leave_time = last_leave_time > time ? last_leave_time : time;
				table_list.pop();					//让一组顾客离店
			}
			else {
				time = time > client->arrive_time() ? time : client->arrive_time();		//找到符合要求的顾客组，顾客进店
				table_list.push(client, time);
				customer_list.pop();
			}
		}
		
	} while (!table_list.empty() || !customer_list.empty());
	customer_list.put_all(cout);
	output_data << "平均停留时间" << '\t' << "平均等待时间" << '\t' << "最后离开时间" << endl;
	output_data << customer_list.ave_stay() << "\t\t" << customer_list.ave_wait() << "\t\t";
	customer::time_out(output_data, time + 660);
	output_data << endl;
	return 0;
}