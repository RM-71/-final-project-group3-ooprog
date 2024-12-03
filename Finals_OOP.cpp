#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

bool isValidNum(const string& reservationID) {
    for (char c : reservationID) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;  
}

bool validInteger(string input, int &amount) {
    if (input.length() > 6) {
        cout << "	Invalid input: Integer exceeds 6 digits." << endl;
        return false;
    }
    for (char c : input) {
        if (!isdigit(c)) {
            cout << "	Invalid input" << endl;
            return false;
        }
    }
    try {
        amount = stoi(input);
        return true;
    } catch (...) {
        cout << "	Invalid input" << endl;
        return false;
    }
}
bool validPayment(string input, float &paymentAmount) {
    int decimalCount = 0;

    for (char c : input) {
        if (!isdigit(c) && c != '.') {
            cout << "	Invalid input: Please input a valid amount." << endl;
            return false;
        }
        if (c == '.') {
            decimalCount++;
            if (decimalCount > 1) {
                cout << "	Invalid input: Please input a valid amount." << endl;
                return false;
            }
        }
    }
    try {
        paymentAmount = stof(input);
    } catch (...) {
        cout << "	Invalid input: Please input a valid amount." << endl;
        return false;
    }
    return true;
}

string caseSensitivity(string input){
    	for (char &c : input) {
        c = tolower(c);
    	}
    	return input;
}

class PaymentStrategy {
public:
    virtual void paymentMethod(float amount) = 0; // Pure virtual function
};

class CreditCardPayment : public PaymentStrategy {
public:
    void paymentMethod(float amount) override {
        cout << "Payment of " << amount << " processed via Credit Card." << endl;
    }
};

class CashPayment : public PaymentStrategy {
public:
    void paymentMethod(float amount) override {
        cout << "Payment of " << amount << " processed via Cash." << endl;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void paymentMethod(float amount) override {
        cout << "Payment of " << amount << " processed via PayPal." << endl;
    }
};

class Account{
private:
    string adminUser = "admin", adminPass = "adminpass";
    string receptionistUser = "receptionist", receptionistPass = "receptionistpass";
    string newUser, newPass, newAccessLevel;

public:
    Account() {}

    void signIn() {
        string tempUser, tempPass;
        cout << "\tLog In" << endl;
        cout << "Username: ";
        getline(cin,tempUser);
        cout << "Password: ";
        getline(cin,tempPass);

        if (tempUser == adminUser && tempPass == adminPass) {
            newAccessLevel = "Admin";
            system("CLS");
            cout << "Login successful as " << newAccessLevel << "!" << endl;
        }
        else if (tempUser == receptionistUser && tempPass == receptionistPass) {
            newAccessLevel = "Receptionist";
            system("CLS");
            cout << "Login successful as " << newAccessLevel << "!" << endl;
        }
        else if (tempUser == newUser && tempPass == newPass){
            newAccessLevel = "Customer";
            system("CLS");
            cout << "Login successful!" << endl;
        }
        else {
            cout << "Invalid username or password!" << endl;
        }
    }

    void signUp() {
            bool valid;
            cout << "\tSign Up" << endl;
               while(!valid){
            cout << "Enter new username: ";
            getline(cin,newUser); 
            if (newUser == adminUser || newUser == receptionistUser) {
            cout << "Username already taken! Please choose a different username." << endl;
            }
            else {
                  cout << "Enter password: ";
                  getline(cin,newPass);
                  valid = true;
                  system("CLS");
            }
        }
    }
    string getAccessLevel(){
        return newAccessLevel;
    }
};


class Log {
private:
    string reservationID, name, date, typeOfRoom;
    int roomNo, year, month, day;
    int checkedIn = 1;
    float roomPrice = 0, reservationFee, payment;

public:
    Log(string id, string n, string d, int y, int m, int dy, int r, string roomType, float resfee)
        : reservationID(id), name(n), date(d), year(y), month(m), day(dy), roomNo(r), typeOfRoom(roomType), checkedIn(1), reservationFee(resfee){}

