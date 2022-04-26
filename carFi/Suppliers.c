#include "Suppliers.h"
#include "Checks.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUS_NUM "defaultnum"
#define SUP_NAME "d_val"
#define PHONE "defaultnum"


/*Checks if given supplier information is valid
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
*
* return : returns 1 if supplier information is valid, 0 otherwise
*/
int checkSupplier(char bus[11],char* name,char phone[11],int num_transactions,long total_transactions)
{
    if(hasNumDigitsString(bus,10))
    {
        if(checkPhoneNumber(phone))
        {
            if(num_transactions >= 0 && num_transactions <= 99999 && total_transactions >= 0 && total_transactions <= 9999999999) return 1;
        }
    }
    return 0;
}

/*Compares two given Suppliers based on business number
*
* supplier1, supplier2 - given Suppliers
*
* return : returns negative value if supplier1 has a smaller business number,
* positive value if supplier1 has larger business number, 0 if Suppliers have the same business number*/
int supplierCompare(const void* supplier1, const void* supplier2)
{
    return strcmp(((Supplier*)supplier1)->businessNum,((Supplier*)supplier2)->businessNum);
}

/*Generate a supplier with given details
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
*
* returns pointer to Supplier with given information if successful, NULL otherwise*/
Supplier* generateSupplier(char bus[11],char* name,char phone[11],int num_transactions,long total_transactions)
{
    if(checkSupplier(bus,name,phone,num_transactions,total_transactions))
    {
        Supplier* supplier;
        supplier = (Supplier*)malloc(sizeof(Supplier));
        supplier->name = (char*)malloc(sizeof(strlen(name)+1));
        if(supplier == NULL || supplier->name == NULL) return NULL;
        strcpy(supplier->businessNum,bus);
        strcpy(supplier->name,name);
        strcpy(supplier->phone,phone);
        supplier->num_of_transactions = num_transactions;
        supplier->total_sum_of_transactions = total_transactions;
        return supplier;
    }
    return NULL;
} 

/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createSupplierTree()
{
    return createTree();
}

/*Adds a new TreeNode containing a Supplier to given Tree
*
* tree - given Tree
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
* 
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int addNewSupplier(Tree tree,char bus[11],char* name,char phone[11],int num_transactions,long total_transactions)
{
    if(tree != NULL && checkSupplier(bus,name,phone,num_transactions,total_transactions))
    {
        Supplier* supplier = generateSupplier(bus,name,phone,num_transactions,total_transactions);
        return insert(tree,supplier,sizeof(Supplier),supplierCompare);
    }
    else
    {
        printf("\nthe supplier not added\n");
    }
    return 0;
}

/*Prompts user for Supplier information and adds a new Supplier to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int addNewSupplierTree(Tree tree)
{
    if(tree != NULL)
    {
        char bus[11];
        char name[20];
        char phone[11];
        int num_transactions;
        long total_transactions;
        char d[2];
        gets(d);
        while(1)
        {
            printf("\nenter supplier business number : ");
            gets(bus);
            if(!hasNumDigitsString(bus,10)) printf("\nbad business number\n");
            else if(getSupplier(tree,bus) != NULL) printf("\nbusiness number exist\n");
            else break;
        }
        while(1)
        {
            printf("\n enter supplier name : ");
            gets(name);
            if(strlen(name) == 0) printf("\nbad name\n");
            else break;
        }
        while(1)
        {
            printf("\n enter supplier phone number : ");
            gets(phone);
            if(!checkPhoneNumber(phone)) printf("\nbad phone \n");
            else break;
        }
        while(1)
        {
            printf("\nenter number of transactions : ");
            scanf("%d",&num_transactions);
            if(!(num_transactions >= 0 && num_transactions <= 99999)) printf("\nbad number of transactions\n");
            else break;
        }
        while(1)
        {
            printf("\nenter total sum of transactions : ");
            scanf("%ld",&total_transactions);
            if(!(total_transactions >= 0 && total_transactions <= 9999999999)) printf("\nbad sum of transactions\n");
            else break;
        }
        if(addNewSupplier(tree,bus,name,phone,num_transactions,total_transactions))
        {
            printf("\nSupplier added!\n");
            return 1;
        }
        else
        {
            printf("\nCould not add supplier\n");
        }
    }
    else
    {
        printf("\nError - null pointer to list\n");
    }
    return 0;
}

/*Returns pointer to a Supplier with given business number from Tree
*
* tree - Tree
* bus_num - Supplier business number
*
* returns requested Supplier if successful, NULL otherwise*/
Supplier* getSupplier(Tree tree, char* bus)
{
    if(tree != NULL && hasNumDigitsString(bus,10))
    {
        if(tree->head != NULL)
        {
            Supplier* d;
            Supplier* returnSupplier;
            Tree_Node* head;
            d = (Supplier*)malloc(sizeof(Supplier));
            if(!d) return NULL;
            strcpy(d->businessNum,bus);
            head = search(tree,d,supplierCompare);
            if(head == NULL)
            {
                free(d);
                d = NULL;
                return NULL;
            }
            returnSupplier = (Supplier*)head->data;
            free(d);
            d = NULL;
            return returnSupplier;
        }
    }
    return NULL;
}

