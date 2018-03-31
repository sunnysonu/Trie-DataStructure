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

typedef struct List
{
	char word[100];
	struct List * next;
}List;

List * createNode(char * word)
{
	List * node = (List *)calloc(1, sizeof(List));
	strcpy_s(node->word, word);
	return node;
}

void addWordToList(List ** list, char * word)
{
	List *temp;
	if (*list == NULL)
	{
		*list = createNode(word);
	}
	else
	{
		for (temp = *list; temp->next != NULL; temp = temp->next);
		temp->next = createNode(word);
	}
}

void printWords(List * list)
{
	for (List * temp = list; temp != NULL; temp = temp->next)
	{
		printf("%s\n", temp->word);
	}
}

void addStartingWord(List ** list, char * word)
{
	List * temp;
	for (temp = *list; temp != NULL; temp = temp->next)
	{
		char temp_word[100];
		strcpy(temp_word, word);
		strcat(temp_word, temp->word);
		strcpy_s(temp->word, temp_word);
	}
}

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

void getTrieWords(Trie ** trie, char * word, int index, List ** list)
{
	for (int i = 0; i < 26; i++)
	{
		if ((*trie)->nextLetter[i] != NULL)
		{
			word[index] = ((*trie)->nextLetter[i])->letter;
			if (((*trie)->nextLetter[i])->isEnd)
			{
				word[index + 1] = '\0';
				addWordToList(list, word);
			}
			getTrieWords(&((*trie)->nextLetter[i]), word, index + 1, list);
		}
	}
}

void deleteWord(Trie **trie, char * word)
{
	if (*(word) != '\0')
	{
		int index = (int)(*word) - 97;
		deleteWord(&((*trie)->nextLetter[index]), word + 1);
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

bool isWordPresent(Trie ** trie, char * word)
{
	if (*word != '\0')
	{
		int index = (int)(*word) - 97;
		if ((*trie)->nextLetter[index] != NULL)
		{
			return isWordPresent(&((*trie)->nextLetter[index]), word + 1);
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ((*trie)->isEnd)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool isSubWordPresent(Trie ** trie, char * word)
{
	if (*word != '\0')
	{
		int index = (int)(*word) - 97;
		if ((*trie)->nextLetter[index] != NULL)
		{
			return isSubWordPresent(&((*trie)->nextLetter[index]), word + 1);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

void Insert(Trie ** trie, char * word)
{
	if (!isWordPresent(trie, word))
	{
		insertWord(trie, word);
	}
}

void Delete(Trie ** trie, char * word)
{
	if (isWordPresent(trie, word))
	{
		deleteWord(trie, word);
	}
}

void wordStartsWithHelper(Trie ** trie, char * word, List ** list)
{
	if (*word != '\0')
	{
		wordStartsWithHelper(&((*trie)->nextLetter[(int)(*word) - 97]), word + 1, list);
	}
	else
	{
		char s[10];
		getTrieWords(trie, s, 0, list);
	}
}

List * wordStartsWith(Trie ** trie, char * word)
{
	List * list = NULL;
	if (isSubWordPresent(trie, word))
	{
		wordStartsWithHelper(trie, word, &list);
		addStartingWord(&list, word);
	}
	return list;
}

List * allWordsInTrie(Trie ** trie)
{
	List * list = NULL;
	wordStartsWithHelper(trie, "", &list);
	return list;
}

int main()
{
	char s[100];
	Trie * trie = getTrieNode(NULL);
	Insert(&trie, "akhil");
	Insert(&trie, "akhil");
	Insert(&trie, "akil");
	Insert(&trie, "akhilesh");
	Insert(&trie, "akhila");
	Insert(&trie, "sonu");
	Insert(&trie, "ironman");
	Insert(&trie, "thanos");
	List * list = NULL;
	List * words = wordStartsWith(&trie, "");
	printWords(words);
	_getch();
	return 0;
}