    string getReservationID() { 
        return reservationID; 
    }
    string getName() { 
        return name; 
    }
    string getDate() { 
        return date; 
    }
    string getTypeOfRoom() { 
        return typeOfRoom;
    }
    int getRoomNo() { 
        return roomNo; 
    }
    int getIsCheckedIn(){
        return checkedIn;
    }
    int getYear() { 
		return year; 
	}
	float getRoomPrice(){
		return  roomPrice;
	}
	int getMonth() {
	    return month; 
		}
	int getDay() { 
		return day; 
	}
	float getReservationFee(){
        return reservationFee;
    }
    
    void setRoomNo(int number){
    	roomNo = number;
	}
	void setReservationFee(){
		reservationFee = roomPrice * 0.20;
	}
    void setDate(string newDate) { 
        date = newDate; 
    }
    void setTypeOfRoom(string newType) { 
        typeOfRoom = newType; 
    }
    void setCheckIn(){
        checkedIn = 2;
    }
    void setCheckOut(){
    	checkedIn = 0;
	}
	void setPrice(string& roomType){
		if (roomType == "single room") roomPrice = 5000;
	    else if (roomType == "queen room") roomPrice = 8000;
	    else if (roomType == "deluxe room") roomPrice = 15000;
	    else if (roomType == "suite") roomPrice = 20000;
	}
    void display() {
    // Set the width of each field to ensure proper alignment
    cout << setw(8) << reservationID 
         << setw(15) << name 
         << setw(15) << date 
         << setw(12) << roomNo 
         << setw(12) << typeOfRoom << endl;
    }
};

class LogManager {
private:
    Log** log;
    PaymentStrategy* paymentMethod;
    int capacity, logCount;

    static LogManager* instance;


    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;
    
    int roomTypeIndex = -1;
    int roomArr[4][5][2] = {
	    {{101, 0},{102, 0},{103, 0},{104, 0},{105, 0}},  // Single Room
	    {{201, 0},{202, 0},{203, 0},{204, 0},{205, 0}},  // Deluxe Room
	    {{301, 0},{302, 0},{303, 0},{304, 0},{305, 0}},  // Queen Room
	    {{401, 0},{402, 0},{403, 0},{404, 0},{405, 0}}   // Suite
		};
	
	
protected:
	LogManager() : capacity(10), logCount(0) {
        log = new Log*[capacity];
    }


public:
    static LogManager* getInstance() {
        if (instance == nullptr) {
            instance = new LogManager();
        }
        return instance;
    }
    
    

