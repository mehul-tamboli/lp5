#include<iostream>
#include<queue>
#include<stdlib.h>
#include<omp.h>

using namespace std;

class node{
  public:
    node *left;
    node *right;
    int data;
};

class BFS{
  public:
    node *insert(node* , int );
    void BFS_Fuction(node*);
};


node* insert(node* root, int data) 
{
    if (root == NULL) {
        root = new node;
        root->data = data;
        root->left = root->right = NULL;
        return root;
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

void BFS_Fuction(node* head)
{
  queue<node*> q;
  q.push(head);
  int qsize;
  
  while(!q.empty())
  {
    qsize = q.size();
    #pragma omp parallel for
    for (int i=0; i<q.size();i++)
    {
      node *currNode;
      #pragma omp critical
      {
        currNode = q.front();
        q.pop();
        cout<<"\t"<<currNode->data;
      }
      
      #pragma omp critical 
      {
        if(currNode->left) {
          q.push(currNode->left);
        }
        if(currNode->right) {
            q.push(currNode->right);
        }
      }
    }
  }
}

int main()
{
  node * root = NULL;
  int num;
  char ans;
  int n;
  
  cout<<"How many nodes";
  cin>>n;
  
  for (int i=0; i<n; i++)
  {
    cout<<"Enter the code "<<i;
    cin>>num;
    
    root = insert(root, num);
  }
  double start = omp_get_wtime();
  BFS_Fuction(root);
  double end = omp_get_wtime();
  
  cout << "\nExecution Time: " << (end - start) << " seconds\n";
  
}
