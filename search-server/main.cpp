// Решите загадку: Сколько чисел от 1 до 1000 содержат как минимум одну цифру 3?
// Напишите ответ здесь: 300
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int numb = 0;
	char ref = '3';
	for (int i = 0; i < 1000; i++)
	{
		string temp = to_string(i);
		for (char item : temp)
		{
			if (ref == item)
			{
				numb++;
			}
		}
	}
	cout << numb << endl;

	return 0;
}
// Закомитьте изменения и отправьте их в свой репозиторий.