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

//*creating all functions (1-5,collecting revenue and functions to store data and show previous data whenever we log in again.)
void VehicleEntry();
void VehicleExit();
void DisplayVehicles();
void ParkingLotStatus();
void Search();
float calculateFee(char type[], float hour);
void saveDataToFile();
void LoadData();

//1.  menu for user to choose the option he/she wants to access.
void menu() {
    int choice;
    while(1) {
        printf("\n1. Vehicle Entry \n");
        printf("2. Vehicle Exit \n");
        printf("3. Display Parked Vehicles status \n");
        printf("4. Parking Lot Status \n");
        printf("5. Search vehicle \n");
        printf("6. EXIT Program \n");
        printf("Enter your choice(1-6): ");
        scanf("%d",&choice);

        switch(choice) {        //need to create functions first,
            case 1: VehicleEntry(); break;
            case 2: VehicleExit(); break;
            case 3: DisplayVehicles(); break;
            case 4: ParkingLotStatus(); break;
            case 5: Search(); break;
            case 6: 
                printf("\nTotal Revenue Collected: %.2f Rupees Only. \n",totalRevenue);
                printf("Thank You for using PARKING-LOT-SYSTEM!!\n");
                return;
            default: printf("\n Invalid Choice! TRY AGAIN. \n");
        }
    }
}

//---------------------------------------VEHICLE ENTRY---------------------------------
void VehicleEntry() {
    if (filledSlots>= totalSlots) {
        printf("\nSORRY! PARKING IS FULL...\n");
        return;
    }

    struct Vehicle v;
    printf("\nEnter Vehicle Number: ");
    scanf("%s",v.number);
    printf("Enter Vehicle Type(Car/Bike/Truck): ");
    scanf("%s",v.type);
    //entering the time of entry (using my laptop's time.)
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    sprintf(v.entryTime, "%02d:%02d", tm->tm_hour, tm->tm_min);
    
    vehicles[filledSlots++] = v;  //adding filledslots by one after every parking
    printf("\nVEHICLE PARKED SUCCESSFULLY at %s\n",v.entryTime);
}

//-----------------------------------VEHICLE EXIT---------------------------------------
void VehicleExit() {
    char num[20];
    printf("\nEnter Vehicle Number to Exit: ");
    scanf("%s", num);

    int found = -1;
    for (int i = 0; i < filledSlots; i++) {
        if (strcmp(vehicles[i].number, num) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nVehicle not found!\n");
        return;
    }
    //ENTERING EXIT TIME AND AND STORING AS VARIABLE NOW.
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    int exitHour = tm_now->tm_hour;
    int exitMin = tm_now->tm_min;

    int entryHour, entryMin;  //ENTRY TIME
    sscanf(vehicles[found].entryTime, "%d:%d", &entryHour, &entryMin);

    int hours = exitHour - entryHour;  //CALCULATING TIME OF PARKING 
    int minutes = exitMin - entryMin;

    if (minutes < 0) {            //(BASIC BORROWING OF SUBTRACTION)
        minutes += 60;
        hours -= 1;
    }
    if (hours < 0) {
        hours += 24; // handle overnight parking
    }

    // Convert partial hour if needed
    float totalHours = hours + (minutes / 60.0);
 
    //CALCULATING FEES 
    float fee = calculateFee(vehicles[found].type, totalHours);
    printf("\nVehicle Number: %s", vehicles[found].number);
    printf("\nEntry Time: %s", vehicles[found].entryTime);
    printf("\nExit Time: %02d:%02d", exitHour, exitMin);
    printf("\nTotal Parked: %.2f hours", totalHours);
    printf("\nParking Fee: %.2f Rupees\n", fee);

    totalRevenue+=fee;

    //removing the vehicle from record.
    for (int i= found; i < filledSlots - 1; i++) {
        vehicles[i] = vehicles[i+1];
    }
    filledSlots--;

    printf("\nVehicle Exit Successful. Thank You!!\n");
}

//-------------------------------DISPLAY VEHICLES-------------------------------------------------
void DisplayVehicles() {
    if (filledSlots == 0) {
        printf("\n NO VEHICLE PARKED YET!!!\n");
        return;
        }
    
    printf("\nLIST OF PARKED VEHICLES:\n");
    printf("\n|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|\n");
    printf("  NUMBER\t\tTYPE\t\tENTRY TIME\n");
    printf("\n|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|\n");
   
    for (int i=0; i<filledSlots; i++) {
        printf("  %s\t%s\t\t%s\n",vehicles[i].number,vehicles[i].type,vehicles[i].entryTime);
    }

    printf("\n|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|4\n");
}

//-----------------------------------PARKING LOT STATUS--------------------------------------------------
void ParkingLotStatus() {
    printf("\nTotal Slots: %d",totalSlots);
    printf("\nFilled Slots: %d", filledSlots);
    printf("\nAvailaible Slots: %d\n",totalSlots-filledSlots);
}

//----------------------------------SEARCHING VEHICLE---------------------------------------------------------
void Search() {
    char num[20];
    printf("\nEnter Vehicle Number to search: ");
    scanf("%s",num);
     
    for (int i = 0; i < filledSlots; i++) {
        if (strcmp(vehicles[i].number, num) == 0) {
            printf("\nVehicle Found!\n");
            printf("Number: %s\nType: %s\nEntry Time: %s\n", 
                   vehicles[i].number, vehicles[i].type, vehicles[i].entryTime);
            return;
        }
    }
    printf("\nVehicle Not Found!\n");
}

//--------------------------FEE CALCULATION----------------------------------------------------
float calculateFee(char type[], float hours) {
    float rate;
    if (strcmp(type, "Car") == 0 || strcmp(type, "car") == 0)     //20 FOR CAR
        rate = 20;
    else if (strcmp(type, "Bike") == 0 || strcmp(type, "bike") == 0)    //10 FOR BIKE
        rate = 10;
    else
        rate = 30;                         //30 FOR TRUCK
    return rate * hours;
} 

//-------------------------------FILE HANDLING---------------------------------------------------------------------------------------------------
void saveDataToFile() {
    FILE *fp = fopen("parkingdata.txt", "w");
    for (int i = 0; i < filledSlots; i++) {
        fprintf(fp, "%s %s %s\n", vehicles[i].number, vehicles[i].type, vehicles[i].entryTime);
    }
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen("parkingdata.txt", "r");
    if (fp == NULL) return;
    while (fscanf(fp, "%s %s %s", vehicles[filledSlots].number, vehicles[filledSlots].type, vehicles[filledSlots].entryTime) != EOF) {
        filledSlots++;
    }
    fclose(fp);
}

//---------------------------------------------RUNNING THE MODULES---------------------------------------------------------------------------------
int main() {
    printf("\n=================WELCOME TO PARKING-LOT-MANAGEMENT SYSTEM===========================\n ");
    loadData();  // load old records if any
    menu();              // start the main program
    saveDataToFile();    // save before exit
    return 0;
}