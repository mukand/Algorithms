#include<iostream>
#include<stack>
#include<cstdlib>
#include<ctime>
using namespace std;
struct tree
{
  int value;
        int maxchild;
  tree *left;
  tree *right;
  tree *parent;
};
#define SIZE 20
void nodemaxchild(tree*);
void inorder(tree*);
tree* insert(tree*,int);
tree *memoryalloc();
void snaketraversal(tree*);
int main()
{
	tree *start;
	//srand(time(0));
	for(int i=0;i<SIZE;i++)
            start=insert(start,rand()%100);
        //snaketraversal(start);
        inorder(start);
}
void inorder(tree *ptr)
{
	if(ptr==NULL)
		return;
	inorder(ptr->left);
	cout<<ptr->value<<" MAX CHILD: "<<ptr->maxchild<<endl;;
	inorder(ptr->right);
}
tree *search(tree *ptr,int value)
{
	if(ptr->value<value)
	{
		if(ptr->right==NULL)
			return ptr;
		else
			return search(ptr->right,value);
	}
	else
	{
		if(ptr->left==NULL)
			return ptr;
		else
			return search(ptr->left,value);
	}
}
tree* insert(tree *start,int value)
{
	tree *ptr,*p;
	ptr=memoryalloc();
	ptr->value=value;
        cout<<ptr->value<<endl;
	if(start==NULL)
	{
		return ptr;
	}
	p=search(start,value);
	ptr->parent=p;
	if(p->value<value)
		p->right=ptr;
	else
		p->left=ptr;
        nodemaxchild(ptr);
        return start;
}
tree *memoryalloc()
{
	tree *ptr;
	ptr=(tree *)malloc(sizeof(tree));
	ptr->right=ptr->parent=ptr->left=NULL;
        ptr->maxchild=0;
	return ptr;
}
void nodemaxchild(tree *node)
{
    int value=0;
    while(node->parent!=NULL)
    {
        value=node->maxchild+1;
        if(node->parent->maxchild<value)
            node->parent->maxchild=value;
        node=node->parent;
    }
}
void snaketraversal(tree *start)
{
    tree *ptr;
    bool flag=true;
    stack<tree*> sf,sb;
    if(start==NULL)
        return;
    sf.push(start);
    cout<<sf.top()->value<<" START "<<endl;
    while(!sf.empty()||!sb.empty())
    {
       // cout<<"START"<<endl;
        if(!sf.empty()&&flag==true)
        {
            ptr=sf.top();
            sf.pop();
            if(ptr->left!=NULL)
                sb.push(ptr->left);
            if(ptr->right!=NULL)
                sb.push(ptr->right);
            //cout<<"print";
            cout<<ptr->value<<" , ";
        }
        else if(flag==true)
        {
            flag=false;
            cout<<endl;
        }
        if(!sb.empty()&&flag==false)
        {
            ptr=sb.top();
            sb.pop();
            if(ptr->right!=NULL)
                sf.push(ptr->right);
            if(ptr->left!=NULL)
                sf.push(ptr->left);
            cout<<ptr->value<<" , ";
        }
        else if(flag==false)
        {
            cout<<endl;
            flag=true;
        }
    }
}
