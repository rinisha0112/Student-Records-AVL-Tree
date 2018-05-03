#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"


static avl_node *check_ret=NULL;//used in check_balance();
static avl_node *find_ret=NULL;
static avl_node *xret=NULL;//used in make_balance_xyz()
static avl_node *xxtemp=NULL;
static avl_node *ret_new_tree=NULL;
static int ub=100;
static int count=0;

//INSERTION FUNCTIONS
avl_node* insert(avl_node *root)
{
	avl_node *new_node,*after_inst,*ptr,*ret,*p;
	after_inst=NULL;
	new_node=(avl_node*)malloc(sizeof(avl_node));
	printf("\nEnter Roll_Number: ");
	scanf("%d",&new_node->roll_no);
	printf("\nEnter Subject Code: ");
	scanf("%s",new_node->subject_code);
	printf("\nEnter Marks: ");
	scanf("%f",&new_node->marks);
	printf("\nEnter Student Name: ");
	scanf("%s",new_node->student_name);
	printf("\nEnter Department Name: ");
	scanf("%s",new_node->department_name);
	printf("\nEnter Semester Number: ");
	scanf("%d",&new_node->semester_number);
	new_node->balance=0;
	new_node->left=NULL;
	new_node->right=NULL;
	after_inst=bst_insert(root,new_node);
	set_balance(after_inst);
	in_order(after_inst);
	check_ret=NULL;		//GLOBAL
	xret=NULL;		//GLOBAL
	ptr=check_balance(after_inst);
	if(ptr==NULL)
	{
		printf("\nStatus: BALANCED!!\n");
		ret=after_inst;
	}
	else
	{
		printf("\nStatus: UNBALANCED\n");
		printf("The unblanced node from bottom is:\n");
		visit(ptr);
		printf("PERFORMING ROTATIONS!\n");
		ret=making_balance_xyz(after_inst,ptr);
		after_inst=ret;
		printf("\nBalancing/rotations completed!!\n");
	}
	return(ret);

}

avl_node* bst_insert(avl_node *root, avl_node *new_node)
{
	avl_node *ptr=root;
	int done=0;
	new_node->left=NULL;
	new_node->right=NULL;
	if(root==NULL)
	{
		root=new_node;
	}
	else
	{
		while(!done)
		{
			if(new_node->roll_no<ptr->roll_no)
			{
				if(ptr->left==NULL)
				{
					ptr->left=new_node;
					done=1;
				}
				else
				{
					ptr=ptr->left;
				}	
			}
			else if(new_node->roll_no>ptr->roll_no)	
			{
				if(ptr->right==NULL)
				{
					ptr->right=new_node;
					done=1;
				}
				else
				{
					ptr=ptr->right;
				}
			}
			else
			{
				if(strcmp(ptr->subject_code,new_node->subject_code)==0)
				{
						printf("Case Updation!!\n");
						ptr->marks=new_node->marks;
						ptr->semester_number=new_node->semester_number;
						strcpy(ptr->department_name,new_node->department_name);
						strcpy(ptr->student_name,new_node->student_name);
						done=1;
						
					
				}
				else if(strcmp(new_node->subject_code,ptr->subject_code)==-1)
				{
					if(ptr->left==NULL)
					{
						ptr->left=new_node;
						done=1;
					}
					else
					{
						ptr=ptr->left;
					}	
					
				}
				else
				{
					if(ptr->right==NULL)
					{
						ptr->right=new_node;
						done=1;
					}
					else
					{
						ptr=ptr->right;
					}
					
				}
			
				
			}
			
		}
	}
	return(root);
}


void set_balance(avl_node *root)
{
	if(root!=NULL)
	{
		//avl_node *ptr1=root;
		int x=height_tree(root->left);
		int y=height_tree(root->right);
		root->balance=x-y;
		set_balance(root->left);
		set_balance(root->right);
	}
	
}


