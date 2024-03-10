#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Structure to represent a reservation
typedef struct Reservation {
    char name[MAX_NAME_LENGTH];
    int tableNumber;
    struct Reservation* next;
} Reservation;

// Structure to represent a restaurant
typedef struct Restaurant {
    int numTables;
    Reservation* head;
    Reservation* tail;
} Restaurant;

// Function to initialize the restaurant
void initRestaurant(Restaurant* restaurant, int numTables) {
    restaurant->numTables = numTables;
    restaurant->head = NULL;
    restaurant->tail = NULL;
}

// Function to add a reservation to the end of the queue
void bookTable(Restaurant* restaurant, const char* name, int tableNumber) {
    if (tableNumber < 1 || tableNumber > restaurant->numTables) {
        printf("Invalid table number\n");
        return;
    }

    // Check if the table is already booked
    Reservation* current = restaurant->head;
    while (current != NULL) {
        if (current->tableNumber == tableNumber) {
            printf("Table %d is already booked\n", tableNumber);
            return;
        }
        current = current->next;
    }

    // Table is available, proceed with booking
    Reservation* newReservation = (Reservation*)malloc(sizeof(Reservation));
    if (newReservation == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    strncpy(newReservation->name, name, MAX_NAME_LENGTH);
    newReservation->tableNumber = tableNumber;
    newReservation->next = NULL;

    if (restaurant->head == NULL) {
        restaurant->head = newReservation;
    } else {
        restaurant->tail->next = newReservation;
    }
    restaurant->tail = newReservation;

    printf("Reservation booked for %s at table %d\n", name, tableNumber);
}


// Function to remove the first reservation from the queue
void cancelReservation(Restaurant* restaurant) {
    if (restaurant->head == NULL) {
        printf("No reservations to cancel\n");
        return;
    }

    Reservation* temp = restaurant->head;
    restaurant->head = restaurant->head->next;
    free(temp);

    printf("Reservation canceled\n");
}

// Function to display all reservations
void displayReservations(const Restaurant* restaurant) {
    printf("Current reservations:\n");
    Reservation* current = restaurant->head;
    while (current != NULL) {
        printf("Name: %s, Table: %d\n", current->name, current->tableNumber);
        current = current->next;
    }
}

// Function to free memory allocated for reservations
void cleanup(Restaurant* restaurant) {
    Reservation* current = restaurant->head;
    while (current != NULL) {
        Reservation* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Restaurant restaurant;
    int numTables;
    printf("Enter number of tables: ");
    scanf("%d", &numTables);

    initRestaurant(&restaurant, numTables);

    int choice;
    do {
        printf("\n1. Book table\n2. Cancel reservation\n3. Display reservations\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[MAX_NAME_LENGTH];
                int tableNumber;
                printf("Enter your name: ");
                scanf("%s", name);
                printf("Enter table number: ");
                scanf("%d", &tableNumber);
                bookTable(&restaurant, name, tableNumber);
                break;
            }
            case 2:
                cancelReservation(&restaurant);
                break;
            case 3:
                displayReservations(&restaurant);
                break;
            case 4:
                cleanup(&restaurant);
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}
