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
	//该类桌子总数/该类桌子最大容纳数（几人桌）/当前已使用几张这样的桌子
};

class table_queue {
public:
	typedef customer_node Node;
	typedef customer_node* NodePtr;

	table_queue() {}
	table_queue(std::istream& is);

	//以下函数是模仿队列的操作行为
	int top_time();						//返回队首指向位置客人的离开时刻
	void pop();							//删除表头元素
	bool empty();						//判断是否还有顾客
	bool full();						//判断是否所有桌子都已坐满
	bool push(NodePtr c, int time);		//客人进入，并计算leave时间戳,若桌子已满，不会进入并返回false
	int max_empty_table();				//返回当前最大空闲桌位

private:
	std::list<NodePtr> cu;				//客人队列
	std::vector<table> t;				//存储table节点，记录所有可用桌位的状态

	int find_table(NodePtr c);			//根据人数，寻找符合条件的餐桌编号，找不到返回-1
};

#endif // !GUARD_table_queue_h
