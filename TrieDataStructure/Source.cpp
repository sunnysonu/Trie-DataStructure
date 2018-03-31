#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Trie
{
	char letter;
	struct Trie * nextLetter[26];
	int no_of_words;
	bool isEnd = false;
} Trie;

Trie * getTrieNode(char letter)
{
	Trie * trie = (Trie *)calloc(1, sizeof(Trie));
	trie->letter = letter;
	trie->no_of_words = 1;
	return trie;
}

void insertWord(Trie ** trie, char * word)
{
	if (*word != '\0')
	{
		int index = (int)(*word) - 97;
		if ((*trie)->nextLetter[index] == NULL)
		{
			Trie * node = getTrieNode(*word);
			if (*(word + 1) == '\0')
				node->isEnd = true;
			(*trie)->nextLetter[index] = node;
		}
		else
		{
			((*trie)->nextLetter[index])->no_of_words++;
		}
		insertWord(&((*trie)->nextLetter[index]), word + 1);
	}
}

void printTrieWords(Trie ** trie, char * word, int index)
{
	for (int i = 0; i < 26; i++)
	{
		if ((*trie)->nextLetter[i] != NULL)
		{
			word[index] = ((*trie)->nextLetter[i])->letter;
			if (((*trie)->nextLetter[i])->isEnd)
			{
				word[index + 1] = '\0';
				printf("%s\n", word);
			}
			printTrieWords(&((*trie)->nextLetter[i]), word, index + 1);
		}
	}
}

void deleteWords(Trie **trie, char * word)
{
	if (*(word) != '\0')
	{
		int index = (int)(*word) - 97;
		deleteWords(&((*trie)->nextLetter[index]), word + 1);
		index = (int)(*(word)) - 97;
		((*trie)->nextLetter[index]->no_of_words)--;
		if ((*trie)->nextLetter[index]->no_of_words == 0)
		{
			Trie *temp = (*trie)->nextLetter[index];
			(*trie)->nextLetter[index] = NULL;
			free(temp);
		}
	}
}

int main()
{
	//char word[10] = "apple";
	char s[100] = "appy";
	Trie * trie = getTrieNode(NULL);
	insertWord(&trie, "apple");
	insertWord(&trie, "appy");
	insertWord(&trie, "mango");
	insertWord(&trie, "batman");
	insertWord(&trie, "happy");
	insertWord(&trie, "zebra");
	insertWord(&trie, "akhil");
	deleteWords(&trie, "akhil");
	printTrieWords(&trie, s, 0);
	_getch();
	return 0;
}