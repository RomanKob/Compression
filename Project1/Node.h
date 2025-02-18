#pragma once
struct Node {
	char symb;
	bool isSymb;
	int freq;
	int level;
	char code[256];
	struct Node* next;
	struct Node* right;
	struct Node* left;
};
