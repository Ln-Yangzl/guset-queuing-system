#include "table_queue.h"

table_queue::table_queue(std::istream& is)
{
	int nums, chairs;
	while (is >> nums >> chairs) {
		t.push_back(table(nums, chairs));
	}
}

int table_queue::top_time()
{
	if (cu.empty()) return INT_MAX;
	return (*cu.begin())->leave;
}

void table_queue::pop()
{
	t[(*cu.begin())->table_number]--;		//对应桌子空位+1
	cu.erase(cu.begin());
}

bool table_queue::empty()
{
	return cu.empty();
}

bool table_queue::full()
{
	bool result = true;
	for (int i = 0; i < t.size(); i++) result &= t[i].full();
	return result;
}

bool table_queue::push(NodePtr c, int time)
{
	int table_num = find_table(c);
	if (table_num == -1) return false;
	t[table_num]++;
	c->table = t[table_num].chairs;
	c->table_number = table_num;
	c->have_eaten = true;
	c->sit = time;
	c->leave = c->sit + c->use;
	cu.push_back(c);
	return true;
}

int table_queue::max_empty_table()
{
	for (int i = t.size() - 1; i >= 0; i--) {
		if (!t[i].full()) return t[i].chairs;
	}
	return 0;
}

int table_queue::find_table(NodePtr c)
{
	int i;
	for (i = 0; i < t.size(); i++) {
		if (t[i].chairs >= c->nums && t[i].occupied != t[i].total) return i;
	}
	return -1;
}

int table::operator--(int)
{
	return occupied--;
}

int table::operator++(int)
{
	return occupied++;
}
