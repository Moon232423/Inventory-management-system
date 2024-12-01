#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For system() function

#define MAX_USERS 50
#define MAX_ITEMS 100
#define MAX_ORDERS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    int itemId;
    int quantity;
    float totalCost;
} Order;

// Global Variables
Item inventory[MAX_ITEMS];
User users[MAX_USERS];
Order orders[MAX_ORDERS];

int itemCount = 0;
int userCount = 0;
int orderCount = 0;

// Admin Credentials
#define ADMIN_USERNAME "mmp"
#define ADMIN_PASSWORD "017"

// Function Prototypes
void registerUser();
int userLogin();
int adminLogin();
void clearScreen();
void saveUsers();
void loadUsers();
void adminMenu();
void userMenu();
void addItem();
void viewItems();
void displayItems();
void updateItem();
void deleteItem();
void orderItem();
void checkout();
void lowStockAlert();
void searchItem();
void removeUser();
void salesReport();
void Inventory();

// Main Function
int main() {
    int choice;

    // Initialize Inventory with Default Items
    Inventory();

    // Load existing users from file
    loadUsers();

    while (1) {
        clearScreen();
        printf("---------------------------- Main Menu --------------------------------");
        printf("\n------------------------------------------------------------------------\n");
        printf("\t \t \t 1. Register User\n");
        printf("\t \t \t 2. User Login\n");
        printf("\t \t \t 3. Admin Login\n");
        printf("\t \t \t 4. Exit\n");
        printf("\n------------------------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (userLogin()) userMenu();
                break;
            case 3:
                if (adminLogin()) adminMenu();
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Clear Screen Function
void clearScreen() {

    system("cls");


}

// Load Users from File
void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return; // No users found, continue with an empty list
    }

    while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
        userCount++;
    }
    fclose(file);
}

// Save Users to File
void saveUsers() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error saving users.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }
    fclose(file);
}

// Register a New User
void registerUser() {
    char username[50], password[50];

    clearScreen();
    printf("\n--- Register User ---\n");
    printf("Enter username: ");
    scanf("%s", username);

    // Check if username already exists
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("This username is already taken. Please choose another.\n");
            getchar(); getchar(); // Wait for Enter
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", password);

    // Add new user to the array
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    saveUsers();

    printf("User registered successfully!\n");
    getchar(); getchar(); // Wait for Enter
}

// User Login
int userLogin() {
    char username[50], password[50];

    clearScreen();
    printf("\n User Login \n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful! Press Enter to continue...\n");
            getchar(); getchar(); // Wait for Enter
            return 1;
        }
    }

    printf("Invalid login. Try again.\n");
    getchar(); getchar(); // Wait for Enter
    return 0;
}

// Admin Login
int adminLogin() {
    char username[50], password[50];

    clearScreen();
    printf("\n--- Admin Login ---\n");
    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Admin login successful! Press Enter to continue...\n");
        getchar(); getchar(); // Wait for Enter
        return 1;
    }

    printf("Invalid admin credentials. Try again.\n");
    getchar(); getchar(); // Wait for Enter
    return 0;
}

// Admin Menu
void adminMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n---------------------------Admin Menu ----------------------------\n");
        printf("\n------------------------------------------------------------------\n");

        printf("\t \t \t1. View Items\n");
        printf("\t \t \t2. Add Item\n");
        printf("\t \t \t3. Update Item\n");
        printf("\t \t \t4. Delete Item\n");
        printf("\t \t \t5. Search Item\n");
        printf("\t \t \t6. Low Stock Alert\n");
        printf("\t \t \t7. Remove User\n");
        printf("\t \t \t8. Sales Report\n");
        printf("\t \t \t9. Logout\n");
        printf("\n------------------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewItems();
                break;
            case 2:
                addItem();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                deleteItem();
                break;
            case 5:
                searchItem();
                break;
            case 6:
                lowStockAlert();
                break;
            case 7:
                removeUser();
                break;
            case 8:
                salesReport();
                break;
            case 9:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// User Menu
void userMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n-------------------------------- User Menu------------------------------------\n");
        printf("\n-------------------------------------------------------------------------------\n");

        printf("\t \t \t1.View Items\n");
        printf("\t \t \t2. Order Items\n");
        printf("\t \t \t3. Checkout\n");
        printf("\t \t \t4. Low Stock Alerts\n");
        printf("\t \t \t5. Return to Main Menu\n");
        printf("\n------------------------------------------------------------------\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewItems();
                break;
            case 2:
                orderItem();
                break;
            case 3:
                checkout();
                break;

            case 4:
                lowStockAlert();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}



void Inventory() {
    strcpy(inventory[0].name, "Processor");
    inventory[0].id = 1;
    inventory[0].quantity = 10;
    inventory[0].price = 200.50;

    strcpy(inventory[1].name, "Motherboard");
    inventory[1].id = 2;
    inventory[1].quantity = 15;
    inventory[1].price = 150.75;

    strcpy(inventory[2].name, "RAM 16GB");
    inventory[2].id = 3;
    inventory[2].quantity = 20;
    inventory[2].price = 75.99;

    strcpy(inventory[3].name, "SSD 512GB");
    inventory[3].id = 4;
    inventory[3].quantity = 25;
    inventory[3].price = 60.30;

    strcpy(inventory[4].name, "Power Supply");
    inventory[4].id = 5;
    inventory[4].quantity = 10;
    inventory[4].price = 45.99;

    strcpy(inventory[5].name, "Graphics Card");
    inventory[5].id = 6;
    inventory[5].quantity = 8;
    inventory[5].price = 499.99;

    strcpy(inventory[6].name, "Cooling Fan");
    inventory[6].id = 7;
    inventory[6].quantity = 30;
    inventory[6].price = 25.50;

    strcpy(inventory[7].name, "HDD 1TB");
    inventory[7].id = 8;
    inventory[7].quantity = 12;
    inventory[7].price = 55.75;

    strcpy(inventory[8].name, "Case");
    inventory[8].id = 9;
    inventory[8].quantity = 5;
    inventory[8].price = 70.00;

    strcpy(inventory[9].name, "Keyboard");
    inventory[9].id = 10;
    inventory[9].quantity = 50;
    inventory[9].price = 20.99;

    itemCount = 10; // Update the itemCount to reflect the initial inventory
}




// View Items Function (Unchanged)
void viewItems() {
    if (itemCount == 0) {
        printf("No items in inventory.\n");
        getchar(); getchar();
        return;
    }

    printf("\n--- Inventory Items ---\n");
    printf("ID\tName\t\t\tQuantity\tPrice\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%-20s\t%d\t\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
    getchar(); getchar();
}

// Add Item Function (Unchanged)
void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more items.\n");
        getchar();
        return;
    }

    printf("\n--- Add Item ---\n");

    printf("Enter item ID: ");
    scanf("%d", &inventory[itemCount].id);
    getchar(); // Clear newline from the buffer

    printf("Enter item name: ");
    gets(inventory[itemCount].name); // Read string with spaces

    printf("Enter quantity: ");
    scanf("%d", &inventory[itemCount].quantity);

    printf("Enter price: ");
    scanf("%f", &inventory[itemCount].price);

    itemCount++;
    printf("Item added successfully!\n");
    getchar(); // Pause for Enter
}


