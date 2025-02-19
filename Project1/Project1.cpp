#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Node.h"
#include "Compressor.h"
#include <limits.h>
#include <vector>
#include <bitset>
using namespace std;


long CountFreq(FILE* fr, int* freq)
{
    fseek(fr, 0L, SEEK_END);
    long lenght = ftell(fr);
    fseek(fr, 0L, SEEK_SET);
    for (int i = 0; i < lenght; i++)
    {
        unsigned char ch = fgetc(fr);
        freq[(unsigned char)ch]++;
    }
    return lenght;
}
void WriteOriginalStr(vector<uint8_t> bitstring, Compressor comp, int len, string filename)
{
    auto fw = fopen(("InputFromOutput" + filename.substr(filename.find_last_of('.'))).c_str(), "wb");
    Node* current_node = comp.GetHead();
    int k = 0;
    for (uint8_t byte : bitstring)
    {
        for (int i = 7; i >= 0; i--)
        {
            k++;
            if (k > len)
            {
                break;
            }
            bool bit = (byte >> i) & 1;
            if (bit == 0)
            {
                current_node = current_node->left;
            }
            else
            {
                current_node = current_node->right;
            }
            if (current_node->isSymb == true)
            {
                fputc(current_node->symb, fw);
                current_node = comp.GetHead();
            }
        }
    }
    fclose(fw);
}
void FillList(int* freq, Compressor* comp)
{  
    for (int i = 0; i < 256; i++)
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
string BuildBinaryText(FILE* fr, Compressor comp, int len)
{
    string result;
    fseek(fr, 0L, SEEK_SET);
    int k = 0;
    for (int i = 0; i < len; i++)
    {
        string str = (comp.FindNode(fgetc(fr), comp.GetHead()))->code;
        result += str;
    }
    return result;
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
string ReadFileName()
{
    string filename = "";
    while (true)
    {
        cout << "Write filename with extension: " << endl;
        cin >> filename;
        if (fopen(filename.c_str(), "rb"))
        {
            auto fr = fopen(filename.c_str(), "rb");
            fclose(fr);
            break;
        }
        else
        {
            cout << "Unknown filename!" << endl;
        }
    }
    return filename;
}
int main()
{
    string filename = ReadFileName();
    Compressor comp;
    long length_orig_str = 0;
    int len = 0;
    int amountBytes = 0;
	while (true)
	{
        cout << "Select option for " << filename <<":\n1 - Compression\n2 - Decompression\n3 - Exit" << endl;
        string answer;
        cin >> answer;   
        if (answer == "1")
        {
            auto fr = fopen(filename.c_str(), "rb");
            int freq[256] = { 0 };
            length_orig_str = CountFreq(fr, freq);
            FillList(freq, &comp);
            comp.BuildTree();
            string new_text = BuildBinaryText(fr, comp, length_orig_str);
            len = new_text.length();
            vector<uint8_t> bitString = getBitString(new_text);
            amountBytes = bitString.size();
            auto fw = fopen("Output", "wb");
            fwrite(bitString.data(), sizeof(uint8_t), bitString.size(), fw);
            fclose(fw);
            fclose(fr);
        }
        if (answer == "2")
        {
            auto fr = fopen("Output", "rb");
            string bitstring;
            int bytesRead = 0;
            for (size_t i = 0; i < amountBytes; i++)
            {
                bitstring += fgetc(fr);
            }
            string binaryText;
            int k = 0;
            for (size_t i = 0; i < amountBytes; i++)
            {
                binaryText += bitset<8>(bitstring[i]).to_string();
            }
            WriteOriginalStr(getBitString(binaryText), comp, len, filename);
            fclose(fr);
        }
        if (answer == "3")
        {
            break;
        }
	}

}
