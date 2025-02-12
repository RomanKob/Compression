#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

int main()
{
	while (true)
	{
        cout << "Select option for Input file:\n1-Compression\n2-Decompression\n3-Exit" << endl;
        string answer;
        cin >> answer;
        if (answer == "1")
        {
            auto fr = fopen("Input", "rb");
            fseek(fr, 0L, SEEK_END);
            long lenght = ftell(fr);
            fseek(fr, 0L, SEEK_SET);
            cout << lenght << endl;
            int freq[128] = { 0 };
            for (int i = 0; i < lenght; i++)
            {
                freq[(unsigned char)fgetc(fr)]++;
            }
            fclose(fr);
        }
        if (answer == "2")
        {

        }
        if (answer == "3")
        {
            break;
        }
	}

}
