
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For system() function

#define MaxUsers 50
#define MaxItems 100
#define MaxOrders 100

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
     char username[50];
} Order;

// Global Variables
Item inventory[MaxUsers];
User users[MaxItems];
Order orders[MaxOrders];

int itemCount = 0;
int userCount = 0;
int orderCount = 0;

// Admin Credentials
#define adminUsername "mmp"
#define adminPassword "017"

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
void addUser();

// Main Function
int main() {
    int choice;

    // Initialize Inventory with Default Items
    Inventory();

    // Load existing users from file
    loadUsers();

    while (1) {
        clearScreen();
        printf("=========================== InVentory Management System ===========================");
        printf("\n=================================================================================\n");
        printf("\t \t \t 1. Register User\n");
        printf("\t \t \t 2. User Login\n");
        printf("\t \t \t 3. Admin Login\n");
        printf("\t \t \t 4. Exit\n");
        printf("\n----------------------------------------------------------------------------------\n");
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
                clearScreen();
            printf("This username is already taken. Please choose another.\n\n");
        printf("press Enter to Back.......");
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
clearScreen();
    printf("User registered successfully!\n\n");
     printf("press Enter to Back.......");

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
                clearScreen();
            printf("Login successful!\n ...Press Enter to continue...");
            getchar(); getchar();
            return 1;
        }
    }
clearScreen();
    printf("Invalid login. Try again.\n\n");
    printf("press Enter to Back.......");

    getchar(); getchar();
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

    if (strcmp(username, adminUsername) == 0 && strcmp(password,adminPassword) == 0) {
            clearScreen();
        printf("\tAdmin login successful!\n\n Press Enter to continue...");
        getchar(); getchar();
        return 1;
    }

    printf("Invalid admin credentials. Try again.\n");
    getchar(); getchar();
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
        printf("\t \t \t9. Add user\n");
        printf("\t \t \t10.Logout\n");
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
                addUser();
                break;

            case 10:
                 return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}


void userMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n-------------------------------- User Menu------------------------------------\n");
        printf("\n-------------------------------------------------------------------------------\n");

        printf("\t \t \t1. View Items\n");
        printf("\t \t \t2. Order Items\n");
        printf("\t \t \t3. Checkout\n");
        printf("\t \t \t4. Return to Main Menu\n");
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
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}



void Inventory() {
    strcpy(inventory[0].name, "Processor");
    inventory[0].id = 1001;
    inventory[0].quantity = 10;
    inventory[0].price = 20000;

    strcpy(inventory[1].name, "Motherboard");
    inventory[1].id = 1002;
    inventory[1].quantity = 15;
    inventory[1].price = 15000;

    strcpy(inventory[2].name, "RAM 16GB");
    inventory[2].id = 1003;
    inventory[2].quantity = 20;
    inventory[2].price = 3000;

    strcpy(inventory[3].name, "SSD 512GB");
    inventory[3].id =1004;
    inventory[3].quantity = 25;
    inventory[3].price = 6000;

    strcpy(inventory[4].name, "Power Supply");
    inventory[4].id = 1005;
    inventory[4].quantity = 10;
    inventory[4].price = 4599;

    strcpy(inventory[5].name, "Graphics Card");
    inventory[5].id = 1006;
    inventory[5].quantity = 8;
    inventory[5].price = 47999;

    strcpy(inventory[6].name, "Cooling Fan");
    inventory[6].id = 1007;
    inventory[6].quantity = 30;
    inventory[6].price = 2550;

    strcpy(inventory[7].name, "HDD 1TB");
    inventory[7].id = 1008;
    inventory[7].quantity = 12;
    inventory[7].price = 2000;

    strcpy(inventory[8].name, "Case");
    inventory[8].id = 1009;
    inventory[8].quantity = 5;
    inventory[8].price = 3000;

    strcpy(inventory[9].name, "Keyboard");
    inventory[9].id = 1010;
    inventory[9].quantity = 50;
    inventory[9].price = 2099;

    itemCount = 10;
}





void viewItems() {
    clearScreen();
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
    printf("\nPlease Enter to continue.......");
    getchar(); getchar();
}

// Add Item Function (Unchanged)
void addItem() {

    clearScreen();

    if (itemCount >= MaxItems) {
        printf("Inventory is full. Cannot add more items.\n");
        getchar();
        return;
    }

    printf("\n--- Add Item ---\n");

    printf("Enter item ID: ");
    scanf("%d", &inventory[itemCount].id);
    getchar();

    printf("Enter item name: ");
    gets(inventory[itemCount].name);

    printf("Enter quantity: ");
    scanf("%d", &inventory[itemCount].quantity);

    printf("Enter price: ");
    scanf("%f", &inventory[itemCount].price);

    itemCount++;
    printf("Item added successfully!\n");
    getchar();
}


