#include <stdio.h>
#include "monty.h"

/**
 * push - Add node to the start of stack double list
 *
 * @stack: head of stack_t list
 * @line_number: number of line from file
 * @args: arguments of get_tokens
 * @line: line from fgets from file
 * @file: monty.m file
 */

void push(stack_t **stack, unsigned int line_number, char **args, char *line, FILE *file)
{
	int copy_n, i;
	stack_t *new_node;

	if (args[1] == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		clean_up(line, stack, file);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	for (i = 0; args[1][i]; i++)
	{
		if (!isdigit(args[1][i]))
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			clean_up(line, stack, file);
			free_array(args);
			exit(EXIT_FAILURE);
		}
	}

	copy_n = atoi(args[1]);
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		clean_up(line, stack, file);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	new_node->n = copy_n;
	new_node->next = *stack;
	new_node->prev = NULL; /* new node always prev = null */
	if (*stack != NULL) /* list not empty, old node must change ->prev */
		(*stack)->prev = new_node; /* change prev from old node */
	*stack = new_node; /* move head to new node */
}

/**
 * pall - Print all nodes of stack
 *
 * @stack: head of stack_t list
 * @line_number: number of line from file
 * @args: arguments of get_tokens
 * @line: line from fgets from file
 * @file: monty.m file
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
