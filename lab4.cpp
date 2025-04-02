
#include <iostream>
#include <cstring>
using namespace std;

class Animal
{
private:
    int id;
    char *species;
    int age;
    char *nickname;
    Animal *next;

public:
    Animal(int id, const char *species, int age, const char *nickname)
        : id(id), age(age), next(nullptr)
    {
        this->species = new char[strlen(species) + 1];
        strcpy(this->species, species);
        this->nickname = new char[strlen(nickname) + 1];
        strcpy(this->nickname, nickname);
        // cout << "Animal: id " << id << ", Species: " << species
        //      << ", Age: " << age << ", Nickname: " << nickname << endl;
    }

    ~Animal()
    {
        cout << "Destroyed animal: id " << id << ", Species: " << species
             << ", Age: " << age << ", Nickname: " << nickname << endl;
        delete[] species;
        delete[] nickname;
    }

    int getId() const { return id; }
    const char *getSpecies() const { return species; }
    int getAge() const { return age; }
    const char *getNickname() const { return nickname; }
    Animal *getNext() const { return next; }

    void setId(int id) { this->id = id; }
    void setSpecies(const char *species)
    {
        delete[] this->species;
        this->species = new char[strlen(species) + 1];
        strcpy(this->species, species);
    }
    void setAge(int age) { this->age = age; }
    void setNickname(const char *nickname)
    {
        delete[] this->nickname;
        this->nickname = new char[strlen(nickname) + 1];
        strcpy(this->nickname, nickname);
    }
    void setNext(Animal *next) { this->next = next; }

    void print()
    {
        cout << "Animal: id " << id << ", Species: " << species
             << ", Age: " << age << ", Nickname: " << nickname << endl;
    }
};

class Zoo
{
private:
    Animal *head;

public:
    Zoo() : head(nullptr) {}

    Zoo(const Zoo &other) : head(nullptr)
    {
        Animal *current = other.head;
        while (current)
        {
            add_Animal(current->getId(), current->getSpecies(), current->getAge(), current->getNickname());
            current = current->getNext();
        }
    }

    Zoo &operator=(const Zoo &other)
    {
        if (this == &other)
            return *this;

        while (head)
        {
            Animal *temp = head;
            head = head->getNext();
            delete temp;
        }

        Animal *current = other.head;
        while (current)
        {
            add_Animal(current->getId(), current->getSpecies(), current->getAge(), current->getNickname());
            current = current->getNext();
        }
        return *this;
    }

    ~Zoo()
    {
        while (head)
        {
            Animal *temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    int add_Animal(int id, const char *species, int age, const char *nickname)
    {
        Animal *current = head;
        while (current && current->getId() < id)
        {
            current = current->getNext();
        }
        if (current && current->getId() == id)
        {
            if (strcmp(current->getNickname(), nickname) == 0)
            {
                current->setAge(age);
            }
            return 0;
        }
        Animal *newAnimal = new Animal(id, species, age, nickname);
        newAnimal->setNext(current);
        if (current == head)
        {
            head = newAnimal;
        }
        else
        {
            Animal *prev = head;
            while (prev && prev->getNext() != current)
            {
                prev = prev->getNext();
            }
            if (prev)
            {
                prev->setNext(newAnimal);
            }
        }
        return 1;
    }

    void remove_Animal(int id)
    {
        Animal *current = head;
        Animal *prev = nullptr;
        while (current && current->getId() != id)
        {
            prev = current;
            current = current->getNext();
        }
        if (current)
        {
            if (prev)
            {
                prev->setNext(current->getNext());
            }
            else
            {
                head = current->getNext();
            }
            delete current;
        }
    }

    void print()
    {
        Animal *current = head;
        while (current)
        {
            current->print();
            current = current->getNext();
        }
    }
};

// int main()
// {

//     Zoo zoo1;
//     zoo1.add_Animal(1, "Lion", 5, "Leo");
//     zoo1.add_Animal(2, "Rabbit", 4, "Rab");
//     zoo1.add_Animal(3, "Elephant", 10, "Dumbo");

//     cout << "Zoo1 before copy:" << endl;
//     zoo1.print();

//     Zoo zoo2 = zoo1;
//     cout << "\nZoo2 (copied from Zoo1):" << endl;
//     zoo2.print();

//     zoo1.add_Animal(4, "Giraffe", 6, "Gira");
//     cout << "\nZoo1 after modification:" << endl;
//     zoo1.print();
//     cout << "\nZoo2 after Zoo1 modification - unchanged:" << endl;
//     zoo2.print();

//     Zoo zoo3;
//     zoo3 = zoo1;
//     cout << "\nZoo3 ( from Zoo1):" << endl;
//     zoo3.print();

//     zoo1.add_Animal(5, "Panda", 3, "Bamboo");
//     cout << "\nZoo1 after another modification:" << endl;
//     zoo1.print();
//     cout << "\nZoo3 after Zoo1 modification -unchanged:" << endl;
//     zoo3.print();

//     return 0;
// }

int main()
{
    // Automatic (stack-allocated) object
    Zoo zoo1;
    zoo1.add_Animal(1, "Lion", 5, "Leo");
    zoo1.add_Animal(2, "Rabbit", 4, "Rab");
    zoo1.add_Animal(3, "Elephant", 10, "Dumbo");

    cout << "Zoo1 before copy:" << endl;
    zoo1.print();

    // Copy constructor - new object created using the copy constructor (automatic object)
    Zoo zoo2 = zoo1;
    cout << "\nZoo2 (copied from Zoo1):" << endl;
    zoo2.print();

    // Modify zoo1 after copying
    zoo1.add_Animal(4, "Giraffe", 6, "Gira");
    cout << "\nZoo1 after modification:" << endl;
    zoo1.print();
    cout << "\nZoo2 after Zoo1 modification - unchanged:" << endl;
    zoo2.print();

    // Automatic object (stack-allocated)
    Zoo zoo3;
    zoo3 = zoo1; // Assignment operator is called here (deep copy)
    cout << "\nZoo3 (assigned from Zoo1):" << endl;
    zoo3.print();

    // Modify zoo1 again
    zoo1.add_Animal(5, "Panda", 3, "Bamboo");
    cout << "\nZoo1 after another modification:" << endl;
    zoo1.print();
    cout << "\nZoo3 after Zoo1 modification - unchanged:" << endl;
    zoo3.print();

    // Dynamic object (heap-allocated)
    Zoo *zoo4 = new Zoo(); // Dynamic allocation of a Zoo object
    zoo4->add_Animal(6, "Tiger", 2, "Tiggy");
    cout << "\nZoo4 (dynamically allocated):" << endl;
    zoo4->print();

    // Modify the dynamic zoo4 object
    zoo4->add_Animal(7, "Koala", 4, "Koa");
    cout << "\nZoo4 after modification:" << endl;
    zoo4->print();

    // Don't forget to delete dynamic object to free memory
    delete zoo4;

    return 0;
}
