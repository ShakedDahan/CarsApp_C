#include "Clients.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


ClientList createClientList()
{
    ClientList list;
    list = (ClientList)malloc(sizeof(clientList));
    if(list == NULL) return NULL;
    list->first = NULL;
    list->last = NULL;
    return list;
}

int client_addFirst(ClientList list, Client* client)
{
    if(list != NULL)
    {
        ClientNode* newNode;
        newNode = (ClientNode*)malloc(sizeof(ClientNode));
        if(newNode == NULL) return 0;
        newNode->client = client;
        newNode->next = list->first;
        list->first = newNode;
        if(newNode->next == NULL) list->last = newNode;
        return 1;
    }
    return 0;
}


int client_addLast(ClientList list, Client* client)
{
    if(list != NULL)
    {
        ClientNode* newNode;
        newNode = (ClientNode*)malloc(sizeof(ClientNode));
        if(newNode == NULL) return 0;
        newNode->client = client;
        if(list->last != NULL )list->last->next = newNode;
        else list->first = newNode;
        list->last = newNode;
        newNode->next = NULL;
        return 1;
    }
    return 0;
}

int addNewClient_list(ClientList list,Client* client)
{
    if(list != NULL)
    {
        if(list->first == NULL)
        { 
            client_addFirst(list,client);
            return 1;
        }
        if(strcmp(client->id,list->first->client->id) <=0)
        {
            client_addFirst(list,client);
            return 1;
        }
        else if(strcmp(client->id,list->last->client->id) >=0)
        {
            client_addLast(list,client);
            return 1;
        }
        else
        {
            ClientNode* scan;
            ClientNode* newNode;
            newNode = (ClientNode*)malloc(sizeof(ClientNode));
            if(newNode == NULL) return 0;
            newNode->client = client;
            scan = list->first;
            while(strcmp(client->id,scan->client->id) < 0) scan = scan->next;
            newNode->next = scan->next;
            scan->next = newNode;
            return 1;
        }            
    }
    else printf("\nclient not added\n");
    return 0;
}

/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createClientTree()
{
    return createTree();
}

/*Compares two given Clients based on ID
*
* client1, client2 - given Clients
*
* return : returns negative value if client1 has a smaller ID number,
* positive value if client1 has larger ID number, 0 if Clients have the same ID number*/
int clientCompare(const void* client1, const void* client2)
{
    return strcmp(((Client*)client1)->id,((Client*)client2)->id);
}

/*Checks if all client information is valid
*
* name : client name
* last_name : client last name
* id : client id
* reg : registration number of rental car
* rent_date : date of start of rental
* rent_hour : hour of start of rental
* rate : rental rate for 24 hours
*
* return : returns 1 if client information is correct, 0 otherwise*/
int CheckClient(char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour,short rate)
{
    if(checkIdString(id))
    {
        if(hasNumDigitsString(reg,7))
        {
            if(check_date(rent_date) && check_time(rent_hour))
            {
                if(rate >= 0 && rate <=999) return 1;
            }
        }
    }
    return 0;
}

/*Creates a Client from given information
*
* name : client name
* last_name : client last name
* id : client id
* reg : registration number of rental car
* rent_date : date of start of rental
* rent_hour : hour of start of rental
* rate : rental rate for 24 hours
*
* returns pointer to Client with given information if successful, NULL otherwise*/
Client* genClient(char* name,char* last_name, char id[10], char carNum[8],Date rent_date,Time rent_hour,short price)
{
    if(CheckClient(name,last_name,id,carNum,rent_date,rent_hour,price))
    {
        Client* client;
        client = (Client*)malloc(sizeof(Client));
        client->first_name = (char*)malloc(sizeof(strlen(name)+1));
        client->last_name = (char*)malloc(sizeof(strlen(last_name)+1));
        if(client == NULL || client->first_name == NULL || client->last_name == NULL) return NULL;
        strcpy(client->first_name,name);
        strcpy(client->last_name,last_name);
        strcpy(client->id ,id);
        strcpy(client->carNum ,carNum);
        client->rent_date = rent_date;
        client->rent_hour = rent_hour;
        client->price = price;
        return client;
    }
    else
    {
        printf("\nError - invalid client information\n");
    }
    return NULL;
}

