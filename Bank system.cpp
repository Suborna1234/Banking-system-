#include <iostream>
#include <vector>
using namespace std;

const double SAVINGS_INTEREST = 4.5;
const double FDR_INTEREST = 7.0;
const double DPS_INTEREST = 8.5;

class Account {
    string name;
    int id;
    double balance;
    bool hasFDR;
    bool hasDPS;
    double fdrAmount;
    int fdrTerm;
    double dpsMonthlyAmount;
    int dpsMonths;

public:
    Account(string n, int i, double b) {
        name = n;
        id = i;
        balance = b;
        hasFDR = false;
        hasDPS = false;
        fdrAmount = 0;
        fdrTerm = 0;
        dpsMonthlyAmount = 0;
        dpsMonths = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << name << " deposited $" << amount << ". New balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << name << " withdrew $" << amount << ". Remaining balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance for " << name << endl;
        }
    }

    void createFDR(double amount, int term) {
        if (balance >= amount) {
            balance -= amount;
            hasFDR = true;
            fdrAmount = amount;
            fdrTerm = term;
            cout << name << " created FDR of $" << amount << " for " << term << " months." << endl;
        } else {
            cout << "Not enough balance to create FDR.\n";
        }
    }

    void createDPS(double monthlyAmount, int months) {
        hasDPS = true;
        dpsMonthlyAmount = monthlyAmount;
        dpsMonths = months;
        cout << name << " started DPS of $" << monthlyAmount << "/month for " << months << " months." << endl;
    }

    void applyInterest() {

        double savingsInterest = balance * SAVINGS_INTEREST / 100.0;
        balance += savingsInterest;
        cout << name << " earned Savings Interest: $" << savingsInterest << endl;


        if (hasFDR) {
            double fdrInterest = fdrAmount * FDR_INTEREST / 100.0 * (fdrTerm / 12.0);
            double maturedAmount = fdrAmount + fdrInterest;
            cout << name << "'s FDR matured with interest: $" << fdrInterest << ", Total returned: $" << maturedAmount << endl;
            balance += maturedAmount;
            hasFDR = false;
        }


        if (hasDPS) {
            double totalDPS = dpsMonthlyAmount * dpsMonths;
            double dpsInterest = totalDPS * DPS_INTEREST / 100.0;
            double totalAmount = totalDPS + dpsInterest;
            cout << name << "'s DPS matured with interest: $" << dpsInterest << ", Total amount: $" << totalAmount << endl;
            balance += totalAmount;
            hasDPS = false;
        }
    }

    void display() const {
        cout << "Name: " << name << ", ID: " << id << ", Balance: $" << balance << endl;
        if (hasFDR) {
            cout << "  Has FDR: $" << fdrAmount << " for " << fdrTerm << " months\n";
        }
        if (hasDPS) {
            cout << "  Has DPS: $" << dpsMonthlyAmount << "/month for " << dpsMonths << " months\n";
        }
    }

    int getId() const { return id; }
};

class Bank {
    vector<Account> accounts;

public:
    void createAccounts() {
        cout << "Enter details for 10 users:\n";
        for (int i = 0; i < 10; i++) {
            string name;
            int id;
            double balance;
            cout << "User " << (i + 1) << " Name: ";
            cin >> name;
            cout << "User " << (i + 1) << " ID: ";
            cin >> id;
            cout << "User " << (i + 1) << " Initial Balance: ";
            cin >> balance;

            accounts.emplace_back(name, id, balance);
            cout << "Account created for " << name << "\n\n";
        }
    }

    Account* findAccount(int id) {
        for (auto& acc : accounts) {
            if (acc.getId() == id) return &acc;
        }
        return nullptr;
    }

    void deposit(int id, double amount) {
        Account* acc = findAccount(id);
        if (acc) acc->deposit(amount);
        else cout << "Account not found!\n";
    }

    void withdraw(int id, double amount) {
        Account* acc = findAccount(id);
        if (acc) acc->withdraw(amount);
        else cout << "Account not found!\n";
    }

    void createFDR(int id, double amount, int term) {
        Account* acc = findAccount(id);
        if (acc) acc->createFDR(amount, term);
        else cout << "Account not found!\n";
    }

    void createDPS(int id, double monthlyAmount, int months) {
        Account* acc = findAccount(id);
        if (acc) acc->createDPS(monthlyAmount, months);
        else cout << "Account not found!\n";
    }

    void applyInterest(int id) {
        Account* acc = findAccount(id);
        if (acc) acc->applyInterest();
        else cout << "Account not found!\n";
    }

    void display(int id) {
        Account* acc = findAccount(id);
        if (acc) acc->display();
        else cout << "Account not found!\n";
    }

    void displayAll() {
        for (const auto& acc : accounts) {
            acc.display();
            cout << "------------------------\n";
        }
    }
};

int main() {
    Bank bank;
    bank.createAccounts();

    int choice;
    int id;
    double amount;
    int term, months;

    do {
        cout << "\n--- Bank Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Create FDR\n4. Create DPS\n5. Apply Interest\n6. Display Account\n7. Display All\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Account ID: "; cin >> id;
                cout << "Enter Deposit Amount: "; cin >> amount;
                bank.deposit(id, amount);
                break;
            case 2:
                cout << "Enter Account ID: "; cin >> id;
                cout << "Enter Withdraw Amount: "; cin >> amount;
                bank.withdraw(id, amount);
                break;
            case 3:
                cout << "Enter Account ID: "; cin >> id;
                cout << "Enter FDR Amount: "; cin >> amount;
                cout << "Enter Term in months: "; cin >> term;
                bank.createFDR(id, amount, term);
                break;
            case 4:
                cout << "Enter Account ID: "; cin >> id;
                cout << "Enter Monthly DPS Amount: "; cin >> amount;
                cout << "Enter DPS Months: "; cin >> months;
                bank.createDPS(id, amount, months);
                break;
            case 5:
                cout << "Enter Account ID: "; cin >> id;
                bank.applyInterest(id);
                break;
            case 6:
                cout << "Enter Account ID: "; cin >> id;
                bank.display(id);
                break;
            case 7:
                bank.displayAll();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