avl_node* check_balance(avl_node *root)
{
	
	avl_node *t;
	if(root!=NULL)
	{
		if(root->balance==2||root->balance==-2)
		{
			check_ret=root;
		}
		check_ret=check_balance(root->left);
		check_ret=check_balance(root->right);
		
	}
	
	return(check_ret);
}


avl_node* rotate_left(avl_node *root)
{
	avl_node *temp;
	if(root==NULL)
	{
		printf("error!\n");
	}
	else if(root->right==NULL)
	{
		printf("Cannot Rotate!");
	}
	else
	{
		temp=root->right;
		root->right=temp->left;
		temp->left=root;
	}
	printf("Rotated left!!\n");
	return(temp);
}
avl_node* rotate_right(avl_node *root)
{
	avl_node *temp;
	if(root==NULL)
	{
		printf("error!\n");
	}
	else if(root->left==NULL)
	{
		printf("Cannot Rotate!");
	}
	else
	{
		temp=root->left;
		root->left=temp->right;
		temp->right=root;
	}
	printf("Rotated right!!\n");
	return(temp);
}

avl_node* find_prev(avl_node *root, avl_node *node)
{
	//static avl_node *ret=NULL;
	if(root!=NULL)
	{
	
	 if(root->left==node||root->right==node)
		{
			find_ret=root;
			
		}
		find_ret=find_prev(root->left,node);
			find_ret=find_prev(root->right,node);
	}
	
	return(find_ret);
}


avl_node* making_balance_xyz(avl_node *root, avl_node *node)
{
	avl_node *prev,*ptr,*temp,*xptr,*xtemp;
	avl_node *ret;
	temp=root;
	
	find_ret=NULL;
	if(root!=node)
	{
		prev=find_prev(root,node);
	}
	else if(root==node)
	{
		prev=root;
	}
	//printf("Visiting Prev!\n");
	//visit(prev);
	if(prev->left==node)
	{
		ptr=prev->left;
		prev->left=NULL;
		//printf("\nExecuted prev->left==node\n");
		//visit(prev->left);
	}
	else if(prev->right==node)
	{
		ptr=prev->right;
		prev->right=NULL;
		//printf("\nExecuted prev->right==node\n");
		
	}
	else if(prev==root)
	{
		 ptr=prev;
	}
	if(node->balance==2)
	{
		if(node->left->balance==1)
		{
			ret=rotate_right(node);
		}
		else if(node->left->balance==-1)
		{
			ret=complex_rotate_right(node);
			//ret=rotate_right(ret);
		}
	}
	else if(node->balance==-2)
	{
		if(node->right->balance==-1)
		{
			ret=rotate_left(node);
		}
		else if(node->right->balance==1)
		{
			ret=complex_rotate_left(node);
			//ret=rotate_left(ret);
		}
	}
	if(prev!=ptr)
	{
		if(prev->left==NULL)
		{
			prev->left=ret;
			//printf("\nAttached\n");
		}
		else if(prev->right==NULL)
		{
			prev->right=ret;
			//printf("\nAttached\n");
		}
	}
	else
	{
		temp=ret;
	}
	set_balance(temp);
	printf("\nFINALIZED ANSWER:\n");
	in_order(temp);
	return(temp);
}
	
	

avl_node* complex_rotate_left(avl_node *root)
{
	avl_node *prev,*ptr,*intr_ret,*store,*ret;
	store=root;
	prev=root;
	ptr=root->right;
	prev->right=NULL;
	intr_ret=rotate_right(ptr);
	prev->right=intr_ret;
	ret=rotate_left(root);
	return(ret);
	
}


avl_node* complex_rotate_right(avl_node *root)
{
	avl_node *prev,*ptr,*intr_ret,*store,*ret;
	store=root;
	prev=root;
	ptr=root->left;
	prev->left=NULL;
	intr_ret=rotate_left(ptr);
	prev->left=intr_ret;
	ret=rotate_right(root);
	return(ret);
}


