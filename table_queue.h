#pragma once
#ifndef GUARD_table_queue_h
#define GUARD_table_queue_h

#include "customer.h"
#include <istream>
#include <list>
#include <vector>

class table {
	friend class table_queue;
public:
	table() :total(0), occupied(0), chairs(0) {}
	table(int t, int c) :total(t), occupied(0), chairs(c) {}

	bool full() { return total == occupied; }

	int operator--(int);
	int operator++(int);

private:
	int total, chairs, occupied;
	//������������/���������������������������/��ǰ��ʹ�ü�������������
};

class table_queue {
public:
	typedef customer_node Node;
	typedef customer_node* NodePtr;

	table_queue() {}
	table_queue(std::istream& is);

	//���º�����ģ�¶��еĲ�����Ϊ
	int top_time();						//���ض���ָ��λ�ÿ��˵��뿪ʱ��
	void pop();							//ɾ����ͷԪ��
	bool empty();						//�ж��Ƿ��й˿�
	bool full();						//�ж��Ƿ��������Ӷ�������
	bool push(NodePtr c, int time);		//���˽��룬������leaveʱ���,������������������벢����false
	int max_empty_table();				//���ص�ǰ��������λ

private:
	std::list<NodePtr> cu;				//���˶���
	std::vector<table> t;				//�洢table�ڵ㣬��¼���п�����λ��״̬

	int find_table(NodePtr c);			//����������Ѱ�ҷ��������Ĳ�����ţ��Ҳ�������-1
};

#endif // !GUARD_table_queue_h
