#include <iostream>
#include <string>
#include <ctime>
#include <memory>
#include "transactions.h"
#include "pointers.h"

class Bank
{
    std::string name;
    std::string unp;
    std::tm regDate;

public:
    Bank(std::string name, std::string unp, std::tm regDate)
            : name(name), unp(unp), regDate(regDate)
    { }

    std::string getName() { return name; }
    void setName(std::string n)
    {
        if (n.empty())
        {
            return;
        }
        name = n;
    }

    std::string getUnp() { return unp; }
    std::tm getRegDate() { return regDate; }
};

class BankClient
{
    std::string name;
    std::string surname;
    std::string passportNum;
    std::tm birthDate;

public:
    std::string getName() { return name; }
    void setName(std::string name)
    {
        if (name.empty())
        {
            return;
        }
        this->name = name;
    }

    std::string getsSurname() { return surname; }
    void setSurname(std::string surname)
    {
        if (surname.empty())
        {
            return;
        }
        this->surname = surname;
    }

    std::string getPassportNum() { return passportNum; }
    void setPassportNum(std::string pn)
    {
        if (pn.empty())
        {
            return;
        }
        this->passportNum = pn;
    }

    std::tm getBirthDate() { return birthDate; }
    void setBirthDate(std::tm bd)
    {
        this->birthDate = bd;
    }

    bool checkData()
    {
        bool res = true;
        res &= !name.empty();
        res &= !surname.empty();
        res &= !passportNum.empty();

        return res;
    }
};

class Contract
{
    std::shared_ptr<BankClient> client;
    std::string bankName;
    std::tm conclusionDate;
    int contractNum;
    std::string city;
    std::string obligations;
    double amount;

public:
    Contract() : client(NULL)
    { }

    Contract(std::shared_ptr<BankClient> client, std::tm cd, int conNum, std::string city, std::string oblg, double amount, std::string bank)
            : client(client), conclusionDate(cd), contractNum(conNum), city(city), obligations(oblg), amount(amount), bankName(bank)
    { }

    std::shared_ptr<BankClient> getClient() { return client; }
    std::tm getConclusionDate() { return conclusionDate; }
    int getContractNum() { return contractNum; }
    std::string getCity() { return city; }
    std::string getObligations() { return obligations; }
    double getAmount() { return amount; }
    std::string getBankName() { return bankName; }

    void set(Contract newData)
    {
        client = newData.getClient();
        bankName = newData.getBankName();
        conclusionDate = newData.getConclusionDate();
        contractNum = newData.getContractNum();
        city = newData.getCity();
        obligations = newData.getObligations();
        amount = newData.getAmount();
    }

    bool checkData()
    {
        bool res = true;
        res &= client->checkData();
        res &= !bankName.empty();
        res &= contractNum != 0;
        res &= !city.empty();
        res &= !obligations.empty();
        res &= amount != 0;

        return res;
    }
    void show()
    {
        std::cout <<"Client first name : "<< client->getName() << std::endl;
        std::cout <<"Client second name : "<< client->getsSurname() << std::endl;
        std::cout <<"Passport id : "<< client->getPassportNum() << std::endl;
        std::cout <<"Bank name : "<< bankName << std::endl;
        std::cout <<"ContractNum : "<< contractNum << std::endl;
        std::cout <<"Obligations : "<< obligations << std::endl;
        std::cout <<"Amount : "<< amount << std::endl;
        std::cout << std::endl;
    }

};


int main()
{
    std::tm regDate;
    regDate.tm_mday = 20;
    regDate.tm_mon = 1;
    regDate.tm_year = 1989;
    UniquePointer<Bank> bank(new Bank("prior", "100220190", regDate));

    BankClient* client = new BankClient();
    client->setName("Egor");
    client->setSurname("Trubetskoy");
    client->setPassportNum("MP1234567");
    std::tm bd;
    bd.tm_mday = 15;
    bd.tm_mon = 4;
    bd.tm_year = 1990;
    client->setBirthDate(bd);
    std::shared_ptr<BankClient> firstClient(client);

    Contract fContract(firstClient, std::tm(), 1, "Minsk", "pay debt", (double)100, bank->getName());

    Transaction<Contract> fTransaction;
    fTransaction.beginTransaction(fContract);
    fTransaction.commit();

    Contract sContract(firstClient, std::tm(), 2, "Moscow", "", (double)100, bank->getName());
    sContract.show();
    fTransaction.beginTransaction(sContract);
    if (fTransaction->checkData())
    {
        fTransaction.commit();
        std::cout << "applied transaction with " << sContract.getBankName() << std::endl;
    }
    else
    {
        std::cout << "some data entered wrong" << std::endl;
        fTransaction.deleteTransactions();
    }

    Contract tContract(firstClient, std::tm(), 3, "Moscow", "pay debt", (double)100, bank->getName());
    tContract.show();
    fTransaction.beginTransaction(tContract);
    if (fTransaction->checkData())
    {
        fTransaction.commit();
        std::cout << "applied transaction with " << tContract.getBankName() << std::endl;
    }
    else
    {
        std::cout << "some data entered wrong in contract with " << tContract.getBankName() << std::endl;
        fTransaction.deleteTransactions();
    }

    return 0;
}