//DELETION FUNCTIONS
avl_node* deletion(avl_node *root,int roll, char *sub)
{
	avl_node *ptr,*prev,*x,*ret,*left_tree,*right_tree,*left_balance,*half;
	ptr=tree_search(root,roll,sub);
	printf("Searched Node!\n");
	visit(ptr);
	find_ret=NULL;
	prev=find_prev(root,ptr);
	//printf("\n\nPrevious Node\n");
	//visit(prev);
	if(ptr!=NULL)
	{
		if(prev==NULL)
		{
			/*left_tree=root->left;
			right_tree=root->right;
			root->left=NULL;
			root->right=NULL;
			if(left_tree!=NULL)
			{
				if(right_tree!=NULL)
				{
					root=bst_insert(left_tree,right_tree);
				}
				else if(right_tree==NULL)
				{
					root=left_tree;
				}
				
			}
			else if(right_tree!=NULL)
			{
				if(left_tree!=NULL)
				{
					root=bst_insert(right_tree,left_tree);
				}
				else if(left_tree==NULL)
				{
					root=right_tree;
				}
				
			}
			else if(left_tree==NULL&&right_tree==NULL)
			{
				root=NULL;
			}*/
			prev=ptr;
			
			
		}
		else if(prev!=NULL)
		{
			if(prev->left==ptr)
			{
				delete_node(&(prev->left));
			}
			else if(prev->right==ptr)
			{
				delete_node(&(prev->right));
			}
		}
	}
	set_balance(root);
	check_ret=NULL;
	xret=NULL;
	x=check_balance(root);
	if(x==NULL)
	{
		printf("\nStatus:BALANCED\n");
			ret=root;
	}
	else
	{
		printf("Status:UNBALANCED\n");
		printf("The unbalanced one from bottom!\n");
		visit(ptr);
	
		ret=making_balance_xyz(root,x);
		root=ret;
		printf("\nBalancing/rotations completed!!\n");
		//ptr=NULL;
	}
	return(ret);
}


void delete_node(avl_node **pptr)
{
	avl_node *q,*r;
	if(*pptr==NULL)
	{
		printf("\nError!\n");
	}
	else if((*pptr)->left==NULL&&(*pptr)->right==NULL)
	{
		*pptr=NULL;
	}
	else if((*pptr)->right==NULL)
	{
		*pptr=(*pptr)->left;
	}
	else if((*pptr)->left==NULL)
	{
		*pptr=(*pptr)->right;
	}
	else
	{
		for(q=(*pptr);q->right!=NULL;)
		{
			r=q;
			q=q->right;
		}
		r->right=q->left;
		q->left=(*pptr)->left;
		q->right=(*pptr)->right;
			r=*pptr;
			*pptr=q;
			free(r);
		
	}

	
}


//SEARCH
avl_node* tree_search(avl_node *root, int roll, char *subject)
{
	avl_node *ret_val;
	ret_val=NULL;
	if(root!=NULL)
	{
		if(root->roll_no==roll&&strcmp(root->subject_code,subject)==0)
		{
			ret_val=root;
		}
		else if(root->roll_no==roll&&strcmp(subject,root->subject_code)==1)
		{
			ret_val=tree_search(root->right,roll,subject);
		}
		else if(root->roll_no==roll&&strcmp(subject,root->subject_code)==-1)
		{
			ret_val=tree_search(root->left,roll,subject);
		}
		else if(roll<root->roll_no)
		{
			ret_val=tree_search(root->left,roll,subject);
		}
		else if(roll>root->roll_no)
		{
			ret_val=tree_search(root->right,roll,subject);
		}
		
	}
	return(ret_val);
	
}


//NUMBER OF RECORDS
int num_nodes(avl_node *root)
{
	int ret_val;
	if(root==NULL)
	{
		ret_val=0;
	}
	else
	{
		ret_val=1+num_nodes(root->left)+num_nodes(root->right);
	}
	return(ret_val);
}

