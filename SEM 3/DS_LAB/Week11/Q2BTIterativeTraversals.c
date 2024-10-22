/*
Q2 Display the elements of Binary Tree created using iterative preorder, post-order
(Use single stack), in-order and level-order traversals.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct btree {
	char ele;
	struct btree *rchild, *lchild;
} btree;

typedef struct {
	btree *Node;
	int flag;
} Stack;

btree *createNode(char ele){
	btree *newNode = calloc(1, sizeof(btree));
	newNode->ele = ele;
	newNode->rchild = newNode->lchild = NULL;
	return newNode;
}
void createIterative(btree **root){
	int ch = 0;
	char dir[50], data, dummy;
	
	printf("Root Node Data : ");
	scanf("%c", &data);	
	*root = createNode(data);
	do {
		int i = 0;
		btree *temp = *root;
		printf("Direction : ");
		scanf("%s", dir);
		scanf("%c", &dummy);
		printf("Data : ");
		scanf("%c", &data);
		while (dir[i] != '\0'){
			if (dir[i] == 'R' || dir[i] == 'r'){
				if (temp->rchild == NULL)
					break;
				else temp = temp->rchild; 
			}
			if (dir[i] == 'L' || dir[i] == 'l'){
				if (temp->lchild == NULL)
					break;
				else temp = temp->lchild; 
			}
			i++;
		}	
		btree *newNode = createNode(data);
		if (dir[i] == 'R' || dir[i] == 'r')
			temp->rchild = newNode;
		else temp->lchild = newNode;
		printf("Enter -1 to Stop : ");
		scanf("%d", &ch);
	} while (ch != -1);
}

void inorder(btree *root){
	if(root){
		inorder(root->lchild);
		printf("%c ", root->ele);
		inorder(root->rchild);
	}
}

void preorder(btree *root){
	if(root){
		printf("%c ", root->ele);
		preorder(root->lchild);
		preorder(root->rchild);
	}
}

void postorder(btree *root){
	btree * current = root;
	stack s[50];
	int tos = -1;
	if(root == NULL)
		return;
	for(;;){
		while(current!=NULL){
			s[++tos].node = current;
			s[tos].flag = 1;
			current = current->llink;
		}
		while(s[tos].flag<0){
			current = s[tos--].node;
			printf("%c ", current->ele);
			if (tos == -1)
				return;
		}
		current = s[tos].node;
		current = current->rlink;
		s[tos].flag = -1;
	}
}

int main(){
	btree *root = NULL;
	createIterative(&root);
	printf("Inorder : ");
	inorder(root);
	printf("\n");
	printf("Preorder : ");
	preorder(root);
	printf("\n");
	printf("Postorder : ");
	postorder(root);
	printf("\n");
	return 0;
}