#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie {
    char title[50];
    char genre[30];
    float rating;
    int popularity;
};

struct Node {
    struct Movie movie;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(struct Movie movie) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->movie = movie;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insertMovie(struct Node* root, struct Movie movie) {
    if (root == NULL) return createNode(movie);
    if (movie.popularity < root->movie.popularity)
        root->left = insertMovie(root->left, movie);
    else
        root->right = insertMovie(root->right, movie);
    return root;
}

void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Title: %s, Genre: %s, Rating: %.1f, Popularity: %d\n",
               root->movie.title, root->movie.genre, root->movie.rating, root->movie.popularity);
        inOrder(root->right);
    }
}

struct Node* searchByTitle(struct Node* root, char* title) {
    if (root == NULL) return NULL;
    struct Node* leftSearch = searchByTitle(root->left, title);
    if (leftSearch != NULL) return leftSearch;
    if (strcmp(root->movie.title, title) == 0) return root;
    return searchByTitle(root->right, title);
}

struct Node* findMin(struct Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

struct Node* deleteMovie(struct Node* root, char* title) {
    if (root == NULL) return root;
    if (strcmp(title, root->movie.title) < 0)
        root->left = deleteMovie(root->left, title);
    else if (strcmp(title, root->movie.title) > 0)
        root->right = deleteMovie(root->right, title);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMin(root->right);
        root->movie = temp->movie;
        root->right = deleteMovie(root->right, temp->movie.title);
    }
    return root;
}

int main() {
    struct Node* root = NULL;
    int choice;
    char title[50];

    while (1) {
        printf("\nChoose an action:\n");
        printf("1. Insert Movie\n2. Search Movie by Title\n3. Display All Movies\n4. Delete Movie\n5. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            struct Movie movie;
            printf("Enter title: ");
            scanf(" %[^\n]s", movie.title);
            printf("Enter genre: ");
            scanf(" %[^\n]s", movie.genre);
            printf("Enter rating: ");
            scanf("%f", &movie.rating);
            printf("Enter popularity: ");
            scanf("%d", &movie.popularity);
            root = insertMovie(root, movie);
        } 
        else if (choice == 2) {
            printf("Enter title to search: ");
            scanf(" %[^\n]s", title);
            struct Node* found = searchByTitle(root, title);
            if (found) {
                printf("Found: %s, %s, %.1f, %d\n", found->movie.title, found->movie.genre, found->movie.rating, found->movie.popularity);
            } else {
                printf("Movie not found\n");
            }
        } 
        else if (choice == 3) {
            printf("Movies in collection:\n");
            inOrder(root);
        } 
        else if (choice == 4) {
            printf("Enter title to delete: ");
            scanf(" %[^\n]s", title);
            root = deleteMovie(root, title);
            printf("Movie deleted (if it existed)\n");
        } 
        else if (choice == 5) {
            break;
        } 
        else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}
