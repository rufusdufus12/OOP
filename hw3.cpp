/********************************
 *Amy Dong                      *
 *Object Oriented Programming   *
 *Terry Hostetler HW3           *
 *CoeCruz                       *
 ********************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

class Time{
public:
	//set hour
	void setHour(unsigned int h) {
		if (h >= 0 && h <= 23) {
			hour = h;
		}
		else {
			throw invalid_argument("Hour must be 0-23");
		}
	}
	//set minute
	void setMinute(unsigned int m) {
		if (m >= 0 && m <= 59) {
			minute = m;
		}
		else {
			throw invalid_argument("Minute must be 0-59");
		}
	}
	//set time
	void setTime(unsigned int h, unsigned int m) {
		setHour(h);
		setMinute(m);
	}
	void setTime(string t) {
		unsigned int h = stoi(t.substr(0, t.find(":")));
		unsigned int m = stoi(t.substr(t.find(":")+1));

		setTime(h, m);
	}

	//get hour
	int getHour() const {
		return hour;	}
	//get minute
	int getMinute() const {
		return minute;	}
	//get time
	string getTime() const {
		stringstream t;
		string str;

		t.fill('0');
		t << setw(2) << getHour() << ":"
		  << setw(2) << minute;
		t >> str;
		return str;
	}
	//get time in minutes from 00:00 (midnight)
	int getTimemin() const {
		return (getHour() * 60 + getMinute());
	}

private:
	unsigned int hour;
	unsigned int minute;
};

class Date{
public:
	//set month
	void setMonth (unsigned int m) {
		if (m >= 1 && m <= 12) {
			month = m;
		}
		else {
			throw invalid_argument("Month must be 1-12");
		}
	}
	//set year
	void setYear(unsigned int y) {
		if (y >= 0 && y < 100) {
			year = y;
		}
		else {
			throw invalid_argument("The year must be in the AD and between 00-99.");
		}
	}
	//set day
	void setDay(unsigned int d) {
		if ((month == 2 && leapYear(year) && d >= 1 && d <= 29) ||
		    (d >= 1 && d <= days[month])) {
				day = d;
		}
		else {
			throw invalid_argument("Day is out of range for the current month");
		}
	}
	//set date
	void setDate(unsigned int m, unsigned int d, unsigned int y) {
		setMonth(m);
		setYear(y);
		setDay(d);
	}
	void setDate(string date) {
		unsigned int d, m, y, pos = 0, pos2 = 0;

		pos = date.find("/");
		m = stoi(date.substr(0, pos));
		pos2 = date.find("/", pos+1);
		d = stoi(date.substr(pos+1, pos2));
		y = stoi(date.substr(pos2+1));
		setDate(m, d, y);
	}

	//get day
	int getDay() const{
		return day; }
	//get month
	int getMonth() const{
		return month; }
	//get month
	int getYear() const{
		return year; }
	//get date
	string getDate() const{
		stringstream d;
		string str;

		d.fill('0');
		d << setw(2) << month << "/"
			<< setw(2) << day << "/"
			<< setw(2) << year;
		d >> str;
		return str;
	}
	//get days
	int getDaysmonth() {
		if (leapYear(year) && month == 2) {
			return 29;
		}
		else {
			return days[month];
		}
	}
	//overload comparison operator <
	//should not have the case of same date
	bool operator <(const Date& d) {
		int yr1 = getYear(), yr2 = d.getYear();

		getYear() <= 15 ? yr1 += 2100 : yr1 += 2000;
		d.getYear() <= 15 ? yr2 += 2100 : yr2 += 2000;

		if (yr1 == yr2) {
			if (getMonth() == d.getMonth()) {
					return (getDay() < d.getDay());
			}
			else {
				return (getMonth() < d.getMonth());
			}
		}
		else {
			return (yr1 < yr2);
		}
	}

private:
	unsigned int month;
	unsigned int day;
	unsigned int year;

	static const unsigned int days[13];
	//test for leap year
	bool leapYear(unsigned int testYear) {
		return (testYear % 4 == 0);
	}
};
const unsigned int Date::days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Account{
public:
	Account(string n, string p, string e){
		setAccount(n, p, e);
	}

	//set name
	void setName(string n) {
		name = n; }
	//set phone number
	void setPhone(string p) {
		phone = p; }
	//set email address
	void setEmail(string e) {
		email = e; }

	//get name
	string getName() const {
		return name; }
	//get phone number
	string getPhone() const {
		return phone; }
	//get email address
	string getEmail() const {
		return email; }

	//set account details
	void setAccount(string n, string p, string e) {
		setName(n);
		setPhone(p);
		setEmail(e);
	}
private:
	string name;
	string phone;
	string email;
};

class Rides{
public:
	//set name
	void setName(string u) {
		name = u; }
	//set from location
	void setFloc(string f) {
		fLoc = f; }
	//set to location
	void setToloc(string to) {
		toLoc = to; }
	//set number of seats
	void setSeats(int n) {
		seats = n; }

	//return name
	string getName() const {
		return name; }
	//return from location
	string getFloc() const {
		return fLoc; }
	//return to location
	string getToloc() const {
		return toLoc; }
	//return number of seats
	unsigned int getSeats() const {
		return seats; }

	//set ride details
	virtual void setRide(string u, string f, string t, int s) {
		setName(u);
		setFloc(f);
		setToloc(t);
		setSeats(s);
	}
private:
	string name;
	string fLoc;
	string toLoc;
	int seats;
};

class OnCall: virtual public Rides{
public:
	OnCall(string u, string f, string t, int n, double c) {
		setRide(u, f, t, n, c);
	}

	//set cost
	void setCost(double c) {
		cost = c; }

	//get cost
	double getCost() const {
		return cost; }

	//set on call ride details
	void setRide(string u, string f, string t, int n, double c) {
		setName(u);
		setFloc(f);
		setToloc(t);
		setSeats(n);
		setCost(c);
	}
private:
	double cost;
};

class Specific: virtual public Rides{
public:
	Specific(Date d, Time t, string u, string f, string tL, int n) {
		setRide(d, t, u, f, tL, n);
	}

	//set date
	void setDate(Date d) {
		date = d; }
	//set time
	void setTime(Time t) {
		time = t; }

	//return date
	string getDate() const{
		return date.getDate(); }
	Date getDdate() const{
		return date; }
	//return time
	string getTime() const {
		return time.getTime(); }
	//return time in min from 00:00
	int getTimemin() const {
		return time.getTimemin(); }

	//set specific ride details
	void setRide(Date d, Time t, string u, string f, string tL, int n) {
		setDate(d);
		setTime(t);
		setName(u);
		setFloc(f);
		setToloc(tL);
		setSeats(n);
	}
private:
	Date date;
	Time time;
};

class Match: public Specific, public OnCall{
public:
	Match(Date d, Time t, string u, string f, string tL, int n, double c) : 
	  Specific(d, t, u, f, tL, n),  OnCall(u, f, tL, n, c){
		  setRide(d, t, u, f, tL, n, c);
	};
	//calculate time difference in minutes
	void setTimedif(Specific* req, Specific* ofr) {
		int mindiff(0);
		if (sameDate(req->getDate(), ofr->getDate())) {
			timedif = abs(req->getTimemin() - ofr->getTimemin());
		} else if (nextDay(req->getDdate(), ofr->getDdate())) {
			Time first, second;
			if (req->getDdate() < ofr->getDdate()) {
				first.setTime(req->getTime()), second.setTime(ofr->getTime());
			} else {
				first.setTime(ofr->getTime()), second.setTime(req->getTime());
			}

			timedif = (1440 - first.getTimemin()) + second.getTimemin();
		} else {
			//2 full day's time difference
			timedif = 2880;
		}
	}
	void setTimedif(int i) {
		timedif = i;
	}
	//set ride specific and on call versions
	void setRide(Date d, Time t, string u, string f, string tL, int n, double c) {
		setDate(d);
		setTime(t);
		setName(u);
		setFloc(f);
		setToloc(tL);
		setSeats(n);
		setCost(c);
	}

	int getTimedif() const {
		return timedif; }
private:
	int timedif;

	//check if the date is the same
	bool sameDate(string r, string o) {
		return (r == o);
	}
	//check for days next to each other
	bool nextDay(Date req, Date ride) {
		bool next = false;
		int days;
		int reqYr = req.getYear(), rideYr = ride.getYear();

		ride.getYear() <= 15 ? rideYr += 2100 : rideYr += 2000;
		req.getYear() <= 15 ? reqYr += 2100 : reqYr += 2000;

		//check same year
		if (reqYr == rideYr) {
			//check same month
			if (req.getMonth() == ride.getMonth()) {
				//check for one day apart within the same month
				if (max(req.getDay(), ride.getDay()) - min(req.getDay(), ride.getDay()) == 1) {
					next = true;
				}
			} else if (max(req.getMonth(), ride.getMonth()) - min(req.getMonth(), ride.getMonth()) == 1) {
				//check for end of one month into next
				if (ride.getDay() == 1 && req.getDay() == req.getDaysmonth()) {
					next = true;
				} else if (req.getDay() == 1 && ride.getDay() == ride.getDaysmonth()) {
					next = true;
				}
			}
		} else if (max(reqYr, rideYr) - min(reqYr, rideYr) == 1) {
			//turn of new year
			if (((req.getMonth() == 12 && req.getDay() == 31) &&
				(ride.getMonth() == 1 && ride.getDay() == 1)) ||
				((req.getMonth() == 1 && req.getDay() == 1) &&
				(ride.getMonth() == 12 && ride.getDay() == 31))) {
					next = true;
			}
		}

		return next;
	}
};

//compare names for accounts
bool accountComp(Account* i, Account* j) {
	return (i->getName() < j->getName());
}
//compare time for ride (date and time)
bool dateComp(Specific* i, Specific* j) {
	if (i->getDate() == j->getDate()) {
		return (i->getTimemin() < j->getTimemin());
	}
	else {
		return (i->getDdate() < j->getDdate());
	}
}
//compare names for oncall
bool nameComp(OnCall* i, OnCall* j) {
	return (i->getName() < j->getName());
}
//compare the difference in times
bool timeComp(Match i, Match j) {
	return (abs(i.getTimedif()) < abs(j.getTimedif()));
}
//compare the difference in cost
bool costComp(Match i, Match j) {
	return (i.getCost() < j.getCost());
}

int main() {
	ifstream in("transactions.in");
	int lnum;
	string code;

	vector<Account *> riders, drivers;
	vector<Specific *> requests, offers;
	vector<OnCall *> oncall;

	//temp data holders
	string name, tL, fL;
	int seats;

	//read file
	if (in.is_open()) {
		in >> lnum;
		for (int i(0); i < lnum; i++) {
			in >> code;

			if (code == "RIDR") {
				string phone, email;
				in >> name >> phone >> email;

				riders.push_back(new Account(name, phone, email));
			}
			else if (code == "DRVR") {
				string phone, email;
				in >> name >> phone >> email;

				drivers.push_back(new Account(name, phone, email));
			}
			else if (code == "REQU") {
				string strdt, strtm;
				in >> strdt >> strtm >> name >> fL >> tL >> seats;

				Date dt; Time tm;
				dt.setDate(strdt);
				tm.setTime(strtm);

				requests.push_back(new Specific(dt, tm, name, fL, tL, seats));
			}
			else if (code == "TOFR") {
				string strdt, strtm;
				in >> strdt >> strtm >> name >> fL >> tL >> seats;

				Date dt; Time tm;
				dt.setDate(strdt);
				tm.setTime(strtm);

				offers.push_back(new Specific(dt, tm, name, fL, tL, seats));
			}
			else if (code == "ONCL") {
				double cost;
				in >> name >> fL >> tL >> seats >> cost;

				oncall.push_back(new OnCall(name, fL, tL, seats, cost));
			}
		}
	}
	else {
		cout << "Unable to open file:  transactions.in\n";
	}

	//sort Accounts by name
	sort(riders.begin(), riders.end(), accountComp);
	sort(drivers.begin(), drivers.end(), accountComp);
	//sort Specific rides by time
	sort(requests.begin(), requests.end(), dateComp);
	sort(offers.begin(), offers.end(), dateComp);
	//sort OnCall rides by name
	sort(oncall.begin(), oncall.end(), nameComp);

	//make output file
	ofstream out("transactions.out");
	if (out.is_open()) {
		out << setfill(' ') << left;

		out << "Rider accounts:\n";
		for (int i(0); i < riders.size(); i++) {
			for (int j(0); j < 7; j++) {
				out << ' ';
			}
			out << setw(15) << riders[i]->getName()
				<< setw(13) << riders[i]->getPhone()
				<< riders[i]->getEmail() << endl;
		}
		out << "Driver accounts:\n";
		for (int i(0); i < drivers.size(); i++) {
			for (int j(0); j < 7; j++) {
				out << ' ';
			}
			out << setw(15) << drivers[i]->getName()
				<< setw(13) << drivers[i]->getPhone()
				<< drivers[i]->getEmail() << endl;
		}
		out << "Requests for rides:\n";
		for (int i(0); i < requests.size(); i++) {
			for (int j(0); j < 7; j++) {
				out << ' ';
			}
			out << setw(9) << requests[i]->getDate()
				<< setw(6) << requests[i]->getTime()
				<< setw(12) << requests[i]->getName()
				<< setw(13) << requests[i]->getFloc()
				<< setw(13) << requests[i]->getToloc()
				<< requests[i]->getSeats() << endl;
		}
		out << "Offers (time-specific) for rides:\n";
		for (int i(0); i < offers.size(); i++) {
			for (int j(0); j < 7; j++) {
				out << ' ';
			}
			out << setw(9) << offers[i]->getDate()
				<< setw(6) << offers[i]->getTime()
				<< setw(12) << offers[i]->getName()
				<< setw(13) << offers[i]->getFloc()
				<< setw(13) << offers[i]->getToloc()
				<< offers[i]->getSeats() << endl;
		}
		out << "On call offers for rides:\n";
		for (int i(0); i < oncall.size(); i++) {
			for (int j(0); j < 7; j++) {
				out << ' ';
			}
			out << setw(12) << oncall[i]->getName()
				<< setw(13) << oncall[i]->getFloc()
				<< setw(13) << oncall[i]->getToloc()
				<< setw(3) << oncall[i]->getSeats()
				<< setprecision(2) << fixed << oncall[i]->getCost()<< endl;
		}

		out << "Ride matches:";
		for (int i(0); i < requests.size(); i++) {
			out << endl;
			for (int j(0); j < 7; j++) {
				out << ' ';
			}
			out << requests[i]->getName() << " ride for "
				<< requests[i]->getSeats() << " from "
				<< requests[i]->getFloc() << " to "
				<< requests[i]->getToloc() << " on "
				<< requests[i]->getDate() << " at time "
				<< requests[i]->getTime() << endl;

			int mCount(0);
			vector<Match> matchRides;

			//check for matching specific rides
			for (int j(0); j < offers.size(); j++) {
				if (requests[i]->getFloc() == offers[j]->getFloc() &&
					requests[i]->getToloc() == offers[j]->getToloc() &&
					requests[i]->getSeats() <= offers[j]->getSeats()) {
						Time tm;
						tm.setTime(offers[j]->getTime());

						Match m(offers[j]->getDdate(), tm, offers[j]->getName(), offers[j]->getFloc(), offers[j]->getToloc(), offers[j]->getSeats(), 0);
						m.setTimedif(requests[i], offers[j]);

						if (m.getTimedif() <= 60) {
							mCount++;
							matchRides.push_back(m);
						}
				}
			}
			//check for matching oncall rides
			for (int j(0); j < oncall.size(); j++) {
				if (requests[i]->getFloc() == oncall[j]->getFloc() &&
					requests[i]->getToloc() == oncall[j]->getToloc() &&
					requests[i]->getSeats() <= oncall[j]->getSeats()) {
						//filler date and time
						Date dt;	Time tm;
						dt.setDate("12/31/15");
						tm.setTime("23:59");

						Match m(dt, tm, oncall[j]->getName(), oncall[j]->getFloc(), oncall[j]->getToloc(), oncall[j]->getSeats(), oncall[j]->getCost());
						m.setTimedif(2880);  //default 2 day time difference

						matchRides.push_back(m);

						mCount++;
				}
			}

			//sort match vector based on time difference
			sort(matchRides.begin(), matchRides.end(), timeComp);
			//sort match vector based on cost (aka free rides come first based on  time)
			sort(matchRides.begin(), matchRides.end(), costComp);

			//output matches
			if (mCount > 0){
				out << "       " << mCount << " Matches found!\n";
				for (int k(0); k < mCount; k++){
					out << "       #" << k+1 << " Ride with "
						<< matchRides[k].getName() << " - ";
					if (matchRides[k].getCost() == 0) {
						out << "leaving on "
						<< matchRides[k].getDate() << " at "
						<< matchRides[k].getTime() << " - "
						<< matchRides[k].getSeats() << " seats available\n";
					}
					else {
						out << matchRides[k].getSeats() << " seats available "
							<< "anytime at $" << setprecision(2) << fixed << matchRides[k].getCost() << endl;
					}
				}
			}
			else {
				out << "       Sorry, no matches found.\n";
			}
		}
	}
	else {
		cout << "There was an issue with making the file:  transactions.out\n";
	}
	return 0;
}
