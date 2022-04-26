#ifndef CLIENTS_H
#define CLIENTS_H
#include "TimeDate.h"
#include "Generic_tree.h"

int printClientCarsForGivenRentDate();

typedef struct  
{
    char* first_name;
    char* last_name;
    char id[10];
    char carNum[8];
    Date rent_date;
    Time rent_hour;
    short price;
} Client;

typedef struct ClientNode
{
    Client* client;
    struct ClientNode* next;
} ClientNode;

typedef struct clientList
{
    ClientNode* first;
    ClientNode* last;
} clientList;

typedef struct clientList* ClientList;


Tree createClientTree();

int addNewClientTree(Tree tree);

int addNewClient_list(ClientList list,Client* client);

int clientCompare(const void* client1, const void* client2);

ClientList createClientList();

int addNewClient(Tree tree,char* name,char* last_name, char id[10], char carNum[8],Date rent_date,Time rent_hour, short price);

Client* genClient(char* name,char* last_name, char id[10], char carNum[8],Date rent_date,Time rent_hour, short price);

int CheckClient(char* name,char* last_name, char id[10], char carNum[8],Date rent_date,Time rent_hour, short price);

int deleteClient(Tree tree,char id[10]);

int deleteAllClients(Tree tree);

int printClient(Client client);

Client* getClient(Tree tree,char id[10]);

ClientList findClient(Tree tree, char* key);

int printClientCarsForGivenRentDate(Tree tree,Date date);

#endif