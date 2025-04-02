#include <iostream>
#include <cstring>

struct Animal
{
    int id;
    char *species;
    int age;
    char *nickname;
    Animal *next;
};
// global pointer Zoo that points to the first Animal in the linked list.
Animal *Zoo = nullptr;

void add_Animal(int id, const char *species, int age, const char *nickname)
{
    Animal *newAnimal = new Animal;
    newAnimal->id = id;
    newAnimal->age = age;
    newAnimal->species = new char[strlen(species) + 1];
    strcpy(newAnimal->species, species); // strcpy() → Copies the string into allocated memory.strcpy()
    newAnimal->nickname = new char[strlen(nickname) + 1];
    strcpy(newAnimal->nickname, nickname);
    newAnimal->next = nullptr;

    if (!Zoo || Zoo->id > id)
    {
        newAnimal->next = Zoo; // Point new animal to the current first node
        Zoo = newAnimal;       // Update Zoo to point to the new first node
        return;
    }

    Animal *current = Zoo;
    while (current->next && current->next->id < id)
    {
        current = current->next;
    }

    if (current->id == id && strcmp(current->nickname, nickname) == 0)
    {
        current->age = age;
        delete[] newAnimal->species;
        delete[] newAnimal->nickname;
        delete newAnimal;
        return;
    }

    newAnimal->next = current->next;
    current->next = newAnimal;
}

void remove_Animal(int id)
{

    Animal *current = Zoo;
    Animal *prev = nullptr;

    while (current && current->id != id)
    {

        prev = current;
        current = current->next;
    };

    if (!current)
        return;

    if (prev)
        prev->next = current->next;
    else
        Zoo = current->next;

    delete[] current->species;
    delete[] current->nickname;
    delete current;
}

void print_Zoo()
{
    Animal *current = Zoo;
    while (current)
    {
        std::cout << "id: " << current->id << ", species: " << current->species << ", age: " << current->age << ", nickname: " << current->nickname << std::endl;
        current = current->next;
    }
}

int main()
{

    std::cout << "Testing\n";
    print_Zoo();

    add_Animal(2, "Lion", 5, "Neo");
    add_Animal(1, "Elephant", 3, "Sam");

    std::cout << "Added animals: \n";
    print_Zoo();

    remove_Animal(1);
    std::cout << "After removing\n";
    print_Zoo();

    remove_Animal(2);
    std::cout << "After removing\n";
    print_Zoo();

    return 0;
}