    void resize() {
        capacity *= 2;
        Log** newLog = new Log*[capacity];
        for (int i = 0; i < logCount; i++) {
            newLog[i] = log[i];
        }
        delete[] log;
        log = newLog;
    }
    
    
void createReservation() {
	string id, name, date, roomType, input;
    int roomNo, year, month, day, choice;
    bool isValid;

    if (logCount >= capacity) {
        cout << "Log is full. Cannot create new reservations.\n";
        return;
    }

    cout << "\nCreate Reservation\n";
   
    cout << "Enter Name: ";
    cin >> name;
    name = caseSensitivity(name);
	cin.ignore();
    while (!isValid){
		cout << "Enter Room Type (Single Room, Deluxe Room, Queen Room, Suite): ";
	    getline(cin, roomType);
	    roomType = caseSensitivity(roomType);
	
	    if (roomType == "single room") {
	        roomTypeIndex = 0;
	    } else if (roomType == "queen room") {
	        roomTypeIndex = 1;
	    } else if (roomType == "deluxe room") {
	        roomTypeIndex = 2;
	    } else if (roomType == "suite") {
	        roomTypeIndex = 3;
	    } else {
	        cout << "Invalid room type entered.\n";
	    }
	
		if (roomType=="single room" || roomType == "queen room" || roomType == "deluxe room" || roomType == "suite"){
		    cout << "Available rooms for " << roomType << ":\n";
		    cout << "Room No\tStatus\n";
		    for (int i = 0; i < 5; i++) {
		        if (roomArr[roomTypeIndex][i][1] == 0) { // Room is available
		            cout << roomArr[roomTypeIndex][i][0] << "\t" << "Available" << endl;
		            isValid = true;
		        } else if (roomArr[roomTypeIndex][i][1] == 1) { // Room is reserved
		            cout << roomArr[roomTypeIndex][i][0] << "\t" << "Reserved" << endl;
		            
		        } else if (roomArr[roomTypeIndex][i][1] == 2) { // Room is occupied
		            cout << roomArr[roomTypeIndex][i][0] << "\t" << "Check-In" << endl;
		        }
		    	if (!isValid) {
			    	cout << "No Available Room Type\n";
				}
			}
		}
	}
	isValid = false;  
	while(!isValid){
	    while (!isValid) {
	        cout << "Enter Room No: ";
	        cin >> input;  // Read input as a string
	        
	        if (validInteger(input, roomNo)) {  // Validate the integer
	            isValid = true;  // Valid input
	        } else {
	            cout << "Please choose a room from the list provided.\n";
	        }
	    }
        isValid = false;

    for (int i = 0; i < 5; i++) {
        if (roomArr[roomTypeIndex][i][0] == roomNo && roomArr[roomTypeIndex][i][1] == 0) {
            isValid = true;
            roomArr[roomTypeIndex][i][1] = 1; 
            break;
        }
    }
    if (!isValid) {
        cout << "Invalid or already reserved room number.\n";
    	}
	}
	isValid = false;
    while (!isValid) {
	        cout << "Enter the year (either 2024 or 2025): ";
	        cin >> input;  // Read input as a string
	        
	        if (validInteger(input, year)&&(year == 2024 || year == 2025)) {  // Validate the integer
	            isValid = true;  // Valid input
	        } else {
	            cout << "Please enter a valid year.\n";
	        }
	    }

    isValid = false;
        while (!isValid) {
	        cout << "Enter month (1-12): ";
	        cin >> input;  // Read input as a string
	        
	        if (validInteger(input, month) && (month >= 1 && month <= 12)) {  // Validate the integer
	            isValid = true;  // Valid input
	        } else {
	            cout << "Invalid month. Please enter a value between 1 and 12.\n";
	        }
	    }

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    isValid = false;
    while (!isValid) {
        cout << "Enter day (1-" << daysInMonth[month - 1] << "): ";
        cin >> input;  // Read input as a string
        
        if (validInteger(input, day) && (day >= 1 && day <= daysInMonth[month - 1])) {  // Validate the integer
            isValid = true;  // Valid input
        } else {
            cout << "Invalid day. Please enter a valid day for the selected month.\n";
        }
    }

    date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);
    stringstream ss;
    ss << setw(4) << setfill('0') << (logCount + 1);
    id = ss.str();
	
	float paymentAmount;
    log[logCount]->setPrice(roomType);
    log[logCount]->setReservationFee();
    isValid = false;
    while(!isValid){
        	cout << "Reservation Fee - " << log[logCount]->getReservationFee();
	        cout << "\nPlease enter payment amount: ";
	        cin >> input;  // Read input as a string

	        if (validPayment(input, paymentAmount)&&(paymentAmount == log[logCount]->getReservationFee())) {  // Validate the integer
	        	cout << "Choose Payment Method (1 - Credit Card, 2 - Cash, 3 - PayPal): ";
                cin >> choice;
                if (choice == 1) {
                    paymentMethod = new CreditCardPayment();
                } else if (choice == 2) {
                    paymentMethod = new CashPayment();
                } else if (choice == 3) {
                    paymentMethod = new PayPalPayment();
                } else {
                    cout << "Invalid choice!" << endl;
                    return;
                }
                paymentMethod->paymentMethod(paymentAmount);
                cout << "Payment successful. Reservation fully paid!" << endl;
	            isValid = true;  // Valid input
	        } else {
	            cout << "Please enter a valid amount.\n";
		}
	}
    
    log[logCount] = new Log(id, name, date, year, month, day, roomNo, roomType, paymentAmount);
    logCount++;
    
