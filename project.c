//AIM OF THIS PROJECT IS TO CREATE AN AUTOMATED PARKING LOT MANAGEMENT PROGRAM USING C TO MAKE IT EASY TO HANDLE RECORD OF VEHICLES.

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//CREATING STRUCTURE FOR STORING VEHICLE DETAILS (VEHICLE: NUMBER/TYPE/TIME).
struct Vehicle {
    char number[20];    //char because car number contain char
    char type[10];      //(Car/Bike/Truck)
    char entryTime[20];   
};

/*Array of structures to store vehicle slot details.*/
struct Vehicle vehicles[100];
int totalSlots = 50;
int filledSlots = 0;
float totalRevenue = 0;

//1.  menu for user to choose the option he/she wants to access.
void menu() {
    int choice;
    while(1) {
        printf("\n=================WELCOME TO PARKING-LOT-MANAGEMENT SYSTEM===========================\n ");
        printf("1. Vehicle Entry \n");
        printf("2. Vehicle Exit \n");
        printf("3. Display Parked Vehicles status \n");
        printf("4. Parking Lot Status \n");
        printf("5. Search vehicle \n");
        printf("6. EXIT Program \n");
        printf("Enter your choice(1-6): ");
        scanf("%d",&choice);

        switch(choice) {        //need to create functions first,
            case 1: VehicleEntry(); break;
            case 2: VehiceExit(); break;
            case 3: DisplayVehicles(); break;
            case 4: ParkingLotStatus(); break;
            case 5: Search(); break;
            case 6: ExitProgram(); break;
            default: printf("\n Invalid Choice! TRY AGAIN. \n");
        }
    }
}


//*creating all functions (1-6)
void VehicleEntry();
void VehiceExit();
void DisplayVehicles();
void ParkingLotStatus();
void Search();
void ExitProgram();

//---------------------------------------VEHICLE ENTRY---------------------------------
void VehicleEntry() {
    if (filledSlots>= totalSlots) {
        printf("\nSORRY! PARKING IS FULL...\n");
        return;
    }

    struct Vehicle v;
    printf("\nEnter Vehichle Number: ");
    scanf("%s",v.number);
    printf("Enter Vehicle Type(Car/Bike/Truck): ");
    scanf("%s",v.type);

    
}
