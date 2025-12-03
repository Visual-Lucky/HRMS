#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

void safeCopy(char* dest, const string& src, size_t maxLen) {
    if (maxLen == 0) return;
    strncpy(dest, src.c_str(), maxLen - 1);
    dest[maxLen - 1] = '\0';
}

string trim(const string& s) {
    size_t a = 0;
    while (a < s.size() && isspace((unsigned char)s[a])) ++a;
    size_t b = s.size();
    while (b > a && isspace((unsigned char)s[b-1])) --b;
    return s.substr(a, b - a);
}

bool validID(const string& s, size_t maxLen) {
    if (s.empty() || s.size() >= maxLen) return false;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (!(isalnum((unsigned char)c) || c == '_' || c == '-')) return false;
    }
    return true;
}

bool validEmail(const string& e) {
    size_t at = e.find('@');
    size_t dot = e.rfind('.');
    if (at == string::npos || dot == string::npos) return false;
    if (at == 0 || dot <= at + 1 || dot == e.size() - 1) return false;
    return true;
}

bool validDate(const string& d) {
    if (d.size() != 10) return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) { if (d[i] != '-') return false; continue; }
        if (!isdigit((unsigned char)d[i])) return false;
    }
    int y = stoi(d.substr(0,4));
    int m = stoi(d.substr(5,2));
    int day = stoi(d.substr(8,2));
    if (y < 1900 || y > 2100) return false;
    if (m < 1 || m > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((m==4||m==6||m==9||m==11) && day>30) return false;
    if (m==2) {
        bool leap = ((y%4==0 && y%100!=0) || (y%400==0));
        if (day > (leap ? 29 : 28)) return false;
    }
    return true;
}

bool validPassword(const string& p) {
    return p.size() >= 6;
}

class Employee {
public:
    char empID[10];
    char empName[20];
    char empPassword[20];
    char empContactNo[20];
    char empType[10];
    char empEmail[30];
    char empAddress[50];
    char empDOB[12];
    char empGender[10];
    char empDepartment[20];
    char empJoinDate[12];
    char empStatus[10];
    bool isAdmin;

    Employee() {
        safeCopy(empID, "E0001", sizeof(empID));
        safeCopy(empName, "Alex Morgan", sizeof(empName));
        safeCopy(empPassword, "admin123", sizeof(empPassword));
        safeCopy(empContactNo, "+911234567890", sizeof(empContactNo));
        safeCopy(empType, "FullTime", sizeof(empType));
        safeCopy(empEmail, "alex@company.com", sizeof(empEmail));
        safeCopy(empAddress, "101 Main St, City", sizeof(empAddress));
        safeCopy(empDOB, "1990-06-15", sizeof(empDOB));
        safeCopy(empGender, "Male", sizeof(empGender));
        safeCopy(empDepartment, "HR", sizeof(empDepartment));
        safeCopy(empJoinDate, "2015-08-01", sizeof(empJoinDate));
        safeCopy(empStatus, "Active", sizeof(empStatus));
        isAdmin = false;
    }