void updateItem() {
        clearScreen();
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
               clearScreen();
            printf("Item updated successfully!\n");
            break;
        }

    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }
printf("\nPlease Enter to Back.......");
    getchar(); getchar();
}
void deleteItem() {

        clearScreen();
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
                clearScreen();
            printf("Item deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }
     printf("\nPlease Enter to Back.......");
    getchar(); getchar();

}

void searchItem() {
     clearScreen();
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
     printf("\nPlease Enter to Back.......");
    getchar(); getchar();
}

void orderItem() {
    clearScreen();
    viewItems();

    int id, quantity, found = 0;
    char mobileNum[12]; // Allow for the null terminator
    const char *paymentMethod;

    printf("\n--- Order Item ---\n");
    printf("Enter item ID: ");
    scanf("%d", &id);
    getchar();  // Consume the newline character left by scanf

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            getchar();
            if (quantity > inventory[i].quantity) {
                printf("Not enough stock available.\n");
            } else {

                printf("Enter your mobile number:\n ");
                scanf("%s", mobileNum);

                // Store order details
                orders[orderCount].itemId = id;
                orders[orderCount].quantity = quantity;
                orders[orderCount].totalCost = quantity * inventory[i].price;
                orderCount++;

                // Update inventory
                inventory[i].quantity -= quantity;

                // Payment Method Prompt
                clearScreen();
                printf("\n--- Order placed successfully! ---\n\n");
                printf("Please, choose a payment method to complete the order.\n");

                printf("1. Bkash\n");
                printf("2. Nagad\n");
                printf("3. Rocket\n");
                printf("4. Bank Card\n");
                printf("Enter your choice (1-4): ");
                int paymentChoice;
                scanf("%d", &paymentChoice);

                switch (paymentChoice) {
                    case 1:
                        paymentMethod = "Bkash";
                        break;
                    case 2:
                        paymentMethod = "Nagad";
                        break;
                    case 3:
                        paymentMethod = "Rocket";
                        break;
                    case 4:
                        paymentMethod = "Bank Card";
                        break;
                    default:
                        printf("Invalid payment method. Order canceled.\n");
                        return;
                }

                clearScreen();
                printf("\nPayment Method: %s\n", paymentMethod);
                printf("\t||Payment Successful||\n\n");
                printf(")>> Thank you for your purchase!<<(\n\n");
                 // Wait for user input
            }
            break;
        }
                        printf("\nPress Enter to Back.......");
                        getchar(); getchar();

    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }
    printf("\nPress Enter to Back.......");
    getchar(); getchar();
}

void checkout() {

     clearScreen();
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

       printf("\nTotal Cost: %.2f taka only\n", total);
    printf("\n\t|| Payment Successful ||\n\n");
    printf(")>> Thank you for your purchase! <<(\n\n");

    printf("\nPress Enter to Back.......");

    getchar(); getchar();

}



void removeUser() {
    clearScreen();
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
printf("\nPress Enter to Back.......");

    getchar(); getchar();
}
void lowStockAlert() {
    clearScreen();
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
printf("\nPress Enter to Back.......");

    getchar(); getchar();
}
void salesReport() {
    clearScreen();
    printf("\n--- Sales Report ---\n");

    if (orderCount == 0) {
        printf("No sales to report.\n");
        return;  // Exit early if no sales have been made
    }

    printf("Item Name\tItem ID\tQuantity\tTotal Cost\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < orderCount; i++) {
        // Loop through the inventory to find the item matching the order's itemId
        int found = 0;
        for (int j = 0; j < itemCount; j++) {
            if (inventory[j].id == orders[i].itemId) {
                printf("%s\t%d\t%d\t%.2f\n", inventory[j].name, orders[i].itemId, orders[i].quantity, orders[i].totalCost);
                found = 1;
                break; // Exit the loop once the item is found

            }


        }

        if (!found) {
            printf("Item with ID %d not found in inventory.\n", orders[i].itemId);
        }
    }
printf("\nPress Enter to Back.......");
    getchar(); getchar(); // Wait for user to press Enter
}
void addUser() {
    clearScreen();
    if (userCount >= MaxUsers) {
        printf("User limit reached!\n");
        return;
    }

    printf("Enter username: ");
    scanf("%49s", users[userCount].username);

    printf("Enter password: ");
    scanf("%49s", users[userCount].password);

    userCount++;  //
    printf("User added successfully!\n\n");

     printf("press to Back.......!\n");

      getchar(); getchar();
}


