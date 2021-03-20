#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using std::ostream;		using std::vector;
using std::endl;
using std::random_shuffle;

void rand_data(ostream& os) {
	srand(time(0));
	vector<int> rand_time(480);
	vector<int> people(5);
	for (int i = 0; i < 5; i++) people[i] = i + 1;
	for (int i = 0; i < 480; i++) rand_time[i] = i;
	//reference:https://www.cnblogs.com/salan668/p/3652532.html �������ظ��������
	random_shuffle(rand_time.begin(), rand_time.end());

	int total = rand() % 25 + 75;		//���ѡ������75��ʱ���
	//ÿ��ʱ����������1-3��˿ͣ�ÿ��˿����1-5��
	for (int i = 0; i < total; i++) {
		int count = rand() % 3 + 1;
		random_shuffle(people.begin(), people.end());
		for (int j = 0; j < count; j++) {
			os << people[j] << '\t' << rand_time[i] << '\t' << rand() % 25 + 5 << endl;
		}
	}
}