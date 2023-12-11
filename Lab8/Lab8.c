#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struktura èvora binarnog stabla
struct _node;
typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;

Position createNode(int value);
Position insert(Position root, int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int levelOrder(Position root);
Position search(Position root, int value);
Position deleteNode(Position root, int value);

int main() {
    /*Node head = {
        .value = 0,
        .left = NULL,
        .right = NULL,
    };*/

    Position root = NULL;

    int rootValue = 0;
    printf("\033[0;32mEnter root value: \033[0m");
    scanf("%d", &rootValue);
    root = insert(root, rootValue);

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Insert node\n");
        printf("2 - Search node\n");
        printf("3 - Delete node\n");
        printf("4 - Print preorder\n");
        printf("5 - Print inorder\n");
        printf("6 - Print postorder\n");
        printf("7 - Print level order\n");
        printf("8 - exit\n");

        char choice[10] = { 0 };
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            int value = 0;
            printf("\033[0;32mEnter value: \033[0m");
            scanf("%d", &value);
            insert(root, value);
        }
        else if (strcmp(choice, "2") == 0) {
            int value = 0;
            Position result = NULL;
            printf("\033[0;32mEnter value: \033[0m");
            scanf("%d", &value);
            result = search(root, value);
            if (result != NULL)
                printf("\033[0;32mNode %d is found.\033[0m\n", value);
            else
                printf("\033[0;32mNode %d is not found.\033[0m\n", value);
        }
        else if (strcmp(choice, "3") == 0) {
            int value = 0;
            printf("\033[0;32mEnter value: \033[0m");
            scanf("%d", &value);
            deleteNode(root, value);
        }
        else if (strcmp(choice, "4") == 0) {
            printf("\033[0;32mPreorder: \033[0m");
            preorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "5") == 0) {
            printf("\033[0;32mInorder: \033[0m");
            inorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "6") == 0) {
            printf("\033[0;32mPostorder: \033[0m");
            postorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "7") == 0) {
            printf("\033[0;32mLevel-order: \033[0m");
            levelOrder(root);
            printf("\n");
        }
        else if (strcmp(choice, "8") == 0) {
            printf("\033[0;32mExiting the program.\033[0m\n");
            break;
        }
        else {
            printf("\033[0;31mInvalid choice. Please enter a valid option.\033[0m\n");
        }
    }

    return EXIT_SUCCESS;
}

Position createNode(int value) {
    Position newNode = NULL;
    newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Can't allocate memory!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Position insert(Position root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value)
        root->right = insert(root->right, value);

    return root;
}

int inorder(Position root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(Position root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(Position root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

int levelOrder(Position root) {
    if (root == NULL)
        return;

    // Red za èekanje èvorova koji se trebaju posetiti
    Position queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Position current = queue[front++];

        printf("%d ", current->value);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
    return EXIT_SUCCESS;
}

Position search(Position root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);

    return search(root->right, value);
}

Position deleteNode(Position root, int value) {
    if (root == NULL)
        return root;

    // Pronalazak èvora koji se treba obrisati
    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        // Èvor sa samo jednim ili bez dece
        if (root->left == NULL) {
            Position temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Position temp = root->left;
            free(root);
            return temp;
        }

        // Èvor sa dvoje dece, pronaði najmanji èvor u desnom podstablu (naslednika)
        Position temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        // Kopiranje vrednosti najmanjeg èvora u trenutni èvor
        root->value = temp->value;

        // Brisanje najmanjeg èvora iz desno podstabla
        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}
