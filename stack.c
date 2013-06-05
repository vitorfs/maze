/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  Stack implementation
 *
 *        Version:  1.0
 *        Created:  05/06/2013 14:05:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vitor Freitas (vfs), vitorfs@gmail.com
 *        Company:  Universidade Federal de Juiz de Fora (UFJF)
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void init_stack(Stack* stack) {
  stack->last = -1;
  stack->values = NULL;
}

void push(Stack* stack, int value) {
  stack->last++;
  if (stack->values == NULL)
    stack->values = (int*) malloc(sizeof(int));
  else
    stack->values = (int*) realloc(stack->values, (stack->last + 1) * sizeof(int));
  stack->values[stack->last] = value;
}

int pop(Stack* stack) {
  int value = -1;

  if (stack->last > -1) {
    value = stack->values[stack->last];
    stack->last--;
    if (stack->last == -1) {
      free(stack->values);
      stack->values = NULL;
    }
    else
      stack->values = (int*) realloc(stack->values, (stack->last + 1) * sizeof(int));
  }

  return value;
}

void print_stack(Stack* stack) {
  int i;
  for (i = 0 ; i <= stack->last ; i++) {
    printf("[%d]", stack->values[i]);
    if (stack->last != i) printf("->");
  }
  printf("\nSize: %d\n", stack->last);
}

int empty_stack(Stack* stack) {
  if (stack->last == -1) {
    return 1;
  }
  else {
    return 0;
  }
}