	system("pause"); system("cls");
    cout << "\nReservation Successful!\n";
    cout << "Reservation ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Room Type: " << roomType << endl;
    cout << "Room Number: " << roomNo << endl;
    cout << "Date: " << date << endl;
    system("pause"); system("cls");
}


void updateReservation() {
string reservationID, input;
bool isValid = false, roomAvailable = true;
while(!isValid){
    	cout << "Enter reservation ID to delete: ";
    	cin >> reservationID;
    	if (isValidNum(reservationID)) 
            isValid = true;
        else 
        	cout << "Invalid input. Please enter a valid Reservation ID (digits only).\n";
        
	}
	isValid = false;
for (int i = 0; i < logCount; i++) {
    if (log[i]->getReservationID() == reservationID) {
        if (log[i]->getIsCheckedIn() == 1) {
            int choice, newDay, newYear, newMonth;
            string newDate, newRoomType;
            roomTypeIndex = -1;

            log[i]->display();  // Display current reservation details
            cout << "\n1 - Date, 2 - Type of Room: ";
            cin >> choice;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 1) {
                // Update reservation date
                while (!isValid) {
                    cout << "Enter the year (2024 or 2025): ";
                    cin >> input;
                    if (validInteger(input, newYear) && (newYear == 2024 || newYear == 2025)) {
                        isValid = true;
                    } else {
                        cout << "Invalid year. Please enter 2024 or 2025.\n";
                    }
                }

                isValid = false;
                while (!isValid) {
                    cout << "Enter month (1-12): ";
                    cin >> input;
                    if (validInteger(input, newMonth) && (newMonth >= 1 && newMonth <= 12)) {
                        isValid = true;
                    } else {
                        cout << "Invalid month. Please enter a value between 1 and 12.\n";
                    }
                }

                int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                isValid = false;
                while (!isValid) {
                    cout << "Enter day (1-" << daysInMonth[newMonth - 1] << "): ";
                    cin >> input;
                    if (validInteger(input, newDay) && (newDay >= 1 && newDay <= daysInMonth[newMonth - 1])) {
                        isValid = true;
                    } else {
                        cout << "Invalid day. Please enter a valid day for the selected month.\n";
                    }
                }

                newDate = to_string(newMonth) + "/" + to_string(newDay) + "/" + to_string(newYear);
                log[i]->setDate(newDate);
                cout << "Reservation date updated successfully to: " << newDate << endl;
            } else if (choice == 2) {
                // Update room type
                while (!isValid) {
                    cout << "Enter new room type (single room, deluxe room, queen room, suite): ";
                    getline(cin, newRoomType);
                    newRoomType = caseSensitivity(newRoomType);

                    if (newRoomType == log[i]->getTypeOfRoom()) {
                        cout << "You already have this room type. Please choose a different one.\n";
                    } else if (newRoomType == "single room" || newRoomType == "deluxe room" ||
                               newRoomType == "queen room" || newRoomType == "suite") {
                        isValid = true;
                    } else {
                        cout << "Invalid room type. Please enter one of the valid types.\n";
                    }
                }

                if (newRoomType == "single room") roomTypeIndex = 0;
                else if (newRoomType == "queen room") roomTypeIndex = 1;
                else if (newRoomType == "deluxe room") roomTypeIndex = 2;
                else if (newRoomType == "suite") roomTypeIndex = 3;

                cout << "Available rooms for " << newRoomType << ":\n";
                cout << "Room No\tStatus\n";
                bool hasAvailableRooms = false;

                for (int j = 0; j < 5; j++) {
                    if (roomArr[roomTypeIndex][j][1] == 0) {
                        cout << roomArr[roomTypeIndex][j][0] << "\tAvailable\n";
                        hasAvailableRooms = true;
                    }
                }

                if (!hasAvailableRooms) {
                    cout << "No available rooms for the selected type.\n";
                    return;
                }

                int selectedRoomNo;
                isValid = false;
                while (!isValid) {
                    cout << "Enter the room number you'd like to select: ";
                    cin >> input;
                    if (validInteger(input, selectedRoomNo)) {
                        for (int j = 0; j < 5; j++) {	
                            if (roomArr[roomTypeIndex][j][0] == selectedRoomNo && roomArr[roomTypeIndex][j][1] == 0) {
                                // Mark previous room as available
                                for (int k = 0; k < 5; k++) {
                                    if (roomArr[i][k][0] == log[i]->getRoomNo()) {
                                        roomArr[i][k][1] = 0;
                                        break;
                                    }
                                }

                                // Update new room
                                roomArr[roomTypeIndex][j][1] = 1;
                                log[i]->setRoomNo(selectedRoomNo);
                                log[i]->setTypeOfRoom(newRoomType);

                                // Handle price difference
                                float originalPrice = log[i]->getReservationFee();
                                log[i]->setPrice(newRoomType);
                                log[i]->setReservationFee();
                                float newPrice = log[i]->getReservationFee();

                                if (newPrice > originalPrice) {
                                    float additionalFee = newPrice - originalPrice;
                                    cout << "Additional Fee due to room change: " << additionalFee << endl;

                                    float paymentAmount = 0;
                                    while (paymentAmount != additionalFee) {
                                        cout << "Please enter additional payment: ";
                                        cin >> paymentAmount;
                                        if (paymentAmount == additionalFee) {
                                            cout << "Payment successful. Room updated successfully.\n";
                                        } else {
                                            cout << "Payment insufficient. Please try again.\n";
                                        }
                                    }
                                } else {
                                    cout << "Room updated successfully.\n";
                                }

                                isValid = true;
                                break;
                            }
                        }

                        if (!isValid) {
                            cout << "Selected room is either unavailable or does not exist. Please try again.\n";
                        }
                    } else {
                        cout << "Invalid input. Please enter a valid room number.\n";
                    }
                }
            }
            return;
        } else {
            cout << "Reservation cannot be updated.\n";
            return;
        }
    }
}
cout << "Reservation ID not found.\n";
}