//HEIGHT
int height_tree(avl_node *root)
{
	int ret_val,height_left,height_right;
	if(root==NULL)
	{
		ret_val=-1;
	}
	else if(root->left==NULL&&root->right==NULL)
	{
		ret_val=0;
	}
	else
	{
		height_left=height_tree(root->left);
		height_right=height_tree(root->right);
		if(height_left>height_right)
		{
			ret_val=1+height_left;
		}
		else
		{
			ret_val=1+height_right;
		}
		
	}
	return(ret_val);
}


//RANGE SEARCH
void range_search(avl_node *root, int start, int end)
{
	if(root!=NULL)
	{
		if(root->roll_no>=start&&root->roll_no<=end)
		{
			visit(root);
			range_search(root->left,start,end);
			range_search(root->right,start,end);
		}
		else if(root->roll_no<start&&root->roll_no<end)
		{
			range_search(root->right,start,end);
		}
		else if(root->roll_no>start&&root->roll_no>end)
		{
			range_search(root->left,start,end);
		}
	}
	
	//else if(root->roll_no>=start&&root->roll_no<=end)
}


//PRINT

//IN_ORDER
void in_order(avl_node *root)
{
	if(root!=NULL)
	{
		visit(root);
		in_order(root->left);
		
		in_order(root->right);
	}
}

//VISITING A NODE
void visit(avl_node *root)
{
	if(root!=NULL)
	{
		printf("\n\nRoll Number:%d\n",root->roll_no);
		printf("Subject_Code:%s\n",root->subject_code);
		printf("Marks:%f\n",root->marks);
		printf("Student Name:%s\n",root->student_name);
		printf("Department Name:%s\n",root->department_name);
		printf("Semester Number:%d\n",root->semester_number);
		printf("BALANCE:%d \n",root->balance);
	}
	else
	{
		printf("Tree is empty!/Searched key not Found!!\n");
	}
}


//GETMAX
void get_max_xyz(avl_node *root, char *sub, avl_node *ret_max)
{
	avl_node *x;
	x=get_max(root,sub,ret_max);
	get_all(root,x->subject_code,x->marks);
}
avl_node* get_max(avl_node *root, char *sub, avl_node *ret_max)
{
	if(root!=NULL)
	{
		if(strcmp(root->subject_code,sub)==0)
		{
			if(root->marks>ret_max->marks)
			{
				ret_max=root;
			}
		}
		ret_max=get_max(root->left,sub,ret_max);
		ret_max=get_max(root->right,sub,ret_max);
	}
	return(ret_max);
	
}


//FAILURES
void get_failures(avl_node *root, char *s, int k)
{
	if(root!=NULL)
	{
		if(strcmp(root->subject_code,s)==0)
		{
			if(root->marks<k)
			{
				visit(root);
			}
		}
		get_failures(root->left,s,k);
		get_failures(root->right,s,k);
	}
}




