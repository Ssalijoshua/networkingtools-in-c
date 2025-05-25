#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    float height;
};


int main() {
    // Create an instance of the Person struct
    struct Person person;

    // Initialize the fields
    strcpy(person.name, "Alice");
    person.age = 30;
    person.height = 5.5;

    // Print the values
    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);
    printf("Height: %.2f\n", person.height);

    return 0;
}