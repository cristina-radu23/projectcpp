#include <iostream>
#include<string>
#include <typeinfo>
using namespace std;

#pragma once
struct Address {
	string street;
	string streetNo;
	string city;
};

class Location {
private:
	int locationId;
	string locationName = "";
	int zonesNo = 0; //mai intai ne trebuie numarul de zone ca apoi in functie de el sa alocam memorie pt vector
	string* zones = nullptr;
	int rowsNo = 0;
	int seatsPerRow = 0;
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
		if (newZones != nullptr)
		{
			if (this->zones)
				delete[] this->zones; //zones e posibil deja sa aiba o lista de valori puse, si ca sa stergem valorile existente si sa punem unele noi
			this->zones = new string[newZoneNo];
			//memcpy(this->zones, newZones, sizeof(string) * newZoneNo);
			for (int i = 0; i < newZoneNo; i++) {
				this->zones[i] = newZones[i];
			}

			this->zonesNo = newZoneNo;
		}
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

#pragma region Address

	void setAddress(const Address& address) {
		this->address.city = address.city;
	}
	const Address& getAddress() const {
		return this->address;
	}

	//Address getAddress()
	//{
	//	return this->address;
	//}
	// 
	//void setAddress(const Address &address)
	//{
	//	this->address.street = address.street;
	//	this->address.streetNo = address.streetNo;
	//	this->address.city = address.city;
	//}
#pragma endregion

public:
#pragma region Constructors
	Location() : locationId(Location::noLocations)
	{
		this->locationName="";
		this->zonesNo = 0;
		this->zones = nullptr;
		this->seatsPerRow = 0;
		this->rowsNo = 0;
		Location::noLocations++;
	}
	Location(string name) : locationId(Location::noLocations)
	{
		this->setLocationName(name);
		Location::noLocations++;
	}
	Location(string name, Address address) : locationId(Location::noLocations)
	{
		this->setLocationName(name);
		this->setAddress(address);
		Location::noLocations++;
	}

	Location(string name, Address address, int seatsPerRow, int rowsNo) : locationId(Location::noLocations)
	{
		this->setLocationName(name);
		this->setAddress(address);
		this->setSeatsPerRow(seatsPerRow);
		this->setRowsNo(rowsNo);
		Location::noLocations++;
	}
	Location(string name, Address address, int seatsPerRow, int rowsNo, int zonesNo, string* zones) : locationId(Location::noLocations)
	{
		this->setLocationName(name);
		this->setAddress(address);
		this->setSeatsPerRow(seatsPerRow);
		this->setRowsNo(rowsNo);
		this->setZones(zones, zonesNo);
		Location::noLocations++;
	}


	//copy constructor
	Location(const Location& loc) :locationId(Location::noLocations)
	{
		//cout << endl << "Copy ctor" << endl;
		this->locationName = loc.locationName;
		this->zonesNo = loc.zonesNo;
		this->rowsNo = loc.rowsNo;
		this->seatsPerRow = loc.seatsPerRow;
		this->setZones(loc.zones, loc.zonesNo);
		this->setAddress(loc.address);
	}

	//destructor
	~Location() {
		//cout << endl << "Destructor" << endl;
		delete[] this->zones;
	}
#pragma endregion

#pragma region Methods
	void print() {
		cout << endl << "Location name: " << this->locationName;
		cout << endl << "Rows number: " << this->rowsNo;
		cout << endl << "Seats per row: " << this->seatsPerRow;
		cout << endl << "Number of zones: " << this->zonesNo;

		if (this->zones != nullptr) {
			cout << endl << "Zones:";
			for (int i = 0; i < this->zonesNo; i++) {
				cout << " " << this->zones[i];
			}
		}
		cout << endl << "Address: ";
		cout << endl << "Address city: " << this->address.city;
		cout << endl << "Address street: " << this->address.street;
		cout << endl << "Address street number: " << this->address.streetNo;
	}

	int getLocationCapacity() {
		return this->rowsNo * this->seatsPerRow;
	}

	void addZone(string zone) {
		if (this->zones == nullptr)
			return;
		string* newArray = new string[this->zonesNo + 1];
		for (int i = 0; i < this->zonesNo; i++) {
			newArray[i] = this->zones[i];
		}
		newArray[this->zonesNo] = zone;
		this->zonesNo += 1;
		if (this->zones != nullptr) {
			delete[] this->zones;
		}
		this->zones = newArray;
	}
#pragma endregion

#pragma region Operators
	void operator=(Location loc) {
		this->setLocationName(loc.locationName);
		this->setZonesNo(loc.zonesNo);
		if (this->zones == loc.zones) {
			return; //it's the same object
		}
		else
		{
			this->setZones(loc.zones, loc.zonesNo);
			this->setRowsNo(loc.rowsNo);
			this->setSeatsPerRow(loc.seatsPerRow);
		}
	}

	Location operator+(string zone) {
		Location copy = *this;
		this->addZone(zone);
		return copy;
	}

	void operator+=(string zone) {
		this->addZone(zone);
	}

	bool operator>(Location& location) {
		if (this->getLocationCapacity() > location.getLocationCapacity()) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(Location& location) {
		if (this->getLocationCapacity() == location.getLocationCapacity())
			return true;
		else
			return false;
	}

	bool operator!() {
		if (this->zonesNo < 0)
			return true;
		else
			return false;
	}

	explicit operator int() {
		return this->getLocationCapacity();
	}

	Location operator++() {
		this->setRowsNo(this->rowsNo + 1);
		return *this;
	}

	Location operator++(int) {
		Location copy = *this;
		this->setRowsNo(this->rowsNo + 1);
		return copy;
	}

	string& operator[](int index)
	{
		if (index >= this->zonesNo) {
			cout << "Array index out of bound, exiting";
			exit(0);
		}
		return this->zones[index];
	}

#pragma endregion

	friend void operator>>(istream& console, Location& location);
};


#pragma once
inline
void operator<<(ostream& console, Location location) {
	console << endl << "The location data is: ";
	console << endl << "Location name: " << " " << location.getLocationName();
	if (location.getZonesNo() > 0) {
		string* zones = location.getZones();
		console << endl << "Zones: ";
		for (int i = 0; i < location.getZonesNo(); i++) {
			console << zones[i] << " ";

		}
	}
	else {
		console << endl << "No zones";
	}
	console << endl << "No of rows: " << " " << location.getRowsNo();
	console << endl << "No of seats per rows: " << " " << location.getSeatsPerRow();
	Address address = location.getAddress();
	console << endl << "Address: " << address.city << ", " << address.street << " " << address.streetNo;
}

#pragma once
inline
void operator>>(istream& console, Location& location) {
	cout << endl << "Location name: "; console >> location.locationName;
	cout << "No of zones: "; console >> location.zonesNo;
	if (location.zonesNo > 0) {
		delete[] location.zones;
		location.zones = new string[location.zonesNo];
		cout << "Zones: " << endl;
		for (int i = 0; i < location.getZonesNo(); i++) {
			cout << "Zone " << i + 1 << ": ";
			console >> location.zones[i];
		}
	}
	cout << "No of rows: "; console >> location.rowsNo;
	cout << "No of seats per rows: "; console >> location.seatsPerRow;
	cout << "Address: ";
	cout << "Address city: "; console >> location.address.city;
	cout << "Address street: "; console >> location.address.street;
	cout << "Address street number: "; console >> location.address.streetNo;

}

#pragma once
inline
Location operator+(string zone, Location loc) {
	return loc + zone; // pt ca il avem si pe celalalt
}