#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <cwchar>

int main(int argc, char * argv[])
{
	wchar_t wstr[] = L"����";    
	setlocale(LC_ALL, "zh_CN.UTF-8");        
	
	short word = 21271;
	char low = word;
	char high = (word>>8);

	short newWord = low + (high<<8);
	
	char* word_str = (char*)(&word);	// ������CPU�ֽ�˳��

	getchar();

	return 0;
}