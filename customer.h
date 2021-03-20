#pragma once

#ifndef GUARD_customer_h
#define GUARD_customer_h

#include "top_head.h"
#include <list>
#include <iostream>

class customer_node {
	friend class customer;
	friend class waiting_queue;
	friend class table_queue;

public:
	customer_node() :nums(0), arrive(0), sit(0), leave(0), table(0), use(0), table_number(0), have_eaten(false){}
	customer_node(int num, int arr, int time_use) :nums(num), arrive(arr), use(time_use), sit(0), leave(0), table(0), table_number(0), have_eaten(false) {}

	int arrive_time() const { return arrive; }
	int leave_time() const { return leave; }
	int customer_nums() const { return nums; }
private:
	int nums, arrive, sit, use, leave, table, table_number;
	//�˿�����/����ʱ��/����ʱ��/�Ͳ���ʱ/���ʱ��/ʹ����λ/��λ���
	bool have_eaten;
};


class customer {
public:
	typedef customer_node Node;
	typedef customer_node* NodePtr;

	customer();
	customer(std::istream& is);
	~customer();

	void put_all(std::ostream& os);			//�Ʊ����
	double ave_stay();						//ƽ��ͣ��ʱ��
	double ave_wait();						//ƽ����λʱ��

	//���º�����ģ�¶��еĲ�����Ϊ
	NodePtr top();						//����itָ��ڵ�ĵ�ַ
	NodePtr fewer(int num);				//���ر�ָ������(��ǰ��������λ��)��Ȼ����һ��Ĺ˿���
	int top_time();						//����itָ��λ�ÿ��˵ĵ���ʱ��
	void pop();							//��it����������ƶ�
	bool empty();						//�ж�it�������Ƿ��Ѿ�ָ��ĩβ
	void reset();						//��it���õ�������λ == ���ģ�����

	static void time_out(std::ostream& os, int time);	//����ʱ���ʽ������ĺ���
private:
	std::list<NodePtr>::iterator it;	//it����������ģ����в���
	std::list<NodePtr> cus;				//���˶���

	static bool compare(const NodePtr x, const NodePtr y);
	
};

#endif // !GUARD_customer_h