#include <stdio.h>
#include "monty.h"
#include <ctype.h>
/**
 * pint - function that print the value at the top of stack
 * @stack: double pointer to head of the stack
 * @line_number: the number of the line in file
 *
 * Return: void
 *
 */
void pint(stack_t **stack, unsigned int line_number)
{
        if (*stack == NULL || stack == NULL)
        {
                printf("L%u: can't pint, stack empty\n", line_number);
                exit(EXIT_FAILURE);
        }
        printf("%d\n", (*stack)->n);
}

/**
 *pall - function that prints the stack
 *@stack: stack structure
 *@line_number: number of instruction
 */

void pall(stack_t **stack, unsigned int line_number, char **args, char *line, FILE *file)
{
	(void)line_number;
	(void)args;
	(void)line;
	(void)file;

	stack_t *temp = NULL;
	int n = 0;

	if (*stack == NULL)
		return;

	temp = *stack;

	while (temp)
	{
		n = temp->n;
		printf("%d\n", n);
		temp = temp->next;
	}
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
void push(stack_t **stack, unsigned int line_number, char **args, char *line, FILE *file)
{
	int copy_n, i;
	stack_t *new_node;
	if (args[1] == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free(line);
		fclose(file);
		if (*stack != NULL)
			free_dlist(stack);
		free(stack);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	for (i = 0; args[1][i]; i++)
	{
		if (!isdigit(args[1][i]))
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			free(line);
			fclose(file);
			if (*stack != NULL) /* in case of empty dlist */
				free_dlist(stack);
			free(stack);
			free_array(args);
			exit(EXIT_FAILURE);
		}
	}

	copy_n = atoi(args[1]);
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(line);
		fclose(file);
		if (*stack != NULL) /* in case of empty dlist */
			free_dlist(stack);
		free(stack);
		free_array(args);
		exit(EXIT_FAILURE);
		return;
	}

	new_node->n = copy_n;
	new_node->next = *stack;
	new_node->prev = NULL; /* new node always prev = null */

	if (*stack != NULL) /* list not empty, old node must change ->prev */
		(*stack)->prev = new_node; /* change prev from old node */

	*stack = new_node; /* move head to new node */
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
