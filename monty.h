#ifndef MONTY_H
#define MONTY_H
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
int n;
struct stack_s *prev;
struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
char *opcode;
void (*f)(stack_t **stack, unsigned int line_number, char **args, char *line, FILE *file);
} instruction_t;

void clean_up(char *line, stack_t **stack, FILE *file);
char **get_tokens(char *str_line);
void free_array(char **args);
void push(stack_t **stack, unsigned int line_number, char **args, char *line, FILE *file);
void pall(stack_t **stack, unsigned int line_number, char **args, char *line, FILE *file);
void free_dlist(stack_t **head);
#endif /* MONTY_H */