    void inputInteractive() {
        string t;
        while (true) {
            cout << "Employee ID (alnum, <9 chars): ";
            getline(cin >> ws, t);
            t = trim(t);
            if (validID(t, sizeof(empID))) { safeCopy(empID, t, sizeof(empID)); break; }
            cout << "ID must be short, alphanumeric (underscores and hyphens allowed). Try again.\n";
        }
        cout << "Name: ";
        getline(cin, t);
        t = trim(t);
        safeCopy(empName, t.empty() ? "Unnamed" : t, sizeof(empName));
        while (true) {
            cout << "Password (min 6 chars): ";
            getline(cin, t);
            if (validPassword(t)) { safeCopy(empPassword, t, sizeof(empPassword)); break; }
            cout << "Pick a stronger password (6+ chars). Try again.\n";
        }
        cout << "Contact No: ";
        getline(cin, t);
        t = trim(t);
        safeCopy(empContactNo, t.empty() ? "+0000000000" : t, sizeof(empContactNo));
        cout << "Type (FullTime/PartTime/Contract): ";
        getline(cin, t);
        safeCopy(empType, trim(t).empty() ? "FullTime" : trim(t), sizeof(empType));
        while (true) {
            cout << "Email: ";
            getline(cin, t);
            t = trim(t);
            if (validEmail(t)) { safeCopy(empEmail, t, sizeof(empEmail)); break; }
            cout << "That doesn't look like an email. Try again.\n";
        }
        cout << "Address: ";
        getline(cin, t);
        safeCopy(empAddress, trim(t).empty() ? "Unknown" : trim(t), sizeof(empAddress));
        while (true) {
            cout << "DOB (YYYY-MM-DD): ";
            getline(cin, t);
            if (validDate(t)) { safeCopy(empDOB, t, sizeof(empDOB)); break; }
            cout << "Invalid date. Use YYYY-MM-DD. Try again.\n";
        }
        cout << "Gender: ";
        getline(cin, t);
        safeCopy(empGender, trim(t).empty() ? "NotSet" : trim(t), sizeof(empGender));
        cout << "Department: ";
        getline(cin, t);
        safeCopy(empDepartment, trim(t).empty() ? "General" : trim(t), sizeof(empDepartment));
        while (true) {
            cout << "Join Date (YYYY-MM-DD): ";
            getline(cin, t);
            if (validDate(t)) { safeCopy(empJoinDate, t, sizeof(empJoinDate)); break; }
            cout << "Invalid date. Try again.\n";
        }
        cout << "Status (Active/Inactive): ";
        getline(cin, t);
        safeCopy(empStatus, trim(t).empty() ? "Active" : trim(t), sizeof(empStatus));
        cout << "Is Admin? (1 = yes, 0 = no): ";
        int a; cin >> a;
        isAdmin = (a != 0);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void displayShort() const {
        cout << left << setw(8) << empID << setw(18) << empName << setw(10) << empDepartment << setw(10) << empType << setw(8) << empStatus;
        if (isAdmin) cout << " [Admin]";
        cout << '\n';
    }

    void displayFull() const {
        cout << "Employee ID   : " << empID << '\n';
        cout << "Name          : " << empName << '\n';
        cout << "Password      : " << empPassword << '\n';
        cout << "Contact No    : " << empContactNo << '\n';
        cout << "Type          : " << empType << '\n';
        cout << "Email         : " << empEmail << '\n';
        cout << "Address       : " << empAddress << '\n';
        cout << "DOB           : " << empDOB << '\n';
        cout << "Gender        : " << empGender << '\n';
        cout << "Department    : " << empDepartment << '\n';
        cout << "Join Date     : " << empJoinDate << '\n';
        cout << "Status        : " << empStatus << '\n';
        cout << "Is Admin      : " << (isAdmin ? "Yes" : "No") << '\n';
    }
};

class Project {
public:
    char projID[10];
    char projName[30];
    char projManagerID[10];
    char projStartDate[12];
    char projEndDate[12];
    char projStatus[15];
    char projDescription[100];

    Project() {
        safeCopy(projID, "PRJ1", sizeof(projID));
        safeCopy(projName, "Website Revamp", sizeof(projName));
        safeCopy(projManagerID, "E0001", sizeof(projManagerID));
        safeCopy(projStartDate, "2025-01-01", sizeof(projStartDate));
        safeCopy(projEndDate, "2025-06-30", sizeof(projEndDate));
        safeCopy(projStatus, "Planned", sizeof(projStatus));
        safeCopy(projDescription, "Improve website UI/UX", sizeof(projDescription));
    }

