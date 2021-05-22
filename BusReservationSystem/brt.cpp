#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
/*
                                            |\    |
                                            | \   |
                                            |  \  |
                                            |    \|
                                     CODE FOR EVERYONE
                                     © Some Rights Reserved
*/

// Note : # represent bugs are fixed

// busCount is the current number of buses
static int busCount = 0;

// class Bus17 which wraps the main logic
class Bus17
{
    string driverName, Arrival, Depart, From, to;
    char busNumber[10], seat[10][4][10];

public:
    // method o get driver information along with his bus
    void getDriverInformation();
    
    // method to make reservation
    void makeReservation();
   
    //method to fill the empty bus seats
    void empty();
    
    // show the bus view
    void showBus();
    
    // show the buses available in buses
    void busesAvailable(int i);
    
    // utility function for showBus method
    // to draw the bus view
    void showBusCurrentPosition(int i);

}bus[10];// bus is the object of class Bus17



// Method to get the buses information
void Bus17::getDriverInformation()
{
    // #bug1 : not taking proper input and not showing proper information on the console
    // # status: fixed
    fstream file;
    // storing data in the file
    file.open("Reservation.txt", ios::app);
    file << "\n\n\t\t\t\tCurrent Data :\n\n";
    if (busCount < 10)
    {
        cout << "Enter bus no:\t\t";
        cin >> bus[busCount].busNumber;
        file << "Bus No :" << bus[busCount].busNumber << endl;
        
        cout << "\nEnter driver name:\t";
        cin.ignore();
        getline(cin, bus[busCount].driverName);
        file << "Driver Name: " << bus[busCount].driverName << endl;
        
        cout << "\nArrival time:\t\t";
        getline(cin, bus[busCount].Arrival);
        cin.ignore(0);
        file << "Arrival Time :" << bus[busCount].Arrival << endl;
        
        cout << "\nDeparture:\t\t";
        getline(cin, bus[busCount].Depart);
        cin.ignore(0);
        file << "Departure Time :" << bus[busCount].Depart << endl;
        
        cout << "\nFrom: \t\t\t";
        getline(cin, bus[busCount].From);
        cin.ignore(0);
        file << "From :" << bus[busCount].From << endl;
        
        cout << "\nTo: \t\t\t";
        getline(cin, bus[busCount].to);
        cin.ignore(0);
        file << "To :" << bus[busCount].to << endl;
        // fill all the seats as empty as soon as the bus is ready for departure
        bus[busCount].empty();
        // increase the busCount
        busCount++;
    }
    else
    {
        cout << "You can't add Bus Data Now !\nWe are sorting the Bus Shortage issue !\n Will inform Shortly !\nThanks !";
    }
    file.close();
}


// Method to make Reservation in bus for Passenger
void Bus17::makeReservation()
{
    fstream file;
    file.open("Reservation.txt", ios::app);
    int seat;
    char number[5];
top:
    cout << "Bus no: ";
    cin >> number;
    int n;
    for (n = 0; n <= busCount; n++)
    {
        // if bus number matches the input bus no
        if (strcmp(bus[n].busNumber, number) == 0)
            break;
    }
    //file << "\n\nReservation Data for Bus No : ";
    while (n <= busCount)
    {
        file << "\n\nReservation Data for Bus No : ";
        file << bus[n].busNumber << endl;
        cout << "\nSeat Number: ";
        cin >> seat;
        // # bug3 : overflow input not show correct output
        // status : fixed
        if (seat > 40)
        {
            cout << "\nThere are only 40 seats Available in this bus.";
        }
        else
        {
            if (strcmp(bus[n].seat[seat / 4][(seat % 4) - 1], "Vacant") == 0)
            {
                file << "Seat No :" << seat;
                cout << "Enter passanger's name: ";
                cin >> bus[n].seat[seat / 4][(seat % 4) - 1];
                cout << "\nReservation Done !" << endl;
                file << "\tPassanger's name:" << bus[n].seat[seat / 4][(seat % 4) - 1] << endl;
                break;
            }
            else
                cout << "The seat no. is already reserved.\n";
        }
    }
    if (n > busCount)
    {
        cout << "Enter correct bus no.\n";
        goto top;
    }
    file.close();
}


// method to fill the seats as Vacant in bus
void Bus17::empty()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            strcpy(bus[busCount].seat[i][j], "Vacant");
        }
    }
}


