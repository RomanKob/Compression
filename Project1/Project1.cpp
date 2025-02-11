#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main()
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
