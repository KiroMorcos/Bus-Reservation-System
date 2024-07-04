#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
extern int errno;
int No_Users = 0;

/* DONE: SUCCESSfUL USERS LOADING IN BST
   NEXT: CODE LOGIN FUNCTION
   Make directory for files
*/

//Debug Login Function

typedef struct User
{
    char *name;
    char *password;
} User;

typedef struct Node
{
    User s;
    struct Node *left;
    struct Node *right;
} Node;

void Print_In_X(int x, char *str)
{
    for (int j = 0; j < x; j++)
        printf(" ");
    printf("%s", str);
}

Node *newNode(User x)
{
    Node *n = malloc(sizeof(Node));
    if (n == NULL)
    {
        fprintf(stderr, "An Error has occurred...\nError Number: %d\n", errno);
        fprintf(stderr, "Error Message: %s\n", strerror(errno));
        return errno;
    }
    n->left = n->right = NULL;
    n->s = x;
    return n;
}

User newUser(char *username, char *pass)
{
    User s;
    s.name = malloc(strlen(username) + 1);
    if (s.name == NULL)
    {
        fprintf(stderr, "An Error has occurred...\nError Number: %d\n", errno);
        fprintf(stderr, "Error Message: %s\n", strerror(errno));
        exit(errno);
    }
    strcpy(s.name, username);
    s.password = malloc(strlen(pass) + 1);
    if (s.password == NULL)
    {
        fprintf(stderr, "An Error has occurred...\nError Number: %d\n", errno);
        fprintf(stderr, "Error Message: %s\n", strerror(errno));
        exit(errno);
    }
    strcpy(s.password, pass);
    return s;
}

void FreeUser(User s)
{
    free(s.name);
    free(s.password);
}

Node *insert(Node *root, User x)
{
    if (root == NULL)
        root = newNode(x);
    else if (strcasecmp(x.name, root->s.name) < 0)
        root->left = insert(root->left, x);
    else if (strcasecmp(x.name, root->s.name) > 0)
        root->right = insert(root->right, x);
    return root;
}

Node *Search(Node *root, User s)
{
    if (root == NULL)
        return NULL;
    if (strcmp(root->s.name, s.name) == 0)
        return root;
    if (strcmp(s.name, root->s.name) < 0)
        return Search(root->left, s);
    if (strcmp(s.name, root->s.name) > 0)
        return Search(root->right, s);
}

void PreorderDisplay(Node *root)
{
    if(root)
    {
        printf("%s\n", root->s.name);
        PreorderDisplay(root->left);
        PreorderDisplay(root->right);
    }
}

Node *ReadUsers(Node *root) // Read Users in BST
{
    User s;
    char name[100];
    char pass[100];
    FILE *f = fopen("Users.txt", "r");
    if (f == NULL)
    {
        fprintf(stderr, "An Error has occurred...\nError Number: %d\n", errno);
        fprintf(stderr, "Error Message: %s\n", strerror(errno));
        return errno;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);
    char *tmp = (char *)malloc(sizeof(char) * (size + 1));
    if (tmp == NULL)
    {
        fprintf(stderr, "An Error has occurred...\nError Number: %d\n", errno);
        fprintf(stderr, "Error Message: %s\n", strerror(errno));
        fclose(f);
        return errno;
    }
    while (fgets(tmp, size, f) != NULL)
    {
        char *token = strtok(tmp, ",");
        strcpy(name, token);
        token = strtok(NULL, "\n");
        strcpy(pass, token);
        s = newUser(name, pass);
        root = insert(root, s);
    }
    free(tmp);
    fclose(f);
    return root;
}

int login(Node *root)
{
    User s;
    char name[100];
    char pass[100];
    int selection;
    do
    {
        selection = 0;
        Print_In_X(50, "Enter Username: ");
        fgets(name, sizeof(name), stdin);
        Print_In_X(50, "Enter Password: ");
        fgets(pass, sizeof(pass), stdin);
        name[strlen(name) - 1] = '\0';
        pass[strlen(pass) - 1] = '\0';
        s = newUser(name, pass);
        Node *found = Search(root, s);
        if (found == NULL)
        {
            Print_In_X(50, "Incorrect Username or Password.\n");
            do
            {
                Print_In_X(50, "Choose an option:\n");
                Print_In_X(50, "1-Try Again\n");
                Print_In_X(50, "2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    Print_In_X(50, "Invalid Selection\n");
            } while (selection != 1 && selection != 2);
            if (selection == 2)
            {
                FreeUser(s);
                exit(0);
            }
        }
        else
        {
            if (strcmp(pass, found->s.password) != 0)
            {
                Print_In_X(50, "Incorrect Username or Password.\n");
                do
                {
                    Print_In_X(50, "Choose an option:\n");
                    Print_In_X(50, "1-Try Again\n");
                    Print_In_X(50, "2-Exit\n");
                    scanf("%d", &selection);
                    getchar();
                    if (selection != 1 && selection != 2)
                        Print_In_X(50, "Invalid Selection\n");
                } while (selection != 1 && selection != 2);
                if (selection == 2)
                {
                    FreeUser(s);
                    exit(0);
                }
            }
            else
            {
                Print_In_X(50, "Logged In Successfully\n");
                FreeUser(s);
                return 1;
            }
        }
    } while (selection == 1);
}

int main(void)
{
    Node *root = NULL;
    root = ReadUsers(root);
    if (root == NULL)
    {
        Print_In_X(50, "An Error has occurred...\n");
        Print_In_X(50, "Cannot Read Users File.\n");
        return 1;
    }
    Print_In_X(50, "=====================================================\n");
    Print_In_X(50, "\tWelcome To Bus Reservation System\n");
    Print_In_X(50, "=====================================================\n");
    int selection;
    do
    {
        Print_In_X(50, "Choose an Option:\n");
        Print_In_X(50, "1-Login\n");
        Print_In_X(50, "2-Exit\n");
        scanf("%d", &selection);
        getchar();
        if (selection != 1 && selection != 2)
            Print_In_X(50, "Invalid Selection.\n");
    } while (selection != 1 && selection != 2);
    if (selection == 1)
    {
        int x = login(root);
    }
    else
        return 0;
}