//Kth HIGHST
void get_kth_highest(avl_node *root, char *s, int k)
{
	avl_node *x,*root1,*root2;
	root1=root2=root;
	xxtemp=NULL;//global
	ub=100;//global
	x=get_single(root1,s,k);
	//printf("\nVisiting return of single value");
	//visit(x);
	get_all(root2,x->subject_code,x->marks);
}
avl_node* get_single(avl_node *root, char *s, int k)
{
	//static avl_node *dummyx;
	avl_node *dummyx,*ret;
	dummyx=(avl_node*)malloc(sizeof(avl_node));
	dummyx->roll_no=0;
	dummyx->marks=0;
	dummyx->balance=0;
	dummyx->semester_number=0;
	dummyx->left=NULL;
	dummyx->right=NULL;
	strcpy(dummyx->subject_code,"\0");
	strcpy(dummyx->department_name,"\0");
	strcpy(dummyx->student_name,"\0");
	if(k!=0)
	{
		//printf("Ub=%d\n",ub);
		xxtemp=new_get_max(root,s,0,ub,dummyx);
		//printf("Visiting xxtemp\n");

		//visit(xxtemp);
		//printf("\n");
		ub=xxtemp->marks;
		//printf("Ub=%d\n",ub);
		k=k-1;
		ret=get_single(root,s,k);
	}
	return(xxtemp);
}
avl_node* new_get_max(avl_node *root, char *sub, int lb, int ub, avl_node *ret_max)
{
	if(root!=NULL)
	{
		if(strcmp(root->subject_code,sub)==0)
		{
			if(root->marks>ret_max->marks&&root->marks<ub)
			{
				//ret_max=root;
				//copying dummy!
				ret_max->roll_no=root->roll_no;
				ret_max->marks=root->marks;
				ret_max->balance=root->balance;
				ret_max->semester_number=root->semester_number;
				ret_max->left=NULL;
				ret_max->right=NULL;
				strcpy(ret_max->subject_code,root->subject_code);
				strcpy(ret_max->department_name,root->department_name);
				strcpy(ret_max->student_name,root->student_name);
			}
		}
		ret_max=new_get_max(root->left,sub,0,ub,ret_max);
		ret_max=new_get_max(root->right,sub,0,ub,ret_max);
	}
	return(ret_max);
}
void get_all(avl_node *root, char *s, int m)
{
	if(root!=NULL)
	{
		if(strcmp(root->subject_code,s)==0&&root->marks==m)
		{
			visit(root);
			printf("\n");
		}
		get_all(root->left,s,m);
		get_all(root->right,s,m);
		
	}
}



//TOPPER
void get_topper(avl_node *root)
{
	avl_node *a,*root1,*root2,*x,*y,*z;
	avl_node *dummyx;
	dummyx=(avl_node*)malloc(sizeof(avl_node));
	dummyx->roll_no=0;
	dummyx->marks=0;
	dummyx->balance=0;
	dummyx->semester_number=0;
	dummyx->left=NULL;
	dummyx->right=NULL;
	strcpy(dummyx->subject_code,"\0");
	strcpy(dummyx->department_name,"\0");
	strcpy(dummyx->student_name,"\0");
	int n,i;
	root1=root2=root;
	a=make_new_x(root1);
	//in_order(a);
	ret_new_tree=NULL;
	x=go_through(a,root2);
	printf("\n\nTotal of Students\n");
	in_order(x);
	y=get_max_marks(x,dummyx);
	//printf("\n\nVisiting y\n");
	//visit(y);
	printf("\n\nTopper\n\n");
	get_all_top(x,y->marks);
	//b=make_new(x);
	
	
}

