/********************************
 *Amy Dong                      *
 *Object Oriented Programming   *
 *Terry Hostetler HW2           *
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
		return hour; }
	//get minute
	int getMinute() const {
		return minute; }
	//get time
	string getTime() const {
		stringstream t;
		string str;

		t.fill('0');
		t << setw(2) << hour << ":"
			<< setw(2) << minute;
		t >> str;
		return str;
	}

private:
	unsigned int hour;
	unsigned int minute;
};

class Date{
public:
	//set month
	void setMonth(unsigned int m) {
		if (m >= 1 && m <=12) {
			month = m;
		}
		else {
			throw invalid_argument("Month must be 1-12");
		}
	}
	//set year
	void setYear(unsigned int y) {
		if (y >= 0) {
			year = y;
		}
		else {
			throw invalid_argument("Years must be in the AD");
		}
	}
	//set day
	void setDay(unsigned int d) {
		if ((month == 2 && leapYear(year) && d >= 1 && d <= 29) ||
			(d >= 1 && d <= days[month])) {
			day = d;
		}
		else {
			throw invalid_argument("Day is out of range for the current month and year");
		}
	}
	//set date
	void setDate(unsigned int m, unsigned int d, unsigned int y) {
		setMonth(m);
		setYear(y);
		setDay(d);
	}
	void setDate(string date) {
		unsigned int dy, mn, yr, pos = 0, pos2 = 0;

		pos = date.find("/");
		mn = stoi(date.substr(0, pos));
		pos2 = date.find("/", pos+1);
		dy = stoi(date.substr(pos+1, pos2));
		yr = stoi(date.substr(pos2+1));
		setDate(mn, dy, yr);
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
		return days[month];
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

class RideDetails{
public:
	//set date
	void setDate(Date d) {
		date = d; }
	//set time
	void setTime(Time t) {
		time = t; }
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
	//set cost
	void setCost(double c){
		cost = c; }
	//set all values of RideDetails
	void setRide(Date d, Time t, string u, string f, string tL, int n) {
		setDate(d);
		setTime(t);
		setName(u);
		setFloc(f);
		setToloc(tL);
		setSeats(n);
		setCost(0);
	}
	void setRide(string u, string f, string tL, int n, double c) {
		setName(u);
		setFloc(f);
		setToloc(tL);
		setSeats(n);
		setCost(c);
	}

	//return date
	string getDate() const{
		return date.getDate(); }
	//return time
	string getTime() const {
		return time.getTime(); }
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
	//return cost
	double getCost() const{
		return cost; }

private:
	Date date;
	Time time;
	string name;
	string fLoc;
	string toLoc;
	unsigned int seats;
	double cost;
};

class MatchDetails{
public:
	//set date
	void setDate(string d) {
		date.setDate(d); }
	//set name
	void setName(string u) {
		name = u; }
	//set time
	void setTime(Time t) {
		time = t; }
	//set number of seats
	void setSeats(int n) {
		seats = n; }
	//set cost
	void setCost(double c) {
		cost = c; }
	//set name, time, and number of seats
	void setMatch(string d, string u, Time t, int n, double c) {
		setDate(d);
		setName(u);
		setTime(t);
		setSeats(n);
		setCost(c);
	}
	//calculate and set the time difference in minutes
	void setTimedif(RideDetails req, RideDetails ride) {
		int hourdiff(0), mindiff(0);
		Time reqT, rideT;
		Date reqD, rideD;
		reqT.setTime(req.getTime());
		rideT.setTime(ride.getTime());
		reqD.setDate(req.getDate());
		rideD.setDate(ride.getDate());

		if(sameDate(reqD, rideD)) {
			//calulate difference in minutes
			//normal cases (can be modified to abs(reqT.getHour() - rideT.getHour()))
			if (reqT.getHour() < rideT.getHour()) {
				mindiff = (60 - reqT.getMinute()) + rideT.getMinute();
				if (reqT.getHour() + 1 >= 24) {
					hourdiff = rideT.getHour() - ((rideT.getHour()+1) % 24);
				} else {
					hourdiff = rideT.getHour() - (reqT.getHour() +1);
				}
			} else if (rideT.getHour() < reqT.getHour()) {
				mindiff = reqT.getMinute() + (60 - rideT.getMinute());
				if (rideT.getHour() + 1 >= 24) {
					hourdiff = reqT.getHour() - ((rideT.getHour()+1) % 24);
				} else {
					hourdiff = reqT.getHour() - (rideT.getHour() +1);
				}
			} else {
				hourdiff = 0;
				mindiff = abs(reqT.getMinute() - rideT.getMinute());
			}
		} else if (nextDay(reqD, rideD)) {
			if ((reqT.getHour() + 12) % 24 > rideT.getHour()) {						//in the case reqtime is 23:59
				mindiff = (60 - reqT.getMinute()) + rideT.getMinute();				//and ridetime is 0:01 situation
				if (reqT.getHour()+1 >= 24){
					hourdiff = rideT.getHour() + ((reqT.getHour()+1) % 24);
				} else {
					hourdiff = (24 - (reqT.getHour()+1)) + rideT.getHour();
				}
			} else if ((rideT.getHour() + 12) % 24 > reqT.getHour()) {				//in the case ridetime is 23:59
				mindiff = (60 - rideT.getMinute()) + reqT.getMinute();				//and reqtime is 0:01 situation
				if (rideT.getHour() >= 24) {
					hourdiff = reqT.getHour() + ((rideT.getHour()+1) % 24);
				} else {
					hourdiff = (24 - (rideT.getHour()+1)) + reqT.getHour();
				}
			}
		} else {
			//abnormal hour difference
			hourdiff = 100;
		}

		//sets time difference in minutes
		timedif = hourdiff*60 + mindiff;
	}

	//return date
	string getDate() const {
		return date.getDate(); }
	//return name
	string getName() const {
		return name; }
	//return time
	string getTime() const {
		return time.getTime(); }
	//return number of seats
	unsigned int getSeats() const {
		return seats; }
	//return the difference in time (in seconds) between request and ride
	double getTimedif() const {
		return timedif; }
	double getCost() const {
		return cost; }

private:
	Date date;
	string name;
	Time time;
	unsigned int seats;
	double timedif;
	double cost;

	//compares if dates are within 24hrs of each other
	bool sameDate(Date req, Date ride) {
		bool same = false;

		//check date
		if (req.getDate() == ride.getDate()) {
			same = true;
		}

		return same;
	}
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

//compare the difference in times
bool timeComp(MatchDetails i, MatchDetails j) {
	return (abs(i.getTimedif()) < abs(j.getTimedif()));
}
//compare the difference in cost
bool costComp(MatchDetails i, MatchDetails j) {
	return (i.getCost() < j.getCost());
}

int main() {
	ifstream requests("requests.in"), rides("rides.in"), oncall("on-call.in");			//open files
	int reqnum, ridenum, numPas;
	string date, time, name, fLoc, toLoc;
	unsigned int dy, mn, yr, pos = 0, pos2 = 0;
	Date dt; Time t;
	vector<RideDetails> reqVec;
	vector<RideDetails> rideVec;

	RideDetails req;
	RideDetails ride;

	//read request file
	if (requests.is_open()){
		requests >> reqnum;
		for (int i(0); i < reqnum; i++){
			requests >> date >> time >> name >> fLoc >> toLoc >> numPas;
			dt.setDate(date);
			t.setTime(time);


			req.setRide(dt, t, name, fLoc, toLoc, numPas);			//put values into class
			reqVec.push_back(req);										//add class to vector
		}
		requests.close();
	}
	else {
		cout << "Unable to open file:  requests.in\n";
	}

	//read rides file
	if (rides.is_open()){
		rides >> ridenum;
		for (int i(0); i < ridenum; i++){
			rides >> date >> time >> name >> fLoc >> toLoc >> numPas;
			dt.setDate(date);
			t.setTime(time);

			ride.setRide(dt, t, name, fLoc, toLoc, numPas);			//put values into class
			rideVec.push_back(ride);									//add class to vector
		}
		rides.close();
	}
	else {
		cout << "Unable to open file:  rides.in\n";
	}

	double cost;
	//read on-call file
	if (oncall.is_open()){
		oncall >> ridenum;
		for (int i(0); i < ridenum; i++){
			oncall >> name >> fLoc >> toLoc >> numPas >> cost;
			ride.setRide(name, fLoc, toLoc, numPas, cost);
			rideVec.push_back(ride);
		}
	}
	else {
		cout << "Unable to open file: on-call.in\n";
	}

	//make output file for matches
	ofstream matches("matches.out");
	if (matches.is_open()){
		for (int i(0); i < reqnum; i++){
			matches << reqVec[i].getName() << " requesting a ride for "
				<< reqVec[i].getSeats() << " from "
				<< reqVec[i].getFloc() << " to "
				<< reqVec[i].getToloc() << " on "
				<< reqVec[i].getDate() << " at time "
				<< reqVec[i].getTime() << endl;

			int mCount = 0;
			vector<MatchDetails> matchVec;

			//check for matches
			for (unsigned int j(0); j < rideVec.size(); j++){
				if (reqVec[i].getFloc() == rideVec[j].getFloc()
					&& reqVec[i].getToloc() == rideVec[j].getToloc()
					&& reqVec[i].getSeats() <= rideVec[j].getSeats()){
						MatchDetails m;
						t.setTime(rideVec[j].getTime());

						m.setMatch(rideVec[j].getDate(), rideVec[j].getName(), t, rideVec[j].getSeats(), rideVec[j].getCost());
						m.setTimedif(reqVec[i], rideVec[j]);

						if ((m.getTimedif() <= 60) || m.getCost() > 0) {
							mCount++;
							matchVec.push_back(m);
							cout << m.getName() << "  " << m.getTimedif() << " " << m.getCost() << endl;
						}
				}
			}

			//sort match vector based on time difference
			sort(matchVec.begin(), matchVec.end(), timeComp);
			//sort match vector based on cost (aka free rides come first based on time)
			sort(matchVec.begin(), matchVec.end(), costComp);

			//output matches
			if (mCount > 0){
				matches << " " << mCount << " Matches found!\n";
				for (int k(0); k < mCount; k++){
					matches << "  #" << k+1 << " Ride with "
						<< matchVec[k].getName() << " - ";
					if (matchVec[k].getCost() == 0) {
						matches << "leaving on "
						<< matchVec[k].getDate() << " at "
						<< matchVec[k].getTime() << " - "
						<< matchVec[k].getSeats() << " seats available\n";
					}
					else {
						matches << matchVec[k].getSeats() << " seats available "
							<< "anytime at $" << setprecision(2) << fixed << matchVec[k].getCost() << endl;
					}
				}
			}
			else {
				matches << " Sorry, no matches found.\n";
			}

			//make it pretty
			if (i < reqnum - 1){
				for (int k(0); k < 17; k++)
					matches << "*";
				matches << endl;
			}
		}
	}
	matches.close();

	return 0;
}
