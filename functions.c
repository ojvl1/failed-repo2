#include <stdio.h>
#include "monty.h"


/**
 * clean_up - free and close items used
 * @line: line from getline file
 * @stack: head of stack_t
 * @file: monty.m file
 */

void clean_up(char *line, stack_t **stack, FILE *file)
{
	free(line);
	if (*stack != NULL)
		free_dlist(stack);
	free(stack);
	fclose(file);
}

/**
 * get_tokens - tokenizes str_line, stores it in array
 * @str_line: string from main, from stdin
 * Return: pointer of array
 */

char **get_tokens(char *str_line)
{
	char **array;
	int tok_count = 0;
	char *token, *str_line_dup;

	str_line_dup = strdup(str_line);/* we need dup to count tokens */
	token = strtok(str_line_dup, " ");

	while (token != NULL)
	{
		tok_count++;
		token = strtok(NULL, " "); /* next token */
	}

	free(str_line_dup);
	array = malloc((tok_count + 1) * sizeof(char *));/* making size for indexes */

	if (array == NULL)
		return (NULL);

	token = strtok(str_line, " "); /* original str to tokenize */
	tok_count = 0;

	while (token != NULL)
	{
		array[tok_count] = strdup(token); /* dup tokens into args,does malloc also*/
		tok_count++;
		token = strtok(NULL, " "); /* next token */
	}
	array[tok_count] = NULL;/* last index of args */
	return (array); /* sending array, args in main receives it */
}

/**
 * free_array - free **array
 * @args: array char **
 */

void free_array(char **args)
{
	int i = 0;

	for (i = 0; args[i] != NULL; i++) /* free the array & indxs */
		free(args[i]);
	free(args);
}

/**
 * free_dlist- free previous list int
 *
 *@head: head pointer of nodes
 */

void free_dlist(stack_t **head)
{

	stack_t *temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
