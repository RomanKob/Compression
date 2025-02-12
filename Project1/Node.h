#pragma once
struct Node
{
	char symb;
	bool isSymb;
	int freq;
	int level;
	struct Node* next;
	struct Node* right;
	struct Node* left;
};
