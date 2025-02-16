#pragma once
#include "Node.h"
#include <iostream>
class Compressor
{
public:
	void AddNode(Node* node);
	void print_list();
	void BuildTree();
	Compressor();
private:
	void GetCodes(Node* node, std::string code);
	Node* head;
	int len;
};

