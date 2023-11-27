#include <iostream>
#include <string>
#include <typeinfo>
#include <ctime>
#include <chrono>  
using namespace std;


enum class TicketType {GENERAL_ACCESS=10, VIP=20};


class Ticket {
private:

//	Event eventName;
	int ticketId;
	float price;
	char* ownerName = nullptr;
	int earlyBookingDiscount[3] = { 3, 5, 10 };
	static int ticketNo;
	TicketType type=TicketType::GENERAL_ACCESS;

public:

	//Event getEventName()
	//{
	//	return this->eventName;
	//}

	void setType(TicketType type)
	{
		this->type = type;
	}

	TicketType getType()
	{
		return this->type;
	}

	float getPrice() {
		return this->price;
	}
	void setPrice(float price) {
		this->price = price;
	}

	string getOwnerName() {
		return string(this->ownerName);
	}

	const int* getEarlyBookingDiscount() {
		return this->earlyBookingDiscount;
	}

	void setOwnerName(string name) {
		this->ownerName = new char[name.size() + 1];
		strcpy_s(this->ownerName, name.size() + 1, name.c_str());
	}
#pragma region Costr/Destr
	Ticket() {
		this->price = 0;
		this->ownerName = nullptr;
		Ticket::ticketNo++;
	}


	Ticket(float price) {
		this->setPrice(price);
		Ticket::ticketNo++;
	}

	Ticket( const char* ownerName/*, Event eventName*/) {
		this->ownerName = new char[strlen(ownerName) + 1];
		strcpy_s(this->ownerName, strlen(ownerName) + 1, ownerName);
		Ticket::ticketNo++;
	//	this->eventName = eventName;
	}

	Ticket(float price, const char* ownerName) {
		//this->ownerName = new char[strlen(ownerName) + 1];
		//strcpy_s(this->ownerName, strlen(ownerName) + 1, ownerName);
		this->setOwnerName(ownerName);
		this->setPrice(price);
		Ticket::ticketNo++;
	}

	~Ticket() {
		delete[] this->ownerName;
		Ticket::ticketNo--;
	}

	//cpy ctor

	Ticket(const Ticket& source) {
		this->price = source.price;
		this->setOwnerName(string(source.ownerName));
	}

#pragma endregion

	//float GetPrice(DateTime date)
	//{
	//	std::time_t t = std::time(0);   // get time now
	//	std::tm* now = std::localtime(&t);
	//	std::cout << now->tm_year;

	//	auto x = (now->tm_year + 1900) / (now->tm_mon + 1) / now->tm_mday;
	//	auto y = date.year / date.month / date.day;

	//	//std::chrono::system_clock::time_point start_date = std::chrono::system_clock::from_iso_string("2022-01-01");
	//	//std::chrono::system_clock::time_point end_date = std::chrono::system_clock::from_iso_string("2022-01-31");
	//	//// Calculate the number of days between the start and end dates
	//	//std::chrono::duration<int, std::ratio<86400>> diff = end_date - start_date;
	//	//std::cout << "Number of days between the two dates: " << diff.count() << std::endl;
	//	//return 0;

	//}


	Ticket operator=(const Ticket& source)
	{
		//test for self equality
		if (&source == this) {
			return source;
		}
		this->price = source.price;
		this->type = source.type;

		return *this;
	}



};

#pragma once
inline

void operator<<(ostream& console, Ticket e)
{
	console << endl <<"person " << e.getOwnerName();
	//console << endl << " has ticket for " << e.getEventName();

}