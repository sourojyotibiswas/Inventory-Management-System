#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

// Define the username and password
#define USERNAME "souro"
#define PASSWORD "souro4414"

struct Product
{
	int id;
	char name[MAX_NAME_LENGTH];
	float price;
	int quantity;
};

// Function to validate the login credentials
int authenticate()
{
	char username[50];
	char password[50];

	printf("\n\t\t\tEnter username: ");
	scanf("%s", username);
	printf("\t\t\tEnter password: ");
	scanf("%s", password);

	if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0)
	{
// Clear the screen after successful login
#ifdef _WIN32
		system("cls");
#endif
		return 1; // Authentication successful
	}
	else
	{
		return 0; // Authentication failed
	}
}

// Function to add a new product to the inventory
void createProduct(struct Product inventory[], int *numProducts)
{
	if (*numProducts >= MAX_PRODUCTS)
	{
		printf("\t\t\tInventory is full. Cannot add more products.\n");
		return;
	}

	struct Product newProduct;
	printf("\n\t\t\tEnter product name: ");
	scanf("%s", newProduct.name);
	printf("\t\t\tEnter product price: ");
	scanf("%f", &newProduct.price);
	printf("\t\t\tEnter product quantity: ");
	scanf("%d", &newProduct.quantity);

	newProduct.id = *numProducts + 1; // Assign a unique ID to the new product

	inventory[*numProducts] = newProduct;
	(*numProducts)++;

	printf("\n\t\t\tProduct added to inventory.\n");
}

// Function to display all products in the inventory
void readProducts(struct Product inventory[], int numProducts)
{
	printf("\n\t\t\tProduct List:\n");
	printf("\t\t\tID\tName\tPrice\tQuantity\n");
	for (int i = 0; i < numProducts; i++)
	{
		printf("%d\t%s\t%.2f\t%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
	}
}

// Function to update a product in the inventory
void updateProduct(struct Product inventory[], int numProducts)
{
	int id;
	printf("\n\t\t\tEnter the ID of the product to update: ");
	scanf("%d", &id);

	for (int i = 0; i < numProducts; i++)
	{
		if (inventory[i].id == id)
		{
			printf("\n\t\t\tEnter new product name: ");
			scanf("%s", inventory[i].name);
			printf("\t\t\tEnter new product price: ");
			scanf("%f", &inventory[i].price);
			printf("\t\t\tEnter new product quantity: ");
			scanf("%d", &inventory[i].quantity);
			printf("\t\t\tProduct updated.\n");
			return;
		}
	}

	printf("\n\t\t\tProduct with ID %d not found.\n", id);
}

// Function to delete a product from the inventory
void deleteProduct(struct Product inventory[], int *numProducts)
{
	int id;
	printf("\n\t\t\tEnter the ID of the product to delete: ");
	scanf("%d", &id);

	for (int i = 0; i < *numProducts; i++)
	{
		if (inventory[i].id == id)
		{
			// Shift remaining products to fill the gap
			for (int j = i; j < *numProducts - 1; j++)
			{
				inventory[j] = inventory[j + 1];
			}
			(*numProducts)--;
			printf("\n\t\t\tProduct with ID %d deleted.\n", id);
			return;
		}
	}

	printf("\n\t\t\tProduct with ID %d not found.\n", id);
}

// Function to save the inventory data to a file
void saveInventoryToFile(struct Product inventory[], int numProducts)
{
	FILE *file = fopen("inventory.txt", "w");
	if (file == NULL)
	{
		printf("\n\t\t\tError opening file for writing.\n");
		return;
	}

	for (int i = 0; i < numProducts; i++)
	{
		fprintf(file, "%d %s %.2f %d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
	}

	fclose(file);
	printf("\n\t\t\tInventory data saved to 'inventory.txt'.\n");
}

// main function starts here
int main()
{
	if (authenticate())
	{
		printf("\n\t\t\tSuccesfully Logged in!\n\n");
	}
	else
	{
		printf("\n\t\t\tAuthentication failed. Exiting...\n\n");
		return 1;
	}
	struct Product inventory[MAX_PRODUCTS];
	int numProducts = 0;

	int choice;
	do
	{
		printf("\t\t\tInventory Management System\n\n");
		printf("\t\t\t  1. Add Product\n");
		printf("\t\t\t  2. View Products\n");
		printf("\t\t\t  3. Update Product\n");
		printf("\t\t\t  4. Delete Product\n");
		printf("\t\t\t  5. Save Inventory to File\n");
		printf("\t\t\t  6. Exit\n\n");
		printf("\t\t\tEnter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			createProduct(inventory, &numProducts);
			break;
		case 2:
			readProducts(inventory, numProducts);
			break;
		case 3:
			updateProduct(inventory, numProducts);
			break;
		case 4:
			deleteProduct(inventory, &numProducts);
			break;
		case 5:
			saveInventoryToFile(inventory, numProducts);
			break;
		case 6:
			printf("\t\t\tExiting...\n");
			break;
		default:
			printf("\t\t\tInvalid choice. Please try again.\n");
		}
	} while (choice != 6);

	return 0;
}