void deleteReservation() {
    string reservationID; bool valid;
    while(!valid){
    	cout << "Enter reservation ID to delete: ";
    	cin >> reservationID;
    	if (isValidNum(reservationID)) 
            valid = true;
        else 
        	cout << "Invalid input. Please enter a valid Reservation ID (digits only).\n";
        
	}

    for (int i = 0; i < logCount; i++) {
        if (log[i]->getReservationID() == reservationID) {
            if (log[i]->getIsCheckedIn() == 1) {
                for (int j = 0; j < 5; j++) {
                    if (roomArr[roomTypeIndex][j][0] == log[i]->getRoomNo()) {
                        roomArr[roomTypeIndex][j][1] = 0; // Room becomes available
                        break;
                    }
                }
                delete log[i];
                for (int j = i; j < logCount - 1; j++) {
                    log[j] = log[j + 1];
                }
                logCount--;
                cout << "Reservation deleted and room is now available.\n";
            } else {
                cout << "Reservation cannot be delete.\n";
            }
            return;
        }
    }

    cout << "Reservation ID not found.\n";
}

void availableRoom() {
    cout << left << setw(10) << "----------------------------------\n";
    cout << left << "    " << setw(10) << "Room No" << setw(15) << "Status" << endl;
    cout << left << setw(15) << "----------------------------------\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j<5; j++){
            if (roomArr[i][j][1] == 0) { 
                cout << roomArr[i][j][0] << "\t" << "Available" << endl;
            } else if (roomArr[i][j][1] == 1) { // Room is reserved
                cout << roomArr[i][j][0] << "\t" << "Reserved" << endl;

            } else if (roomArr[i][j][1] == 2) { // Room is occupied
                cout << roomArr[i][j][0] << "\t" << "Check-In" << endl;
            }
        }
    }
}

