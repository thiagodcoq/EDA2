#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int value)
{
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL)
    {
        printf("Erro: Falha na alocação de memória\n");
        exit(1);
    }
    new->value = value;
    new->left = NULL;
    new->right = NULL;
}

Node *buildTree(int leaves[], int n)
{
    if (n == 0)
    {
        return NULL;
    }
    Node **nodes = (Node **)malloc(n * sizeof(Node *));
    if (nodes == NULL)
    {
        printf("Erro: Falha na alocação de memória\n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        nodes[i] = createNode(leaves[i]);
    }
    while (n > 1)
    {
        int newN = (n + 1) / 2;
        Node **newNodes = (Node **)malloc(newN * sizeof(Node *));
        if (newNodes == NULL)
        {
            printf("Erro: Falha na alocação de memória\n");
            exit(1);
        }
        for (int i = 0; i < n / 2; i++)
        {
            Node *parent = createNode(nodes[2 * i]->value + nodes[2 * i + 1]->value);
            parent->left = nodes[2 * i];
            parent->right = nodes[2 * i + 1];
            newNodes[i] = parent;
        }
        if (n % 2 == 1)
        {
            newNodes[newN - 1] = nodes[n - 1];
        }
        free(nodes);
        nodes = newNodes;
        n = newN;
    }
    Node *root = nodes[0];
    free(nodes);
    return root;
}

void print_order(struct Node *root)
{
    if (root)
    {
        print_order(root->left);
        printf("%d ", root->value);
        print_order(root->right);
    }
}

void freeTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    int folhas[] = {1, 5, 6, 7, 8, 10, 11, 15, 20, 21, 22};
    int n = sizeof(folhas) / sizeof(folhas[0]);
    Node *root = buildTree(folhas, n);
    print_order(root);
    printf("\n");
    freeTree(root);
    return 0;
}
