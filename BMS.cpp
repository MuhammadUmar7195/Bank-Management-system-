#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <sstream> // Include for stringstream

using namespace std;

template <typename T>
string to_string_custom(T value)
{
    stringstream ss;
    ss << value;
    return ss.str();
}

class Bank
{
private:
    string bankName;

public:
    Bank(string name) : bankName(name) {}

    void displayBankDetails() const
    {
        cout << "\t Bank Name: " << bankName << endl;
    }
};

class HeadOffice
{
private:
    struct Branch
    {
        string branchID;
        string address;
    };
    vector<Branch> branches;

public:
    void addBranch(string id, string addr)
    {
        Branch newBranch = {id, addr};
        branches.push_back(newBranch);
    }

    void displayBranches() const
    {
        cout << "\t Branches:" << endl;
        for (vector<Branch>::const_iterator it = branches.begin(); it != branches.end(); ++it)
        {
            cout << "\t Branch ID: " << it->branchID << ", Address: " << it->address << endl;
        }
    }
};

class Employee
{
protected:
    string name;
    int salary;

public:
    Employee(string _name, int _salary) : name(_name), salary(_salary) {}

    virtual void displayDetails() const = 0;
    virtual int getSalary() const = 0;
};

class Manager : public Employee
{
public:
    Manager(string _name, int _salary) : Employee(_name, _salary) {}

    void displayDetails() const override
    {
        cout << "\t Manager Name: " << name << ", Salary: " << salary << endl;
    }

    int getSalary() const override
    {
        return salary;
    }
};

class Staff : public Employee
{
private:
    string resignationDate;

public:
    Staff(string _name, int _salary, string _resignationDate) : Employee(_name, _salary), resignationDate(_resignationDate) {}

    void displayDetails() const override
    {
        cout << "\t Staff Name: " << name << ", Salary: " << salary << ", Resignation Date: " << resignationDate << endl;
    }

    int getSalary() const override
    {
        return salary;
    }
};

class Transaction
{
private:
    string transactionType;
    double amount;
    string date;

public:
    Transaction(string type, double _amount, string _date) : transactionType(type), amount(_amount), date(_date) {}

    string getTransactionType() const { return transactionType; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }
};

class Loan
{
private:
    string accountNo;
    double loanAmount;
    double interestRate;
    double totalAmountDue;

public:
    Loan(string _accountNo, double _loanAmount, double _interestRate)
        : accountNo(_accountNo), loanAmount(_loanAmount), interestRate(_interestRate)
    {
        totalAmountDue = loanAmount + (loanAmount * (interestRate / 100));
    }

    string getAccountNo() const { return accountNo; }
    double getLoanAmount() const { return loanAmount; }
    double getInterestRate() const { return interestRate; }
    double getTotalAmountDue() const { return totalAmountDue; }
};

class ATM
{
private:
    double cashAvailable;

public:
    ATM(double initialCash) : cashAvailable(initialCash) {}

    void depositCash(double amount)
    {
        cashAvailable += amount;
        cout << "\t Deposit successful. Current cash available: " << cashAvailable << endl;
    }

    void withdrawCash(double amount)
    {
        if (cashAvailable >= amount)
        {
            cashAvailable -= amount;
            cout << "\t Withdrawal successful. Current cash available: " << cashAvailable << endl;
        }
        else
        {
            cout << "\t Insufficient cash available." << endl;
        }
    }

    double getCashAvailable() const { return cashAvailable; }
};

class Customer
{
private:
    string name;
    string accountNo;
    string address;
    string fathersName;
    string CNIC;
    string fathersCNIC;
    double cash;
    vector<string> transactionHistory;
    vector<Loan> loans;

public:
    Customer(string _name, string _accountNo, string _address, string _fathersName, string _CNIC, string _fathersCNIC, double _cash) : name(_name), accountNo(_accountNo), address(_address), fathersName(_fathersName), CNIC(_CNIC), fathersCNIC(_fathersCNIC), cash(_cash) {}

    string getName() const { return name; }
    string getAccountNo() const { return accountNo; }
    string getAddress() const { return address; }
    string getFathersName() const { return fathersName; }
    string getCNIC() const { return CNIC; }
    string getFathersCNIC() const { return fathersCNIC; }
    double getCash() const { return cash; }
    const vector<string> &getTransactionHistory() const { return transactionHistory; }

