#pragma once
#include "Node.h"
#include <iostream>
class Compressor
{
public:
	void AddNode(Node* node);
	void print_list();
	void BuildTree();
	Node* GetHead() { return head; };
	Node* FindNode(char value, Node* node);
	void GetOriginalStr(std::string code, int len);
	Compressor();
private:
	void GetCodes(Node* node, std::string code, int level);
	char FindSymbol(std::string code, Node* node);
	Node* head;
	int len;
};