    void inputInteractive() {
        string t;
        while (true) {
            cout << "Project ID: ";
            getline(cin >> ws, t);
            t = trim(t);
            if (validID(t, sizeof(projID))) { safeCopy(projID, t, sizeof(projID)); break; }
            cout << "Project ID should be short alphanumeric. Try again.\n";
        }
        cout << "Project Name: ";
        getline(cin, t);
        safeCopy(projName, trim(t).empty() ? "Unnamed" : trim(t), sizeof(projName));
        cout << "Project Manager ID: ";
        getline(cin, t);
        safeCopy(projManagerID, trim(t).empty() ? "E0001" : trim(t), sizeof(projManagerID));
        while (true) {
            cout << "Start Date (YYYY-MM-DD): ";
            getline(cin, t);
            if (validDate(t)) { safeCopy(projStartDate, t, sizeof(projStartDate)); break; }
            cout << "Invalid date. Try again.\n";
        }
        while (true) {
            cout << "End Date (YYYY-MM-DD): ";
            getline(cin, t);
            if (validDate(t)) { safeCopy(projEndDate, t, sizeof(projEndDate)); break; }
            cout << "Invalid date. Try again.\n";
        }
        cout << "Status (Planned/Ongoing/Completed): ";
        getline(cin, t);
        safeCopy(projStatus, trim(t).empty() ? "Planned" : trim(t), sizeof(projStatus));
        cout << "Short Description: ";
        getline(cin, t);
        safeCopy(projDescription, trim(t).empty() ? "No description." : trim(t), sizeof(projDescription));
    }

    void displayShort() const {
        cout << left << setw(8) << projID << setw(22) << projName << setw(12) << projManagerID << setw(12) << projStatus << '\n';
    }

    void displayFull() const {
        cout << "Project ID    : " << projID << '\n';
        cout << "Name          : " << projName << '\n';
        cout << "Manager ID    : " << projManagerID << '\n';
        cout << "Start Date    : " << projStartDate << '\n';
        cout << "End Date      : " << projEndDate << '\n';
        cout << "Status        : " << projStatus << '\n';
        cout << "Description   : " << projDescription << '\n';
    }
};

class Client {
public:
    char clientID[10];
    char clientName[30];
    char clientContactNo[20];
    char clientEmail[30];
    char clientAddress[60];
    char clientNotes[100];

    Client() {
        safeCopy(clientID, "CL001", sizeof(clientID));
        safeCopy(clientName, "Global Co", sizeof(clientName));
        safeCopy(clientContactNo, "+911112223334", sizeof(clientContactNo));
        safeCopy(clientEmail, "contact@global.co", sizeof(clientEmail));
        safeCopy(clientAddress, "500 Business Rd", sizeof(clientAddress));
        safeCopy(clientNotes, "Priority client", sizeof(clientNotes));
    }

    void inputInteractive() {
        string t;
        while (true) {
            cout << "Client ID: ";
            getline(cin >> ws, t);
            t = trim(t);
            if (validID(t, sizeof(clientID))) { safeCopy(clientID, t, sizeof(clientID)); break; }
            cout << "Client ID must be short alphanumeric. Try again.\n";
        }
        cout << "Client Name: ";
        getline(cin, t);
        safeCopy(clientName, trim(t).empty() ? "Unnamed" : trim(t), sizeof(clientName));
        cout << "Contact No: ";
        getline(cin, t);
        safeCopy(clientContactNo, trim(t).empty() ? "+0000" : trim(t), sizeof(clientContactNo));
        while (true) {
            cout << "Email: ";
            getline(cin, t);
            t = trim(t);
            if (validEmail(t)) { safeCopy(clientEmail, t, sizeof(clientEmail)); break; }
            cout << "Invalid email. Try again.\n";
        }
        cout << "Address: ";
        getline(cin, t);
        safeCopy(clientAddress, trim(t).empty() ? "Unknown" : trim(t), sizeof(clientAddress));
        cout << "Notes: ";
        getline(cin, t);
        safeCopy(clientNotes, trim(t).empty() ? "No notes." : trim(t), sizeof(clientNotes));
    }

    void displayShort() const {
        cout << left << setw(8) << clientID << setw(22) << clientName << setw(16) << clientContactNo << '\n';
    }

    void displayFull() const {
        cout << "Client ID     : " << clientID << '\n';
        cout << "Name          : " << clientName << '\n';
        cout << "Contact No    : " << clientContactNo << '\n';
        cout << "Email         : " << clientEmail << '\n';
        cout << "Address       : " << clientAddress << '\n';
        cout << "Notes         : " << clientNotes << '\n';
    }
};

class HRMS {
private:
    const char* empFile;
    const char* projFile;
    const char* clientFile;

public:
    HRMS(const char* e = "employees.dat", const char* p = "projects.dat", const char* c = "clients.dat")
        : empFile(e), projFile(p), clientFile(c) { }

private:
    bool appendEmployee(const Employee& e) {
        fstream f(empFile, ios::out | ios::app | ios::binary);
        if (!f) return false;
        f.write(reinterpret_cast<const char*>(&e), sizeof(e));
        f.close();
        return true;
    }