    void addTransaction(const Transaction &transaction)
    {
        string transactionInfo = transaction.getTransactionType() + ": " + to_string_custom(transaction.getAmount()) + " on " + transaction.getDate();
        transactionHistory.push_back(transactionInfo);
    }

    void deposit(double amount)
    {
        cash += amount;
        cout << "\t Deposit successful. New balance: " << cash << endl;
    }

    void withdraw(double amount)
    {
        if (cash >= amount)
        {
            cash -= amount;
            cout << "\t Withdrawal successful. New balance: " << cash << endl;
        }
        else
        {
            cout << "\t Insufficient balance." << endl;
        }
    }

    void viewTransactions() const
    {
        cout << "\t Transaction History:" << endl;
        for (vector<string>::const_iterator it = transactionHistory.begin(); it != transactionHistory.end(); ++it)
        {
            cout << *it << endl;
        }
    }

    void requestLoan()
    {
        double loanAmount, interestRate;
        cout << "\t Enter loan amount: ";
        cin >> loanAmount;
        cout << "\t Enter interest rate (%): ";
        cin >> interestRate;
        Loan newLoan(accountNo, loanAmount, interestRate);
        loans.push_back(newLoan);
        cout << "\t Loan requested successfully." << endl;
    }

    void viewLoans() const
    {
        cout << "\t Loan Details:" << endl;
        for (vector<Loan>::const_iterator it = loans.begin(); it != loans.end(); ++it)
        {
            cout << "\t Account Number: " << it->getAccountNo() << endl;
            cout << "\t Loan Amount: " << it->getLoanAmount() << endl;
            cout << "\t Interest Rate: " << it->getInterestRate() << "%" << endl;
            cout << "\t Total Amount Due: " << it->getTotalAmountDue() << endl;
            cout << endl;
        }
    }

    void contactSupport() const
    {
        cout << "\t Contacting customer support..." << endl;
        // Implement customer support functionality here
    }
    void changeAccountNumber(const string &newAccountNo)
    {
        accountNo = newAccountNo;
        cout << "\t Account number changed successfully. New account number: " << accountNo << endl;
    }
};

class BankManagementSystem
{
private:
    vector<Customer> customers;
    string loggedInUser;

public:
    BankManagementSystem() : loggedInUser("") {}

    void createAccount()
    {
        string name, accountNo, address, fathersName, CNIC, fathersCNIC;
        double cash;
        cout << "\t Enter customer name: ";
        cin >> name;
        cout << "\t Enter account number: ";
        cin >> accountNo;
        cout << "\t Enter address: ";
        cin >> address;
        cout << "\t Enter father's name: ";
        cin >> fathersName;
        cout << "\t Enter CNIC: ";
        cin >> CNIC;
        cout << "\t Enter father's CNIC: ";
        cin >> fathersCNIC;
        cout << "\t Enter initial cash amount: ";
        cin >> cash;
        Customer newCustomer(name, accountNo, address, fathersName, CNIC, fathersCNIC, cash);
        customers.push_back(newCustomer);
        cout << "\t Account created successfully." << endl;
    }

    void viewAllCustomerDetails() const
    {
        cout << "\t All Customer Details:" << endl;
        for (vector<Customer>::const_iterator it = customers.begin(); it != customers.end(); ++it)
        {
            cout << "\t Name: " << it->getName() << endl;
            cout << "\t Account No.: " << it->getAccountNo() << endl;
            cout << "\t Address: " << it->getAddress() << endl;
            cout << "\t Father's Name: " << it->getFathersName() << endl;
            cout << "\t CNIC: " << it->getCNIC() << endl;
            cout << "\t Father's CNIC: " << it->getFathersCNIC() << endl;
            cout << "\t Cash: " << it->getCash() << endl;
            cout << endl;
        }
    }

