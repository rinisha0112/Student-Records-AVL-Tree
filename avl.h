#ifndef AVL_H
#define AVL_H
typedef struct avl_node_tag
{
	int roll_no;
	char subject_code[20];
	float marks;
	char student_name[20];
	char department_name[20];
	int semester_number;
	int balance;
	struct avl_node_tag *left;
	struct avl_node_tag *right;
}avl_node;

//FUNCTIONS FOR INSERTION!!!!
avl_node* insert(avl_node *root);		//GATHERS DATA
avl_node* bst_insert(avl_node *root, avl_node *new_node);		//BST TYPE INSERTION
void set_balance(avl_node *root);		//GIVES HEIGHT DIFFERENCE TO EACH NODE OF TREE
avl_node* check_balance(avl_node *root);		//RETURNS THE NODE WITH DOUBLE DASH FROM BOTTOM
avl_node* making_balance_xyz(avl_node *root, avl_node *node);		//MAKES TREE BALANCED IN HEIGHT USING ROTATION FUNCTIONS GIVEN BELOW
avl_node* rotate_left(avl_node *root);		//NORMAL ROTATION LEFT
avl_node* rotate_right(avl_node *root);		//NORMAL ROTATION RIGHT
avl_node* find_prev(avl_node *root, avl_node *node);		//FIND PREV TO DETACH THE NODE  WHERE ROTATION TAKES PLACE 
avl_node* complex_rotate_left(avl_node *root);		//FIRST ROTATE RIGHT THEN LEFT
avl_node* complex_rotate_right(avl_node *root);		//FIRST ROTATE LEFT THEN RIGHT

//DELETION
avl_node* deletion(avl_node *root,int roll, char *sub);		//LOCATE NODE TO DELETE AND SETS PREV
void delete_node(avl_node **pptr);			//DELETES APPROPRIATE NODE WITHOUT INCREASING HEIGHT OF TREE

//SEARCH
avl_node* tree_search(avl_node *root, int roll, char *subject);

//NUMBER OF RECORDS
int num_nodes(avl_node *root);

//HEIGHT
int height_tree(avl_node *root);

//RANGE SEARCH
void range_search(avl_node *root, int start, int end);

//PRINT
void in_order(avl_node *root);
void visit(avl_node *root);


//GETMAX
void get_max_xyz(avl_node *root, char *sub, avl_node *ret_max);
avl_node* get_max(avl_node *root, char *sub, avl_node *ret_max);

//FAILURES
void get_failures(avl_node *root, char *s, int k);


//Kth HIGHEST
void get_kth_highest(avl_node *root, char *s, int k);		//ORIGINAL FUNCTION
avl_node* get_single(avl_node *root, char *s, int k);		//The kth Highest(single student)
void get_all(avl_node *root, char *s, int m);				//Students who too have kth highest marks
avl_node* new_get_max(avl_node *root, char *sub, int lb, int ub, avl_node *ret_max);   //This sets the upperbound to the previous topper marks!!




//TOPPER
void get_topper(avl_node *root);		//Prints topper
avl_node* make_new_x(avl_node *root);		//Make new tree which keep record of distinct roll no(call it tree T1)
avl_node* new_bst_tree(avl_node *root, avl_node *new_node);		//using new bst above tree T1 is formed(this bst doesnot save nodes with same roll no)
int roll_search(avl_node *root, int roll);						//used in new_bst
avl_node* go_through(avl_node *a, avl_node *root);				//traverse every node of new tree T1
avl_node* range_search_total(avl_node *root, int start, int end, avl_node *ret);		//calculates average marks of student
avl_node* get_max_marks(avl_node *root, avl_node *rettt);		//finds topper based on average calculated
void get_all_top(avl_node *root, int m);		//find similar toppers
void visit_topper(avl_node *root);				//printing purpose!



//avl_node* make_balance(avl_node *node);
//avl_node* making_balance_x(avl_node *root, avl_node *node);
//link_node* get_top_link(link_node *lptr);
//void print_link(link_node *lptr);
#endif
