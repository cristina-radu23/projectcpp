#include <iostream>
#include<string>
#include <typeinfo>
#include "Location.cpp"
#include "Ticket.cpp"

using namespace std;

#pragma once
struct DateTime {
	int day;
	int month;
	int year;
	int hour;
	int minute;
};



class Event {
private:
	int eventId;
	string eventName="";
	DateTime dateTime;
	Location location;
	int ticketsNo = 0;
	//Ticket* tickets = nullptr;

public:
	static const int MIN_NAME = 2;
	static const int MAX_NAME = 100;
	static int eventNo;

public:
	Event(string eventName, string locationName, Address address) : location(locationName, address)
	{
		this->setEventName(eventName);
	}

#pragma region EventName


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

	string getEventName()
	{
		return this->eventName;
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

#pragma region TicketsNo


	void setTicketsNo(int value)
	{
		this->ticketsNo = value;
	}

	int getTicketsNo()
	{
		return this->ticketsNo;
	}

#pragma endregion

#pragma region Tickets
	//Ticket* getTickets()
	//{
	//	Ticket* copy = new Ticket[this->ticketsNo];
	//	for (int i = 0; i < this->ticketsNo; i++) {
	//		copy[i] = Ticket(this->tickets[i]);
	//	}
	//	return copy;
	//}
	//void setTickets(Ticket* newTickets, int newTicketsNo)
	//{
	//	if (newTickets != nullptr)
	//	{
	//		if (this->tickets)
	//			delete[] this->tickets; //zones e posibil deja sa aiba o lista de valori puse, si ca sa stergem valorile existente si sa punem unele noi
	//		this->tickets = new Ticket[newTicketsNo];
	//		//memcpy(this->zones, newZones, sizeof(string) * newZoneNo);
	//		for (int i = 0; i < newTicketsNo; i++) {
	//			this->tickets[i] = Ticket(newTickets[i]);
	//		}

	//		this->ticketsNo = newTicketsNo;
	//	}
	//}
#pragma endregion

	void print() {
		cout << endl << "Event name: " << this->eventName;
		//cout << endl << "Data: " << this->dateTime;
		cout << endl << "Location: ";
		this->location.print();
	}

#pragma region Constructors

	Event()
	{
		this->eventName = "";
	}

	// ctor w param eventName

	Event(string eventName, Location location)
	{
		this->eventName = eventName;
		this->location = Location(location);
		eventNo++;
	}


	// ctor w all param

	Event(string eventName, DateTime data, Location location, int ticketsNo)
	{
		this->dateTime = data;
		this->location = Location(location);
		this->eventName = eventName;
		this->ticketsNo = ticketsNo;
		eventNo++;
	}

	//copy ctor
	Event(const Event& source)
	{
		this->dateTime = source.dateTime;
		this->location = Location(source.location);
		this->eventName = source.eventName;
		this->ticketsNo = source.ticketsNo;
		eventNo++;
	}

	//destructor

	~Event()
	{
		eventNo--;
	}

	Event operator=(const Event& source)
	{
		//test for self equality
		if (&source == this) {
			return source;
		}
		this->eventName = source.eventName;
		this->location = source.location;

		return *this;
	}
#pragma endregion

#pragma region Methods
	void delayEventByHour(int delay) {
		this->dateTime.hour += delay;
	}
#pragma endregion


#pragma region Operators
	void operator=(Event ev) {
		this->dateTime = ev.dateTime;
		this->location = Location(ev.location);
		this->eventName = ev.eventName;
	}

	Event operator+(int delay) {
		Event copy = *this;
		this->delayEventByHour(delay);
		return copy;
	}

	void operator+=(int delay) {
		this->delayEventByHour(delay);
	}

	bool operator>(Event& ev) {
		if (this->ticketsNo > ev.ticketsNo) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(Event& ev) {
		if (this->ticketsNo == ev.ticketsNo)
			return true;
		else
			return false;
	}

	bool operator!() {
		if (this->ticketsNo == 0)
			return true;
		else
			return false;
	}

	explicit operator string() {
		return this->eventName + " " + to_string(this->dateTime.day) + "/" + to_string(this->dateTime.month) + "/" + to_string(this->dateTime.year);
	}

	Event operator++() {
		this->delayEventByHour(this->dateTime.hour + 1);
		return *this;
	}

	Event operator++(int) {
		Event copy = *this;
		this->delayEventByHour(this->dateTime.hour + 1);
		return copy;
	}

	//Ticket& operator[](int index)
	//{
	//	if (index >= this->ticketsNo) {
	//		cout << "Array index out of bound, exiting";
	//		exit(0);
	//	}
	//	return this->tickets[index];
	//}

#pragma endregion

	friend void operator<<(ostream& console, Event e);
};

#pragma once
inline
void operator<<(ostream& console, Event e)
{
	console << endl << "The event is: " << e.getEventName();
	console << endl << "The event location is: " << e.location;

}

//operatori si ctori