    void updateCustomerData()
    {
        string accountNo;
        cout << "\t Enter account number of the customer you want to update: ";
        cin >> accountNo;
        for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getAccountNo() == accountNo)
            {
                string newName, newAddress, newFathersName, newCNIC, newFathersCNIC;
                double newCash;
                cout << "\t Enter new name: ";
                cin >> newName;
                cout << "\t Enter new address: ";
                cin >> newAddress;
                cout << "\t Enter new father's name: ";
                cin >> newFathersName;
                cout << "\t Enter new CNIC: ";
                cin >> newCNIC;
                cout << "\t Enter new father's CNIC: ";
                cin >> newFathersCNIC;
                cout << "\t Enter new cash amount: ";
                cin >> newCash;
                *it = Customer(newName, accountNo, newAddress, newFathersName, newCNIC, newFathersCNIC, newCash);
                cout << "\t Customer data updated successfully." << endl;
                return;
            }
        }
        cout << "\t Customer not found with account number " << accountNo << endl;
    }

    void deposit()
    {
        string accountNo;
        double amount;
        cout << "\t Enter account number: ";
        cin >> accountNo;
        cout << "\t Enter amount to deposit: ";
        cin >> amount;
        for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getAccountNo() == accountNo)
            {
                it->deposit(amount);
                Transaction transaction("Deposit", amount, "Current Date");
                it->addTransaction(transaction);
                return;
            }
        }
        cout << "\t Customer not found with account number " << accountNo << endl;
    }

    void withdraw()
    {
        string accountNo;
        double amount;
        cout << "\t Enter account number: ";
        cin >> accountNo;
        cout << "\t Enter amount to withdraw: ";
        cin >> amount;
        for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getAccountNo() == accountNo)
            {
                it->withdraw(amount);
                Transaction transaction("\t Withdrawal", amount, "Current Date");
                it->addTransaction(transaction);
                return;
            }
        }
        cout << "\t Customer not found with account number " << accountNo << endl;
    }

    void viewTransactionHistory()
    {
        string accountNo;
        cout << "\t Enter account number: ";
        cin >> accountNo;
        for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getAccountNo() == accountNo)
            {
                it->viewTransactions();
                return;
            }
        }
        cout << "\t Customer not found with account number " << accountNo << endl;
    }

    void viewLoans()
    {
        string accountNo;
        cout << "\t Enter account number: ";
        cin >> accountNo;
        for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getAccountNo() == accountNo)
            {
                it->viewLoans();
                return;
            }
        }
        cout << "\t Customer not found with account number " << accountNo << endl;
    }

    void requestLoan()
    {
        string accountNo;
        cout << "\t Enter account number: ";
        cin >> accountNo;
        for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getAccountNo() == accountNo)
            {
                it->requestLoan();
                return;
            }
        }
        cout << "\t Customer not found with account number " << accountNo << endl;
    }
    void changeAccountNumber()
    {
        string accountNo, newAccountNo;
        cout << "\t Enter account number: ";
        cin >> accountNo;
        cout << "\t Enter new account number: ";
        cin >> newAccountNo;
        for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getAccountNo() == accountNo)
            {
                it->changeAccountNumber(newAccountNo);
                return;
            }
        }
        cout << "\t Customer not found with account number " << accountNo << endl;
    }

    void viewBankDetails(const Bank &bank, const HeadOffice &headOffice, const vector<Employee *> &employees) const
    {
        bank.displayBankDetails();
        headOffice.displayBranches();
        cout << "\n\t Staff and Manager Details:" << endl;
        for (vector<Employee *>::const_iterator it = employees.begin(); it != employees.end(); ++it)
        {
            (*it)->displayDetails();
        }
    }

    void manageBankDetails(Bank &bank)
    {
        string newName;
        cout << "\t Enter new bank name: ";
        cin >> newName;
        bank = Bank(newName);
        cout << "\t Bank details updated successfully." << endl;
    }

    void manageHeadOffice(HeadOffice &headOffice)
    {
        string branchID, address;
        cout << "\t Enter branch ID: ";
        cin >> branchID;
        cout << "\t Enter branch address: ";
        cin >> address;
        headOffice.addBranch(branchID, address);
        cout << "\t Branch added successfully." << endl;
    }

    void manageEmployees(vector<Employee *> &employees)
    {
        char choice;
        cout << "\t Select employee type: (M)anager / (S)taff: ";
        cin >> choice;
        string name;
        int salary;
        string resignationDate;
        cout << "\t Enter employee name: ";
        cin >> name;
        cout << "\t Enter employee salary: ";
        cin >> salary;
        if (choice == 'M' || choice == 'm')
        {
            employees.push_back(new Manager(name, salary));
        }
        else if (choice == 'S' || choice == 's')
        {
            cout << "\t Enter resignation date (YYYY-MM-DD): ";
            cin >> resignationDate;
            employees.push_back(new Staff(name, salary, resignationDate));
        }
        else
        {
            cout << "\t Invalid choice." << endl;
        }
        cout << "\t Employee added successfully." << endl;
    }
    void contactSupport()
    {
        cout << "\t Customer Support" << endl;
        cout << "\t 1. Contact Info" << endl;
        cout << "\t 2. Change Account No" << endl;
        cout << "\t 3. Update Customer Data" << endl;
        cout << "\t 4. FAQs" << endl;
        cout << "\t 5. Exit" << endl;
        int choice;
        cout << "\t Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\t Contact Info: 03147372660\n Email: BOP@gmail.com" << endl;
            break;
        case 2:
            changeAccountNumber();
            break;
        case 3:
            updateCustomerData();
            break;
        case 4:
            cout << "\t Frequently Asked Questions:" << endl;
            cout << "\t 1. How to deposit cash?" << endl;
            cout << "\t A1. You can deposit cash by visiting any of our branches or using our ATMs." << endl;
            cout << "\t Q2. How to apply for a loan?" << endl;
            cout << "\t A2. You can apply for a loan by visiting any of our branches and filling out the loan application form." << endl;
            // Add more FAQs as needed
            break;
        case 5:
            cout << "\t Exiting customer support." << endl;
            break;
        default:
            cout << "\t Invalid choice." << endl;
        }
    }

    // Function to save data to a file
    void saveDataToFile()
    {
        ofstream file("bank_data.txt");
        if (file.is_open())
        {
            for (size_t i = 0; i < customers.size(); ++i)
            {
                const Customer &customer = customers[i];
                file << customer.getName() << "," << customer.getAccountNo() << "," << customer.getAddress() << "," << customer.getFathersName() << "," << customer.getCNIC() << "," << customer.getFathersCNIC() << "," << customer.getCash() << endl;
            }
            file.close();
        }
        else
        {
            cout << "\t Unable to open file for saving data." << endl;
        }
    }

    // Function to load data from a file
    void loadDataFromFile()
    {
        ifstream file("bank_data.txt");
        if (file.is_open())
        {
            customers.clear(); // Clear existing data
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string name, accountNo, address, fathersName, CNIC, fathersCNIC;
                double cash;
                getline(ss, name, ',');
                getline(ss, accountNo, ',');
                getline(ss, address, ',');
                getline(ss, fathersName, ',');
                getline(ss, CNIC, ',');
                getline(ss, fathersCNIC, ',');
                ss >> cash;
                Customer newCustomer(name, accountNo, address, fathersName, CNIC, fathersCNIC, cash);
                customers.push_back(newCustomer);
            }
            file.close();
        }
        else
        {
            cout << "\t Unable to open file for loading data." << endl;
        }
    }

    ~BankManagementSystem()
    {
        saveDataToFile(); // Save data to file when the program exits.
    }
};