void checkOut() {
        string reservationID, input;
        float amount, paymentAmount;
        int days, choice;
        bool isValid = false;
        
        cout << "Enter reservation ID to check out: ";
        cin.ignore();
        getline(cin, reservationID);
        for (int i = 0; i < logCount; i++) {
            if (log[i]->getReservationID() == reservationID) {
                while (!isValid){
                    cin.ignore();
                    cout << "Please input the amount of days you stayed: ";
                    getline(cin, input);
                    if (validInteger(input, days)) {  // Validate the integer
                        isValid = true;  // Valid input
                    }
                    else{
                        cout << "Please enter a valid ID";
                    }
                }
                
                string temp = log[i]->getTypeOfRoom();
                log[i]->setPrice(temp);
                amount = log[i]->getRoomPrice();
                amount *= days;
                
                isValid = false;
                while(!isValid){
                    while(!isValid){
                        cout << "Total Cost - P" << amount;
                        cin.ignore();
                        cout << "\nPlease enter payment amount: ";
                        getline(cin, input);  // Read input as a string
          
                        if (validPayment(input, paymentAmount)) {  // Validate the integer
                            isValid = true;  // Valid input
                        } else {
                            cout << "Please enter a valid amount.\n";
                        }
                    
                      isValid = false;
                    while(!isValid){
                        if (paymentAmount == amount) {
                            cout << "Choose Payment Method (1 - Credit Card, 2 - Cash, 3 - PayPal): ";
                            getline(cin, input);
                            if (validInteger(input, choice)){
                                isValid = true;
                                } 
                                else {
                                cout << "Invalid Input. please enter a valid payment method\n";
                                }
                            }    else {
                            cout << "Invalid payment. Please try again.\n";
                            }
                        }
                            isValid = false;
                            if (choice == 1) {
                                paymentMethod = new CreditCardPayment();
                            } else if (choice == 2) {
                                paymentMethod = new CashPayment();
                            } else if (choice == 3) {
                                paymentMethod = new PayPalPayment();
                            } else {
                                cout << "Invalid choice!" << endl;
                                return;
                            }
                            paymentMethod->paymentMethod(paymentAmount);
                            cout << "Payment successful. Fully paid!" << endl;
                            isValid = true;
                        } 
                }
                
                cout << "Checked out successfully: \n";
                log[i]->setCheckOut();
                roomArr[roomTypeIndex][i][1] = 0; 
                log[i]->display();
                return;
            }
        }
        cout << "Reservation ID not found.\n";
    }

void checkIn() {
    string reservationID;
    cout << "Enter reservation ID to check in: ";
    getline(cin, reservationID);
    

    for (int i = 0; i < logCount; i++) {
        if (log[i]->getReservationID() == reservationID) {
            cout << "Checked in successfully: \n";
            log[i]->setCheckIn();
            roomArr[roomTypeIndex][i][1] = 2; 
            log[i]->display();
            return;
        }
    }
    cout << "Reservation ID not found.\n";
}

void displayLogs(int c) {
    system("cls");
    if (logCount == 0) {
        cout << "No reservations available to display.\n";
    } else {
        int currentQuarter = -1;
        int currentYear = -1;
        int currentMonth = -1;

        cout << "\nDisplaying all reservations:\n";
        for (int i = 0; i < logCount; i++) {
            int year = log[i]->getYear();
            int month = log[i]->getMonth();
            int quarter = (month - 1) / 3 + 1; // Calculate the quarter

            if (c == 1) { // Monthly display
                // Print the monthly header if it changes
                if (year != currentYear || month != currentMonth) {
                    currentYear = year;
                    currentMonth = month;
                    cout << "\nMonth " << currentMonth << " of " << currentYear << "\n";
                    cout << setw(8) << "ID" 
                         << setw(15) << "Name"
                         << setw(15) << "Date"
                         << setw(12) << "Room No."
                         << setw(12) << "Room Type" << endl;
                }
            } else if (c == 2) { // Quarterly display
                // Print the quarter header if it changes
                if (year != currentYear || quarter != currentQuarter) {
                    currentYear = year;
                    currentQuarter = quarter;
                    cout << "\nQ" << currentQuarter << " of " << currentYear << "\n";
                    cout << setw(8) << "ID" 
                         << setw(15) << "Name"
                         << setw(15) << "Date"
                         << setw(12) << "Room No."
                         << setw(12) << "Room Type" << endl;
                }
            } else if (c == 3) { // Yearly display
                // Print the year header if it changes
                if (year != currentYear) {
                    currentYear = year;
                    cout << "\nYear " << currentYear << "\n";
                    cout << setw(8) << "ID" 
                         << setw(15) << "Name"
                         << setw(15) << "Date"
                         << setw(12) << "Room No."
                         << setw(12) << "Room Type" << endl;
                }
            }
            // Display the log entry with consistent column width
            cout << setw(8) << log[i]->getReservationID() << setw(15) << log[i]->getName()<< setw(15) << log[i]->getDate()<< setw(12) << log[i]->getRoomNo()<< setw(12) << log[i]->getTypeOfRoom() << endl;
        }
    }
}