    bool appendProject(const Project& p) {
        fstream f(projFile, ios::out | ios::app | ios::binary);
        if (!f) return false;
        f.write(reinterpret_cast<const char*>(&p), sizeof(p));
        f.close();
        return true;
    }

    bool appendClient(const Client& c) {
        fstream f(clientFile, ios::out | ios::app | ios::binary);
        if (!f) return false;
        f.write(reinterpret_cast<const char*>(&c), sizeof(c));
        f.close();
        return true;
    }

    bool employeeExists(const char* id) {
        fstream f(empFile, ios::in | ios::binary);
        if (!f) return false;
        Employee e;
        bool found = false;
        while (f.read(reinterpret_cast<char*>(&e), sizeof(e))) {
            if (strcmp(e.empID, id) == 0) { found = true; break; }
        }
        f.close();
        return found;
    }

    bool projectExists(const char* id) {
        fstream f(projFile, ios::in | ios::binary);
        if (!f) return false;
        Project p;
        bool found = false;
        while (f.read(reinterpret_cast<char*>(&p), sizeof(p))) {
            if (strcmp(p.projID, id) == 0) { found = true; break; }
        }
        f.close();
        return found;
    }

    bool clientExists(const char* id) {
        fstream f(clientFile, ios::in | ios::binary);
        if (!f) return false;
        Client c;
        bool found = false;
        while (f.read(reinterpret_cast<char*>(&c), sizeof(c))) {
            if (strcmp(c.clientID, id) == 0) { found = true; break; }
        }
        f.close();
        return found;
    }

    void listAllEmployees() {
        fstream f(empFile, ios::in | ios::binary);
        if (!f) { cout << "No employees.\n"; return; }
        Employee e;
        cout << left << setw(8) << "ID" << setw(18) << "Name" << setw(12) << "Department" << setw(12) << "Type" << setw(8) << "Status" << '\n';
        cout << string(70, '-') << '\n';
        while (f.read(reinterpret_cast<char*>(&e), sizeof(e))) {
            e.displayShort();
        }
        f.close();
    }

    void listAllProjects() {
        fstream f(projFile, ios::in | ios::binary);
        if (!f) { cout << "No projects.\n"; return; }
        Project p;
        cout << left << setw(8) << "ID" << setw(22) << "Name" << setw(12) << "Manager" << setw(12) << "Status" << '\n';
        cout << string(64, '-') << '\n';
        while (f.read(reinterpret_cast<char*>(&p), sizeof(p))) {
            p.displayShort();
        }
        f.close();
    }

    void listAllClients() {
        fstream f(clientFile, ios::in | ios::binary);
        if (!f) { cout << "No clients.\n"; return; }
        Client c;
        cout << left << setw(8) << "ID" << setw(22) << "Name" << setw(16) << "Contact" << '\n';
        cout << string(56, '-') << '\n';
        while (f.read(reinterpret_cast<char*>(&c), sizeof(c))) {
            c.displayShort();
        }
        f.close();
    }

    bool findEmployeeByID(const char* id, Employee& out) {
        fstream f(empFile, ios::in | ios::binary);
        if (!f) return false;
        Employee e;
        bool found = false;
        while (f.read(reinterpret_cast<char*>(&e), sizeof(e))) {
            if (strcmp(e.empID, id) == 0) { out = e; found = true; break; }
        }
        f.close();
        return found;
    }

    bool findProjectByID(const char* id, Project& out) {
        fstream f(projFile, ios::in | ios::binary);
        if (!f) return false;
        Project p;
        bool found = false;
        while (f.read(reinterpret_cast<char*>(&p), sizeof(p))) {
            if (strcmp(p.projID, id) == 0) { out = p; found = true; break; }
        }
        f.close();
        return found;
    }

    bool findClientByID(const char* id, Client& out) {
        fstream f(clientFile, ios::in | ios::binary);
        if (!f) return false;
        Client c;
        bool found = false;
        while (f.read(reinterpret_cast<char*>(&c), sizeof(c))) {
            if (strcmp(c.clientID, id) == 0) { out = c; found = true; break; }
        }
        f.close();
        return found;
    }

