#include "customer.h"
#include <algorithm>
#include <iomanip>

using std::list;	using std::setw;
using std::setfill;

customer::customer()
{
	it = cus.begin();
}

customer::customer(std::istream& is)
{
	int num, arrive, time_use;
	while (is >> num >> arrive >> time_use) {
		NodePtr temp = new Node(num, arrive, time_use);
		cus.push_back(temp);
	}
	cus.sort(compare);
	reset();
}

customer::~customer()
{
	for (list<NodePtr>::iterator it = cus.begin(); it != cus.end(); it++) delete* it;
}

void customer::put_all(std::ostream& os)
{
	os << "���\t�˿�����\t����ʱ��\t�ȴ���ʱ\t�Ͳ�����\t�Ͳ�ʱ��\t�Ͳ���ʱ\t�뿪ʱ��\n";
	int i = 1;
	for (list<NodePtr>::iterator it = cus.begin(); it != cus.end(); it++, i++) {
		os << setfill('0') << setw(3) << i << '\t' << "   " << (*it)->nums << "\t\t";
		time_out(os, (*it)->arrive + 660);
		os << "\t\t";
		time_out(os, (*it)->sit - (*it)->arrive);
		os << "\t\t";
		os << (*it)->table << "����";
		os << "\t\t";
		time_out(os, (*it)->sit + 660);
		os << "\t\t";
		time_out(os, (*it)->use);
		os << "\t\t";
		time_out(os, (*it)->leave + 660);
		os << '\n';
	}
}

double customer::ave_stay()
{
	int stay = 0;
	for (list<NodePtr>::iterator begin = cus.begin(); begin != cus.end(); begin++) {
		stay += ((*begin)->leave - (*begin)->arrive);
	}
	return (double)stay / (double)cus.size();
}

double customer::ave_wait()
{
	int wait = 0;
	for (list<NodePtr>::iterator begin = cus.begin(); begin != cus.end(); begin++) {
		wait += ((*begin)->sit - (*begin)->arrive);
	}
	return (double)wait / (double)cus.size();
	return 0;
}

customer::NodePtr customer::top()
{
	if (cus.empty()) return NULL;
	return *it;
}

customer::NodePtr customer::fewer(int num)
{
	list<NodePtr>::iterator current = it;
	while (current != cus.end() && ((*current)->nums > num || (*current)->have_eaten)) current++;		//��ǰ���Ƕ�β�ҵ�ǰ�˿�������������ߵ�ǰ�˿����ѾͲͣ������������
	if (current == cus.end()) return NULL;
	return *current;
}

int customer::top_time()
{
	if (empty()) return INT_MAX;
	return (*it)->arrive;
}

void customer::pop()
{
	while (it != cus.end() && (*it)->have_eaten) it++;
}

bool customer::empty()
{
	return it == cus.end();
}

void customer::reset()
{
	it = cus.begin();
}

bool customer::compare(const NodePtr x, const NodePtr y)
{
	return (x->arrive < y->arrive) || (x->arrive == y->arrive && x->nums < y->nums);
}

void customer::time_out(std::ostream& os, int time)
{
	os << (time / 60) % 24 << ':' << setfill('0') << setw(2) << time % 60;
}