int main()
{
    Bank bank(" Bank Of Punjab (BOP)"); // Initialize bank object with the default name.
    HeadOffice headOffice;
    headOffice.addBranch("001", "Lahore");
    headOffice.addBranch("002", "Karachi");

    // Creating employees
    Manager manager("Asad ullah Ansari", 150000);
    Staff staff1("Umar Asif", 30000, "2023-01-15");
    Staff staff2("Ali Hassan", 3200, "2022-12-31");

    // Storing employees in a vector
    vector<Employee *> employees;
    employees.push_back(&manager);
    employees.push_back(&staff1);
    employees.push_back(&staff2);

    // Key to access bank details
    string accessKey = "bank123";

    BankManagementSystem bms;
    bms.loadDataFromFile(); // Load data from file when the program starts.

    char choice;
    string enteredKey;

    // Display bank name at the start.
    bank.displayBankDetails();

    while (true)
    {
        cout << "\n\n\t Please select an option:" << endl;
        cout << "\t 1. Bank Details" << endl;
        cout << "\t 2. Enter Customer Site" << endl;
        cout << "\t 3. Enter Admin Site" << endl;
        cout << "\t 4. Customer Support" << endl;
        cout << "\t 5. Exit" << endl;

        cout << "\t Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            cout << "\t Enter access key for bank details: ";
            cin >> enteredKey;
            if (enteredKey == accessKey)
            {
                bms.viewBankDetails(bank, headOffice, employees);
            }
            else
            {
                cout << "\t Invalid access key!" << endl;
            }
            break;
        case '2':
            while (true)
            {
                cout << "\n\nWelcome to the Customer Site!" << endl;
                cout << "\t Please select an option:" << endl;
                cout << "\t 1. Create Account" << endl;
                cout << "\t 2. ATM" << endl;
                cout << "\t 3. Transaction History" << endl;
                cout << "\t 4. Request Loan" << endl;
                cout << "\t 5. View Loans" << endl;
                cout << "\t 6. Back" << endl;
                cout << "\t Enter your choice: ";
                cin >> choice;
                if (choice < '1' || choice > '6')
                {
                    cout << "\t Invalid choice. Please enter a number between 1 and 8." << endl;
                    continue;
                }
                if (choice == '6')
                {
                    break; // Go back to the main menu.
                }
                switch (choice)
                {
                case '1':
                    bms.createAccount();
                    break;
                case '2':
                    while (true)
                    {
                        cout << "\n\nATM Menu:" << endl;
                        cout << "\t 1. Deposit" << endl;
                        cout << "\t 2. Withdraw" << endl;
                        cout << "\t 3. Back" << endl;
                        cout << "\t Enter your choice: ";
                        cin >> choice;
                        if (choice < '1' || choice > '3')
                        {
                            cout << "\t Invalid choice. Please enter a number between 1 and 3." << endl;
                            continue;
                        }
                        if (choice == '3')
                        {
                            break; // Go back to the customer site menu.
                        }
                        switch (choice)
                        {
                        case '1':
                            bms.deposit();
                            break;
                        case '2':
                            bms.withdraw();
                            break;
                        }
                    }
                    break;
                case '3':
                    bms.viewTransactionHistory();
                    break;
                case '4':
                    bms.requestLoan();
                    break;
                case '5':
                    bms.viewLoans();
                    break;
                }
            }
            break;
        case '3':
            cout << "\t Enter admin password: ";
            cin >> enteredKey; // Reusing enteredKey variable for password.
            if (enteredKey == "admin")
            {
                while (true)
                {
                    cout << "\n\n\t Welcome to the Admin Site!" << endl;
                    cout << "\t Please select an option:" << endl;

                    cout << "\t 1. Manage Bank Details" << endl;
                    cout << "\t 2. Manage Head Office" << endl;
                    cout << "\t 3. Manage Employees" << endl;
                    cout << "\t 4. View Customers List" << endl;
                    cout << "\t 5. Back" << endl;
                    cout << "\t Enter your choice: ";
                    cin >> choice;
                    if (choice < '1' || choice > '5')
                    {
                        cout << "\t Invalid choice. Please enter a number between 1 and 5." << endl;
                        continue;
                    }
                    if (choice == '5')
                    {
                        break; // Go back to the main menu
                    }
                    switch (choice)
                    {
                    case '1':
                        bms.manageBankDetails(bank);
                        break;
                    case '2':
                        bms.manageHeadOffice(headOffice);
                        break;
                    case '3':
                        bms.manageEmployees(employees);
                        break;
                    case '4':
                        bms.viewAllCustomerDetails();
                        break;
                    }
                }
            }
            else
            {
                cout << "\t Invalid password!" << endl;
            }
            break;
        case '5':
            cout << "\t Thank you for using our Bank Management System. Goodbye!" << endl;
            return 0; // Exit the program
            break;
        case '4':
            bms.contactSupport();
            break;
        default:
            cout << "\t Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    }

    return 0;
}