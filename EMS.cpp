#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
using namespace std;

class Employee {
public:
    int id;
    string name;
    string position;
    double salary;
    string phoneNumber;
    string emailAddress;
    string address;
    string dateOfBirth;
    string gender;
    string dateOfJoining;

    Employee* next;

    Employee(int empId, string empName, string empPosition, double empSalary, string empPhoneNumber,
        string empEmailAddress, string empAddress, string empDateOfBirth, string empGender, string empDateOfJoining) {
        id = empId;
        name = empName;
        position = empPosition;
        salary = empSalary;
        phoneNumber = empPhoneNumber;
        emailAddress = empEmailAddress;
        address = empAddress;
        dateOfBirth = empDateOfBirth;
        gender = empGender;
        dateOfJoining = empDateOfJoining;
        next = nullptr;
    }
};


class Department {
public:
    string dept_name;
    Employee* ehead;
    Department* next;

    Department() {
        dept_name = "";
        ehead = nullptr;
        next = nullptr;
    }

    Department(string name) {
        dept_name = name;
        ehead = nullptr;
        next = nullptr;
    }

    void addEmployee(int data, string empName, string empPosition, double empSalary, string empPhoneNumber,
        string empEmailAddress, string empAddress, string empDateOfBirth, string empGender, string empDateOfJoining) {
        
        Employee* emp = new Employee(data , empName,  empPosition,  empSalary,  empPhoneNumber,
             empEmailAddress,  empAddress,  empDateOfBirth,  empGender,  empDateOfJoining);
        if (ehead == nullptr) {
            ehead = emp;
        }
        else {
            emp->next = ehead;
            ehead = emp;
        }
    }

    void updateEmployee(int id,string name,string email,string phone,string addres) {
        Employee* curr = ehead;
        while (curr != nullptr) {
            if (curr->id == id) {
                curr->name = name;
                curr->emailAddress = email;
                curr->phoneNumber = phone;
                curr->address = addres;
                return;
            }
            curr = curr->next;
        }
        cout << "Employee not found." << endl;
    }

