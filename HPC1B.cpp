#include<iostream>
#include<stack>
#include<stdlib.h>
#include<omp.h>

using namespace std;

class node {
public:
    node *left;
    node *right;
    int data;
};

class DFS {
public:
    node* insert(node*, int);
    void DFS_Function(node*);
};

node* DFS::insert(node* root, int data) 
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

void DFS::DFS_Function(node* head)
{
    if (head == NULL) return;

    stack<node*> s;
    s.push(head);

    while (!s.empty()) 
    {
        node* currNode;

        #pragma omp parallel 
        {
            #pragma omp single
            {
                currNode = s.top();
                s.pop();
                cout << "\t" << currNode->data;

                #pragma omp task
                {
                    if (currNode->right) {
                        s.push(currNode->right);
                    }
                }

                #pragma omp task
                {
                    if (currNode->left) {
                        s.push(currNode->left);
                    }
                }
            }
        }
    }
}

int main()
{
    DFS tree;
    node* root = NULL;
    int num, n;

    cout << "How many Nodes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the code " << (i + 1) << ": ";
        cin >> num;

        root = tree.insert(root, num);
    }

    double start = omp_get_wtime();
    tree.DFS_Function(root);
    double end = omp_get_wtime();

    cout << "\nExecution Time: " << (end - start) << " seconds\n";
}

