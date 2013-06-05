/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  Stack definitions
 *
 *        Version:  1.0
 *        Created:  05/06/2013 14:04:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vitor Freitas (vfs), vitorfs@gmail.com
 *        Company:  Universidade Federal de Juiz de Fora (UFJF)
 *
 * =====================================================================================
 */

#ifndef STACK_H
#define STACK_H
typedef struct {
  int last;
  int* values;
} Stack;

void init_stack(Stack* stack);
int empty_stack(Stack* stack);
void push(Stack* stack, int value);
int pop(Stack* stack);
void print_stack(Stack* stack);
#endif