    bool replaceEmployee(const char* id, const Employee& newRec) {
        fstream in(empFile, ios::in | ios::binary);
        if (!in) return false;
        const char* tmp = "tmp_emp.dat";
        fstream out(tmp, ios::out | ios::binary | ios::trunc);
        Employee e;
        bool done = false;
        while (in.read(reinterpret_cast<char*>(&e), sizeof(e))) {
            if (!done && strcmp(e.empID, id) == 0) {
                out.write(reinterpret_cast<const char*>(&newRec), sizeof(newRec));
                done = true;
            } else {
                out.write(reinterpret_cast<const char*>(&e), sizeof(e));
            }
        }
        in.close(); out.close();
        if (done) {
            remove(empFile);
            rename(tmp, empFile);
        } else {
            remove(tmp);
        }
        return done;
    }

    bool replaceProject(const char* id, const Project& newRec) {
        fstream in(projFile, ios::in | ios::binary);
        if (!in) return false;
        const char* tmp = "tmp_proj.dat";
        fstream out(tmp, ios::out | ios::binary | ios::trunc);
        Project p;
        bool done = false;
        while (in.read(reinterpret_cast<char*>(&p), sizeof(p))) {
            if (!done && strcmp(p.projID, id) == 0) {
                out.write(reinterpret_cast<const char*>(&newRec), sizeof(newRec));
                done = true;
            } else {
                out.write(reinterpret_cast<const char*>(&p), sizeof(p));
            }
        }
        in.close(); out.close();
        if (done) {
            remove(projFile);
            rename(tmp, projFile);
        } else {
            remove(tmp);
        }
        return done;
    }

    bool replaceClient(const char* id, const Client& newRec) {
        fstream in(clientFile, ios::in | ios::binary);
        if (!in) return false;
        const char* tmp = "tmp_client.dat";
        fstream out(tmp, ios::out | ios::binary | ios::trunc);
        Client c;
        bool done = false;
        while (in.read(reinterpret_cast<char*>(&c), sizeof(c))) {
            if (!done && strcmp(c.clientID, id) == 0) {
                out.write(reinterpret_cast<const char*>(&newRec), sizeof(newRec));
                done = true;
            } else {
                out.write(reinterpret_cast<const char*>(&c), sizeof(c));
            }
        }
        in.close(); out.close();
        if (done) {
            remove(clientFile);
            rename(tmp, clientFile);
        } else {
            remove(tmp);
        }
        return done;
    }

    bool deleteEmployeeByID(const char* id) {
        fstream in(empFile, ios::in | ios::binary);
        if (!in) return false;
        const char* tmp = "tmp_emp.dat";
        fstream out(tmp, ios::out | ios::binary | ios::trunc);
        Employee e;
        bool deleted = false;
        while (in.read(reinterpret_cast<char*>(&e), sizeof(e))) {
            if (!deleted && strcmp(e.empID, id) == 0) {
                deleted = true;
            } else {
                out.write(reinterpret_cast<const char*>(&e), sizeof(e));
            }
        }
        in.close(); out.close();
        if (deleted) {
            remove(empFile);
            rename(tmp, empFile);
        } else {
            remove(tmp);
        }
        return deleted;
    }

    bool deleteProjectByID(const char* id) {
        fstream in(projFile, ios::in | ios::binary);
        if (!in) return false;
        const char* tmp = "tmp_proj.dat";
        fstream out(tmp, ios::out | ios::binary | ios::trunc);
        Project p;
        bool deleted = false;
        while (in.read(reinterpret_cast<char*>(&p), sizeof(p))) {
            if (!deleted && strcmp(p.projID, id) == 0) {
                deleted = true;
            } else {
                out.write(reinterpret_cast<const char*>(&p), sizeof(p));
            }
        }
        in.close(); out.close();
        if (deleted) {
            remove(projFile);
            rename(tmp, projFile);
        } else {
            remove(tmp);
        }
        return deleted;
    }

