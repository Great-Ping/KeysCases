//GoshaCar.h
#include<stdio.h>

struct VirtualTable;

typedef struct {
    struct VirtualTable const* virtual;
    unsigned int age;
} Animal;

struct VirtualTable {
    void (*growl)(struct Animal * _this);
};

//При желании можно и в сокрытие, см .с файл
struct Baboon;

void initAnimal(struct Animal* _this);
unsigned int animalGetAge(struct Animal* _this);
void animalSetAge(struct Animal* _this, unsigned int age);
void animalGrowl(struct Animal* _this);

void initBaboon(struct Baboon* _this);