avl_node* make_new_x(avl_node *root)
{
	static avl_node *new_tree=NULL;
	avl_node *t,*dummyx;
	if(root!=NULL)
	{
		dummyx=(avl_node*)malloc(sizeof(avl_node));
		dummyx->roll_no=root->roll_no;
		dummyx->marks=root->marks;
		dummyx->balance=0;
		dummyx->semester_number=root->semester_number;
		dummyx->left=NULL;
		dummyx->right=NULL;
		strcpy(dummyx->subject_code,root->subject_code);
		strcpy(dummyx->department_name,root->department_name);
		strcpy(dummyx->student_name,root->student_name);
		new_tree=new_bst_tree(new_tree,dummyx);
		//printf("\n\nUpdated New Tree!!!!!\n\n");
		//in_order(new_tree);
		t=make_new_x(root->left);
		t=make_new_x(root->right);
	}
	return(new_tree);
	
}
avl_node* new_bst_tree(avl_node *root, avl_node *new_node)
{
	avl_node *ptr=root;
	int done=0;
	new_node->left=NULL;
	new_node->right=NULL;
	if(root==NULL)
	{
		root=new_node;
	}
	else
	{
		if(roll_search(ptr,new_node->roll_no)==0)
		{
			while(!done)
			{
				if(new_node->roll_no<ptr->roll_no)
				{
					if(ptr->left==NULL)
					{
						ptr->left=new_node;
						done=1;
					}
					else
					{
						ptr=ptr->left;
					}	
				}
				else if(new_node->roll_no>ptr->roll_no)	
				{
					if(ptr->right==NULL)
					{
						ptr->right=new_node;
						done=1;
					}
					else
					{
						ptr=ptr->right;
					}
				}
				else
				{
					if(strcmp(ptr->subject_code,new_node->subject_code)==0)
					{
							printf("Case Updation!!\n");
							ptr->marks=new_node->marks;
							ptr->semester_number=new_node->semester_number;
							strcpy(ptr->department_name,new_node->department_name);
							strcpy(ptr->student_name,new_node->student_name);
							done=1;
							
						
					}
					else if(strcmp(new_node->subject_code,ptr->subject_code)==-1)
					{
						if(ptr->left==NULL)
						{
							ptr->left=new_node;
							done=1;
						}
						else
						{
							ptr=ptr->left;
						}	
						
					}
					else
					{
						if(ptr->right==NULL)
						{
							ptr->right=new_node;
							done=1;
						}
						else
						{
							ptr=ptr->right;
						}
						
					}
				
					
				}
				
			}
		}			
	}
		
	return(root);
}
int roll_search(avl_node *root, int roll)
{
	int ret=0;
	if(root!=NULL)
	{
		if(root->roll_no==roll)
		{
			ret=1;
		}
		else
		{
			ret=roll_search(root->left,roll);
			ret=roll_search(root->right,roll);
			
		}
	}
	return(ret);
}
avl_node* go_through(avl_node *a, avl_node *root)
{
	avl_node *x,*t;
	avl_node *dummyx;
	dummyx=(avl_node*)malloc(sizeof(avl_node));
	dummyx->roll_no=0;
	dummyx->marks=0;
	dummyx->balance=0;
	dummyx->semester_number=0;
	dummyx->left=NULL;
	dummyx->right=NULL;
	strcpy(dummyx->subject_code,"\0");
	strcpy(dummyx->department_name,"\0");
	strcpy(dummyx->student_name,"\0");
	if(a!=NULL)
	{
		count=0;//statc global
		x=range_search_total(root,a->roll_no,a->roll_no,dummyx);
		x->marks=x->marks/count;
		//printf("Ansswers provided by Range Search!!!\n\n");
		//visit(x);
		ret_new_tree=bst_insert(ret_new_tree,x);
		//printf("\n\nNew_tree With new_total!!!\n\n");
		//in_order(ret_new_tree);
		t=go_through(a->left,root);
		t=go_through(a->right,root);
	
	}
	
	return(ret_new_tree);
}
avl_node* range_search_total(avl_node *root, int start, int end, avl_node *ret)
{
	if(root!=NULL)
	{
		if(root->roll_no>=start&&root->roll_no<=end)
		{
			count++;
			ret->marks=(ret->marks+root->marks);
			ret->roll_no=root->roll_no;
			//dummyx->marks=root->marks;
			ret->balance=0;
			ret->semester_number=root->semester_number;
			ret->left=NULL;
			ret->right=NULL;
			strcpy(ret->subject_code,root->subject_code);
			strcpy(ret->department_name,root->department_name);
			strcpy(ret->student_name,root->student_name);
			ret=range_search_total(root->left,start,end,ret);
			ret=range_search_total(root->right,start,end,ret);
		}
		else if(root->roll_no<start&&root->roll_no<end)
		{
			ret=range_search_total(root->right,start,end,ret);
		}
		else if(root->roll_no>start&&root->roll_no>end)
		{
			ret=range_search_total(root->left,start,end,ret);
		}
	}
	return(ret);	
}
avl_node* get_max_marks(avl_node *root, avl_node *rettt)
{

		if(root!=NULL)
		{
			
				if(root->marks>rettt->marks)
				{
					rettt->roll_no=root->roll_no;
					rettt->marks=root->marks;
					rettt->balance=0;
					rettt->semester_number=root->semester_number;
					rettt->left=NULL;
					rettt->right=NULL;
					strcpy(rettt->subject_code,"Courses Enrolled!");
					strcpy(rettt->department_name,root->department_name);
					strcpy(rettt->student_name,root->student_name);
				}
				rettt=get_max_marks(root->left,rettt);
				rettt=get_max_marks(root->right,rettt);
		}
		return(rettt);
	
}
void get_all_top(avl_node *root, int m)
{
	if(root!=NULL)
	{
		if(root->marks==m)
		{
			visit_topper(root);
			printf("\n");
		}
		get_all_top(root->left,m);
		get_all_top(root->right,m);
		
	}
	
}
void visit_topper(avl_node *root)
{
	if(root!=NULL)
	{
		printf("/nRoll Number:%d\n",root->roll_no);
		//printf("Subject_Code:%s\n",root->subject_code);
		printf("Average Marks:%f\n",root->marks);
		printf("Student Name:%s\n",root->student_name);
		printf("Department Name:%s\n",root->department_name);
		printf("Semester Number:%d\n",root->semester_number);
		printf("Balance:%d \n",root->balance);
	}
	else
	{
		printf("Tree is empty!/Searched key not Found!!\n");
	}
	
}