    bool deleteClientByID(const char* id) {
        fstream in(clientFile, ios::in | ios::binary);
        if (!in) return false;
        const char* tmp = "tmp_client.dat";
        fstream out(tmp, ios::out | ios::binary | ios::trunc);
        Client c;
        bool deleted = false;
        while (in.read(reinterpret_cast<char*>(&c), sizeof(c))) {
            if (!deleted && strcmp(c.clientID, id) == 0) {
                deleted = true;
            } else {
                out.write(reinterpret_cast<const char*>(&c), sizeof(c));
            }
        }
        in.close(); out.close();
        if (deleted) {
            remove(clientFile);
            rename(tmp, clientFile);
        } else {
            remove(tmp);
        }
        return deleted;
    }

    bool authenticateAdminInteractive(string& outEmpID) {
        cout << "Admin Login - Employee ID: ";
        string id; getline(cin >> ws, id);
        cout << "Password: ";
        string pwd; getline(cin, pwd);
        fstream f(empFile, ios::in | ios::binary);
        if (!f) { cout << "No employee records yet.\n"; return false; }
        Employee e;
        bool ok = false;
        while (f.read(reinterpret_cast<char*>(&e), sizeof(e))) {
            if (strcmp(e.empID, id.c_str()) == 0 && strcmp(e.empPassword, pwd.c_str()) == 0 && e.isAdmin) { ok = true; break; }
        }
        f.close();
        if (ok) { outEmpID = id; return true; }
        cout << "Authentication failed or not an admin.\n";
        return false;
    }

public:
    void addEmployeeInteractive() {
        Employee e;
        cout << "\n--- Add Employee ---\n";
        e.inputInteractive();
        if (employeeExists(e.empID)) { cout << "Employee ID already exists. Aborting.\n"; return; }
        if (appendEmployee(e)) cout << "Saved.\n"; else cout << "File error.\n";
    }

    void listEmployeesInteractive() {
        cout << "\n--- Employees ---\n";
        listAllEmployees();
    }

    void viewEmployeeInteractive() {
        char id[20];
        cout << "Enter Employee ID to view: ";
        cin >> ws; cin.getline(id, sizeof(id));
        Employee e;
        if (findEmployeeByID(id, e)) { e.displayFull(); } else cout << "Not found.\n";
    }

    void editEmployeeInteractive() {
        char id[20];
        cout << "Enter Employee ID to edit: ";
        cin >> ws; cin.getline(id, sizeof(id));
        Employee e;
        if (!findEmployeeByID(id, e)) { cout << "Not found.\n"; return; }
        cout << "Current record:\n"; e.displayFull();
        cout << "\nEnter new values:\n";
        e.inputInteractive();
        if (replaceEmployee(id, e)) cout << "Updated.\n"; else cout << "Failed to update.\n";
    }

    void deleteEmployeeInteractive() {
        char id[20];
        cout << "Enter Employee ID to delete: ";
        cin >> ws; cin.getline(id, sizeof(id));
        if (deleteEmployeeByID(id)) cout << "Deleted.\n"; else cout << "Not found.\n";
    }

    void addProjectInteractive() {
        Project p;
        cout << "\n--- Add Project ---\n";
        p.inputInteractive();
        if (projectExists(p.projID)) { cout << "Project ID exists. Aborting.\n"; return; }
        if (appendProject(p)) cout << "Saved.\n"; else cout << "File error.\n";
    }

    void listProjectsInteractive() {
        cout << "\n--- Projects ---\n";
        listAllProjects();
    }

    void viewProjectInteractive() {
        char id[20];
        cout << "Enter Project ID to view: ";
        cin >> ws; cin.getline(id, sizeof(id));
        Project p;
        if (findProjectByID(id, p)) p.displayFull(); else cout << "Not found.\n";
    }

    void editProjectInteractive() {
        char id[20];
        cout << "Enter Project ID to edit: ";
        cin >> ws; cin.getline(id, sizeof(id));
        Project p;
        if (!findProjectByID(id, p)) { cout << "Not found.\n"; return; }
        cout << "Current:\n"; p.displayFull();
        cout << "\nNew values:\n";
        p.inputInteractive();
        if (replaceProject(id, p)) cout << "Updated.\n"; else cout << "Failed.\n";
    }

