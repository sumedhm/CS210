#include <stdio.h>
#include <stdlib.h>


int n,m,i,j,v,w,dfn=0;
typedef struct {								//Structure of a vertex.
	int value;
	int visited;
	int DFN;
	int high_pt;
	int AP;
	int parent;
}node;

int min(int a,int b)
{
	if (a<b) return a;
	else return b;
}

typedef struct node_ {      	                                                  //Structure for adjency list
        int element;
        struct node_ * next;
	struct node_ * conn_comp;
}list;
list *temp;
list *temp1;

void DFS(int v,node vertex[],list adj_list[],list *temp1){
	vertex[v].visited = 1;
	vertex[v].DFN = dfn;
	vertex[v].high_pt = dfn;
	dfn++;
	list * temp = adj_list[v].next;		//This temp is local.temp1 is not.
	while(temp!=NULL){
		int w = temp->element;
		if(vertex[w].visited==0)
		{
			vertex[w].parent = v;
			while(temp1->conn_comp != NULL) temp1 = temp1->conn_comp;
			temp1->conn_comp=(list*)malloc(sizeof(list));
			temp1 = temp1->conn_comp;
			temp1->element = w;
			temp1->next = NULL;	//Next undefined for conn_components except the root as next stores only the roots of diff comps.
			temp1->conn_comp = NULL;		//Temporarily null.
			DFS(w,vertex,adj_list,temp1);
			vertex[v].high_pt = min(vertex[v].high_pt,vertex[w].high_pt);
			if (vertex[w].high_pt >= vertex[v].DFN) {vertex[v].AP = 1;}
		}
		else if (vertex[v].parent != w)
		{
			vertex[v].high_pt = min(vertex[w].DFN,vertex[v].high_pt);
		}
	temp = temp->next;
	}
	return;
}


int main(void)
{
printf("\n/*Please read these instructions:\n\t1.The program takes first input as n & m.Be sure to enter correct no.of edges as it stops taking input only after m edges are entered.\n\t2.Enter each edge only once.Entering it twice is equivalent to entering wrong adjency list.\n\t3.Make sure the input is in the format as mentioned in the assignment problem.\n\t4.Some garbage is printed after execution,it is to free memory, please look for the answer just below where you entered input.\n\t5.If you think ans is wrong please recheck to see as the order of printing the answer may be different but it may contain all answers.\n\t6.If the program does not execute after entering all inputs,please count to see the no.of edges you entered(except n &m)\n\t7.{}-denotes empty set.\n\t*/");

int con_comp_count=0;
printf("\n/*\nEnter input:\n(This will automatically stop after taking  m edges.)*/\n");
scanf("%d %d", &n, &m);
node vertex[n];							//Declaring n vertices
	for (i=0;i<n;i++)
	{
		vertex[i].value = i;
		vertex[i].visited = 0;
		vertex[i].DFN = -1;					//Invalid DFN previously.
		vertex[i].high_pt = -1;
		vertex[i].AP = 0;
		vertex[i].parent = -1;
	}

list adj_list[n];							//Adjency list for n vertices.
list roots;
list *temp2;	
	for (i=0;i<n;i++)						//Saving adjency list.
	{	adj_list[i].element = i;
		adj_list[i].next = NULL;
		adj_list[i].conn_comp = NULL;				//This is undefined for adj_list,only defined for roots.
	}
	w=1; //taking m edges now.
	while (w<=m)
	{	
		scanf("%d %d",&i,&j);w++;
		temp = &adj_list[i];
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp ->next = (list*) malloc (sizeof(list));
		temp = temp->next;
		temp->element = j;
		temp->next = NULL;
		temp = &adj_list[j];
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = (list*) malloc (sizeof(list));
		temp = temp->next;
		temp->element = i;
		temp->next = NULL;
	}
//Start DFS traversal.

con_comp_count++; roots.element = 0;roots.next = NULL;
temp1 = &roots;temp1->element=0;
temp1->conn_comp = NULL;
DFS(0,vertex,adj_list,temp1);
temp = &roots;i=0;
	while (i<n)
	{
		if (vertex[i].visited == 1) i++;
		else {
			con_comp_count++;
			temp->next = (list*) malloc (sizeof(list));
			temp = temp->next;
			temp->element = i;
			temp->next = NULL;
			temp->conn_comp = NULL;
			temp1 = temp;
			temp2 = temp;
			dfn=0;
			DFS(i,vertex,adj_list,temp1);
			temp = temp2;			//assuring temp doesnt change during DFS.
			}
	}

//Output now.
i=0;temp = &roots;
printf("\n\n/*\nThere are %d connected components in the graph:\n{", con_comp_count);
j = 0;
while(temp!=NULL){if (j>0) printf(" & {");
	temp1 = temp;
	v=0;						//v is for counting no.of children of roots(for articulation points).
while(temp1!=NULL){
	i = temp1 -> element;
	printf("%d,",i);
	if (vertex[i].parent == temp->element) v++;
	temp1 = temp1->conn_comp;
	}
	if (v>1) vertex[temp->element].AP = 1;
	else vertex[temp->element].AP = 0;
	printf("}");j = 1;
	temp = temp->next;
}
printf("\nThe articulation points are : {");
for(i=0;i<n;i++)
{
	if (vertex[i].AP == 1) printf("%d,",vertex[i].value);
}
printf("}\nThe bridges are : {");
for (i=0;i<n;i++){
	if(vertex[i].parent != -1){
	if (vertex[i].high_pt >= vertex[i].DFN) printf("(%d,%d),",vertex[i].parent,vertex[i].value);
}
}
printf("}\t*/\n");
printf("\n/*\nProgram has ended,\nFreeing memory*/\n");

/* start freeing all allocated space*/
//free conn_components list.
temp = &roots;
while(temp!=NULL){temp1 = temp->conn_comp;
	while(temp1!=NULL){
		temp2 = temp1->conn_comp;
		free(temp1);
		temp1 = temp2;
	}
	temp2 = temp->next;
	free(temp);
	temp = temp2;
}
//free adjency lists.
for(i=0;i<n;i++)
{temp = &adj_list[i];
while (temp!=NULL)
	{
		temp1 = temp->next;
		free(temp);
		temp = temp1;
	}
}
//free vertices.
for (i=0;i<n;i++) free(&vertex[i]);

return 0;
}
