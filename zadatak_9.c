#include<stdio.h>
#include<stdlib.h>

typedef struct Node* Position;

struct Node {
	int num;
	Position left;
	Position right;

};

Position AllocateMemory(Position current_pos, int el)
{
	current_pos = (Position)malloc(sizeof(struct Node));
	if (current_pos == NULL)
	{
		printf("Greska pri alokaciji memorije!");
		return 0;
	}
	else // if(current_pos != NULL)
	{
		current_pos->num = el;
		current_pos->left = NULL;
		current_pos->right = NULL;
		return current_pos;
	}

}

Position Insert(Position current_pos, int el)
{
	if (current_pos == NULL) {
		current_pos = AllocateMemory(current_pos, el);
	}
	else if (current_pos->num > el)
	{
		current_pos->left = Insert(current_pos->left, el);
	}
	else // if(current_pos->num < el)
	{
		current_pos->right = Insert(current_pos->right, el);
	}

	return current_pos;
}

Position Find(Position current_pos, int el)
{
	if (current_pos == NULL)
		return NULL;
	else if (current_pos->num == el)
	{
		return current_pos;
	}
	else if (current_pos->num > el)
	{
		return Find(current_pos->left, el);

	}
	else //if (current_pos->num > el)
	{
		 return Find(current_pos->right, el);
	}

}

void PrintPreorder(Position current_pos)
{
	if (current_pos == NULL)
		return ;

	printf("%d ", current_pos->num);
	PrintPreorder(current_pos->left);
	PrintPreorder(current_pos->right);

}

void PrintInOrder(Position current_pos)
{
	if (current_pos == NULL)
		return;

	
	PrintInOrder(current_pos->left);
	printf("%d ", current_pos->num);
	PrintInOrder(current_pos->right);

}

void PrintPostorder(Position current_pos)
{
	if (current_pos == NULL)
		return;


	PrintPostorder(current_pos->left);
	PrintPostorder(current_pos->right);
	printf("%d ", current_pos->num);

}

Position FindMax(Position current_pos)
{
	if (current_pos == NULL) return NULL;

	while (current_pos->right != NULL)
	{
		current_pos = current_pos->right;
	}

	return current_pos;
}

Position FindMin(Position current_pos)
{
	if (current_pos == NULL) return NULL;

	while (current_pos->left != NULL)
	{
		current_pos = current_pos->left;
	}

	return current_pos;
}

Position Delete(Position current_pos, int el)
{
	if (current_pos == NULL) {
		return NULL;
	}
	
	if (current_pos->num == el)
	{
		if (current_pos->left == NULL && current_pos->right == NULL)
		{
			free(current_pos);
			return NULL;

		}
		else if (current_pos->left != NULL && current_pos->right != NULL)
		{
			Position result = FindMin(current_pos->right);
			current_pos->num = result->num;
			current_pos->right = Delete(current_pos->right, current_pos->num);
		}
		else if (current_pos->left == NULL && current_pos->right != NULL)
		{
			Position result = current_pos->right;
			free(current_pos);
			return result;
		}
		else //if (current_pos->left != NULL && current_pos->right == NULL)
		{
			Position result = current_pos->left;
			free(current_pos);
			return result;
		}

	}
	else if (current_pos->num > el) 
	{
		current_pos->left = Delete(current_pos->left, el);
	
	}
	else // if (current_pos->num < el) 
	{
		current_pos->right = Delete(current_pos->right, el);
	}

	return current_pos;


}


int main(void)
{
	Position root = NULL;
	Position q;

	root = Insert(root, 5);
	root = Insert(root, 3);
	root = Insert(root, 4);
	root = Insert(root, 8);
	root = Insert(root, 12);
	root = Insert(root, 2);
	root = Insert(root, 7);
	root = Insert(root, 1);
	root = Insert(root, 16);
	root = Insert(root, 14);

	//q = Find(root, 7);
	
	PrintPreorder(root);
	puts("\n");
	PrintInOrder(root);
	puts("\n");
	PrintPostorder(root);
	puts("\n");

	root = Delete(root, 5);

	return 0;

}