#include <stdio.h>
#include "monty.h"

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
 * free_array - free the args array
 * @args : array from get tokens, tokenization of str_line
 */

void free_array(char **args)
{
	int i = 0;

	for (i = 0; args[i] != NULL; i++) /* free the array & indxs */
		free(args[i]);
	free(args);
}

/**
 * add_dnodeint- Add to the start a Dlinked node
 *
 * @n: int from struct
 * @head: pointer to nodes or null
 * Return: Adress of new node
 */
void push(stack_t **head, unsigned int line_number, char **args)
{
	int copy_n;
	(void)line_number;
	stack_t *new_node;
	if (args[1] == NULL)
		return;
	
	copy_n = atoi(args[1]);
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		printf(" Memory failed to allocate\n");
		return;
	}

	new_node->n = copy_n;
	new_node->next = *head;
	new_node->prev = NULL; /* new node always prev = null */

	if (*head != NULL) /* list not empty, old node must change ->prev */
		(*head)->prev = new_node; /* change prev from old node */

	*head = new_node; /* move head to new node */
	printf("new_node = %d\n", new_node->n);
}

/**
 *free_dlistint- free previous list int
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
