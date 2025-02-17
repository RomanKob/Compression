#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Node.h"
#include "Compressor.h"
#include "bit2char.h"
#include <limits.h>
#include <vector>
#include <bitset>
using namespace std;


void CountFreq(FILE* fr, int* freq, string &text)
{
    fseek(fr, 0L, SEEK_END);
    long lenght = ftell(fr);
    fseek(fr, 0L, SEEK_SET);
    for (int i = 0; i < lenght; i++)
    {
        char ch = fgetc(fr);
        text += ch;
        freq[(unsigned char)ch]++;
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
void BuildBinaryText(string source, string &target, Compressor comp)
{
    int k = 0;
    while (source[k])
    {
        string str = (comp.FindNode(source[k], comp.GetHead()))->code;
        target += str;
        k++;
    }
}
vector<uint8_t> getBitString(const string& encodedString) {
    vector<uint8_t> bitString;
    uint8_t currentByte = 0;
    int bitCount = 0;
    for (char bit : encodedString) {
        currentByte = (currentByte << 1) | (bit - '0'); 
        bitCount++;
        
        if (bitCount == 8) {
            bitString.push_back(currentByte);
            currentByte = 0; 
            bitCount = 0; 
        }
    }

    if (bitCount > 0) {
        currentByte <<= (8 - bitCount); 
        bitString.push_back(currentByte);
    }

    return bitString;
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
            string text = "";
            int freq[256] = { 0 };
            CountFreq(fr, freq, text);
            Compressor comp;
            FillList(freq, &comp);
            comp.print_list();
            comp.BuildTree();
            string new_text = "";
            BuildBinaryText(text, new_text, comp);
            vector<uint8_t> bitString = getBitString(new_text);
            auto fw = fopen("Output", "wb");
            fwrite(bitString.data(), sizeof(uint8_t), bitString.size(), fw);
            fclose(fw);
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
