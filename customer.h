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
	//顾客人数/到达时间/就坐时间/就餐用时/离店时间/使用桌位/桌位编号
	bool have_eaten;
};


class customer {
public:
	typedef customer_node Node;
	typedef customer_node* NodePtr;

	customer();
	customer(std::istream& is);
	~customer();

	void put_all(std::ostream& os);			//制表输出
	double ave_stay();						//平均停留时间
	double ave_wait();						//平均等位时间

	//以下函数是模仿队列的操作行为
	NodePtr top();						//返回it指向节点的地址
	NodePtr fewer(int num);				//返回比指定人数(当前最大空闲桌位数)相等或更少一点的顾客组
	int top_time();						//返回it指向位置客人的到来时刻
	void pop();							//将it迭代器向后移动
	bool empty();						//判断it迭代器是否已经指向末尾
	void reset();						//将it重置到链表首位 == 清空模拟队列

	static void time_out(std::ostream& os, int time);	//用于时间格式化输出的函数
private:
	std::list<NodePtr>::iterator it;	//it迭代器用来模拟队列操作
	std::list<NodePtr> cus;				//客人队列

	static bool compare(const NodePtr x, const NodePtr y);
	
};

#endif // !GUARD_customer_h