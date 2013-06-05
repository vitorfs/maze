/*
 * =====================================================================================
 *
 *       Filename:  maze.c
 *
 *    Description:  Implementation of a depth-first search for solving maze
 *                  problems
 *
 *        Version:  1.0
 *        Created:  04/06/2013 09:45:55
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
#include <math.h>
#include "graph.h"
#include "stack.h"

int read_graph(char* filename, Graph* g) {
  FILE *PTRFILE;

  PTRFILE = fopen(filename, "rt");
  
  if (PTRFILE == NULL) {
    return -1;
  }
  else {
    char line[80];
    char str_aux[80];
    int i;
    int j;
    int k;
    int arc_1;
    int arc_2;
    
    empty_graph(g);

    for (i = 0 ; fgets(line, 80, PTRFILE) != NULL ; i++) {
      if (i == 0) {
        insert_vertex(g, atoi(line));
      }
      else {
        for (j = 0, k = 0 ; j < 80 && line[j] != 32 && line[j] != '\0' ; j++, k++)  str_aux[k] = line[j];
        str_aux[k] = '\0';
        arc_1 = atoi(str_aux);
        j = j + 1;
        str_aux[0] = '\0';
        for (k = 0 ; j < 80 && line[j] != 32 && line[j] != '\0' ; j++, k++) str_aux[k] = line[j];
        str_aux[k] = '\0';
        arc_2 = atoi(str_aux);
        insert_arc(g, arc_1, arc_2, 1);
      }
    }
  }
  return 0;
}

void dfs_r(Graph* maze, int vertex, int aim, int depth) {
  if (depth == 0) {
    return;
  }
  else {
    maze->visited_vertex[vertex] = 1;
    int i;
    for (i = 0 ; i <= maze->vertex_count ; i++) {
      if (maze->arcs[vertex][i] == 1 && maze->visited_vertex[i] == 0) { //possui adjacencia
        if (i == aim) { //achou o objetivo
          printf("\n");
        } 
        else {
          printf("[%d]->", i);
          dfs_r(maze, i, aim, depth - 1);
        }
      }
    }
  }
}

int dfs(Graph* maze, int v, int aim, int depth) {
  int success = 0;
  int fail = 0;
  int i;
  int j;
  Stack* open_nodes = (Stack*) malloc(sizeof(Stack));
  init_stack(open_nodes);
  Stack* closed_nodes = (Stack*) malloc(sizeof(Stack));
  init_stack(closed_nodes);
  
  int* parent = (int*) malloc(maze->vertex_count * sizeof(int));
  for (i = 0 ; i < maze->vertex_count ; parent[i++] = -1);

  push(open_nodes, v);

  i = 0;

  /*while (!(fail || success)) {
    if (empty_stack(open_nodes)) {
      fail = 1;
    }
    else {*/
    while (!empty_stack(open_nodes)) {
      int v;
      v = pop(open_nodes);
      if (v == aim) {
        //success = 1;
        push(closed_nodes, v);
        for (i = 0 ; i <= closed_nodes->last ; i++) {
          printf("[%d]->", closed_nodes->values[i]);
        }
        printf("\n");

        //print_stack(closed_nodes);
        //print_stack(open_nodes);

        int next;
        if (!empty_stack(open_nodes)) {
          next = pop(open_nodes);
          int sair = 1;
          int poped;
          //while(parent[pop(closed_nodes)] != parent[next] || empty_stack(closed_nodes)) {
          while(1) {
            poped = pop(closed_nodes);
            maze->visited_vertex[poped] = 0;
            if (parent[poped] == parent[next])
              break;
            if (parent[poped] == -1)
              break;
          }
          push(open_nodes, next);
        }
      }
      else {
        int i;
        for (i = 0 ; i < maze->vertex_count ; i++) {
          if (maze->arcs[v][i] == 1 && maze->visited_vertex[i] == 0) {
            push(open_nodes, i);
            parent[i] = v;
          }
        }
        maze->visited_vertex[v] = 1;
        push(closed_nodes, v);
      }
    //}
    if (depth-- == 0) break;
  //}
  //print_stack(closed_nodes);
  //success == 1 ? printf("A busca localizou o alvo.\n") : printf("A busca nao localizou o alvo.\n");
    }
  return success;
}

int dfs_2(Graph* maze, int v, int aim, int depth) {
  int i;
  int j;
  Stack* open_nodes = (Stack*) malloc(sizeof(Stack));
  init_stack(open_nodes);
  Stack* closed_nodes = (Stack*) malloc(sizeof(Stack));
  init_stack(closed_nodes);
  
  int* parent = (int*) malloc(maze->vertex_count * sizeof(int));
  for (i = 0 ; i < maze->vertex_count ; parent[i++] = -1);

  push(open_nodes, v);

  i = 0;

  while (!empty_stack(open_nodes)) {
    int v;
    v = pop(open_nodes);
    if (v == aim) {
      int x;
      print_stack(closed_nodes);
      while(x = parent[pop(closed_nodes)] != parent[open_nodes->values[open_nodes->last]]) {
        maze->visited_vertex[x] = 0;
      }
      print_stack(closed_nodes);
    }
    else {
      int i;
      for (i = 0 ; i < maze->vertex_count ; i++) {
        if (maze->arcs[v][i] == 1 && maze->visited_vertex[i] == 0) {
          push(open_nodes, i);
          parent[i] = v;
        }
      }
      maze->visited_vertex[v] = 1;
      push(closed_nodes, v);
    }
  }
  return 0;
}

void print_maze(Graph* graph) {
  int maze_size = sqrt(graph->vertex_count);
  int i;
  int j;
  int k;

  for (i = 0, k = 0 ; i < maze_size ; i++) {
    for (j = 0 ; j < maze_size ; j++, k++) {
      int* adj = get_adjacency(graph, k);
      if (adj[0] > 0) {
        printf("[%2d . ]", k);
      } 
      else {
        printf("[%2d # ]", k);  
      }
      free(adj);
    }
    printf("\n");
  }

}

/*
 * Command line arguments:
 * 1 filename
 * 2 starting vertex
 * 3 aim vertex
 * 4 depth limit
 */
int main(int argc, char* argv[]) {
  
  char* filename;
  int read_status = -1;
  int start;
  int aim;
  int limit = -1;

  Graph* graph = (Graph*) malloc(sizeof(Graph));

  filename = (char*) malloc(128 * sizeof(char));
  
  if (argc > 3) {
    filename = argv[1];
    start = atoi(argv[2]);
    aim = atoi(argv[3]);

    if (argc > 4) {
      limit = atoi(argv[4]);
    }

    read_status = read_graph(filename, graph);

    if (read_status == -1) {
      printf("File doesn't exist.\n");
      return -1;
    }
  }
  else {
    printf("The program expects at least three arguments.\n");
    return -1;
  }

  print_maze(graph);
  printf("\n");
  dfs(graph, start, aim, limit);
  //dfs_r(graph, start, aim, limit);

  return 0;
}
