/********************************
 *Amy Dong						*
 *Object Oriented Programming	*
 *Terry Hostetler HW1			*
 *CoeCruz						*
 ********************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class RideDetails{
public:
	//set time
	void setTime(string t) {
		time = t;
	}
	//set name
	void setName(string u) {
		name = u;
	}
	//set from location
	void setFloc(string f) {
		fLoc = f;
	}
	//set to location
	void setToloc(string to) {
		toLoc = to;
	}
	//set number of seats
	void setSeats(int n) {
		seats = n;
	}
	//set all values of RideDetails
	void setRide(string t, string u, string f, string tL, int n) {
		setTime(t);
		setName(u);
		setFloc(f);
		setToloc(tL);
		setSeats(n);
	}

	//return time
	string getTime() const {
		return time; }
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

private:
	string time;
	string name;
	string fLoc;
	string toLoc;
	unsigned int seats;
};

class MatchDetails{
public:
	//set name
	void setName(string u) {
		name = u;
	}
	//set time
	void setTime(string t) {
		time = t;
	}
	//set number of seats
	void setSeats(int n) {
		seats = n;
	}
	//set name, time, and number of seats
	void setMatch(string u, string t, int n) {
		setName(u);
		setTime(t);
		setSeats(n);
	}
	//calculate and set the time difference in minutes
	void setTimedif(string reqtime, string ridetime) {
		unsigned int reqhour = stoi(reqtime.substr(0, reqtime.find(":")));
		unsigned int reqmin = stoi(reqtime.substr(reqtime.find(":")+1));
		unsigned int ridehour = stoi(ridetime.substr(0, ridetime.find(":")));
		unsigned int ridemin = stoi(ridetime.substr(ridetime.find(":")+1));
		int hourdiff, mindiff;

		if ((reqhour + 12) % 24 > ridehour) {				//in the case reqtime is 23:59
			mindiff = (60 - reqmin) + ridemin;				//and ridetime is 0:01 situation
			reqhour += 1;
			if (reqhour >= 24){
				reqhour %= 24;
				hourdiff = reqhour + ridehour;
			} else {
				hourdiff = (24 - reqhour) + ridehour;
			}
		} else if ((ridehour + 12) % 24 > reqhour) {		//in the case ridetime is 23:59
			mindiff = (60 - reqmin) + ridemin;				//and reqtime is 0:01 situation
			ridehour += 1;
			if (ridehour >= 24) {
				ridehour %= 24;
				hourdiff = reqhour + ridehour;
			} else {
				hourdiff = (24 - ridehour) + reqhour;
			}
		} else if (reqhour < ridehour) {					//normal cases (can be modified to abs(reqhour - ridehour))
			mindiff = (60 - reqmin) + ridemin;
			reqhour += 1;
			if (reqhour >= 24) {
				reqhour %= 24;
			}
			hourdiff = ridehour - reqhour;
		} else if (ridehour < reqhour) {
			mindiff = reqmin + (60 - ridemin);
			ridehour += 1;
			if (ridehour >= 24) {
				ridehour %= 24;
			}
			hourdiff = reqhour - ridehour;
		} else {
			hourdiff = 0;
			mindiff = reqmin - ridemin;
			mindiff = abs(mindiff);
		}

		//sets time difference in minutes
		timedif = hourdiff*60 + mindiff;
	}


	//return name
	string getName() const {
		return name; }
	//return time
	string getTime() const {
		return time; }
	//return number of seats
	unsigned int getSeats() const {
		return seats; }
	//return the difference in time (in seconds) between request and ride
	double getTimedif() const {
		return timedif;}

private:
	string name;
	string time;
	unsigned int seats;
	double timedif;
};

//compare the difference in times
bool timeComp(MatchDetails i, MatchDetails j) {
		return (abs(i.getTimedif()) < abs(j.getTimedif()));
}

int main() {
	ifstream requests("requests.in"), rides("rides.in");			//open files
	int reqnum, ridenum, numPas;
	string time, name, fLoc, toLoc;
	vector<RideDetails> reqVec;
	vector<RideDetails> rideVec;

	RideDetails req;
	RideDetails ride;

	//read request file
	if (requests.is_open()){
		requests >> reqnum;
		for (int i(0); i < reqnum; i++){
			requests >> time >> name >> fLoc >> toLoc >> numPas;
			req.setRide(time, name, fLoc, toLoc, numPas);			//put values into class
			reqVec.push_back(req);									//add class to vector
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
			rides >> time >> name >> fLoc >> toLoc >> numPas;
			ride.setRide(time, name, fLoc, toLoc, numPas);			//put values into class
			rideVec.push_back(ride);								//add class to vector
		}
		rides.close();
	}
	else {
		cout << "Unable to open file:  rides.in\n";
	}

	//make output file for matches
	ofstream matches("matches.out");
	if (matches.is_open()){
		for (int i(0); i < reqnum; i++){
			matches << reqVec[i].getName() << " requesting a ride from "
				<< reqVec[i].getFloc() << " to "
				<< reqVec[i].getToloc() << " at time "
				<< reqVec[i].getTime() << endl;

			int mCount = 0;
			vector<MatchDetails> matchVec;

			//check for matches
			for (int j(0); j < ridenum; j++){
				if (reqVec[i].getFloc() == rideVec[j].getFloc()
					&& reqVec[i].getToloc() == rideVec[j].getToloc()
					&& reqVec[i].getSeats() <= rideVec[j].getSeats()){
						MatchDetails m;

						m.setMatch(rideVec[j].getName(), rideVec[j].getTime(), rideVec[j].getSeats());
						m.setTimedif(reqVec[i].getTime(), rideVec[j].getTime());

						mCount++;
						matchVec.push_back(m);
				}
			}

			//sort match vector based on time difference
			sort(matchVec.begin(), matchVec.end(), timeComp);

			//output matches
			if (mCount > 0){
				matches << " " << mCount << " Matches found!\n";
				for (int k(0); k < mCount; k++){
					matches << "  #" << k+1 << " Ride with "
						<< matchVec[k].getName() << " - leaving at "
						<< matchVec[k].getTime() << " - "
						<< matchVec[k].getSeats() << " seats available\n";
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

	return 0;
}