    bool deleteEmployee(int data) {
        if (ehead == nullptr) {
            cout << "No employees to delete." << endl;
            return false;
        }

        Employee* curr = ehead;
        Employee* prev = nullptr;
        if (curr->id == data) {
            ehead = curr->next;
            cout << "Employee deleted with id:" << curr->id << endl;
            delete curr;
            
            return true;
        }

        while (curr != nullptr) {
            if (curr->id == data) {
                prev->next = curr->next;
                cout << "Employee deleted with id:" << curr->id << endl;
                delete curr;
                
                return true;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Employee not found." << endl;
        return false;
    }

    void printEmployees() {
        Employee* emp = ehead;
        while (emp != nullptr) {
            cout << "Employee id: " << emp->id << endl;
          
            cout << "Employee name: " << emp->name << endl;
            cout << "Employee position: " << emp->position << endl;
            cout << "Employee salary: " << emp->salary << endl;
            cout << "Employee phone number: " << emp->phoneNumber << endl;
            cout << "Employee email address: " << emp->emailAddress << endl;
            cout << "Employee address: " << emp->address << endl;
            cout << "Employee date of birth: " << emp->dateOfBirth << endl;
            cout << "Employee gender: " << emp->gender << endl;
            cout << "Employee date of joining: " << emp->dateOfJoining << endl;

            emp = emp->next;
        }
    }


    Employee* searchEmployee(int data) {
        Employee* emp = ehead;
        while (emp != nullptr) {
            if (emp->id == data) {
                return emp;
            }
            emp = emp->next;
        }
        return nullptr;
    }
};

class EmployeeList {
public:
    Department* head;

    EmployeeList() {
        head = nullptr;
    }

    void addDepartment(string name) {
        Department* dept = new Department(name);
        if (head == nullptr) {
            head = dept;
        }
        else {
            Department* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = dept;
        }
    }

    void addEmployee(string deptName, int data, string empName, string empPosition, double empSalary, string empPhoneNumber,
        string empEmailAddress, string empAddress, string empDateOfBirth, string empGender, string empDateOfJoining) {
        Department* dept = head;
        
        while (dept != nullptr) {
            if (dept->searchEmployee(data) != nullptr) {
                cout << "An employee with ID " << data << " already exists." << endl;
                return;
            }
            dept = dept->next;
        }

        dept = head;
        while (dept != nullptr && dept->dept_name != deptName) {
            dept = dept->next;
        }
        if (dept == nullptr) {
            cout << "Department not found." << endl;
            return;
        }
        else {
            dept->addEmployee(data, empName, empPosition, empSalary, empPhoneNumber,
                empEmailAddress, empAddress, empDateOfBirth, empGender, empDateOfJoining);
            cout << "Employee added to department: " << deptName << " with id: " << data << endl;
        }
    }
    void display_all_departments() {
        Department* dept = head;
        if (dept == nullptr) {
            cout << "no department added yet" << endl;

        }
        else {
            cout << "departments:"<<endl;
            while (dept != nullptr) {
                 cout<< dept->dept_name<<endl;
                dept = dept->next;
            }
        }
    }
    void printDepartments() {
        Department* dept = head;
        while (dept != nullptr) {
            cout << "Department: " << dept->dept_name << endl;
            dept->printEmployees();
            dept = dept->next;
        }
    }

    void updateEmployee(string deptName, int id, string name, string email, string phone, string addres) {
        Department* dept = head;
        while (dept != nullptr && dept->dept_name != deptName) {
            dept = dept->next;
        }
        if (dept == nullptr) {
            cout << "Department not found." << endl;
            return;
        }
        else {
            dept->updateEmployee(id, name,  email,  phone, addres);
            cout << "Employee info updated in department: " << deptName <<endl;
        }
    }

    void deleteEmployee(string deptName, int data) {
        Department* dept = head;
        while (dept != nullptr && dept->dept_name != deptName) {
            dept = dept->next;
        }
        if (dept == nullptr) {
            cout << "Department not found." << endl;
            return;
        }
        bool check = 0;

        check=dept->deleteEmployee(data);
        if (check == 1) {
            cout << "And department: " << deptName << endl;
        }
    }

    Employee* searchEmployee(int data) {
        Department* dept = head;
        while (dept != nullptr) {
            Employee* emp = dept->searchEmployee(data);
            if (emp != nullptr) {
                return emp;
            }
            dept = dept->next;
        }
        return nullptr;
    }
    void displayEmployeesInDepartment(string deptName) {
        Department* dept = head;
        while (dept != nullptr && dept->dept_name != deptName) {
            dept = dept->next;
        }

        if (dept == nullptr) {
            cout << "Department not found." << endl;
            return;
        }

        dept->printEmployees();
    }
};

class Admin {
    string name;
    string password;
public:
    bool verification() {
        
        ifstream fin;
        fin.open("admin.txt");
        if (!fin.is_open()) {
            cout << "file not found" << endl;
            return false;
        }
        cout << "Enter your credidentials to login:"<<endl;
        string tempName;
        string tempPass;
        bool found = false;

        cout << "Username: "<<endl;
        string inputName;
        cin.ignore();
        getline(cin, inputName);
       
        cout << "Password: " << endl;
        string inputPassword;
        
        getline(cin, inputPassword);

        while (!fin.eof()) {
            getline(fin,tempName );
            getline(fin, tempPass);


            if (inputName == tempName && inputPassword == tempPass) {
                name = tempName;
                password = tempPass;
                found = true;
                cout << "Authentication successful. Welcome, " << name << "!" << endl;
                return true;
                break;
            }
        }

        fin.close();

        if (!found) {
           
            return false;
        }


        return false;
    }
    
    EmployeeList empList;

    void addDepartment(string name) {
        empList.addDepartment(name);
        cout << "Department added: " << name << endl;
    }

    void addEmployee(string deptName, int data, string empName, string empPosition, double empSalary, string empPhoneNumber,
        string empEmailAddress, string empAddress, string empDateOfBirth, string empGender, string empDateOfJoining) {
        empList.addEmployee(deptName, data, empName, empPosition, empSalary, empPhoneNumber,
            empEmailAddress, empAddress, empDateOfBirth, empGender, empDateOfJoining);
        
    }
    void display_all_departments() {
        empList.display_all_departments();
    }

    void updateEmployee(string deptName,  int id, string name, string email, string phone, string addres) {
        empList.updateEmployee(deptName,  id,  name,  email,  phone,  addres);
       
    }

    void deleteEmployee(string deptName, int data) {
        empList.deleteEmployee(deptName, data);
        
    }

    void displayEmployees() {
        empList.printDepartments();
    }
    void displayEmployeesInDepartment(string deptName) {
        cout << "Employees in the " << deptName << " department:" << endl;
        empList.displayEmployeesInDepartment(deptName);
    }

    void searchEmployee(int data) {
        Employee* emp = empList.searchEmployee(data);
        if (emp != nullptr) {
            cout << "Employee found with id: " << emp->id << endl;
            cout << "Employee name: " << emp->name << endl;

            Department* dept = empList.head;
            while (dept != nullptr) {
                Employee* foundEmp = dept->searchEmployee(data);
                if (foundEmp != nullptr) {
                    cout << "Employee department: " << dept->dept_name << endl;
                    break;
                }
                dept = dept->next;
            }
            cout << "Employee position: " << emp->position << endl;
            cout << "Employee salary: " << emp->salary << endl;
            cout << "Employee phone number: " << emp->phoneNumber << endl;
            cout << "Employee email address: " << emp->emailAddress << endl;
            cout << "Employee address: " << emp->address << endl;
            cout << "Employee date of birth: " << emp->dateOfBirth << endl;
            cout << "Employee gender: " << emp->gender << endl;
            cout << "Employee date of joining: " << emp->dateOfJoining << endl;
        }
        else {
            cout << "Employee not found." << endl;
        }
    }

};

int main() {
    Admin admin;
    bool error_check = 0;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "|                                                               |" << endl;
    cout << "|                    Employee Mangement System                  |" << endl;
    cout << "|                                                               |" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    while (true) {
        cout << "Are you an Admin or an Employee?" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Employee" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            error_check = admin.Admin::verification();
            if (error_check == true) {
                while (true) {
                    cout << "Admin Menu:" << endl;
                    cout << "1. Add Department" << endl;
                    cout << "2. Add Employee" << endl;
                    cout << "3. Delete Employee" << endl;
                    cout << "4. Display Employees" << endl;
                    cout << "5. Display Employees for given department" << endl;
                    cout << "6. Display every department in company" << endl;
                    cout << "7. Log out from admin menu" << endl;
                    cout << "Enter your choice: ";
                    int adminChoice;
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1: {
                        cout << "Enter department name: ";

                        string name;
                        cin >> name;
                        admin.addDepartment(name);
                        break;
                    }
                    case 2: {
                        cout << "Enter department name: ";
                        string deptName;
                        cin.ignore();
                        getline(cin, deptName);

                        cout << "Enter employee id: ";
                        int data;
                        cin >> data;
                        cin.ignore();

                        cout << "Enter employee name: ";
                        string empName;
                        getline(cin, empName);

                        cout << "Enter employee position: ";
                        string empPosition;
                        getline(cin, empPosition);

                        cout << "Enter employee salary: ";
                        double empSalary;
                        cin >> empSalary;
                        cin.ignore();

                        cout << "Enter employee phone number: ";
                        string empPhoneNumber;
                        getline(cin, empPhoneNumber);

                        cout << "Enter employee email address: ";
                        string empEmailAddress;
                        getline(cin, empEmailAddress);

                        cout << "Enter employee address: ";
                        string empAddress;
                        getline(cin, empAddress);

                        cout << "Enter employee date of birth: ";
                        string empDateOfBirth;
                        getline(cin, empDateOfBirth);

                        cout << "Enter employee gender: ";
                        string empGender;
                        getline(cin, empGender);

                        cout << "Enter employee date of joining: ";
                        string empDateOfJoining;
                        getline(cin, empDateOfJoining);

                        admin.addEmployee(deptName, data, empName, empPosition, empSalary, empPhoneNumber,
                            empEmailAddress, empAddress, empDateOfBirth, empGender, empDateOfJoining);
                        break;
                    }




                    case 3: {
                        cout << "Enter department name: ";
                        string deptName;
                        cin >> deptName;
                        cout << "Enter employee data to delete: ";
                        int data;
                        cin >> data;
                        admin.deleteEmployee(deptName, data);
                        break;
                    }
                    case 4: {
                        admin.displayEmployees();
                        break;
                    }
                    case 5: {
                        cout << "enter department name to search employees in that department" << endl;
                        string deptName;
                        cin >> deptName;
                        admin.displayEmployeesInDepartment(deptName);
                        break;
                    }
                    case 6: {
                        admin.display_all_departments();
                        break;
                    }
                    case 7: {
                        cout << "Exiting Admin menu..." << endl;
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
                    }

                    if (adminChoice == 7) {
                        break;
                    }
                }
                break;
            }
            else {
                cout << "Authentication failed.incorrect password or username." << endl;
                break;
 }
        }
            

               
        case 2: {
            while (true) {
                cout << "Employee Menu:" << endl;
                cout << "1. view your info" << endl;
                cout << "2. Update your info" << endl;
                cout << "3. Log out from employee menu" << endl;
                cout << "Enter your choice: ";
                int empChoice;
                cin >> empChoice;

                switch (empChoice) {
                case 1: {
                    cout << "Enter your employee id to search: ";
                    int data;
                    cin >> data;
                    admin.searchEmployee(data);
                  
                    break;
                }
                
                case 2: {
                    cout << "Enter department name: ";
                    string deptName;
                    cin.ignore();
                    getline(cin, deptName);

                    cout << "Enter employee id: ";
                    int id;
                    cin >> id;
                    cin.ignore();

                    cout << "Enter new employee name: ";
                    string name;
                    getline(cin, name);

                    cout << "Enter new employee email: ";
                    string email;
                    getline(cin, email);

                    cout << "Enter new employee phone number: ";
                    string phone;
                    getline(cin, phone);

                    cout << "Enter new employee address: ";
                    string address;
                    getline(cin, address);

                    admin.updateEmployee(deptName, id, name, email, phone, address);
                    break;
                }
                
                case 3: {
                    cout << "Exiting Employee menu..." << endl;
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
                }

                if (empChoice == 3) {
                    break;  
                }
            }
            break;
        }
        case 3: {
            cout << "Exiting Employee Management System..." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }
    system("pause");
    return 0;
}

    


