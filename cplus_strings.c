#include <stdio>
#include <string>
#include <stdlib>

/*
* char *substr(char *s, int start, int length)
* extrai uma substring de uma string
* retorna um ponteiro char para a substring
*
*/
char *substr(char *s, int start, int length)
{
	char *_substr;

	//aloca memoria para a substring
	_substr = (char *) malloc((length+1) * sizeof(char));

	//copia a substring para a variavel
	strncpy(_substr, s+start, length * sizeof(char));

	//finaliza a string com o caracter nulo
	_substr[length] = '\0';

	return _substr;
}

/*
* char **split(char *s, char c)
* transforma uma string em um array baseado em caracteres separadores
* retorna um array char
*
*/
char **split(char *s, char *delimiter)
{
	char **token_array;
	char *current;
	char *previous = NULL;
	char *_substr;
	int length;
	int length_substr;
	int delimiters_found = 0;
	int offset = 0;
	int tokens;

	length = (int)strlen(s);

	//conta as ocorrencias de caracteres separadores
	do
	{
		current = strstr(s+offset, delimiter);
		if (current != NULL)
		{
			offset = (current - s) + 1;
			delimiters_found++;
		}

	} while(current != NULL);

	tokens = delimiters_found+1;
	//aloca memoria para a o array de tokens (substrings)
	token_array = (char **)malloc(tokens * sizeof(char *));

	offset = 0;

	for (int i = 0; i < tokens; ++i)
	{
		//aponta para o caracter encontrado
		current = strstr(s+offset, delimiter);

		//calcula o tamanho da string que está entre os caracteres de separação
		length_substr = (current != NULL) ? current - ((previous != NULL) ? previous+1 : s) : s+length - previous-1;

		token_array[i] = substr(s, offset, length_substr);

		offset = (current != NULL) ? current - s + 1: 0;

		previous = current;
	}

	return token_array;
}

/*
*
* Teste das funções de string
*
*/
void main() {
	char *msg;
	char **arr;

	msg = "DEVICE 0|W|abcdefghijklmnh|FFF321";

	arr = split(msg, "|");

	printf("token %s\n", arr[0]);
	printf("token %s\n", arr[1]);
	printf("token %s\n", arr[2]);
	printf("token %s\n", arr[3]);
};