/*Returns pointer to a Client with given ID number from Tree
*
* tree - Tree
* id - Client ID number
*
* returns requested Client if successful, NULL otherwise*/
Client* getClient(Tree tree,char id[10])
{
    if(tree != NULL && checkIdString(id))
    {
        if(tree->head != NULL)
        {
            Tree_Node* node;
            Client* check;
            Client* returnClient;
            check = (Client*)malloc(sizeof(Client));
            if(!check) return NULL;
            strcpy(check->id,id);
            node = search(tree,check,clientCompare);
            if(node == NULL)
            {
                free(check);
                check = NULL;
                return NULL;
            }
            returnClient = (Client*)node->data;
            free(check);
            check = NULL;
            return returnClient;
        }
    }
    return NULL;
}

/*Recursive helper function to function getClientDate
*
* root - Tree root
* date - given Date
* list - ClientList
*
* return : returns a ClientList of Clients who rented cars on given date if successful, NULL otherwise*/
ClientList getClientDate_helper(Tree_Node* root,Date date,ClientList list)
{
    if(!root) return NULL;
    getClientDate_helper(root->left,date,list);
    if(dateCompare(date,((Client*)root->data)->rent_date) == 0)
    {
        addNewClient_list(list,(Client*)root->data);
    }
    getClientDate_helper(root->right,date,list);
    return list;
}

/*Generates a ClientList of all Clients from Tree who rented cars on given date
*
* tree - given Tree 
* date - given Date
* list - ClientList
*
* return : returns a ClientList of Clients who rented cars on given date if successful, NULL otherwise*/
ClientList getClientDate(Tree tree,Date date)
{
    if(tree != NULL && check_date(date))
    {
        if(tree->head != NULL)
        {
            ClientList list;
            list = createClientList();
            return getClientDate_helper(tree->head,date,list);
        }
    }
    return NULL;
}

/*Finds all Clients by specified ID number, or date of rental
*
* tree - given Tree
* key - string with which to search Tree; can be either a 9 digit ID number, or a date in format dd/mm/yyyy
*
* return : returns a ClientList of Clients found by searching Tree either by Client ID, or date of rental*/
ClientList findClient(Tree tree, char* key)
{
    if(tree != NULL && tree->head != NULL)
    {
        if(checkIdString(key))
        {
            ClientList list;
            Client* client;
            client = getClient(tree,key);
            list = createClientList();
            if(client == NULL) return NULL;
            addNewClient_list(list,client);
            return list;
        }
        else if(check_date(dateFromString(key)))
        {
            return getClientDate(tree,dateFromString(key));
        }
    }
    return NULL;
}

