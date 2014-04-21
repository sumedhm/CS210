/*This data structure for an n × n matrix will
 * consist of exactly 2n + m nodes where m is the number of non zero entries in the matrix. Each node
 * will have identical structure, that is, a row-head node, and a column-head node will have and non-zero element node 
 * identical structure . Any matrix will be accessed by two pointers  pointing to the lists of column-head nodes and row-head nodes
 * respectively
 * */

/* The program works even if row ,and coloumn order in row, order  of input is changed*/


#include<stdio.h>                                                            //including header files for I/O and structures
#include<stdlib.h>

typedef struct node                                                          //defining structure of node which is common for whole 
{
	int Matrix,Row,Column;
	int value ;
	struct node *next_down ;
	struct node *next_right ;
} node;

node *move(int Row, int Column, node *temp) 	                            //function to find position for element to be inserted into sparse matrix 
{ 
	if((temp->Row) == 0) 
	{  
                 while(Column > 1) {temp = (temp->next_right) ; Column-- ;}
                 while(((temp->next_down) != NULL)&&(temp->next_down->Row) < Row){ temp = (temp->next_down);}
        }
	else if((temp->Column) == 0)
	{ 
                 while(Row > 1) {temp = (temp->next_down) ; Row-- ;}
                 while(((temp->next_right)!= NULL)&&(temp->next_right->Column) < Column){ temp = (temp->next_right) ;}
        }
	return temp ;
}

main()
{
	int n,i,j,Matrix,Row,Column,val;
	node *P1 , *Q1 , *P2, *Q2, *t1, *t2, *temp1, *temp2, *temp3, *temp4;    //required variables are declared here
										//P for column heads and Q for row heads
	t2 = t1 = NULL ;

printf("Enter the order of the matrix and follow with rowwise nonzero entries for Matrix 1 and then for Matrix 2 \n"); //printing promt for user

	scanf(" %d",&n);                                                //reading value of order of the matrices

for(j = 1 ; j <= 2; j++)                                        	//creating nodes for coloumn references for both the matrices
{
	i = n;
	while(i > 0)
 	{
		node *new ;
 		new = (node *)malloc(sizeof(node));
		new->Matrix = j;new->Row = 0;new->Column = 1;new->value = 0;
		new->next_down = t1;new->next_right = t2;t2 = new ;i = i-1;
 	}
 	if(j == 1) P1=t2;
	else if(j == 2) P2=t2;
 	t2 = NULL;
}

for(j = 1 ; j <= 2; j++)                                      		//creating nodes for row references for both the matrices
{
 	i = n;
 	while(i > 0)
 	{
 		node *new ;
 		new = (node *)malloc(sizeof(node));
 		new->Matrix = j;new->Row = 1;new->Column = 0;new->value =  0;
 		new->next_down = t1;new->next_right = t2;t1 = new ;i = i-1;
 	}
 	if(j==1) Q1 = t1;
 	else if(j==2) Q2 = t1;
 	t1 = NULL;                                                 
} 


 for(i=0 ;  ; i++ )                                          		//loop for reading the non zero elements of sparse matrix
 {                                                           
 	scanf(" %d", &Matrix );                                          
 	if(Matrix == 0) break;                                           //breaks the loop when 0 is encountered for first time
 	scanf(" %d", &Row );
 	scanf(" %d", &Column );
 	scanf(" %d", &val );
 	node *new ;
 	new = (node *)malloc(sizeof(node));                       	//creating node for the non zero element
 	new->Matrix = Matrix ;new->Row = Row ;new->Column = Column ;new->value = val ;     

 	if(Matrix == 1) 
	{                                             			// inserting element into proper matrix
        	t1 = P1 ; t2 = Q1 ;
        	t1 = move( Row, Column, t1);
        	t2 = move( Row, Column, t2);
        }
	if(Matrix == 2)
	{ 
        	t1 = P2 ; t2 = Q2 ;
        	t1 = move( Row, Column, t1);
          	t2 = move( Row, Column, t2);
        }

 	new->next_down = t1->next_down ; new->next_right = t2->next_right ;  //intialising pointers in node and allocating poniters to node
 	t2->next_right=new;t1->next_down = new ;
 }

	printf("\nThe product of the matices is:\n");          		//begin to print the product

 t1 = Q1 ;
 t2 = P2 ;
while((t1 != NULL) && (t2 != NULL))                   		//loop for restoring values of pointers(rowhead and column head after each row)  
 { 
	temp1 = t1;
	temp2 = t2;
 	while((t1 != NULL) && (t2 != NULL))                    //loop for calculating rowwise product elements of matrices
 	{     
 		temp3 = t1;
 		temp4 = t2;
 		val = 0;
 		while((t1 != NULL) && (t2 != NULL))
  		{
 		if((t1->Column == t2->Row)) 
		{
			val = val + (t1->value)*(t2->value); 
			Row = t1->Row ; Column = t2->Column;
			t1 = t1->next_right ;t2 = t2->next_down;//calculating product of row element of 1st matrix with the coloumn element of 2nd 
		}
		else if((t1->Column) > (t2->Row))  		// if matching element not found ;
		{ 
			t2 = t2->next_down ;        
		}
 		else if ((t1->Column) < (t2->Row))
		{
			t1 = t1->next_right ;
		}
 		}
 		if (val != 0) printf(" %d %d %d \n", Row, Column, val);      //prints the product along after row and coloumn number

 		t2 = temp4->next_right ;
 		t1 = temp3;
 	}
 	t1 = temp1->next_down ;
 	t2 = temp2;
 }
  
}										//main function ends
