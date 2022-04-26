#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Checks.h"
#include "Common.h"
int clientNumberWithGivenCarYear_helper(Tree_Node* clientHead,Tree cars,char year[5])
{
    Car* car;
    int counter;
    if(!clientHead) return 0;
    counter = 0;
    car = getCar(cars,((Client*)clientHead->data)->carNum);
    if(car != NULL)
    {
        if(strcmp(car->yearOfManufacture,year) == 0) counter++;
    }
    counter += (clientNumberWithGivenCarYear_helper(clientHead->left,cars,year)+clientNumberWithGivenCarYear_helper(clientHead->right,cars,year));
    return counter;
}

int clientNumberWithGivenCarYear(Tree clientTree,Tree cars,char year[5])
{
    if(clientTree != NULL && clientTree->head != NULL && cars != NULL && cars->head != NULL &&checkYear(year))
    {
        return clientNumberWithGivenCarYear_helper(clientTree->head,cars,year);
    }
    else printf("\nbad year\n");
    return -1;
}