void sortBookings() {
		string input;
	    int choice;
		bool isValid = false;
		isValid = false;
		while (!isValid) {
	        cout << "\nSorting Methods\n1. Monthly\n2. Quarterly\n3. Yearly\nSort by: ";
	        cin >> input;  
	        
	        if (validInteger(input, choice) && input <= "3" && input >= "1") {  // Validate the integer
	            isValid = true;  
	        }
			else {
	            cout << "Invalid choice. Please enter a num from the choices.\n";
	        }
		
	    switch (choice) {
		    case 1:  // Sort by Month considering Year and Day
		        std::sort(log, log + logCount, [](Log* a, Log* b) {
		            return (a->getYear() < b->getYear()) ||
		                   (a->getYear() == b->getYear() && a->getMonth() < b->getMonth()) ||
		                   (a->getYear() == b->getYear() && a->getMonth() == b->getMonth() && a->getDay() < b->getDay());
		        });
		        break;
		
		    case 2:  // Sort by Quarter considering Year and Day
		        std::sort(log, log + logCount, [](Log* a, Log* b) {
		            int quarterA = (a->getMonth() - 1) / 3;
		            int quarterB = (b->getMonth() - 1) / 3;
		            return (a->getYear() < b->getYear()) || 
		                   (a->getYear() == b->getYear() && quarterA < quarterB) || 
		                   (a->getYear() == b->getYear() && quarterA == quarterB && a->getDay() < b->getDay());
		        });
		        break;
		
		    case 3:  // Sort by Year and Day
		        std::sort(log, log + logCount, [](Log* a, Log* b) {
		            return (a->getYear() < b->getYear()) || 
		                   (a->getYear() == b->getYear() && a->getDay() < b->getDay());
		        });
		        break;
		
		    default:
		        cout << "Invalid choice.\n";
		}
	}
	    cout << "Bookings sorted successfully.\n";
	    
	    displayLogs(choice);
	}

virtual void menu(int choice, bool exit) {}
};

LogManager* LogManager::instance = nullptr;


class User : public LogManager {
public:
void menu(int choice, bool exit) override {
    while (exit) {
        cout << "\n\tMenu\n1-Create Reservation\n2-Update Reservation\n3-Delete Reservation\n4-Check Available Rooms\n5-Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            LogManager::getInstance()->createReservation(); 
            break;
        case 2:
            LogManager::getInstance()->updateReservation();
            break;
        case 3:
            LogManager::getInstance()->deleteReservation();
            break;
        case 4:
            LogManager::getInstance()->availableRoom();
            break;
        case 5:
            exit = false;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
    	}
    }
}
};

class Staff: public LogManager {
public:
    void menu(int choice, bool exit) override {
    while (exit) {
        cout << "\n\tMenu \n 1-Create Reservation \n 2-Update Reservation \n 3-Delete Reservation \n 4-Check The Available Rooms \n 5-Check In \n 6-Check out \n 7-Booking Records \n 8-Exit\nEnter your Choice (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1:
                 LogManager::getInstance()->createReservation();
                break;
            case 2:
                 LogManager::getInstance()->updateReservation();
                break;
            case 3:
                 LogManager::getInstance()->deleteReservation();
                break;
            case 4:
                 LogManager::getInstance()->availableRoom();
                break;
            case 5:
                 LogManager::getInstance()->checkIn();
                break;
            case 6:
                 LogManager::getInstance()->checkOut();
                break;
            case 7:
                 LogManager::getInstance()->sortBookings();
            	break;
            case 8:
                exit = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
};



int main() {
Account reg;
User user;
Staff staff;
bool exit = true;

while (exit){
    int choice;
    bool entry = false;
    string input;
    cout << "1-Sign In \n";
    cout << "2-Sign Up \n";
    cout << "3-Exit \n";
    while (!entry) {
        cout << "Enter choice: ";
        cin >> input;  // Read input as a string
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (validInteger(input, choice)) {  // Validate the integer
            entry = true;  // Valid input
        } else {
            cout << "Please enter a valid choice.\n";
        }
    }

    system("CLS");

    switch(choice){
        case 1:
            reg.signIn();
            if(reg.getAccessLevel() == "Admin" || reg.getAccessLevel() == "Receptionist"){
                staff.menu(choice,exit);
            } else if (reg.getAccessLevel() == "Customer"){
                user.menu(choice,exit);
            }
        break;
        case 2:
            reg.signUp();
        break;
        case 3:
            exit = false;
        break;
        default:
            cout << "Invalid Input\n";
    }
}

    return 0;
}