/*Adds a new TreeNode containing a Client to given Tree
*
* name : client name
* last_name : client last name
* id : client id
* reg : registration number of rental car
* rent_date : date of start of rental
* rent_hour : hour of start of rental
* rate : rental rate for 24 hours
*
* return : returns 1 if operation succeeded, prints an error message and return 0 otherwise*/
int addNewClient(Tree tree,char* name,char* last_name, char id[10], char carNum[8],Date rent_date,Time rent_hour, short price)
{
    if(tree != NULL)
    {
        if(CheckClient(name,last_name,id,carNum,rent_date,rent_hour,price))
        {   
            Client* client;
            client = genClient(name,last_name,id,carNum,rent_date,rent_hour,price);
            return insert(tree,client,sizeof(Client),clientCompare);         
        }
        else printf("\nError - invalid Client\n");
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}

/*Prompts user for Client information and adds a new Client to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int addNewClientTree(Tree tree)
{
    if(tree != NULL)
    {
        char name[20];
        char last_name[20];
        char id[10];
        char carNum[8];
        Date rent_date;
        Time rent_hour;
        short price;
        char d[2];
        gets(d);
        while(1)
        {
            printf("\nenter client first name : ");
            gets(name);
            if(strlen(name) == 0) printf("\nbad name\n");
            else break;
        }
        while(1)
        {
            printf("\nenter client last name : ");
            gets(last_name);
            if(strlen(last_name) == 0) printf("\nbad last name\n");
            else break;
        }
        while(1)
        {
            printf("\nenter client ID : ");
            gets(id);
            if(!checkIdString(id)) printf("\nbad ID\n");
            else if(getClient(tree,id) != NULL) printf("\nclient ID exist\n");
            else break;
        }
        while(1)
        {
            printf("\nenter client car number : ");
            gets(carNum);
            if(!hasNumDigitsString(carNum,7)) printf("\nbad car number\n");
            else break;
        }
        while(1)
        {
            char datestring[11];
            printf("\nPlease enter date format dd/mm/yyyy : ");
            gets(datestring);
            rent_date = dateFromString(datestring);
            if(dateCompare(rent_date,def_date()) == 0) printf("\nbad date\n");
            else break;
        }
        while(1)
        {
            char timestring[6];
            printf("\nenter time format hh:mm : ");
            gets(timestring);
            rent_hour = timeFromString(timestring);
            if(timeCompare(rent_hour,def_time()) == 0) printf("\nbad time\n");
            else break;
        }
        while(1)
        {
            printf("\nPenter rent price : ");
            scanf("%hd",&price);
            if(!(price >=0 && price <= 999)) printf("\nbad rent price\n");
            else break;
        }
        if(addNewClient(tree,name,last_name,id,carNum,rent_date,rent_hour,price))
        {
            printf("\nClient added!\n");
            return 1;
        }
        else
        {
            printf("\nclient not added\n");
            return 0;
        }

    
}
return 0;
}

/*Deletes a TreeNode containing Client with given ID number from the Tree
*
* tree - Tree
* id : given ID number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteClient(Tree tree,char id[10])
{
    if(tree != NULL && tree->head != NULL && checkIdString(id))
    {
        Client* d;
        int retval;
        d = (Client*)malloc(sizeof(Client));
        strcpy(d->id,id);
        retval = deleteNode(tree,d,sizeof(Client),clientCompare);
        free(d);
        return retval;
    }
    return 0;
}

/*Deletes all TreeNodes from the Tree
*
* tree : Tree
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllClients(Tree tree)
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

/*Recursive helper function to function printClientCarsForGivenRentDate
*
* root - Tree root
* date - given Date
*
* returns 1 if all Clients for given rent date printed successfully, 0 otherwise*/
int printClientCarsForGivenRentDate_helper(Tree_Node* root,Date date)
{
    if(!root) return 0;
    printClientCarsForGivenRentDate_helper(root->left,date);
    if(dateCompare(date,((Client*)root->data)->rent_date) == 0)
    {
        printClient(*((Client*)root->data));
    }
    printClientCarsForGivenRentDate_helper(root->right,date);
    return 1;
}

/*Prints all clients who rented a car on a specified date
*
* tree - given Tree
* date - date of rental
*
* returns 1 if successful, 0 otherwise*/
int printClientCarsForGivenRentDate(Tree tree,Date date)
{
    if(tree != NULL && tree->head != NULL && check_date(date))
    {
        return printClientCarsForGivenRentDate_helper(tree->head,date);
    }
    return 0;
}


/*Prints information for given Client
*
* client - given client
*
* returns 1 always*/
int printClient(Client client)
{
    printf("name:%s\nlast name:%s\nid:%s\ncar number:%s\nrent date:%s\nrent hour:%s\nrent price:%d}\n",client.first_name,client.last_name,client.id,client.carNum,date_string(client.rent_date),time_string(client.rent_hour),client.price);
    return 1;
}

