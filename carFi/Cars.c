#include "Cars.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



Tree createCarTree()
{
    return createTree();
}


int carCompare(const void* car1, const void* car2)
{
    return strcmp(((Car*)car1)->car_num,((Car*)car2)->car_num);
}


int checkCar(char carNum[8],char ShNum[6],char* manufac,char* model,char* color,char yearManu[5],char yearRoad[5],int op,int cp,int eng)
{
    if(hasNumDigitsString(carNum,7) && hasNumDigitsString(ShNum,5))
    {
        if(isSingleWord(manufac))
        {
            if(checkYear(yearManu) && checkYear(yearRoad) && strcmp(yearManu,yearRoad) <=0)
            {
                if(op >= 0 && op <= 9999999 && cp >= 0 && cp <=9999999 && eng >= 1000 && eng <= 9999) return 1;
            }
        }
    }
    return 0;
}

Car* generateCar(char carNum[8],char ShNum[6],char* manufac,char* model,char* color,char yearManu[5],char yearRoad[5],int op,int cp,int eng)
{
    if(checkCar(carNum,ShNum,manufac,model,color,yearManu,yearRoad,op,cp,eng))
    {
        Car* car;
        car = (Car*)malloc(sizeof(Car));
        car->manufacturer = (char*)malloc(sizeof(strlen(manufac)+1));
        car->model = (char*)malloc(sizeof(strlen(model)+1));
        car->color = (char*)malloc(sizeof(strlen(color)+1));
        if(car == NULL || car->manufacturer == NULL || car->model == NULL || car->color == NULL) return NULL;
        strcpy(car->car_num,carNum);
        strcpy(car->shiled_num , ShNum);
        strcpy(car->manufacturer ,manufac);
        strcpy(car->model , model);
        strcpy(car->color , color);
        strcpy(car->yearOfManufacture , yearManu);
        strcpy(car->yearOnRoad , yearRoad);
        car->supplyPrice = op;
        car->curPrice = cp;
        car->engine = eng;
        return car;
    }
    return NULL;
}


Car* getCar(Tree tree, char* reg)
{
    if(tree != NULL && hasNumDigitsString(reg,7))
    {
        if(tree->head != NULL)
        {
            Car* d;
            Car* returnCar;
            Tree_Node* node;
            d = (Car*)malloc(sizeof(Car));
            if(!d) return NULL;
            strcpy(d->car_num,reg);
            node = search(tree,d,carCompare);
            if(node == NULL)
            {
                free(d);
                d = NULL;
                return NULL;
            }
            returnCar = (Car*)node->data;
            free(d);
            d = NULL;
            return returnCar;
        }
    }
    else
    {
        printf("\nError - Tree is null or invalid registration number\n");
    }
    return NULL;
}

int addNewCar(Tree tree, char carNum[8],char ShNum[6],char* manufac,char* model,char* color,char yearManu[5],char yearRoad[5],int op,int cp,int eng)
{
    if(checkCar(carNum,ShNum,manufac,model,color,yearManu,yearRoad,op,cp,eng) && tree != NULL)
    {
        Car* car = generateCar(carNum,ShNum,manufac,model,color,yearManu,yearRoad,op,cp,eng);
     
        return insert(tree,car,sizeof(Car),carCompare);
    }
    else
    {
        printf("\nError - Invalid car information or null Tree\n");
    }
    return 0;
}


int inputCar(Tree tree)
{
    if(tree != NULL)
    {
        char carNum[8];
        char ShNum[6];
        char manufac[20];
        char model[20];
        char color[20];
        char yearManu[5];
        char yearRoad[5];
        int op, cp, eng;
        char d[2];
        gets(d);
        while(1)
        {
            printf("\nPlease enter car number : ");
            gets(carNum);
            if(!hasNumDigitsString(carNum,7)) printf("\nbad car number\n");
            else if(getCar(tree,carNum)) printf("\nThere is already a car with this car num number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter shiled number : ");
            gets(ShNum);
            if(!hasNumDigitsString(ShNum,5)) printf("\nbad shiled number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter manufacturer name : ");
            gets(manufac);
            if(strlen(manufac) == 0) printf("\nbad Manufacturer name\n");
            else if(!isSingleWord(manufac)) printf("\nbad manufacturer name\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter model name : ");
            gets(model);
            if(strlen(model) == 0) printf("\nbad Model\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter color : ");
            gets(color);
            if(strlen(color) == 0) printf("\nbad color\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter year of manufacture : ");
            gets(yearManu);
            if(!checkYear(yearManu)) printf("\nbad year\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter year on road : ");
            gets(yearRoad);
            if(!checkYear(yearRoad)) printf("\nbad year\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter supply price : ");
            scanf("%d",&op);
            if(!(op >= 0 && op <= 9999999)) printf("\nbad supply price\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter current price : ");
            scanf("%d",&cp);
            if(!(cp >= 0 && cp <= 9999999)) printf("\nbad cur price\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter engine : ");
            scanf("%d",&eng);
            if(!(eng >= 1000 && eng <= 9999)) printf("\nbad engine\n");
            else break;
        }
        if(addNewCar(tree,carNum,ShNum,manufac,model,color,yearManu,yearRoad,op,cp,eng))
        {
            printf("\nCar added successfully\n");
            return 1;
        }
        else
        {
            printf("\ncar not added\n");
            return 0;
        }
    }
   
    return 0;
}

int carNumberWithGivenCapacity_helper(Tree_Node* head,int eng)
{
    int counter;
    if(head == NULL) return 0;
    counter = 0;
    if(((Car*)head->data)->engine == eng)
    {
        counter++;
    }
    counter += (carNumberWithGivenCapacity_helper(head->left,eng)+carNumberWithGivenCapacity_helper(head->right,eng));
    return counter;
}


int carNumberWithGivenCapacity(Tree tree,int eng)
{
    if(tree != NULL && tree->head != NULL)
    {
        if(eng >= 0 && eng <= 9999)
        {
            return carNumberWithGivenCapacity_helper(tree->head,eng);
        }
        else printf("bad engine\n");
    }
    return 0;
}


int deleteCar(Tree tree, char reg[8])
{
    if(tree != NULL && tree->head != NULL &&hasNumDigitsString(reg,7))
    {
        Car* d;
        int retval;
        d = (Car*)malloc(sizeof(Car));
        strcpy(d->car_num,reg);
        retval = deleteNode(tree,d,sizeof(Car),carCompare);  
        free(d);
        return retval;
    }
    return 0;
}

int deleteAllCars(Tree tree)
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


int printCar(Car car)
{
    printf("car number:%s\nshiled num:%s\nmanufacturer name:%s\nmodel:%s\ncolor:%s\nyearOfManufacture:%s\ncurPrice:%d\nengine:%d}\n",car.car_num,car.shiled_num,car.manufacturer,car.model,car.color,car.yearOfManufacture,car.curPrice,car.engine);
    return 1;
}
