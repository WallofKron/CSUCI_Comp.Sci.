/*
 Robert Florence
 CSUCI
 Prof. A.J./Dolan-Stern
 Lab 7
 Task 1
 
 */

#include "stdio.h"
#include <stdlib.h>
#include <string.h>

#define inputarraylength 200
#define MAXVERTICES 100

int *visited;

void printgrapharray(int vertamount, int graph[][vertamount]);
void DFS(int i, int numvert, int graph[][numvert]);

int main(int argc, char* argv[]){

    int numvert = 1;
    char edges[inputarraylength];
    char vertices[inputarraylength];
    
	freopen("input.txt","r", stdin);

	scanf("V={%[^}]s", vertices);

    printf("\nVERTICES\n");
	printf("%s\n",vertices);			//comma-seperated list of names

    for (int i =0; i < inputarraylength; i++) {
        
        if(vertices[i]==','){
        
            numvert++;                          //get number of vertices
        }
    }
    const char *verts[numvert];         //create vertice array

    printf("numvert: %d\n", numvert);
    
    visited = calloc(numvert, sizeof(int));                              //create visited array

    for (int q = 0; q < numvert; q++) {
        visited[q] = 0;
    }
    
    int graph[numvert][numvert];                    //create n*n matrix array
    
    for (int k = 0; k < numvert; k++) {
        for (int z = 0; z < numvert; z++) {
            
            graph[k][z] = 0;                            //init the graph 2-d array slots to 0
        }
    }
    //printgrapharray(numvert, graph);                      //testing the initilization of array
    
    char *token;
    
    token = strtok(vertices,", ");

    for(int j = 0; token != NULL; j++){
    
        verts[j] = token;                        //break all the comma sep values into their own array slot
        token = strtok( NULL, ", ");
    }

    printf("\nEDGES\n");

	scanf("}\n E={");                   //get rid of garbage
    
    char *fromedge;
    char *toedge;

	while(getc(stdin) == '{'){             //parse the edges and adjust the adjacency matrix to represent edges

		scanf("%[^}]s", edges);
        
        printf("**%s**\n", edges);
        
        fromedge = strtok(edges,", ");
        toedge = strtok( NULL, ", ");
        
       /* 
        printf("%s\n", fromedge);                   //testing the breaking apart of 'edges'
        printf("%s\n", toedge);
        */
        
        
        for (int p = 0; p < numvert; p++) {                 //cycle through row (fromedge) to see where edge is
        
            if(strcmp(fromedge, verts[p]) == 0){                //if we found where edge is from
                
                for (int q = 0; q < numvert; q++) {             //loop through column to find toedge
                 
                    if (strcmp(toedge, verts[q]) == 0) {         //when we found both, change the adj matrix
                     
                        if (graph[p][q] == 1) {
                           
                            printf("Edge %s, %s already exists!\n", fromedge, toedge);
                            
                        } else {
                            //printf("slot[%d][%d] = 1, matrix updated\n", p, q);
                            graph[p][q] = 1;
                        
                        }
                        
                    }
                }
            }
        }
        
        
		scanf("}, ");
	}
    printgrapharray(numvert, graph);
    
    DFS(0,numvert,graph);
    
    printf("\n");
    int flag = 0;
    
    
    for (int x = 0; x < numvert; x++) {
        if (visited[x] > 1){
            
            printf(">>>DEADLOCK DETECTED<<<");
            flag = 1;
        }
    }
    if (flag == 0) {
        printf(">>>NO DEADLOCK<<<\n\n");

    }

}


void printgrapharray( int vertamount, int graph[][vertamount]){
        printf("\nADJACENCY MATRIX!\n");
    
    for (int icount = 0; icount < vertamount; icount++) {
        
        for (int kcount = 0; kcount < vertamount; kcount++) {
        
            printf("%d ",graph[icount][kcount]);
        }
        
        printf("\n");
    }
    printf("\n");
}

void DFS(int i, int numvert, int graph[][numvert]){
    int j;
    
    printf("\n%d ",i);
    
    visited[i]++;
    
    for(j = 0; j < numvert; j++){
        
        if(!visited[j] && graph[i][j] == 1){
            
            DFS(j,numvert,graph);
        }
    }
}
