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
    GetCodes(head, "");

}
Compressor::Compressor()
{
    head = 0;
    len = 0;
}

void Compressor::GetCodes(Node* node, std::string code)
{
    if (node->isSymb == true)
    {
        int k = 0;
        while (code[k])
        {
            node->code[k] = code[k];
            k++;
        }
        return;
    }
    GetCodes(node->left, code + "0");
    GetCodes(node->right, code + "1");
}
