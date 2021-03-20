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
 * �˳����е�����ʱ��ʵ�ʴ洢�Ķ��Ǵ�0��ʼ��ʱ�䣬�ҽ����������������������λ��
 * ֻ���ڸ�ʽ�������ʱ��Ż����Ϊ11:00��ʼ�ģ�������ʱ���ʽ�ķ�ʽ�����������֤�˳����ڲ�ʱ��Ƚϵķ����ԡ�
 */

int main() {
	ofstream customer_file("input_customer.txt"), output_data("output_data.txt");
	rand_data(customer_file);
	ifstream table_file("input_table.txt"), cust_file("input_customer.txt");
	customer customer_list(cust_file);
	table_queue table_list(table_file);
	int time = 0, last_leave_time = 0;
	NodePtr client(NULL);
	//����ģ�飬����ͼ��ɲο�ʵ�鱨��
	//������꣬�����ʱ�������push��popʱ�����ϣ�����ʵ�ַ����ɲο���Ӧͷ�ļ�
	do {
		if (table_list.full() || table_list.top_time() <= customer_list.top_time()) {		//��λ�������߿������ʱ����ǰ����һ��������
			time = table_list.top_time();
			last_leave_time = last_leave_time > time ? last_leave_time : time;
			table_list.pop();
		}
		else {
			client = customer_list.fewer(table_list.max_empty_table());			//��һ���ܹ����ϵ�ǰ������λ����ǰ�����飬������ȣ�Ҳ���ܹ˿�����С����λ��
			if (client == NULL) {					//�Ҳ��������Ŀ�����
				if(table_list.empty()) break;		//û���¹˿�����λ�ѿ�
				time = table_list.top_time();
				last_leave_time = last_leave_time > time ? last_leave_time : time;
				table_list.pop();					//��һ��˿����
			}
			else {
				time = time > client->arrive_time() ? time : client->arrive_time();		//�ҵ�����Ҫ��Ĺ˿��飬�˿ͽ���
				table_list.push(client, time);
				customer_list.pop();
			}
		}
		
	} while (!table_list.empty() || !customer_list.empty());
	customer_list.put_all(cout);
	output_data << "ƽ��ͣ��ʱ��" << '\t' << "ƽ���ȴ�ʱ��" << '\t' << "����뿪ʱ��" << endl;
	output_data << customer_list.ave_stay() << "\t\t" << customer_list.ave_wait() << "\t\t";
	customer::time_out(output_data, time + 660);
	output_data << endl;
	return 0;
}