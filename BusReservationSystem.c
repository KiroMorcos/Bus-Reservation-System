#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
int NoOfUsers = 0;

typedef struct
{
    char *username;
    char *password;
} User;

typedef struct
{
    char *name;
    int age;
    bool reserved;
    int bus_number;
    int seat_number;
} Passenger;

typedef struct
{
    int SeatNumber;
    bool free;
    char *Name;
} Seat;

typedef struct
{
    int numSeats;
    int freeSeats;
    double stdFee;
    char *Destination;
    time_t departureTime;
    time_t arrivalTime;
    Seat *seats;
} Bus;

typedef struct
{
    User user;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(User s)
{
    Node *n = malloc(sizeof(Node));
    if (n == NULL)
    {
        printf("Error...Cannot Allocate Memory.\n");
        exit(1);
    }
    n->user = s;
    n->left = n->right = NULL;
    return n;
}

Node *insert(Node *root, User s)
{
    if (root == NULL)
        return newNode(s);
    else if (strcasecmp(s.username, root->user.username) < 0)
        root->left = insert(root->left, s);
    else if (strcasecmp(s.username, root->user.username) > 0)
        root->right = insert(root->right, s);
    return root;
}

Node *Search(Node *root, char *username)
{
    if (root == NULL)
        return NULL;
    if (strcasecmp(root->user.username, username) == 0)
        return root;
    if (strcasecmp(username, root->user.username) < 0)
        return Search(root->left, username);
    if (strcasecmp(username, root->user.username) > 0)
        return Search(root->right, username);
}

Node *ReadUsers(Node *root)
{
    User *s = malloc(sizeof(User));
    if (s == NULL)
    {
        printf("Error...Cannot Allocate Memory.\n");
        exit(2);
    }
    FILE *f = fopen("Users.txt", "r");
    if (f == NULL)
    {
        printf("Error...Cannot Open Users File.\n");
        exit(3);
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);
    char temp[size + 1];
    while (fgets(temp, size, f) != NULL)
    {
        char *token = strtok(temp, ",");
        s->username = malloc(strlen(token) + 1);
        if (s->username == NULL)
        {
            printf("Error...Cannot Allocate Memory.\n");
            exit(4);
        }
        strcpy(s->username, token);
        token = strtok(NULL, ",");
        s->password = malloc(strlen(token) + 1);
        if (s->password == NULL)
        {
            printf("Error...Cannot Allocate Memory.\n");
            exit(5);
        }
        strcpy(s->password, token);
        NoOfUsers++;
        root = insert(root, *s);
    }
    fclose(f);
    return root;
}

int main(void)
{
    int selection;
    Node *root = NULL;
    root = ReadUsers(root);
    printf("=====================================================\n");
    printf("\tWelcome To Bus Reservation System\n");
    printf("=====================================================\n");
    do
    {
        printf("Choose an Option:\n");
        printf("1-Login\n2-Exit\n");
        scanf("%d", &selection);
        getchar();
        if (selection != 1 && selection != 2)
            printf("Invalid Selection.\n");
    } while (selection != 1 && selection != 2);
    if (selection == 1)
    {
        //Login();
    }
    else
        return 0;
}