    void deleteProjectInteractive() {
        char id[20];
        cout << "Enter Project ID to delete: ";
        cin >> ws; cin.getline(id, sizeof(id));
        if (deleteProjectByID(id)) cout << "Deleted.\n"; else cout << "Not found.\n";
    }

    void addClientInteractive() {
        Client c;
        cout << "\n--- Add Client ---\n";
        c.inputInteractive();
        if (clientExists(c.clientID)) { cout << "Client ID exists. Aborting.\n"; return; }
        if (appendClient(c)) cout << "Saved.\n"; else cout << "File error.\n";
    }

    void listClientsInteractive() {
        cout << "\n--- Clients ---\n";
        listAllClients();
    }

    void viewClientInteractive() {
        char id[20];
        cout << "Enter Client ID to view: ";
        cin >> ws; cin.getline(id, sizeof(id));
        Client c;
        if (findClientByID(id, c)) c.displayFull(); else cout << "Not found.\n";
    }

    void editClientInteractive() {
        char id[20];
        cout << "Enter Client ID to edit: ";
        cin >> ws; cin.getline(id, sizeof(id));
        Client c;
        if (!findClientByID(id, c)) { cout << "Not found.\n"; return; }
        cout << "Current:\n"; c.displayFull();
        cout << "\nNew values:\n";
        c.inputInteractive();
        if (replaceClient(id, c)) cout << "Updated.\n"; else cout << "Failed.\n";
    }

    void deleteClientInteractive() {
        char id[20];
        cout << "Enter Client ID to delete: ";
        cin >> ws; cin.getline(id, sizeof(id));
        if (deleteClientByID(id)) cout << "Deleted.\n"; else cout << "Not found.\n";
    }

