#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CART_SIZE 50

// Structure for a product
struct Product {
    int id;
    char name[100];
    float price;
    struct Product* next;
};

// Function to create a new product
struct Product* createProduct(int id, const char* name, float price) {
    struct Product* newProduct = (struct Product*)malloc(sizeof(struct Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->price = price;
    newProduct->next = NULL;
    return newProduct;
}

// productList-linked list to store the products
struct Product* productList = NULL;

// Structure for a shopping cart
struct CartItem {
    int productId;
    int quantity;
};

struct CartItem shoppingCart[MAX_CART_SIZE];
int cartSize = 0;

// Function to add a product to the product list (can add it in the main code itself as user cant change)
void addProduct(int id, const char* name, float price) {
    struct Product* newProduct = createProduct(id, name, price);
    newProduct->next = productList;
    productList = newProduct;
}

// Function to display the list of products available to buy from
void displayProducts() {
    struct Product* current = productList;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Price: %.2f\n", current->id, current->name, current->price);
        current = current->next;
    }
}

// Function to search for a product by ID
struct Product* findProduct(int productId) {
    struct Product* current = productList;
    while (current != NULL) {
        if (current->id == productId) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to add a product to the shopping cart
void addToCart(int productId, int quantity) {
    struct Product* product = findProduct(productId);
    if (product == NULL) {
        printf("Product not found.\n");
        return;
    }

    if (cartSize >= MAX_CART_SIZE) {
        printf("Shopping cart is full.\n");
        return;
    }

    shoppingCart[cartSize].productId = productId;
    shoppingCart[cartSize].quantity = quantity;
    cartSize++;
    printf("%d %s(s) added to the shopping cart.\n", quantity, product->name);
}

void deletefromcart(int productId){
    int prodfound=0;
    int x=-1;
    for (int i=0;i<cartSize; i++){
        if (shoppingCart[i].productId == productId){
            prodfound=1;
            x=i;
            break;
        }
    }
    if (prodfound){
        for (int i=x;i<cartSize-1;i++){
            shoppingCart[i]=shoppingCart[i+1];

        }
        cartSize--;
        printf("The product is removed from the cart");
    }
    else{
        printf("The product is not in the cart.\n");
    }

}

// Function to display the shopping cart
void displayCart() {
    printf("Shopping Cart Contents:\n");
    for (int i = 0; i < cartSize; i++) {
        struct Product* product = findProduct(shoppingCart[i].productId);
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               product->id, product->name, product->price, shoppingCart[i].quantity);
    }
}

// function to generate the bill-shows th total cost based on products price and quantity

float GenerateBill(){
    float total=0.0;
    for (int i=0;i<cartSize;i++){
        struct Product *product = findProduct(shoppingCart[i].productId);
        if (product != NULL){
            total += shoppingCart[i].quantity * product->price;
        }
    }
    return total;
}

int main() {
    // Adding the products manually in the code
    addProduct(1, "Reynolds Trimax", 60.0);
    addProduct(2, "Classmate 160 pages long notebook", 100.0);
    addProduct(3, "Wildcraft bag", 500.0);
    addProduct(4, "Tennis ball", 50.0);
    addProduct(5, "Cadbury Dairy milk", 20.0);
    addProduct(6, "Tupperware water bottle", 200.0);
    addProduct(7, "Faber Castel Colour pencils", 120.0);
    addProduct(8, "Camlin Geometry Box", 80.0);
    addProduct(9, "Casio fx991-ex", 1200.0);
    addProduct(10, "Boat earphones", 800.0);


    
    int choice;
    do {
        printf("Menu:\n");
        printf("1. Display all Products\n");
        printf("2. Search for a Product\n");
        printf("3. Add an item to Shopping Cart\n");
        printf("4. Delete an item from cart\n");
        printf("5. Display the Shopping Cart\n");
        printf("6. Generate Bill\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayProducts();
                break;

            case 2:
                // Implement search for a product by ID here
                int productId;
                printf("Enter the product ID to search: ");
                scanf("%d", &productId);
                struct Product* foundProduct = findProduct(productId);
                if (foundProduct != NULL) {
                    printf("Found Product:\n");
                    printf("ID: %d, Name: %s, Price: %.2f\n", foundProduct->id, foundProduct->name, foundProduct->price);
                } else {
                    printf("Product not found.\n");
                }
                break;

            case 3:
                // Implement adding products to the shopping cart here
                int cartProductId, quantity;
                printf("Enter the product ID to add to the cart: ");
                scanf("%d", &cartProductId);
                printf("Enter the quantity: ");
                scanf("%d", &quantity);
                addToCart(cartProductId, quantity);
                break;

            case 4:
                int Id;
                printf("Enter the Id of the product to delete from the cart: ");
                scanf("%d",&Id);
                deletefromcart(Id);
                break;


            case 5:
                displayCart();
                break;

            case 6:
                 printf("Your Total Bill is: Rs %.2f\n", GenerateBill());
                 break;

            case 7:
                printf("Thank You!!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    // Freezing the product list for good memory management
    struct Product* current = productList;
    while (current != NULL) {
        struct Product* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
