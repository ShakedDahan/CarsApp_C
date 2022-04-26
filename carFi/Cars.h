#ifndef CARS_H
#define CARS_H
#include "Generic_tree.h"

typedef struct  
{
    char car_num[8];
    char shiled_num[6];
    char* manufacturer;
    char* model;
    char* color;
    char yearOfManufacture[5];
    char yearOnRoad[5];
    int supplyPrice;
    int curPrice;
    int engine;
} Car;

Tree createCarTree();
int carCompare(const void* car1, const void* car2);
int addNewCar(Tree tree,char car_num[8],char shiled_num[6],char* manufactureName,char* model,char* ,char yearManu[5],char yearRoad[5],int supplyPrice,int curPrice,int engine);
int inputCar(Tree tree);
int checkCar(char car_num[8],char shiled_num[6],char* manufac,char* model,char* color,char yearManu[5],char yearRoad[5],int supplyPrice,int curPrice,int engine);
int carNumberWithGivenCapacity(Tree tree ,int engine);
int deleteCar(Tree tree, char reg[8]);
int deleteAllCars(Tree tree);
int printCar(Car car);
Car* generateCar(char car_num[8],char shiled_num[6],char* manufac,char* model,char* color,char yearManu[5],char yearRoad[5],int supplyPrice,int curPrice,int engine);
Car* getCar(Tree tree, char* reg);

#endif