/*Recursive helper function to function threeGreatestSuppliers
* 
* root - Tree root
* suppliers - struct Greatest representing business numbers of greatest suppliers
*
* return : returns 1 if successful, 0 otherwise*/
int threeGreatestSuppliers_helper(Tree_Node* head,Greatest* greatest)
{
    if(!head) return 0;
    if(((Supplier*)head->data)->total_sum_of_transactions >= greatest->max_tran1)
    {
        greatest->max_tran3 = greatest->max_tran2;
        strcpy(greatest->bNum3,greatest->bNum2);
        greatest->max_tran2 = greatest->max_tran1;
        strcpy(greatest->bNum2,greatest->bNum1);
        greatest->max_tran1 = ((Supplier*)head->data)->total_sum_of_transactions;
        strcpy(greatest->bNum1,((Supplier*)head->data)->businessNum);
    }
    else if(((Supplier*)head->data)->total_sum_of_transactions >= greatest->max_tran2)
    {
        greatest->max_tran3 = greatest->max_tran2;
        strcpy(greatest->bNum3,greatest->bNum2);
        greatest->max_tran2 = ((Supplier*)head->data)->total_sum_of_transactions;
        strcpy(greatest->bNum2,((Supplier*)head->data)->businessNum);
    }
    else if(((Supplier*)head->data)->total_sum_of_transactions >= greatest->max_tran3)
    {
        greatest->max_tran3 = ((Supplier*)head->data)->total_sum_of_transactions;
        strcpy(greatest->bNum3,((Supplier*)head->data)->businessNum);
    }
    threeGreatestSuppliers_helper(head->left,greatest);
    threeGreatestSuppliers_helper(head->right,greatest);
    return 1;
}

/*Gets business numbers of the three greatest Suppliers in given Tree in the form of struct Greatest
*
* tree - given Tree
*
* return : returns struct Greatest containing business numbers of the three suppliers with whom there were
* the largest total sums of transactions*/
Greatest threeGreatestSuppliers(Tree tree)
{
    Greatest suppliers;
    strcpy(suppliers.bNum1,BUS_NUM);
    strcpy(suppliers.bNum2,BUS_NUM);
    strcpy(suppliers.bNum3,BUS_NUM);
    suppliers.max_tran1 = suppliers.max_tran2 = suppliers.max_tran3 = 0;
    if(tree != NULL)
    {
        if(tree->elementCount >= 3)
        {
            threeGreatestSuppliers_helper(tree->head,&suppliers);
            return suppliers;
        }
        else
        {
            printf("\nthere is no 3 supp\n");
        }
    }
    return suppliers;
}

/*Finds the average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)
*
* root - Tree root
* numSuppliers - number of Suppliers in Tree
*
* return : returns average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)*/
long averageOfSupplierMoney(Tree_Node* head,int numSuppliers)
{
    if(!head) return 0;
    return ((((Supplier*)head->data)->total_sum_of_transactions)/(numSuppliers))+averageOfSupplierMoney(head->right,numSuppliers)+averageOfSupplierMoney(head->left,numSuppliers);
}

/*Deletes a TreeNode containing Supplier with given business number from the Tree
*
* tree - Tree
* bus_num : given business number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteSupplier(Tree tree,char bus[11])
{
    if(tree != NULL && tree->head != NULL && hasNumDigitsString(bus,10))
    {
        Supplier* d;
        int r;
        d = (Supplier*)malloc(sizeof(Supplier));
        strcpy(d->businessNum,bus);
        r = deleteNode(tree,d,sizeof(Supplier),supplierCompare);
        free(d);
        return r;
    }
    else
    {
        printf("\nSupplier not added\n");
    }
    return 0;
}

/*Deletes all TreeNodes from the Tree
*
* tree : Tree
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllSuppliers(Tree tree)
{
    if(tree != NULL)
    {
        if(tree->head == NULL) return 1;
        else
        {
            return deleteTree(tree);
        }
    }
    
    return 0;
}

/*Prints information for given Supplier
*
* supplier - given supplier
*
* returns 1 always*/
int printSupplier(Supplier supplier)
{
    printf("business number:%s\nname:%s\nphone:%s\nnum_transactions:%d\ntotal_transactions:%ld\n",supplier.businessNum,supplier.name,supplier.phone,supplier.num_of_transactions,supplier.total_sum_of_transactions);
    return 1;
}

/*Recursive helper function to function printSuppliers
*
* root - Tree root
*
* returns 1 if successful, 0 otherwise*/
int printSuppliers_helper(Tree_Node* head)
{
    if(!head) return 0;
    printSuppliers_helper(head->left);
    printf("\n");
    printSupplier(*((Supplier*)head->data));
    printSuppliers_helper(head->right);
    return 1;
}

/*Prints all suppliers in given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise*/
int printSuppliers(Tree tree)
{
    if(tree != NULL && tree->head != NULL)
    {
        printSuppliers_helper(tree->head);
    }
    return 0;
}

