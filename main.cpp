#include <iostream>
#include <fstream>
#include <string>

class Address
{
    public:
        Address() {
            this->city = "0";
            this->street = "0";
            this->building = 0;
            this->appartment = 0;
        }
        void setAddress(std::string city, std::string street, int building, int appartment) {
            this->city = city;
            this->street = street;
            this->building = building;
            this->appartment = appartment;
        }
        std::string getCity() {
            return this->city;
        }
        std::string getStreet() {
            return this->street;
        }
        std::string print() {
            return this->city +  ", " + 
                this->street + ", " + 
                std::to_string(this->building) + ", " + 
                std::to_string(this->appartment) + "\n";
        }
    private:
        std::string city;
        std::string street;
        int building;
        int appartment;
};

void sort(Address* &addresses, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            std::string city, pcity, street, pstreet;
            Address *p = (addresses + j);
            Address *pp = (addresses + j + 1);

            city = p->getCity();
            street = p->getStreet();
            pcity = pp->getCity();
            pstreet = pp->getStreet();

            Address tmp;
            if (city.compare(pcity) == 0 && street.compare(pstreet) > 0) {
                tmp = *(p);
                *(p) = *(pp);
                *(pp) = tmp;
            }
            else if (city.compare(pcity) > 0) {
                tmp = *(p);
                *(p) = *(pp);
                *(pp) = tmp;
            }
        }
    }
}

int main() {
    std::ifstream input("in.txt");
    int count = 0;
    input >> count;

    if (count <= 0) {
        std::cerr << "Ошибка во входном файле";
        return 1;
    }

    Address *list = new Address[count];
    for (int i = 0; i < count; i++) {
        std::string city, street;
        int building, appartment;

        input >> city;
        input >> street;
        input >> building;
        input >> appartment;

        Address *p = (list + i);
        p->setAddress(city, street, building, appartment);
    }

    if (!input.eof()) {
        std::cerr << "Ошибка во входном файле";
        return 1;
    }
    input.close();

    sort(list, count);
    std::ofstream output("out.txt");
    for (int i = 0; i < count; i++) {
        Address *p = (list + i);
        output << p->print();
    }
    output.close();
    delete[] list;

    return 0;
}