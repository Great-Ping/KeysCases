#include<stdio.h>
#include "GoshaCar.h"

//Сокрытые поля
struct Baboon {
    Animal base;
};

//Методы которые можно переопределить в классах наследниках
void animalGrowlVirtual(Animal* _this);
void baboonGrowlVirtual(Animal* _this);

void initAnimal(Animal* _this) {
    _this->age = 0;
    static struct VirtualTable const animalVirtual = {
        &animalGrowlVirtual
    };
    _this->virtual = &animalVirtual;
}

void initBaboon(struct Baboon* _this) {
    initAnimal(&_this->base);
    static struct VirtualTable const baboonVirtual = {
        &baboonGrowlVirtual
    };
    _this->base.virtual = &baboonVirtual;
}

unsigned int animalGetAge(Animal* _this) {
    return _this->age;
}

void animalSetAge(Animal* _this, unsigned int age) {
    _this->age = age;
}

void animalGrowl(Animal* _this) {
    _this->virtual->growl(_this);
}

void animalGrowlVirtual(Animal* _this) {
    //Пустая заглушка
}

void baboonGrowlVirtual(Animal* _this) {
    printf("oiiaa\n");
}

int main(){
    struct Baboon baboon;
    initBaboon(&baboon);
    //Кастим к предку
    animalGrowl((Animal*)(&baboon));

    return 0;
}
