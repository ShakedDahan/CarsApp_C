#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cars.h"
#include "Clients.h"
#include "Checks.h"
#include "TimeDate.h"
#include "Suppliers.h"
#include "Common.h"


int DEMO()
{
    Tree cars;
    Tree clients;
    Tree suppliers;
    cars = createCarTree();
    clients = createClientTree();
    suppliers = createSupplierTree();
    addNewCar(cars,"6922258","11111","Toyota","Corolla","Silver","2018","2019",132900,90000,1500);
    addNewCar(cars,"8970159","14513","Hyundai","Ioniq","Black","2017","2017",143900,100000,1600);
    addNewCar(cars,"1209865","84651","Kia","Picanto","Red","2015","2015",84500,100000,1197);
    addNewClient(clients,"Nimrod","Ashkenazi","319034385","8970159",gen_date(2021,5,5),gen_time(0,0),250);
    addNewClient(clients,"Gilad","Shmueli","314673187","6922258",gen_date(2021,5,5),gen_time(8,0),235);
    addNewClient(clients,"Lital","Mazuz","207482183","1209865",gen_date(2021,5,5),gen_time(23,59),180);
    addNewSupplier(suppliers,"4687321035","Toyota","0534575432",3,200000);
    addNewSupplier(suppliers,"5387121430","NEC","0521572821",5,3000);
    addNewSupplier(suppliers,"5104543330","Eldan","0546903186",8,150000);
    runInterface(cars,clients,suppliers);
    return 0;
}

int main(void)
{
    DEMO();
    return 0;
}