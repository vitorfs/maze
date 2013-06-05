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
#include "graph.h"

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

int busca_profundidade(Graph* maze, int vertex, int aim, int depth) {
  if (depth == 0) {
    return -1;
  }
  else {
    maze->visited_vertex[vertex] = 1;
    int i;
    for (i = 0 ; i <= maze->vertex_count ; i++) {
      if (maze->arcs[vertex][i] == 1 && maze->visited_vertex[i] == 0) { //possui adjacencia
        if (i == aim) { //achou o objetivo
          printf("\n");
          return i;
        } 
        else {
          printf(" <- %d", busca_profundidade(maze, i, aim, depth - 1));
        }
      }
    }
    return vertex;
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

  busca_profundidade(graph, start, aim, limit);

  return 0;
}
