#include <stdio.h>
#include "monty.h"

int main(int argc, char **argv)
{
	unsigned int line_number = 0;
	int i;
	ssize_t len;

	instructions_t instructions[] = {
		{"push", push()},
		{"pall", pall()},
		{NULL, NULL}
	};
	
	if (argc != 2 || argv[1] == NULL)
		printf("Error Commands\n");

	FIlE *file;

	file = fopen(argv[1], "r");/* read monty.m file */
	if (file == NULL)
		printf("Error opening file\n");

	while ((fgets(line, sizeof(len), file) != NULL)) /* Line by line copy into line */
	{
		line_number++;
		line[strlen - 1] = '\0'; /* remove \n from the end of line */

		args = get_tokens(line); /* makes tokens and args array with mallocs */
		for (i = 0; instructions[i].f != NULL; i++)/* iterate srtuct instructions */
		{
			if (strcmp(instructions[i]->opcode, args[0]) == 0) /* find match for operation command */
			{
				instructions[i].f(stack_t **stack,line_number, args); /* call function */
				free_array(args);
			}
		}
	}

	free(line);
	fclose(file);
	return (0);
}
