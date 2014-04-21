#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char O_Stack[100];
char N_Stack[100];
char *top1 = O_Stack;
char *top2 = N_Stack;
double *x,*y;
double value_x,value_y;
char c;									//This character has been used for atoi conversions.

int Power(int op1,int op2)						//Function to evaluate ^ operation
{
	int result;
	if (op2==0) return 1;
	else if (op2==1) return op1;
	else if ((op2 % 2)==0) return (Power(op1,op2/2) * Power(op1,op2/2));
	else return (Power(op1,op2/2) * Power(op1,op2/2) * op1);
}

int InsideStackPriority(char operator)					//Returns inside stack priority of operators
	{
		switch(operator)
		{
			case '(' : return 0;
			case '=' : return 1;
			case '+' : return 2;
			case '-' : return 2;
			case '*' : return 3;
			case '/' : return 3;
			case '^' : return 4;
			default : return -1;
		}
	}

int OutsideStackPriority(char operator)					//returns outside stack priority of operators.
	{
		switch(operator)
		{
			case '(' : return 7;
			case '=' : return 6;
			case '+' : return 2;
			case '-' : return 2;
			case '*' : return 3;
			case '/' : return 3;
			case '^' : return 5;
			default : return -1;
		}
	}

char *TOP (char *Stack)							//returns pointer to top of a stack.called by first element of stack
	{
		if (Stack == O_Stack) return top1;
		else return top2;
	}

void Pop(char *Stack)							//deletes top element
	{
		if (TOP(Stack) == top1) 
		{
			top1 = top1 - 1;*(top1+1)='\0';
		}
		else 
		{	top2=top2-1;*(top2+1)='\0';}
		return;
	}

void Push(char next,char *Stack)					//adds an element to the top
        {
                if (TOP(Stack)==top1)
		{
			top1 = (top1 +1);
                	*top1 = next;
                }
		else {
			top2 = top2+1;
			*top2 = next;
			}
		return;
        }

void Execute(char *Stack)						//execute function,b used in N_stack to differentiate b/w two consecutive 										nos.lying in the N stack
{	
        char operator;							//operator from O Stack
	int result=0,operand1=0,operand2=0;				//The two operands.
	operator = *TOP(O_Stack);				
	if (*TOP(N_Stack)=='b') Pop(N_Stack);	
	if(operator != '=')						//Trivial operations.
	{	if (*TOP(N_Stack)!='x' && *TOP(N_Stack)!='y')
			{						//operand2 is above operand1..pop 2 before 1 so.
				c= *TOP(N_Stack);			//Taking care of nos.with more than a digit.
                                while(c!='b')
                                {
                                        operand2 = (operand2*10) + (c-'0');
                                        Pop(N_Stack);
                                        c= *TOP(N_Stack);
                                }
				Pop(N_Stack);				//Pop out 'b'.
        		}
		else 							//Wasnt the top element a digit?
		{	if (*TOP(N_Stack)=='b') Pop(N_Stack);
			if (*TOP(N_Stack)=='x')
			{
				operand2 = *x;Pop(N_Stack);		//Popping x.
			}
			if (*TOP(N_Stack)=='y')
			{
				operand2 = *y;Pop(N_Stack);		//Popping y.
			}
		}
		if (*TOP(N_Stack)=='b') Pop(N_Stack);
		if (*TOP(N_Stack)!='x' && *TOP(N_Stack)!='y')
                        {
                                c= *TOP(N_Stack);
		                while (c!='b'&& c!='#')
                		{
					operand1 = (operand1*10) + (c-'0');	//atoi(c)=c-'0'.converting char to int.
                        		Pop(N_Stack);
					c= *TOP(N_Stack);
                		}						//Do not Pop out 'b' here.
                        }
                else {if (*TOP(N_Stack)=='b') Pop(N_Stack);
                        if (*TOP(N_Stack)=='x') 
                        {
                                operand1 = *x;Pop(N_Stack);
                        }
                        if (*TOP(N_Stack)=='y')
                        {
                                operand1 = *y;Pop(N_Stack);
                        }
                }
		if(operator == '+')  result= operand1 + operand2 ;		//Result calculations.applying operations.
  		else  if(operator == '-')  result = operand1 - operand2 ;
	   	else if(operator == '*')  result = operand1*operand2 ;
    		else if(operator == '/')  result = operand1/operand2 ;
     		else if(operator == '^') result = Power(operand1,operand2);
		while (result!=0)						//Storing result back into the N_Stack.
        	{
        		c= (result%10) + '0';					//c+'0' converts int c to char c.
        		Push(c,N_Stack);
        		result=result/10;
        	}
        	Push('b',N_Stack);						//Add 'b' to differentiate result with previous no.
	}

	else if(operator == '=')						//The non-trivial case of '='.
	{	if (*TOP(N_Stack)=='b') Pop(N_Stack);
		c= *TOP(N_Stack);
		while(c!='b')							//Pop out operand2,must be an integer as right side expression of 											'=' has to be calculated before.
		{
			operand2 = (operand2*10) +(c-'0');
			Pop(N_Stack);
			c= *TOP(N_Stack);
		}Pop(N_Stack);							//Pop out 'b'
		c = *TOP(N_Stack);Pop(N_Stack);					//Pop out operand1.must be x or y.then pop out 'b'.
		if (c=='x') *x=operand2;
		else if (c=='y') *y=operand2;					//Change value of operand1 now.
	Push(c,N_Stack);Push('b',N_Stack);					//Keep it back as x or y,not operand 1.
	}
	return;									//Return to main.
}

