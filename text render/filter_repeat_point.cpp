#include <vector>
#include <iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
using namespace std;


void filterAdjacentRepeatPoint() {
	int data[] = {1,2,2,3,4,5,6};
	int indices[] = {2, 0, 2, 3, 2, 6};

	vector<int> points;
	vector<int> segmentColors;

	int dataSize = sizeof(data) / sizeof(data[0]);
	int indiceSize = sizeof(indices) / sizeof(indices[0]);

	// �ȷ�ɢ��segmentColors����
	// segmentColors��¼�����߶�֮�����ɫ�����һ��Ԫ��û���塣
	int colorSec = 0;
	for (int cursor = 0; cursor < dataSize; cursor++) {
		int color = indices[colorSec * 3];
		// int begin = mFatColorsCache.get(colorSec * 3 + 1);
		int end = indices[colorSec * 3 + 2];
		if (end == cursor && colorSec < indiceSize / 3 - 1) {
			colorSec++;
			color = indices[colorSec * 3];
		}
		int var = data[cursor];
		if (points.size() == 0 || var != points[points.size() - 1]) {
			points.push_back(var);
			if (cursor == dataSize - 1 || var != data[cursor+1]) {
				segmentColors.push_back(color);	
			}
		}
	}

	// �ۺ�segmentColors���飡
	// ��ı�ԭ����ɫ�������䣬FIXME ����·���θ������β�ƥ�䣡

	vector<int> fatColorsCache;

	int idx = 0;
	while (idx < segmentColors.size()) {
		int color = segmentColors[idx];
		int begin = idx;

		// ��ȡ���һ��Ԫ��
		for (; idx < segmentColors.size() - 1 && color == segmentColors[idx]; idx++)
			;

		fatColorsCache.push_back(color);
		fatColorsCache.push_back(begin);
		fatColorsCache.push_back(idx);

		if (idx == segmentColors.size() - 1) { // ȡ��ĩβ��
			break;
		}
	} // while loop

	// fatColorsCache �д�����ɫ
	// points�д�������
	
	copy(segmentColors.begin(), segmentColors.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	copy(points.begin(), points.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	copy(fatColorsCache.begin(), fatColorsCache.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main()
{	
	filterAdjacentRepeatPoint();

	getchar();

	return 0;
}