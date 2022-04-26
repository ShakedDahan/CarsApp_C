#include "Car.h"

Tree createCarTree()
{
  return createTree();

}
CAR zeroCar()
{ /* THIS FUNC INITIATE A EMPTY CAR */
    CAR c;
    c.color=(char*)malloc(1);
    c.modelName=(char*)malloc(1);
    c.manufactureName=(char*)malloc(1);
    c.engine=0;
   c.manufactureYear=0;
   c.onRoadYear=0;
   c.shieldNum=0;
   c.supplyPrice=0;
   strcpy(c.licenceNum,"0");
   strcpy(c.manufactureName,"0");
   strcpy(c.color,"0");
   strcpy(c.modelName,"0");
   return c;
}
CAR newCar()

{
    /* THIS FUNCTION CHECK'S ALL THE REQUIERMENTS TO CONFIRM OR DECLINE IF ITS A GOOD CAR PARAMETERS FROM THE USER */
    long shieldNum,manufactureYear,onRoadYear,engine,supplyPrice,curPrice;
    char manufactureName[255],modelName[255],color[255],licenceNum[255];
    CAR a;
    printf("\nTHE NEW CAR\n");
    printf("please enter a licence number : \n");
    scanf( "%s" , licenceNum );
    
    if(strlen(licenceNum)==7&&isNumbers(licenceNum))
    {
        strcpy(a.licenceNum,licenceNum);
    }
    else
    {
        printf("bad licenceNum %s\nthe car is not added\n",licenceNum);
        return zeroCar();
    }
    printf("please enter a color : \n");
    scanf( "%s" , color );
    a.color=(char*)malloc(strlen(color)+1);
     if (strlen(color)>1)
    {
        strcpy(a.color,color);
    }
    else 
    {
        printf("Bad Color, Car is not added: %s\n",color);
        return zeroCar();
    }
    printf("please enter a model name : \n");
    scanf( "%s" , modelName );
    a.modelName=(char*)malloc(strlen(modelName)+1);
      if (strlen(modelName)>1)
    {
        strcpy(a.modelName,modelName);
    }
    else
    {
        printf("Bad model name , Car is not added: %s\n",modelName);
        return zeroCar();
    }
    printf("please enter a manufacturer name : \n");
    scanf( "%s" , manufactureName );
    a.manufactureName=(char*)malloc(strlen(manufactureName)+1);
     if (strlen(manufactureName)>1)
    {
         strcpy(a.manufactureName,manufactureName);
    }
    else
    {
        printf("Bad manufacture name, Car is not added : %s\n",manufactureName);
        return zeroCar();
    }
    printf("please enter a engine capacity : \n");
    scanf("%ld",&engine);
    if(fourDigitNum(engine))
    {
        a.engine=engine;
    }
    else
    {
        printf("bad engine capacity , Car is not added %ld\n",engine);
        return zeroCar();
    }
    printf("please enter a shield number : \n");
    scanf("%ld",&shieldNum);
     if(fiveDigitNum(shieldNum))
    {
        a.shieldNum=shieldNum;
    }
    else
    {
        printf("bad shieldNum %ld\nthe car is not added\n",shieldNum);
        return zeroCar();
    }
    printf("please enter a manufacture year : \n");
    scanf("%ld" , &manufactureYear);
      if(fourDigitNum(manufactureYear))
    {
        a.manufactureYear=manufactureYear;
    }
    else
    {
        printf("bad manufactureYear %ld\nthe car is not added\n",manufactureYear);
        return zeroCar();
    }
    printf("please enter a on road year : \n");
    scanf("%ld",&onRoadYear);
      if(fourDigitNum(onRoadYear))
    {
        a.onRoadYear=onRoadYear;
    }
    else
    {
        printf("bad onRoadYear %ld\nthe car is not added\n",onRoadYear);
        return zeroCar();
    }
    printf("please enter a supply price : \n");
    scanf("%ld",&supplyPrice);
     if(sevenDigitNum(supplyPrice))
    {
        a.supplyPrice=supplyPrice;
    }
    else
    {
        printf("bad supplyPrice %ld\nthe car is not added\n",supplyPrice);
        return zeroCar();
    }
    printf("please enter a cur price : \n");
    scanf("%ld",&curPrice);
     if(sevenDigitNum(curPrice))
    {
        a.curPrice=curPrice;
    }
    else
    {
        printf("bad curPrice %ld\nthe car is not added\n",curPrice);
        return zeroCar();
    }
    return a;
}
void* cpy_car()
{
    CAR* new_node=(CAR*)malloc(sizeof(CAR));
    *new_node=newCar();
    return new_node;
}
int compare_node(const void *a, const void *b) {
    return strcmp((char*)a,((CAR*)(b))->licenceNum);
}




int deleteCar(Tree tree, char key[])
{
    void* value=key;
 if(deleteNode(tree,value,sizeof(CAR),compare_node))
 {
    return 1;
 }
    return 0;
}

bool deleteAllCars(Tree **tree)
{
    return true;
}

int addNewCar(Tree tree){
    void* value=cpy_car();
    if(insert(tree,value,sizeof(CAR),compare_node))
    return 1;
    return 0;
}
