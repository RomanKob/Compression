#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

void AddNode(Node** head, char value, int fr)
{
    Node* pnew;
    Node** pp = head;
    while (*pp)
    {
        if (fr < (*pp)->freq)
        {
            break;
        }
        else
        {
            pp = &((*pp)->next);
        }
    }
    pnew = (Node*)malloc(sizeof(Node));
    pnew->freq = fr;
    pnew->next = *pp;
    pnew->symb = value;
    *pp = pnew;
}
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
void FillList(int* freq, Node** head)
{  
    for (int i = 0; i < 128; i++)
    {
        if (freq[i] != 0)
        {
            AddNode(head, (char)i, freq[i]);
        }
    }
}
void Print(Node* head)
{
    Node* p = head;
    while (p)
    {
        cout << p->symb << " ";
        p = p->next;
    }
    cout << "\n";
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
            Node* head = 0;
            CountFreq(fr, freq);
            FillList(freq, &head);
            Print(head);
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
