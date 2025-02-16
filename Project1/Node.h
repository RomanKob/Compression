#pragma once
struct Node {
	char symb;
	bool isSymb;
	int freq;
	char code[128];
	struct Node* next;
	struct Node* right;
	struct Node* left;
};