// Method to Show the Bus Status
void Bus17::showBus()
{
    int count;
    char number[5];
// # bug3: taking incorrect output stuck the program
// #status : fixed in top1
top1:
    cout << "-------------------------------------------------------------------------------------------------------------------";
    cout << "\nEnter bus no : ";
    cin >> number;
    int temp = busCount;
    // find the current bus
    for (count = 0; count < busCount; count++)
    {
        if (strcmp(bus[count].busNumber, number) == 0)
            break;
    }
    for (int i = 0; i < temp; i++)
    {
        if (bus[count].busNumber != bus[i].busNumber)
        {
            cout << "Enter correct bus no.\n";
            // fix this row
            // #fixed
            goto top1;
        }
    }
    if (count <= busCount)
    {
        cout << "Bus no: \t" << bus[count].busNumber << "\nDriver Name: \t" << bus[count].driverName << "\t\tArrival time: \t"
             << bus[count].Arrival << "\tDeparture time:" << bus[count].Depart << "\nFrom: \t\t" << bus[count].From << "\t\tTo: \t\t" << bus[count].to << "\n";
        cout << "\n--------------------------------------------------------------------------------------------------------------------"; // calling the positon function here
        bus[count]
            .showBusCurrentPosition(count);
        int seatNo = 1;
        // show the reserved seats
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                seatNo++;
                if (strcmp(bus[count].seat[i][j], "Vacant") != 0)
                    cout << "\nThe seat no " << (seatNo - 1) << " is reserved for " << bus[count].seat[i][j] << ".\n";
            }
        }
        cout << "------------------------------------------------------------------------------------ --------------------------------";
    }
    if (count > busCount)
        cout << "Enter correct bus no: ";
}


// Utility Method to show the current bus information
void Bus17::showBusCurrentPosition(int l)
{
    int s = 0;          // seat no is zero
    int emptySeats = 0; // Empty seats count is 0
    for (int i = 0; i < 10; i++)
    {
        cout << "\n";
        for (int j = 0; j < 4; j++)
        {
            s++;
            if (strcmp(bus[l].seat[i][j], "Vacant") == 0)
            {
                cout.width(5);
                cout.fill(' ');
                cout << s << ".";
                cout.width(10);
                cout.fill(' ');
                cout << bus[l].seat[i][j];
                // increase the empty seats count
                emptySeats++;
            }
            else
            {
                cout.width(5);
                cout.fill(' ');
                // s is the current seat number
                cout << s << ".";
                cout.width(10);
                cout.fill(' ');
                // show current seat number in the output
                // l is the bus number feed to the position function which gives the current position of the bus
                cout << bus[l].seat[i][j];
            }
        }
    }
    cout << "\n\nThere are " << emptySeats << " seats empty in Bus No: " << bus[l].busNumber << "\n";
    fstream file;
    file.open("Reservation.txt", ios::app);
    file << "\n\nThere are " << emptySeats << " seats empty in Bus No: " << bus[l].busNumber << "\n";
    file.close();
}


// Method to showBus the number of buses Available in the depot to Depart
void Bus17::busesAvailable(int n)
{
    // # if no bus
    if (busCount == 0)
    {
        cout << "There are no buses in depot....Wait some time !";
    }
    else
    {
        cout << "\n--------------------------------------------------------------------------------------------------------------------------------------";
        cout
            << "\nBus no:\t\t\t" << bus[n].busNumber << "\nDriver Name:\t\t" << bus[n].driverName
            << "\nArrival Time:\t\t" << bus[n].Arrival << "\nDeparture Time:\t\t" << bus[n].Depart << "\nFrom:\t\t\t" << bus[n].From << "\nTo:\t\t\t" << bus[n].to << "\n";
        cout << "----------------------------------------------------------------------------------------------------------------------------------------";
    }
}



int main()
{
    // this will clear the console screen system("cls");
    // make your choice
    int choice;
    while (1)
    {
        cout << "\n\n";
        cout << "------------------------------------------------------------------------------------ ----------------------------------------------------";
        cout
            << "\n\n";
        cout << "\t\t\t1.Enter Bus Information(Owned Buses=10)\n\t\t\t"
             << "2.Make Reservation\n\t\t\t"
             << "3.Show Current Bus Vacancies \n\t\t\t"
             << "4.Buses Available In Depot \n\t\t\t"
             << "5.Don't want to make makeReservation? Press 5 !";
        cout << "\n\n-------------------------------------------------------------------------------- --------------------------------------------------------";
        cout
            << "\n\n\t\t\tEnter your choice:-> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            bus[busCount].getDriverInformation();
            break;
        case 2:

            if (busCount == 0) // #
            {
                cout << "There are no buses in depot....Wait some time !";
            }
            else
            {
                bus[busCount].makeReservation();
            }
            break;
        case 3:
            if (busCount == 0) // #
            {
                cout << "There are no buses in depot....Wait some time !";
            }
            else
            {
                bus[0].showBus();
            }
            break;
        case 4:
            if (busCount == 0) // #
            {
                cout << "There are no buses in depot....Wait some time !";
            }
            else
            {
                int i = 0;
                while (i < busCount)
                {
                    bus[i].busesAvailable(i);
                    i++;
                }
            }
            break;
        case 5: 
            cout << "Thanks for visiting us ! \n Have a Good Day !";
            exit(0);
        }
    }
    return 0;
}