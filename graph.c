/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  Implementation of the graph structure that will be used to solve
 *                  the maze search problem
 *
 *        Version:  1.0
 *        Created:  04/06/2013 23:51:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vitor Freitas (vfs), vitorfs@gmail.com
 *        Company:  Universidade Federal de Juiz de Fora (UFJF)
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void empty_graph(Graph* g) {
  g->vertex_count = 0;
  g->arcs = NULL;
  g->visited_vertex = NULL;
}

void init_graph(Graph* g, int n) {
  int i, j;
  empty_graph(g);

  g->vertex_count = n;
  g->arcs = (int**) calloc(n, sizeof(int*));
  for (i = 0 ; i < g->vertex_count ; i++)
    g->arcs[i] = (int*) calloc(n, sizeof(int));
  g->visited_vertex = (int*) calloc(n, sizeof(int));
}

void free_graph(Graph* g) {
  int i;

  for (i = 0 ; i < g->vertex_count ; i++)
    free(g->arcs[i]);
  free(g);
  g = NULL;
}

int insert_arc(Graph* g, int a1, int a2, int weight) {
  if (a1 >= 0 && a1 < g->vertex_count && a2 >= 0 && a2 < g->vertex_count && g->arcs[a1][a2] == 0) {
    g->arcs[a1][a2] = weight;
    g->arcs[a2][a1] = weight;
    return 0;
  }
  return -1;
}

int remove_arc(Graph* g, int a1, int a2) {
  int weight = -1;
  if (a1 >= 0 && a1 < g->vertex_count && a2 >= 0 && a2 < g->vertex_count && g->arcs[a1][a2] > 0) {
    weight = g->arcs[a1][a2];
    g->arcs[a1][a2] = 0;
    g->arcs[a2][a1] = 0;
  }
  return weight;
}

int exists_arc(Graph* g, int a1, int a2) {
  return g->arcs[a1][a2] > 0;
}

int* get_adjacency(Graph* g, int v) {
  int degree;

  degree = get_vertex_degree(g, v);

  int* adjacency = (int*) malloc((degree + 1) * sizeof(int));

  adjacency[0] = degree; // Using the first position of the pointer to determine the size of the array
  
  int i;
  int j;
  for (i = 0, j = 1 ; j <= degree ; i++) {
    if (g->arcs[i][v] > 0) {
      adjacency[j++] = i;
    }
  }

  return adjacency;
}

int get_vertex_degree(Graph* g, int v) {
  int i;
  int degree = 0;

  for (i = 0 ; i < g->vertex_count ; i++)
    if (g->arcs[i][v] > 0)
      degree++;

  return degree;
}

void insert_vertex(Graph* g, int v) {
  if (g->arcs == NULL) {
    init_graph(g, v); 
  }

  else {
    int i, j;
    g->vertex_count += v;
    g->arcs = (int**) realloc(g->arcs, g->vertex_count * sizeof(int*));
    
    for (i = 0 ; i < g->vertex_count - v ; i++)
      g->arcs[i] = (int*) realloc(g->arcs[i], g->vertex_count * sizeof(int)); // realloc the part of the matrix which were used before

    for ( ; i < g->vertex_count ; i++) 
      g->arcs[i] = (int*) calloc(g->vertex_count, sizeof(int)); // alloc the new part of the matrix

    for (i = 0 ; i < g->vertex_count - v ; i++) {
      for (j = g->vertex_count - v ; j < g->vertex_count ; j++) {
        g->arcs[i][j] = 0;
      }
    }
  }
}

int remove_vertex(Graph* g, int v) {
  int i, j;

  if (v == g->vertex_count - 1) {
    for (i = 0 ; i < g->vertex_count ; i++)
      g->arcs[i][g->vertex_count - 1] = g->arcs[i][v];

    for (j = 0 ; j < g->vertex_count ; i++)
      g->arcs[g->vertex_count - 1][j] = g->arcs[v][j];
  }

  g->vertex_count--;

  free(g->arcs[g->vertex_count - 1]);
  g->arcs = (int**) realloc(g->arcs, g->vertex_count * sizeof(int*));

  for (i = 0 ; i < g->vertex_count ; i++)
    g->arcs[i] = (int*) realloc(g->arcs[i], g->vertex_count * sizeof(int));

}

void print_graph(Graph* g) {
  int i, j;

  printf("  ");
  for (i = 0 ; i < g->vertex_count ; i++) printf(" %d ", i);
  for (i = 0 ; i < g->vertex_count ; i++) {
	 printf("\n");
    printf("%d ", i);
    for (j = 0 ; j < g->vertex_count ; j++) {
      printf("[%d]", g->arcs[i][j]);
    }
  }
  printf("\n\n");
}

void print_adjacency(int* a) {
  int i;

  for (i = 1 ; i <= a[0] ; i++)
    printf("[%d]", a[i]);

  if (a[0] == 0) printf("\n");

  printf("\n");
}

