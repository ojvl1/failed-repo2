#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

void clean_up(char *line, stack_t **stack, FILE *file)
{
	free(line);
	free_dlist(stack);
	free(stack);
	fclose(file);
}

int main(int argc, char **argv)
{
	unsigned int line_number = 0;
	char *line = NULL, **args;
	size_t len = 0, i;
	stack_t **stack;

	instruction_t instructions[] = {
		{"push", push},
		{NULL, NULL}
	};


	if (argc != 2 || argv[1] == NULL)
	{
		printf("USAGE: monty bytecodes/001.m\n");
		exit(EXIT_FAILURE);
	}

	FILE *file;
	stack = malloc(sizeof(stack_t *));
	*stack = NULL;

	file = fopen(argv[1], "r");/* read monty.m file */
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file <%s>\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((getline(&line, &len, file) != EOF)) /* Line by line copy into line */
	{
		line_number++;
		line[strlen(line) - 1] = '\0'; /* remove \n from the end of line */
		args = get_tokens(line); /* makes tokens and args array with mallocs */
		for (i = 0; instructions[i].f != NULL; i++) /*Still have functions to call*/
		{
			if (strcmp(instructions[i].opcode, args[0]) == 0) /* Matched a case */
			{
				printf("Matched line %d\n", line_number);
				instructions[i].f(stack, line_number, args);
				break;
			}
		}
		if (instructions[i].f == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, args[0]);
			free_array(args);
			clean_up(line, stack, file);
			exit(EXIT_FAILURE);
		}
		free_array(args);
	}
	clean_up(line, stack, file);
	return (0);
}
