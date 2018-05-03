#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
int main()
{
	avl_node *root=NULL,*t;
	avl_node *dummy;
	dummy=(avl_node*)malloc(sizeof(avl_node));
	dummy->roll_no=0;
	dummy->marks=0;
	dummy->balance=0;
	dummy->semester_number=0;
	dummy->left=NULL;
	dummy->right=NULL;
	strcpy(dummy->subject_code,"\0");
	strcpy(dummy->department_name,"\0");
	strcpy(dummy->student_name,"\0");
	int x,flag=0,n,i,roll,k1,k2,k;
	char sub[20];
	printf("\n\nSTUDENT RECORD\n\n");
	l1:
	printf("\n\n");
	printf("PRESS:\n");
	printf("1.INSERTION\n");
	printf("2.DELETION\n");
	printf("3.SEARCH\n");
	printf("4.NUMBER OF RECORDS\n");
	printf("5.HEIGHT\n");
	printf("6.RANGE SEARCH\n");
	printf("7.PRINT\n");
	printf("8.GETMAX\n");
	printf("9.FAILURES\n");
	printf("10.Kth HIGHEST\n");
	printf("11.TOPPER\n");
	printf("12.QUIT\n");
	printf("\n\nEnter Your Choice:");
	scanf("%d",&x);

		switch(x)
		{
			case 1:
				printf("\n\nOPERATION: INSERTION\n\n");
				printf("Enter Number of Records you want to Insert:");
				scanf("%d",&n);
				for(i=0;i<n;i++)
				{
					root=insert(root);
				}
				printf("\n\nInsertion Completed!!!\n\n");
				goto l1;
				
			case 2:
				printf("\n\nOPERATION: DELETION\n\n");
				printf("Enter Roll Number to Delete: ");
				scanf("%d",&roll);
				printf("Enter Subject Code: ");
				scanf("%s",sub);
				root=deletion(root,roll,sub);
				printf("Deletion Completed!\n\n");
				printf("AFTER DELETION: \n");
				in_order(root);
				goto l1;
				
			case 3:
				printf("\n\nOPERATION: SEARCH\n\n");
				printf("Enter Roll Number to Search: ");
				scanf("%d",&roll);
				printf("Enter Subject Code: ");
				scanf("%s",sub);
				t=tree_search(root,roll,sub);
				printf("RESULTS OF TREE SEARCH:\n");
				visit(t);
				goto l1;
			
			case 4:
				printf("\n\nOPERATION: NUMBER OF RECORDS\n\n");
				n=num_nodes(root);
				printf("\nNUMBER OF RECORD PRESENT CURRENTLY ARE: %d\n",n);
				goto l1;
				
			case 5:
				printf("\n\nOPERATION: HEIGHT\n\n");
				n=height_tree(root);
				printf("\nHEIGHT OF TREE IS %d\n",n);
				goto l1;
				
			case 6:
				printf("\n\nOPERATION: RANGE SEARCH\n\n");
				printf("Enter Key1:");
				scanf("%d",&k1);
				printf("Enter Key2:");
				scanf("%d",&k2);
				printf("\nRESULT OF RANGE SEARCH:\n");
				range_search(root,k1,k2);
				goto l1;
				
			case 7:
				printf("\n\nOPERATION: PRINT\n\n");
				in_order(root);
				goto l1;
				
			case 8:
				printf("\n\nOPERATION: GETMAX\n\n");
				printf("Enter Subject Code : ");
				scanf("%s",sub);
				printf("\nTOPPERS OF SUBJECT CODE %s ARE:",sub);
				get_max_xyz(root,sub,dummy);
				goto l1;
				
			case 9:
				printf("\n\nOPERATION: FAILURES\n\n");
				printf("Enter Subject Code : ");
				scanf("%s",sub);
				printf("Enter Passing marks: ");
				scanf("%d",&n);
				printf("STUDENT WHO FAILED IN SUBJECT CODE %s ARE:",sub);
				get_failures(root,sub,n);
				goto l1;
				
			case 10:
				printf("\n\nOPERATION: Kth HIGHEST\n\n");
				printf("Enter Subject Code : ");
				scanf("%s",sub);
				printf("Enter an Integer K: ");
				scanf("%d",&k);
				printf("\nSTUDENT SCORING Kth HIGHEST MARKS IN THE GIVEN SUBJECT ARE:\n");
				get_kth_highest(root,sub,k);
				goto l1;
				
			case 11:
				printf("\n\nOPERATION: TOPPER\n\n");
				printf("\nTOPPERS OF CLASS:\n");
				get_topper(root);
				goto l1;
				
				
				
			case 12:
				printf("\n\nTHANKS!!!\n\n");
				break;
				
			
		}
		return(0);
		
}
	

