#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <windows.h>
#include <fstream>

#include "Robots.h"
#include "location.h"
using namespace std;

void menu();

int main()
{

    char choice, cont('Y');

    // pointers
    location * lptr = NULL;
    location * LocationsList = NULL;
    Robots * currRobot = NULL;
    Robots * ListRobots = NULL;


    while (cont == 'Y'){
    menu();
    cout << "Please select an option from the menu: ";
    cin >> choice;
    cout << endl;

    switch (choice){

    case 'D':{
                // displays all the robots after the HTTPS for loop has completed
            lptr = LocationsList;
            while (lptr != NULL){
            currRobot = (Robots*)lptr; currRobot -> Display(); lptr -> Display();
            lptr = lptr -> GetNextLocation();}
                } break;


    case 'F':{
            // Sadly, I have never had the experience of reaching from a HTTPS website, but the idea here was to retrieve the file from the site and convert it to a readable txt file
            // after the txt file is read and loaded by selecting option U the user can create a readable .txt file that can be reuploaded and overwrite the previous information for the file
            const char* url = "https://60c8ed887dafc90017ffbd56.mockapi.io/robots";
            const char* dst = "C:\\here\\inputfile.txt";

            if (S_OK == URLDownloadToFile(NULL, url, dst, 0, NULL))
            {
                cout << "File successfully downloaded;" << endl;
                return 0;
            }
            else {cout << "Download has failed" << endl;
                return -1;}
                } break;


    case 'U':{
            // displays all information in required output file format as stated on the Githuib readme file
            ofstream MYfile; int num;
            MYfile.open("outputfile.txt");
            lptr = LocationsList;
            while (lptr != NULL){
                currRobot = (Robots*)lptr;
                MYfile << "{" << endl;
                num = currRobot -> GetrobotId();
                MYfile << "robotId: " << num << "," << endl;
                num = currRobot -> GetbatteryLife();
                MYfile << "batteryLevel: " << num << "," << endl;
                num = currRobot -> GetlocationX();
                MYfile << "x: " << num << "," << endl;
                num = currRobot -> GetlocationY();
                MYfile << "y: " << num << ",}" << endl;
                lptr = lptr -> GetNextLocation();}
                MYfile.close();
                } break;


    case 'L': {
            // retrieves the data and makes new Robots for them
            string hold, pieceOf; // holds the string info before a class is created
            int num; // a variable that holds a replaceable num;
            char read; // parses the data character by character
            vector <int> data(0); // records when each robot data set has ended and another begins

            // set to read from input file downloaded from URL
            fstream file;
            file.open("inputfile.txt");
            file >> hold;


            for (int i = 0; i < hold.length(); i++){
                int counter; // counters the amount of commas inserted to the program
                read = hold[i];
                if (read == ',') {++counter;}
                if (counter == 4){counter = 0; data.push_back(i);}
            }


            for (int i = 0; i < data.size(); i++)
            {
                currRobot = new Robots;

                // Parse the retrieved string
                size_t foundBattery = hold.find("batteryLevel");
                    foundBattery = foundBattery + 14;
                        if ((hold[foundBattery] != ',') && (hold[foundBattery+1] != ',')){pieceOf = hold[foundBattery]; pieceOf = pieceOf + hold[foundBattery+1];}
                        else if (hold[foundBattery] != ',') {pieceOf = hold[foundBattery];}
                    num = stoi(pieceOf);
                    currRobot -> SetbatteryLife(num);

                    size_t foundrobotId = hold.find("robotId");
                    foundrobotId = foundrobotId + 10;
                        if ((hold[foundrobotId] != '"') && (hold[foundrobotId+1] != '"')){pieceOf = hold[foundrobotId]; pieceOf = pieceOf + hold[foundrobotId+1];}
                        else if (hold[foundrobotId] != '"') {pieceOf = hold[foundrobotId];}
                    num = stoi(pieceOf);
                    currRobot -> SetrobotId(num);


                size_t foundlocationX = hold.find("x");
                    foundlocationX = foundlocationX + 3;
                        if ((hold[foundlocationX] != ',') && (hold[foundlocationX+1] != ',')){pieceOf = hold[foundlocationX]; pieceOf = pieceOf + hold[foundlocationX+1];}
                        else if (hold[foundlocationX] != ',') {pieceOf = hold[foundlocationX];}
                    num = stoi(pieceOf);
                    currRobot -> SetlocationX(num);


                size_t foundlocationY = hold.find("y\"");
                    foundlocationY = foundlocationY + 3;
                        if ((hold[foundlocationY] != ',') && (hold[foundlocationY+1] != ',')){pieceOf = hold[foundlocationY]; pieceOf = pieceOf + hold[foundlocationY+1];}
                        else if (hold[foundlocationY] != ',') {pieceOf = hold[foundlocationY];}
                    num = stoi(pieceOf);
                    currRobot -> SetlocationY(num);

                    data[i] = data[i+1] - data[i];
                    hold.erase(0, data[i]);

                    // adds the curr robot to the linked list
                    lptr = currRobot;
                    lptr -> SetNextLocation(LocationsList);
                    LocationsList = lptr;
                    currRobot -> SetNextRobot(ListRobots);
                    ListRobots = currRobot;
    }
                file.close();
                } break;


    case 'A': {
                // allows user to add robots directly to the system and those robots will be added to the output file
                // a filter would be nice to limit the user from providing an overlapping robotID
                int num;
                currRobot = new Robots;
                cout << "What is the robots ID number :";
                cin >> num;
                currRobot -> SetrobotId(num);
                currRobot -> SetbatteryLife(100);
                currRobot -> SetlocationX(0);
                currRobot -> SetlocationY(0);
                cout << "The robot has been fully recharged and deployed at the origin\n" << endl;

                lptr = currRobot;
                lptr -> SetNextLocation(LocationsList);
                LocationsList = lptr;

                currRobot -> SetNextRobot(ListRobots);
                ListRobots = currRobot;
                } break;


    case 'P': {
                // local variables used for implementation
                int numX, numY, robotX, robotY, battery1, battery2, loadID;
                double  distanceX, distanceY, distanceZ, closest(100.0);
                Robots * closestRobot = NULL;
                currRobot = ListRobots;

                cout << "What is the pallet ID number: ";
                cin >> loadID;
                cout << "What is the pallets X location: ";
                cin >> numX;
                cout << "What is the pallets Y location: ";
                cin >> numY;

                while (currRobot != NULL){
                robotX = currRobot -> GetlocationX();
                robotY = currRobot -> GetlocationY();

                // distance calculations
                distanceX = pow((numX - robotX), 2);
                distanceY = pow((numY - robotY), 2);
                distanceZ = distanceX + distanceY;
                distanceZ = sqrt(distanceZ);

                if (distanceZ < closest)
                    {closest = distanceZ; closestRobot = currRobot;}

                else if (distanceZ == closest) { // checks for which robot has higher battery if distance is the same
                        battery1 = closestRobot -> GetbatteryLife();
                        battery2 = closestRobot -> GetbatteryLife();
                        if (battery1 < battery2){closestRobot = currRobot;}
                            }

                currRobot = currRobot -> GetNextRobot();
                    }

                cout << "\nThis is the closests robot\n";
                lptr = closestRobot;
                closestRobot = (Robots*)lptr; closestRobot -> Display();
                cout << "DistanceToGoal: " << closest << endl;
                closestRobot -> SetlocationX(numX);
                closestRobot -> SetlocationX(numY);
                cout << "The robot has went to retrieve the pallet: P" << loadID << endl;

                } break;


    case 'R': {
                // since we were presented with what would we add I though it would be cool to send the robots to recharge
                // this does it in a "perfect world manner" but it would be cool to add actual rate of charge functions close to the robots model
                // then a set function could be made of what robots need to be charged and what robots would disperse to cover the now open area and handle the open workload
                int IDnum, wantedID, found(0);
                Robots * wantedRobot = NULL;
                currRobot = ListRobots;

                cout << "What robot would you like to recharge? (Type the Robot ID number): "; // searches for the matching robot and displays their information to the window
                cin >> wantedID;
                while(found == 0)
                    {
                        IDnum = currRobot -> GetrobotId();
                        if (IDnum == wantedID)
                            {wantedRobot = currRobot; found = 1;}
                        currRobot = currRobot -> GetNextRobot();
                    }

                    cout << "The desired robot is returning to station to recharge" << endl; // assuming the station is at origin (0, 0)
                    lptr = wantedRobot;
                    wantedRobot = (Robots*)lptr; wantedRobot -> Display(); lptr -> Display();
                    wantedRobot -> SetlocationX(0);
                    wantedRobot -> SetlocationY(0);
                    wantedRobot -> SetbatteryLife(100);
                    cout << "\nThe robot has recharged" << endl;
                    lptr = wantedRobot;
                    wantedRobot = (Robots*)lptr; wantedRobot -> Display(); lptr -> Display();

                } break;

    case 'X': {
                cont = 'N';
                } break;

    }
    }
    return 0;
}

void menu()
{
    cout << "***** Menu of Available Options *****" << endl;
    cout << "(D) Display current robots and their locations" << endl;
    cout << "(F) Download a file from the robots movement" << endl;
    cout << "(U) Upload your data back to the website" << endl;
    cout << "(L) Load the most updated list of robots and their locations" << endl;
    cout << "(A) Add a new Robot to the system" << endl;
    cout << "(P) Pick Up a Pallet" << endl;
    cout << "(R) Recharge a Robot" << endl;
    cout << "(X) Exit the program" << endl;
}
