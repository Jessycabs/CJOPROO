//conta: 12345 pin: 54321; conta: 67890 pin: 98765
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Classe Account representando uma conta bancária
class Account {
private:
    int accountNumber;
    int pin;
    double balance;

public:
    Account(int accNum, int pinCode, double initialBalance)
        : accountNumber(accNum), pin(pinCode), balance(initialBalance) {}

    int getAccountNumber() const { return accountNumber; }
    bool validatePin(int inputPin) const { return pin == inputPin; }
    double getBalance() const { return balance; }

    bool withdraw(double amount) {
        if (amount > balance || amount <= 0 || static_cast<int>(amount) % 10 != 0) {
            return false;
        }
        balance -= amount;
        return true;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
};

// Classe ATM representando o terminal
class ATM {
private:
    vector<Account> accounts;
    Account* authenticatedAccount = nullptr;

    Account* findAccount(int accountNumber) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accountNumber) {
                return &acc;
            }
        }
        return nullptr;
    }

public:
    ATM() {
        // Contas pré-configuradas
        accounts.push_back(Account(12345, 54321, 1000.0));
        accounts.push_back(Account(67890, 98765, 1500.0));
    }

    bool authenticate(int accountNumber, int pin) {
        Account* acc = findAccount(accountNumber);
        if (acc && acc->validatePin(pin)) {
            authenticatedAccount = acc;
            return true;
        }
        return false;
    }

    void showMainMenu() {
        if (!authenticatedAccount) {
            cout << "Erro: Nenhuma conta autenticada.\n";
            return;
        }

        int choice;
        do {
            cout << "\nATM Menu:\n";
            cout << "1. Ver saldo\n";
            cout << "2. Sacar\n";
            cout << "3. Depositar\n";
            cout << "4. Sair\n";
            cout << "Escolha uma opção: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Saldo atual: R$" << fixed << setprecision(2)
                         << authenticatedAccount->getBalance() << "\n";
                    break;
                case 2: {
                    double amount;
                    cout << "Informe o valor para saque (múltiplo de R$10): ";
                    cin >> amount;
                    if (authenticatedAccount->withdraw(amount)) {
                        cout << "Saque realizado com sucesso.\n";
                    } else {
                        cout << "Saque inválido ou saldo insuficiente.\n";
                    }
                    break;
                }
                case 3: {
                    double amount;
                    cout << "Informe o valor para depósito: ";
                    cin >> amount;
                    authenticatedAccount->deposit(amount);
                    cout << "Depósito realizado com sucesso.\n";
                    break;
                }
                case 4:
                    cout << "Encerrando sessão.\n";
                    break;
                default:
                    cout << "Opção inválida. Tente novamente.\n";
            }
        } while (choice != 4);
        authenticatedAccount = nullptr;
    }
};

int main() {
    ATM atm;
    cout << "Bem-vindo ao sistema ATM!\n";

    while (true) {
        int accountNumber, pin;
        cout << "\nInforme o número da conta (ou -1 para sair): ";
        cin >> accountNumber;
        if (accountNumber == -1) break;

        cout << "Informe o PIN: ";
        cin >> pin;

        if (atm.authenticate(accountNumber, pin)) {
            atm.showMainMenu();
        } else {
            cout << "Número da conta ou PIN incorreto.\n";
        }
    }
    cout << "Obrigado por usar o sistema ATM!\n";
    return 0;
}
