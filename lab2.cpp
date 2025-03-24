// Task 2 (Usage of References)
#include <iostream>
#include <cstring>
using namespace std;

struct Animal
{
    int id;
    char *species;
    int age;
    char *nickname;
    Animal *next;

    Animal(int i, const char *s, const char *n)
    {
        id = i;
        species = strdup(s);
        nickname = strdup(n);
        age = -1;
        next = nullptr;
    }

    ~Animal()
    {
        delete[] species;
        delete[] nickname;
    }
};

Animal *Zoo = nullptr;

int &update(int id, const char *nickname, const char *species)
{
    Animal *current = Zoo;
    Animal *prev = nullptr;

    while (current)
    {
        if (current->id == id)
        {
            if (strcmp(current->nickname, nickname) != 0)
            {
                delete[] current->nickname;
                current->nickname = strdup(nickname);

                delete[] current->species;
                current->species = strdup(species);

                current->age = -1;
            }
            return current->age;
        }
        prev = current;
        current = current->next;
    }

    Animal *new_animal = new Animal(id, species, nickname);

    if (!Zoo || Zoo->id > id)
    {
        new_animal->next = Zoo;
        Zoo = new_animal;
    }
    else
    {
        current = Zoo;
        while (current && current->id < id)
        {
            prev = current;
            current = current->next;
        }
        prev->next = new_animal;
        new_animal->next = current;
    }

    return new_animal->age;
}

void print_Zoo()
{
    Animal *current = Zoo;
    while (current)
    {
        cout << "ID: " << current->id
             << ", Nickname: " << current->nickname
             << ", Species: " << current->species
             << ", Age: " << current->age << endl;
        current = current->next;
    }
}

int main()
{

    update(123, "King Kong", "big ape");
    update(234, "Lion King", "lion");
    update(123, "King Kong Mr.", "big ape");
    update(345, "Mighty Elephant", "elephant");

    print_Zoo();

    update(145, "King Kong Mr.", "big ape")++;
    cout << "After:" << endl;
    print_Zoo();

    return 0;
}
