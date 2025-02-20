#include "Compressor.h"
#include "Node.h"
#include <iostream>
void Compressor::AddNode(Node* node)
{
    Node** pp = &head;
    while (*pp)
    {
        if (node->freq < (*pp)->freq)
        {
            break;
        }
        else
        {
            pp = &((*pp)->next);
        }
    }
    node->next = *pp;
    *pp = node;
    len++;
}
void Compressor::print_list()
{
    Node* pp = head;
    while (pp)
    {
        std::cout << pp->symb << " ";
        pp = pp->next;
    }
    std::cout << "\n";
}
void Compressor::BuildTree()
{
    while (len > 1)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->isSymb = false;
        node->left = head;
        node->right = head->next;
        node->freq = node->left->freq + node->right->freq;
        AddNode(node);
        head = head->next->next;
        len -= 2;
    }
    if (head->isSymb == true)
    {
        GetCodes(head, "0", 1);
    }
    else
    {
        GetCodes(head, "", 1);
    }   
}
Node* Compressor::FindNode(char value, Node* node)
{
    if (node->isSymb == true && node->symb == value)
    {
        return node;
    }
    if (node->isSymb == true)
    {
        return nullptr;
    }
    Node* new_node = FindNode(value, node->left);
    if (new_node == nullptr)
    {
        new_node = FindNode(value, node->right);
    }
    return new_node;
}
void Compressor::GetOriginalStr(std::string code, int len)
{
    auto fw = fopen("InputFromOutput", "w");
    std::string temp = "";
    for (int i = 0; i < len; i++)
    {
        temp += code[i];
        unsigned char ch = FindSymbol(temp, head);
        if (ch != 0)
        {
            fputc(ch, fw);
            temp = "";
        }
    }
    fclose(fw);
}
char Compressor::FindSymbol(std::string code, Node* node)
{
    if (node->isSymb == true)
    {
        if (code.compare(node->code) == 0)
        {
            return node->symb;
        }
        return 0;
    }
    if (node->level > code.length())
    {
        return 0;
    }
    char symb = FindSymbol(code, node->left);
    if (symb == 0)
    {
        symb = FindSymbol(code, node->right);
    }
    return symb;
}
Compressor::Compressor()
{
    head = 0;
    len = 0;
}

void Compressor::GetCodes(Node* node, std::string code, int level)
{
    node->level = level;
    if (node->isSymb == true)
    {
        int k = 0;
        while (code[k])
        {
            node->code[k] = code[k];
            k++;
        }
        node->code[k] = '\0';
        return;
    }
    GetCodes(node->left, code + "0", level + 1);
    GetCodes(node->right, code + "1", level + 1);
}