main()										//MAIN FUNCTION
{
	char next;								//Stores next character of expression,may be digit,variable,operation
	char expression[100];
	N_Stack[0]='#';								//Bottom of N stack.top2 doesnt change.
	N_Stack[1]='b';top2=top2+1;
	O_Stack[0]='#';								//Bottom of O Stack.top1 doesnt change.
	printf("\n\n\tEnter the expression to evaluate(Please do not give any spaces):\n\t");
	scanf("%s", expression);
	int i=0;								//Reading the expression.
	next = expression[i];x = &value_x;y = &value_y;
	*x=1.0;*y=1.0;float result;
	while (1)							
	{
		if ((next>='0' && next <='9') || next == 'x' || next=='y')	//An operand?
			{	while (next>='0' && next <='9')			//Digit or a variable?while to handle multiple digits no.
				{	Push(next,N_Stack);
					i++;next=expression[i];
				}
				if (next == 'x' || next =='y') 
				{
					Push(next,N_Stack);
				}
				Push('b',N_Stack);				//Push 'b' at last no matter a no.or variable.
			}
		if (next == ')') 						//Handling parantheses.
			{
				while (*TOP(O_Stack) != '(')			//Operate till matching ( found.
				{
					Execute(O_Stack);
					Pop(O_Stack);
				}
			Pop(O_Stack);						//Pop matching (
			}
		if (next == '\0') 						//Expression ends?
			{
				while (*TOP(O_Stack) != '#')			//operate till # found to finish it off.
				{
					Execute(O_Stack);Pop(O_Stack);
				}

			Pop(O_Stack);						//Pop #
			break;}
		
		if (InsideStackPriority(next)>=0) 				//Priorities decided on the basis of associativity and precedence of 											operators so as to decide which to be executed first.
		{
				while(InsideStackPriority(*TOP(O_Stack)) >= OutsideStackPriority(next))
				{	
					Execute(O_Stack);			//If the top operator can be executed operate
					Pop(O_Stack);				//After executing pop it out.
				}
				
				Push(next,O_Stack);				//Else put above it the next operator.
			}
	i++;									//Repeating till '\0'--End of string.
	next = expression[i];
	}
	if (*TOP(N_Stack)=='b') Pop(N_Stack);					//popping result,the final stored value in N_stack
	c= *TOP(N_Stack);result = 0;
        while(c!='b'&& c!='#')
        	{
			result = result*10 +(c-'0');
			Pop(N_Stack);
			c= *TOP(N_Stack);
		}
	printf("\nThe value of x is: %.2lf\nThe value of y is: %.2lf\n And the value of expression is:%.2f\n", *x, *y, result); //print answer.
}

