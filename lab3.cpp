#include <iostream>
#include <cstring>
using namespace std;

class Animal
{
public:
    int id;
    char *species;
    int age;
    char *nickname;
    Animal *next;

    Animal(int id, const char *species, int age, const char *nickname)
        : id(id), age(age), next(nullptr)
    {
        this->species = new char[strlen(species) + 1];
        strcpy(this->species, species);
        this->nickname = new char[strlen(nickname) + 1];
        strcpy(this->nickname, nickname);
        cout << "Animal: id " << id << ", Species: " << species
             << ", Age: " << age << ", Nickname: " << nickname << endl;
    }

    ~Animal()
    {
        cout << "Destroyed animal: id" << id << ", Species: " << species
             << ", Age: " << age << ", Nickname: " << nickname << endl;
        delete[] species;
        delete[] nickname;
    }
    void print()
    {
        cout << "Animal: id " << id << ", Species: " << species
             << ", Age: " << age << ", Nickname: " << nickname << endl;
    }
};

class Zoo
{
public:
    Animal *head;

    Zoo() : head(nullptr) {}
    ~Zoo()
    {
        while (head)
        {
            Animal *temp = head;
            head = head->next;
            delete temp;
        }
    }

    int add_Animal(int id, const char *species, int age, const char *nickname)
    {
        Animal **current = &head;
        while (*current && (*current)->id < id)
        {
            current = &((*current)->next);
        }
        if (*current && (*current)->id == id)
        {
            if (strcmp((*current)->nickname, nickname) == 0)
            {
                (*current)->age = age;
            }
            return 0;
        }
        Animal *newAnimal = new Animal(id, species, age, nickname);
        newAnimal->next = *current;
        *current = newAnimal;
        return 1;
    }

    void remove_Animal(int id)
    {
        Animal **current = &head;
        while (*current && (*current)->id != id)
        {
            current = &((*current)->next);
        }
        if (*current)
        {
            Animal *temp = *current;
            *current = (*current)->next;
            delete temp;
        }
    }

    void print()
    {
        Animal *current = head;
        while (current)
        {
            current->print();
            current = current->next;
        }
    }
};

int main()
{
    Zoo zoo1;
    Zoo *zoo2 = new Zoo();

    zoo1.add_Animal(1, "Lion", 5, "Leo");
    zoo1.add_Animal(2, "Rabbit", 4, "Rab");
    zoo1.print();
    zoo2->add_Animal(3, "Elephant", 10, "Dumbo");
    zoo2->add_Animal(1, "Lion", 6, "Leo");
    zoo2->print();
    zoo1.remove_Animal(1);
    zoo1.print();

    delete zoo2;
    return 0;
}

// # Add the copy constructor and assigmnetn operator '=' to the Zoo Class

// # Zoo& operator = (const Zoo & x);
// # Zoo(const Zoo & x)

// # Modification in the class Animal if needed
// # The main() in the testing use autoamtic and dynamic objects of Zoo
