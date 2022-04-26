#ifndef CAR_H_
#define CAR_H_
#include "Generic.h"
#include "Requirments.h"
#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
typedef struct
{
    long shieldNum,
        manufactureYear,
        onRoadYear,
        engine,
        supplyPrice,
        curPrice;

    char *manufactureName,
         *modelName,
         *color;

     char licenceNum[7];

}CAR;

void* cpy_car();
CAR newCar();

 Tree createCarTree();
int addNewCar();
int carNumberWithGivenCapacity(Tree *p,long cap);
int deleteCar(Tree tree,char ln[]);
bool deleteAllCars(Tree **p);
#endif