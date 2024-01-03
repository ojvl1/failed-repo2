#include <stdio.h>
#include "monty.h"

int main(int argc, char **argv)
{
	unsigned int line_number = 0;
	char *line = NULL, **args;
	size_t len = 0;

	if (argc != 2 || argv[1] == NULL)
	{
		printf("Error Commands\n");
		return (-1);
	}

	FILE *file;

	file = fopen(argv[1], "r");/* read monty.m file */
	if (file == NULL)
	{
		printf("Error opening file\n");
		return (-1);
	}

	while ((getline(&line, &len, file) != EOF)) /* Line by line copy into line */
	{
		line_number++;
		line[strlen(line) - 1] = '\0'; /* remove \n from the end of line */
		args = get_tokens(line); /* makes tokens and args array with mallocs */
		printf("line_number #%d: %s %s\n", line_number, args[0], args[1]);
		free_array(args);
	}

	free(line);
	fclose(file);
	return (0);
}