//HEIGHT


//NUMBER OF RECORDS


//SEARCH


/*avl_node* make_balance(avl_node *node)
{
	avl_node *ret;
	if(node->balance==2)
	{
		if(node->left->balance==1)
		{
			ret=rotate_right(node);
		}
		else if(node->left->balance==-1)
		{
			ret=rotate_left(node->left);
			//ret=rotate_right(ret);
		}
	}
	else if(node->balance==-2)
	{
		if(node->right->balance==-1)
		{
			ret=rotate_left(node);
		}
		else if(node->right->balance==1)
		{
			ret=rotate_right(node->right);
			//ret=rotate_left(ret);
		}
	}
	set_balance(ret);
	return(ret);
	
}*/


/*
avl_node* making_balance_x(avl_node *root, avl_node *node)
{
	avl_node *prev,*ptr,*temp,*xptr,*xtemp;
	avl_node *ret;
	temp=root;
	
	find_ret=NULL;
	if(root!=node)
	{
		prev=find_prev(root,node);
	}
	else if(root==node)
	{
		prev=root;
	}
	//printf("Visiting Prev!\n");
	//visit(prev);
	if(prev->left==node)
	{
		ptr=prev->left;
		prev->left=NULL;
		//printf("\nExecuted prev->left==node\n");
		//visit(prev->left);
	}
	else if(prev->right==node)
	{
		ptr=prev->right;
		prev->right=NULL;
		//printf("\nExecuted prev->right==node\n");
		
	}
	else if(prev==root)
	{
		 ptr=prev;
	}
/*	printf("\nIn inorder prev\n");
	in_order(prev);
	printf("\nin inorder ptr\n");
	in_order(ptr);*/
	/*if(ptr->balance==2)
	{
		if(ptr->left->balance==1)
		{
			ret=rotate_right(ptr);
		}
		else if(ptr->left->balance==-1)
		{
			ret=rotate_left(ptr->left);
			if(prev!=ptr)
			{
				if(prev->left==NULL)
				{
					prev->left=ret;
					//printf("\nAttached\n");
				}
				else if(prev->right==NULL)
				{
					prev->right=ret;
					//printf("\nAttached\n");
				}
			}
			else
			{
				prev->left=ret;
				//printf("\nMai toh uppar gaya hi nahii!!\n");
			}
			printf("\n\n");
			printf("\nCalling in_order!\n");
			in_order(temp);
			xtemp=temp;
			xptr=check_balance(temp);
			if(xptr!=NULL)
			{
				xret=making_balance_x(temp,xptr);
			}
			
			
			//ret=rotate_right(ret);
		}
	}
	else if(ptr->balance==-2)
	{
		if(ptr->right->balance==-1)
		{
			ret=rotate_left(ptr);
		}
		else if(ptr->right->balance==1)
		{
			ret=rotate_right(ptr->right);
			if(prev!=ptr)
			{
				if(prev->left==NULL)
				{
					prev->left=ret;
					printf("\nAttached\n");
				}
				else if(prev->right==NULL)
				{
					prev->right=ret;
					printf("\nAttached\n");
				}
			}
			else
			{
				prev->right=ret;
				printf("\nMai toh uppar gayahich nahii!!\n");
				printf("kar liya baba attach!!!\n");
			}
			printf("After First Rotation:\n");
			in_order(temp);
			xtemp=temp;
			xptr=check_balance(temp);
			if(xptr!=NULL)
			{
				xret=making_balance_x(temp,xptr);
			}
			
			//ret=rotate_left(ret);
		}
	}
/*	printf("\nin inorder temp\n");
	in_order(temp);
	printf("\nin inorder ret\n");
	in_order(ret);*/
	/*if(xret==NULL)
	{
		if(prev!=ptr)
		{
			if(prev->left==NULL)
			{
				prev->left=ret;
				printf("\nAttached\n");
			}
			else if(prev->right==NULL)
			{
				prev->right=ret;
				printf("\nAttached\n");
			}
		}
		else
		{
			temp=ret;
		}
	}
	else
	{
		xtemp=xret;
		temp=xtemp;
	}
	
	//in_order(prev);
	set_balance(temp);
	printf("\nBaLANCED\n");
	printf("\nFINALIZED ANSWER\n");
	in_order(temp);
	return(temp);
	
}*/
/*avl_node* make_new(avl_node *root, avl_node *prev)
{
	static avl_node *new_tree=NULL;
	avl_node *t,*dummyx;
	
	if(root!=NULL)
	{
		if(root->roll_no!=prev->roll_no)
		{
			dummyx=(avl_node*)malloc(sizeof(avl_node));
			dummyx->roll_no=root->roll_no;
			dummyx->marks=root->marks;
			dummyx->balance=0;
			dummyx->semester_number=root->semester_number;
			dummyx->left=NULL;
			dummyx->right=NULL;
			strcpy(dummyx->subject_code,root->subject_code);
			strcpy(dummyx->department_name,root->department_name);
			strcpy(dummyx->student_name,root->student_name);
			new_tree=bst_insert(new_tree,dummyx);
			printf("\n\nUpdated New Tree!!!!!\n\n");
			in_order(new_tree);
			prev=root;
			
	
			
		}
	
		if(root->left!=NULL&&root->right!=NULL)
		{
			if(root->left->roll_no==root->roll_no||root->right->roll_no==root->roll_no)
			{
				
			
		 		if(root->left->roll_no!=root->roll_no&&root->right->roll_no==root->roll_no)
				{
					t=make_new(root->right,prev);
					printf("Here 1 \n");
					t=make_new(root->left,prev);
					printf("Here 2 \n");
				}
				else if(root->left->roll_no==root->roll_no&&root->right->roll_no!=root->roll_no)
				{
					t=make_new(root->left,prev);
					printf("Here 3\n");
					t=make_new(root->right,prev);
					printf("Here 4\n");
				}
				else if(root->left->roll_no!=root->roll_no&&root->right->roll_no!=root->roll_no)
				{
					t=make_new(root->left,prev);
					printf("Here 5\n");
					t=make_new(root->right,prev);
					printf("Here 6\n");
				}
				else if(root->left->roll_no==root->roll_no&&root->right->roll_no==root->roll_no)
				{
					t=make_new(root->left,prev);
					printf("Here 10\n");
					t=make_new(root->right,prev);
					printf("Here 11\n");
					
				}
			}
			else
			{
					t=make_new(root->left,prev);
					printf("Here 7\n");
					t=make_new(root->right,prev);
					printf("Here 8\n");
			}
			
			
		}
			return(new_tree);		
	}

		
}*/
