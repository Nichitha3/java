#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent customer information
struct Customer {
    char name[50];
    char address[100];
    char email[50];
};

// Union to represent different types of products
union Product {
    char productName[50];
    char serviceType[50];
};

// Structure to represent a purchase
struct Purchase {
    union Product product;
    int quantity;
    float price;
};

// Function prototypes
void addCustomer(struct Customer *customer);
void addPurchase(struct Purchase **purchases, int *numPurchases);
float calculateTotal(struct Purchase *purchases, int numPurchases);
void printInvoice(struct Customer customer, struct Purchase *purchases, int numPurchases);

int main() {
    struct Customer customer;
    struct Purchase *purchases = NULL;
    int numPurchases = 0;
    int choice;

    do {
        // Display menu
        printf("\nCustomer Billing System\n");
        printf("1. Add Customer\n");
        printf("2. Add Purchase\n");
        printf("3. Calculate Total\n");
        
        printf("4. Print Invoice\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer(&customer);
                break;
            case 2:
                addPurchase(&purchases, &numPurchases);
                break;
            case 3: {
                float total = calculateTotal(purchases, numPurchases);
                printf("Total Purchase Amount: $%.2f\n", total);
                break;
            }
            case 4:
                printInvoice(customer, purchases, numPurchases);
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    // Free dynamically allocated memory
    free(purchases);

    return 0;
}

// Function to add customer information
void addCustomer(struct Customer *customer) {
    printf("Enter customer name: ");
    scanf("%s", customer->name);
    printf("Enter customer address: ");
    scanf("%s", customer->address);
    printf("Enter customer email: ");
    scanf("%s", customer->email);
    printf("Customer information added successfully!\n");
}

// Function to add a purchase
void addPurchase(struct Purchase **purchases, int *numPurchases) {
    // Allocate memory for a new purchase
    *purchases = realloc(*purchases, (*numPurchases + 1) * sizeof(struct Purchase));

    // Check if memory allocation is successful
    if (*purchases == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    struct Purchase *newPurchase = &(*purchases)[*numPurchases];

    // Get product information
    printf("Enter product name or service type: ");
    scanf("%s", newPurchase->product.productName);

    // Get quantity and price
    printf("Enter quantity: ");
    scanf("%d", &newPurchase->quantity);
    printf("Enter price per unit: ");
    scanf("%f", &newPurchase->price);

    (*numPurchases)++;
    printf("Purchase added successfully!\n");
}

// Function to calculate the total purchase amount
float calculateTotal(struct Purchase *purchases, int numPurchases) {
    float total = 0.0;

    for (int i = 0; i < numPurchases; i++) {
        total += purchases[i].quantity * purchases[i].price;
    }

    return total;
}

// Function to print the invoice
void printInvoice(struct Customer customer, struct Purchase *purchases, int numPurchases) {
    printf("\nInvoice\n");
    printf("Customer Name: %s\n", customer.name);
    printf("Customer Address: %s\n", customer.address);
    printf("Customer Email: %s\n", customer.email);

    printf("\nPurchase Details\n");
    for (int i = 0; i < numPurchases; i++) {
        printf("Product/Service: %s\n", purchases[i].product.productName);
        printf("Quantity: %d\n", purchases[i].quantity);
        printf("Price per unit: $%.2f\n", purchases[i].price);
        printf("Subtotal: $%.2f\n\n", purchases[i].quantity * purchases[i].price);
    }

    float total = calculateTotal(purchases, numPurchases);
    printf("Total Purchase Amount: $%.2f\n", total);
}