    void adminMenu(const string& adminID) {
        while (true) {
            cout << "\n--- ADMIN MENU ---\n";
            cout << "1. Employees\n2. Projects\n3. Clients\n4. Logout\nChoose: ";
            int ch; if (!(cin >> ch)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
            if (ch == 1) {
                while (true) {
                    cout << "\nEmployees: 1.Add 2.List 3.View 4.Edit 5.Delete 6.Back\nChoose: ";
                    int e; if (!(cin >> e)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                    if (e == 1) addEmployeeInteractive();
                    else if (e == 2) listEmployeesInteractive();
                    else if (e == 3) viewEmployeeInteractive();
                    else if (e == 4) editEmployeeInteractive();
                    else if (e == 5) deleteEmployeeInteractive();
                    else if (e == 6) break;
                    else cout << "Invalid choice.\n";
                }
            } else if (ch == 2) {
                while (true) {
                    cout << "\nProjects: 1.Add 2.List 3.View 4.Edit 5.Delete 6.Back\nChoose: ";
                    int p; if (!(cin >> p)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                    if (p == 1) addProjectInteractive();
                    else if (p == 2) listProjectsInteractive();
                    else if (p == 3) viewProjectInteractive();
                    else if (p == 4) editProjectInteractive();
                    else if (p == 5) deleteProjectInteractive();
                    else if (p == 6) break;
                    else cout << "Invalid choice.\n";
                }
            } else if (ch == 3) {
                while (true) {
                    cout << "\nClients: 1.Add 2.List 3.View 4.Edit 5.Delete 6.Back\nChoose: ";
                    int c; if (!(cin >> c)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                    if (c == 1) addClientInteractive();
                    else if (c == 2) listClientsInteractive();
                    else if (c == 3) viewClientInteractive();
                    else if (c == 4) editClientInteractive();
                    else if (c == 5) deleteClientInteractive();
                    else if (c == 6) break;
                    else cout << "Invalid choice.\n";
                }
            } else if (ch == 4) {
                cout << "Logging out.\n";
                break;
            } else cout << "Invalid.\n";
        }
    }

    void userMenu(const string& empID) {
        while (true) {
            cout << "\n--- USER MENU ---\n";
            cout << "1. View My Profile\n2. View Projects\n3. View Clients\n4. Logout\nChoose: ";
            int ch; if (!(cin >> ch)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
            if (ch == 1) {
                Employee e;
                if (findEmployeeByID(empID.c_str(), e)) e.displayFull(); else cout << "Profile not found.\n";
            } else if (ch == 2) listAllProjects();
            else if (ch == 3) listAllClients();
            else if (ch == 4) break;
            else cout << "Invalid.\n";
        }
    }

    void runUnitTests() {
        cout << "\n=== Running Unit Tests (safe mode) ===\n";
        const char* te = "test_employees.dat";
        const char* tp = "test_projects.dat";
        const char* tc = "test_clients.dat";
        remove(te); remove(tp); remove(tc);
        HRMS t(te, tp, tc);
        int pass = 0, fail = 0;
        auto show = [&](bool cond, const char* msg) {
            if (cond) { cout << "[PASS] " << msg << '\n'; ++pass; }
            else { cout << "[FAIL] " << msg << '\n'; ++fail; }
        };
        Employee e1;
        safeCopy(e1.empID, "T100", sizeof(e1.empID));
        safeCopy(e1.empName, "Test User", sizeof(e1.empName));
        safeCopy(e1.empPassword, "secret1", sizeof(e1.empPassword));
        safeCopy(e1.empEmail, "test@example.com", sizeof(e1.empEmail));
        safeCopy(e1.empDOB, "1995-05-05", sizeof(e1.empDOB));
        safeCopy(e1.empJoinDate, "2020-01-01", sizeof(e1.empJoinDate));
        e1.isAdmin = true;
        show(t.appendEmployee(e1), "Add valid employee");
        show(!t.employeeExists("NONEXIST"), "Check non-existing employee returns false");
        show(t.employeeExists("T100"), "Employee exists after add");
        Employee eDup = e1;
        show(!t.appendEmployee(eDup), "Duplicate append prevented by exists check in normal flow (appendEmployee alone will append so this test is just about exists)");
        Employee eBad = e1; safeCopy(eBad.empID, "BAD-ID!", sizeof(eBad.empID));
        show(!validID(string(eBad.empID), sizeof(eBad.empID)), "Invalid ID detected");
        Project p1; safeCopy(p1.projID, "TP1", sizeof(p1.projID)); safeCopy(p1.projStartDate, "2024-01-01", sizeof(p1.projStartDate)); safeCopy(p1.projEndDate, "2024-12-31", sizeof(p1.projEndDate));
        show(t.appendProject(p1), "Add project to test file");
        Client c1; safeCopy(c1.clientID, "TC1", sizeof(c1.clientID)); safeCopy(c1.clientEmail, "client@test.com", sizeof(c1.clientEmail));
        show(t.appendClient(c1), "Add client to test file");
        show(t.projectExists("TP1"), "Project exists after add");
        show(t.clientExists("TC1"), "Client exists after add");
        show(t.deleteEmployeeByID("T100"), "Delete employee by ID");
        show(!t.employeeExists("T100"), "Employee no longer exists after delete");
        remove(te); remove(tp); remove(tc);
        cout << "Tests complete. Passed: " << pass << " Failed: " << fail << '\n';
    }

    void start() {
        while (true) {
            cout << "\n=== HRMS ===\n";
            cout << "1. Admin Login\n2. User Login\n3. Run Tests (safe)\n4. Exit\nChoose: ";
            int choice;
            if (!(cin >> choice)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
            if (choice == 1) {
                string adminID;
                if (authenticateAdminInteractive(adminID)) adminMenu(adminID);
            } else if (choice == 2) {
                cout << "User Login - Employee ID: ";
                string id; getline(cin >> ws, id);
                cout << "Password: ";
                string pwd; getline(cin, pwd);
                fstream f(empFile, ios::in | ios::binary);
                bool ok = false;
                if (f) {
                    Employee e;
                    while (f.read(reinterpret_cast<char*>(&e), sizeof(e))) {
                        if (strcmp(e.empID, id.c_str()) == 0 && strcmp(e.empPassword, pwd.c_str()) == 0) { ok = true; break; }
                    }
                    f.close();
                }
                if (ok) userMenu(id); else cout << "Login failed.\n";
            } else if (choice == 3) {
                runUnitTests();
            } else if (choice == 4) {
                cout << "Goodbye.\n";
                break;
            } else cout << "Invalid choice.\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    HRMS app;
    app.start();
    return 0;
}