#include <iostream>
#include<string>
#include <typeinfo>
using namespace std;

struct DateTime {
	int day;
	int month;
	int year;
	int hour;
	int minute;
};
struct Address {
	string street;
	string streetNo;
	string city;
};
class Location {
	private:
		int locationId;
		string locationName;
		int zonesNo; //mai intai ne trebuie numarul de zone ca apoi in functie de el sa alocam memorie pt vector
		string* zones = nullptr;
		int rowsNo;
		int seatsPerRow;
		int seatsCapacity;
		Address address;
		static int noLocations;


public:
	static const int MIN_NAME = 2;
	static const int MAX_NAME = 100;

public:
	#pragma region LocationName
	string getLocationName()
	{
		return this->locationName;
	}

	void setLocationName(string value)
	{
		if (value.size() >= Location::MIN_NAME)
		{
			this->locationName = value;
		}
		else
		{
			throw new exception("Name too short");
		}
		if (value.size() <= Location::MAX_NAME)
		{
			this->locationName = value;
		}
		else
		{
			throw new exception("Name too long");
		}

	}
	#pragma endregion

	#pragma region Zones
	string* getZones()
	{
		string* copy = new string[this->zonesNo]; //se face copie ca sa nu se modifice valorile din obiectul original
		for (int i = 0; i < this->zonesNo; i++) {
			copy[i] = this->zones[i];
		}
		return copy;
	}
	void setZones(string* newZones, int newZoneNo)
	{
		delete[] this->zones; //zones e posibil deja sa aiba o lista de valori puse, si ca sa stergem valorile existente si sa punem unele noi
		this->zones = new string[newZoneNo];
		memcpy(this->zones, newZones, sizeof(string) * newZoneNo);

		this->zonesNo = newZoneNo;
	}
	#pragma endregion

	#pragma region ZonesNo
	int getZonesNo()
	{
		return this->zonesNo;
	}
	void setZonesNo(int value)
	{
		this->zonesNo = value;
		//if (decltype(value) == decltype(int)) //poate nu merge
		//{
		//	this->rowsNo = value;
		//}
		//else 
		//{
		//	throw new exception("Value is not integer");
		//}
	}
	#pragma endregion

	#pragma region RowsNo
	int getRowsNo()
	{
		return this->rowsNo;
	}
	void setRowsNo(int value) 
	{
		this->rowsNo = value;
		//if (typeid(value) == typeid(int)) //poate nu merge
		//{
		//	this->rowsNo = value;
		//}
		//else 
		//{
		//	throw new exception("Value is not integer");
		//}
	}
	#pragma endregion

	#pragma region SeatsPerRow
	int getSeatsPerRow()
	{
		return this->seatsPerRow;
	}

	void setSeatsPerRow(int value)
	{
		if (typeid(int) == typeid(value)) //poate nu merge
			this->seatsPerRow = value;
		else {
			throw new exception("Value is not integer");
		}
	}
	#pragma endregion

	#pragma region SeatsCapacity
	int getSeatsCapacity()
	{
		return this->seatsCapacity;
	}

	void setSeatsCapacity(int value)
	{
		if (typeid(int) == typeid(value)) //poate nu merge
			this->seatsCapacity = value;
		else {
			throw new exception("Value is not integer");
		}
	}
	#pragma endregion

	#pragma region Address
	Address getAddress()
	{
		return this->address;
	}
	void setAddress(Address address) 
	{
		this->address.street = address.street;
		this->address.streetNo = address.streetNo;
		this->address.city = address.city;
	}
	#pragma endregion

	public:
	#pragma region Constructors
	Location(string name, Address address) : locationId(Location::noLocations)
	{
		this->setLocationName(name);
		this->setAddress(address);
		Location::noLocations++;
	}

	Location(string name, Address address, int seatsPerRow, int seatsCapacity, int rowsNo) : locationId(Location::noLocations)
	{
		this->setLocationName(name);
		this->setAddress(address);
		this->setSeatsCapacity(seatsCapacity);
		this->setSeatsPerRow(seatsPerRow);
		this->setRowsNo(rowsNo);
		Location::noLocations++;
	}

