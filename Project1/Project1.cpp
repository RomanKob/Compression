#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Node.h"
#include "Compressor.h"
using namespace std;


void CountFreq(FILE* fr, int* freq)
{
    fseek(fr, 0L, SEEK_END);
    long lenght = ftell(fr);
    fseek(fr, 0L, SEEK_SET);
    for (int i = 0; i < lenght; i++)
    {
        freq[(unsigned char)fgetc(fr)]++;
    }
}
void FillList(int* freq, Compressor* comp)
{  
    for (int i = 0; i < 128; i++)
    {
        if (freq[i] != 0)
        {
            Node* node = (Node*)malloc(sizeof(Node));
            node->symb = i;
            node->isSymb = 1;
            node->freq = freq[i];
            comp->AddNode(node);
        }
    }
}

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
            int freq[128] = { 0 };
            CountFreq(fr, freq);
            Compressor comp;
            FillList(freq, &comp);
            comp.print_list();
            comp.BuildTree();
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
