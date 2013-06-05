/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  Header for the graph implementation
 *
 *        Version:  1.0
 *        Created:  04/06/2013 23:51:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vitor Freitas (vfs), vitorfs@gmail.com
 *        Company:  Universidade Federal de Juiz de Fora (UFJF)
 *
 * =====================================================================================
 */

#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
  int vertex_count;
  int* visited_vertex;
  int** arcs; // 0 represents the lack of adjacency
} Graph;

void empty_graph(Graph* g);
void init_graph(Graph* g, int n);
void free_graph(Graph* g);
int insert_arc(Graph* g, int a1, int a2, int weight);
int remove_arc(Graph* g, int a1, int a2);
int exists_arc(Graph* g, int a1, int a2);
int* get_adjacency(Graph* g, int v);
int get_vertex_degree(Graph* g, int v);
void insert_vertex(Graph* g, int v);
int remove_vertex(Graph* g, int v);
void print_graph(Graph* g);
void print_adjacency(int* a);
#endif

