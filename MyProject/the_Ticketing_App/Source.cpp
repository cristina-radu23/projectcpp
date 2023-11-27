#include <iostream>
#include<string>
#include <typeinfo>
#include "Location.cpp"
#include "Event.cpp"
#include "Ticket.cpp"
using namespace std;

int Location::noLocations = 0;
int Event::eventNo = 0;
int Ticket::ticketNo = 0;

int main()
{
	Address address;
	address.street = "Bld Preciziei";
	address.streetNo = "3";
	address.city = "Bucuresti";
	string* zones = new string[2];
	zones[0] = "stanga";
	zones[1] = "dreapta";
	Location location("Cinema city AFI", address, 12, 10);
	location.setZones(zones, 2);
	//Location location("Cinema city AFI");
	//cin >> location;
	//location.print();
	cout << endl << "Location total seats capacity: " << location.getLocationCapacity();

	Location location2 = location;
	Address address2;
	address2.street = "Bld Iuliu Maniu";
	address2.streetNo = "76";
	address2.city = "Bucuresti";
	location2.setLocationName("Cinema city ParkLake");
	location2.setAddress(address2);
	location2 = location2 + "centru";

	cout << location;
	cout << endl;
	cout << location2;

	location2 += "fata scenei";
	location2.setRowsNo(20);
	cout << endl;
	cout << location2;

	//if (location > location2)
	//	cout << endl << location.getLocationName() << " is bigger";
	//else
	//	cout << endl << location2.getLocationName() << " is bigger";

	//if (!location2)
	//	cout << endl << location2.getLocationName() << " doesn't have any zone";
	//else
	//	cout << endl << location2.getLocationName() << " has at least one zone";

	//int cap = (int)location2;
	//cout << endl << "The capacity for " << location2.getLocationName() << " is " << cap;

	//location2++;
	//cout << endl << "The capacity for " << location2.getLocationName() << " is " << location2.getLocationCapacity();

	//if (location == location2)
	//	cout << endl << "The locations have the same capacity";
	//else
	//	cout << endl << "The locations don't have the same capacity";
	//cout << endl << location2[2] << endl;
	//time_t t = time(0);   // get time now
	//tm* now = localtime(&t);
	//cout << (now->tm_year + 1900) << '-'
	//	<< (now->tm_mon + 1) << '-'
	//	<< now->tm_mday
	//	<< "\n";
	cout << endl;
	Event event1("concert", location2);
	cout <<endl << event1;

	Ticket bilet1(120, "Radu Diana");
	//event1.setTickets(ticket, 2);
	cout << bilet1;
}