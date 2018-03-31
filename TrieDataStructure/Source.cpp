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

void insertWord(Trie ** trie, char * word, int index)
{
	int length = strlen(word);
	if (index < length)
	{
		if ((*trie)->nextLetter[(int)word[index] - 97] == NULL)
		{
			Trie * node = getTrieNode(word[index]);
			if (index == length - 1)
				node->isEnd = true;
			(*trie)->nextLetter[(int)word[index] - 97] = node;
		}
		else
		{
			((*trie)->nextLetter[(int)word[index] - 97])->no_of_words++;
		}
		index++;
		insertWord(&((*trie)->nextLetter[(int)word[index - 1] - 97]), word, index);
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
	insertWord(&trie, "apple", 0);
	insertWord(&trie, "appy", 0);
	insertWord(&trie, "mango", 0);
	insertWord(&trie, "batman", 0);
	insertWord(&trie, "appy", 0);
	insertWord(&trie, "happy", 0);
	insertWord(&trie, "zebra", 0);
	insertWord(&trie, "akhil", 0);
	printf("Before Deleting\n");
	printTrieWords(&trie, s, 0);
	printf("After Deleting\n");
	deleteWords(&trie, "apple");
	deleteWords(&trie, "mango");
	printTrieWords(&trie, s, 0);
	_getch();
	return 0;
}