void updateItem() {
    int id, found = 0;

    printf("\n--- Update Item ---\n");
    printf("Enter item ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", inventory[i].name);
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);

            printf("Item updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }

    getchar(); getchar();
}
void deleteItem() {
    int id, found = 0;

    printf("\n--- Delete Item ---\n");
    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            for (int j = i; j < itemCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            printf("Item deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }

    getchar(); getchar();

}

void searchItem() {
    char searchName[50];
    int found = 0;

    printf("\n--- Search Item ---\n");
    printf("Enter item name: ");
    scanf("%s", searchName);

    for (int i = 0; i < itemCount; i++) {
        if (strstr(inventory[i].name, searchName)) {
            printf("ID: %d, Name: %s, Quantity: %d, Price: %.2f\n",
                   inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No items found matching '%s'.\n", searchName);
    }

    getchar(); getchar();
}


void orderItem() {
    int id, quantity, found = 0;
    char mobileNumber[15]; // To store the mobile number

    printf("\n--- Order Item ---\n");
    printf("Enter item ID: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (quantity > inventory[i].quantity) {
                printf("Not enough stock available.\n");
            } else {
                // Collect mobile number
                printf("Enter your mobile number: ");
                scanf("%s", mobileNumber);

                // Store order details
                orders[orderCount].itemId = id;
                orders[orderCount].quantity = quantity;
                orders[orderCount].totalCost = quantity * inventory[i].price;
                orderCount++;

                // Update inventory
                inventory[i].quantity -= quantity;

                printf("Order placed successfully!\n");
                printf("Please, checkout your products\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }

    getchar(); getchar(); // Wait for user to press Enter
}

void checkout() {
    float total = 0;

    printf("\n--- Checkout ---\n");

    if (orderCount == 0) {
        printf("No items ordered yet.\n");
        return;  // Exit if no orders exist
    }

    printf("Item ID\tQuantity\tTotal Cost\n");
    printf("-------\t--------\t-----------\n");

    // Print each order's details and calculate total cost
    for (int i = 0; i < orderCount; i++) {
        printf("%d\t\t%d\t\t%.2f\n", orders[i].itemId, orders[i].quantity, orders[i].totalCost);
        total += orders[i].totalCost;
    }

    // Find and print the purchased item names and total cost
    printf("\nTotal Cost: %.2f\n", total);
    printf("Thank you for your purchase!\n");

    getchar();   getchar();// Wait for user input
}


void removeUser() {
    char username[50];
    int found = 0;

    printf("\n--- Remove User ---\n");
    printf("Enter username to remove: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            found = 1;
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            saveUsers();
            printf("User removed successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("User '%s' not found.\n", username);
    }

    getchar(); getchar();
}
void lowStockAlert() {
    printf("\n--- Low Stock Alert ---\n");

    int alertFound = 0;
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].quantity < 5) {
            printf("ID: %d, Name: %s, Quantity: %d\n", inventory[i].id, inventory[i].name, inventory[i].quantity);
            alertFound = 1;
        }
    }

    if (!alertFound) {
        printf("No low stock items.\n");
    }

    getchar(); getchar();
}
void salesReport() {
    printf("\n--- Sales Report ---\n");

    if (orderCount == 0) {
        printf("No sales to report.\n");
        return;  // Exit early if no sales have been made
    }

    printf("Item Name\tItem ID\tQuantity\tTotal Cost\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < orderCount; i++) {
        // Directly print the order details
        printf("%s\t%d\t%d\t%.2f\n", inventory[orders[i].itemId - 1].name, orders[i].itemId, orders[i].quantity, orders[i].totalCost);
    }

    getchar(); getchar(); // Wait for user to press Enter
}