	//copy constructor
	Location(Location& loc) :locationId(Location::noLocations) 
	{
		cout << "Copy ctor" << endl;
		this->setLocationName(loc.locationName);
		this->setZonesNo(loc.zonesNo);
		this->setRowsNo(loc.rowsNo);
		this->setSeatsCapacity(loc.seatsCapacity);
		this->setSeatsPerRow(loc.seatsPerRow);
		this->setZones(loc.zones, loc.zonesNo);
		this->setAddress(loc.address);
	}

	//destructor
	~Location() {
		cout << "Destructor" << endl;
		delete[] this->zones;
	}
	#pragma endregion

	void print() {
		cout << endl << "Location name: " << this->locationName;
		cout << endl << "Rows number: " << this->rowsNo;
		cout << endl << "Seats per row: " << this->seatsPerRow;
		cout << endl << "Seats capacity: " << this->seatsCapacity;
		cout << endl << "Number of zones: " << this->zonesNo;

		if (this->zones != nullptr) {
			cout << endl << "Zones:";
			for (int i = 0; i < this->zonesNo; i++) {
				cout << " " << this->zones[i];
			}
		}
	}
};

class Event {
	private:
		int eventId;
		string eventName;
		DateTime dateTime;
		Location location;

	public:
		static const int MIN_NAME = 2;
		static const int MAX_NAME = 100;
		static int genEventId;

	public:
	Event(string eventName, string locationName, Address address) : location(locationName, address) {
		this->setEventName(eventName);
	}
	#pragma region EventName
	string getEventName()
	{
		return this->eventName;
	}

	void setEventName(string value)
	{
		if (value.size() >= Event::MIN_NAME)
		{
			this->eventName = value;
		}
		else
		{
			throw new exception("Name too short");
		}
		if (value.size() <= Event::MAX_NAME)
		{
			this->eventName = value;
		}
		else
		{
			throw new exception("Name too long");
		}

	}
	#pragma endregion

	#pragma region DateTime
	DateTime getDateTime()
	{
		return this->dateTime;
	}
	void setDateTime(DateTime dateTime)
	{
		this->dateTime.day = dateTime.day;
		this->dateTime.month = dateTime.month;
		this->dateTime.year = dateTime.year;
	}
	#pragma endregion

	#pragma region Location
	Location getLocation() {
		return this->location;
	}

	void setLocation(Location loc) {
		this->location = loc;
	}
	#pragma endregion

	void print() {
		cout << endl << "Event name: " << this->eventName;
		//cout << endl << "Data: " << this->dateTime;
		cout << endl << "Location: ";
		this->location.print();
	}

};

int Location::noLocations = 0;
int Event::genEventId = 0;

int main()
{
	Address address;
	address.street = "Bld Iuliu Maniu";
	address.streetNo = "76";
	address.city = "Bucuresti";
	Location loc("Sala Palatului", address);
	int zonesNo;
	cout << "Nr zone: "; cin >> zonesNo;
	string* zones = new string[zonesNo];
	for (int i = 0; i < zonesNo; i++) 
	{
		cout << "Zona " << i+1 <<": "; cin >> zones[i];
	}
	int rowsNo;
	cout << "Nr randuri: "; cin >> rowsNo;
	cout << typeid("rowsNo").name() << endl;

	if (typeid(rowsNo) == typeid(int)) //poate nu merge
	{
		loc.setRowsNo(rowsNo);
	}
	else
	{
		throw new exception("Value is not integer");
	}

	loc.setRowsNo(rowsNo);

	loc.setZones(zones, zonesNo);

//	Location* loc2 = new Location(loc);
	//loc2->print();

	Event* event = new Event("Concert", "Pta Constitutiei", address);
	event->print();
	event->setLocation(loc);
	event->print();

 }