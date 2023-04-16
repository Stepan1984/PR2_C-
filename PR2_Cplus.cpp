#include "classes.h"
#include <iostream>
#include <stdio.h>
#include <locale.h>
#define SIZE 4

using namespace std;

void add_menu(seedbed **);
seedbed * init_obj(int);
void do_for_all_menu(seedbed **);
void do_for_all(seedbed ** , int );
void show(seedbed ** );
void choose(seedbed ** );

int main(void)
{
    setlocale(LC_ALL, "Rus");

    seedbed ** array = new seedbed * [SIZE]; // создаём массив из 4 элементов базового класса
    for(int i = 0; i < SIZE; i++) 
        array[i] = NULL;
    
    int menu;
    do
    {
        system("cls");
        cout << "1. Добавить новый продукт" << endl;
        cout << "2. Выполнить действие для всех продуктов" << endl;
        cout << "3. Показать все продукты" << endl;
        cout << "4. Взаимодействовать с определённым продуктом" << endl;
        cout << "5. Завершить работу программы" << endl;
        cin >> menu;
        cin.get();

        switch(menu)
        {
            case 1:
                add_menu(array);
                break;
            case 2:
                do_for_all_menu(array);
                break;
            case 3:
                show(array);
                break;
            case 4:
                choose(array);
                break;
        }
    }while(menu != 5);
    return 0;
}

void add_menu(seedbed ** array) // функция добавления продукта
{   
    bool flag = false;
    int i;
    for(i = 0; i < SIZE; i++) // проверяем грядку на свободные места
    {
        if(array[i] == NULL)
            break;
        else
        {
            flag = true;
            break;
        }
    }

    if(flag) // если мест на грядке нет
    {
        cout << "Грядка заполнена" << endl << "ENTER - для продолжения" << endl;
        while(cin.get() != '\n');
        return;
    }

    int menu;
    do
    {
        system("cls");
        cout << "Добавить:" << endl;
        cout << "1. Арбуз" << endl;
        cout << "2. Дыня" << endl;
        cout << "3. Картошка" << endl;
        cout << "4. Виноград" << endl;
        cout << "5. Отмена" << endl;
        cin >> menu;
        cin.get();

        if(menu >= 1 && menu <= 4)
        {
            array[i] = init_obj(menu); // создаём объект и добавляем его в массив
            if(i < SIZE - 1 ) // если в массиве ещё есть место
                i++;
            break;
        }

    }while(menu != 5);
    return;
}

seedbed * init_obj(int type) // функция инициализации объекта
{
    double weight; // вес
    bool ripeness; // спелость
    string variety; // сорт
    bool gender;
    string yes;

    do
    {
        system("cls");
        cout << "Вес: ";
        cin >> weight;
    }while(weight < 0);

    cout << "Спелый? (д/н)" << endl;
    do
    {
        cin >> yes;
        cin.get();
    }while(yes != "д" && yes != "Д" && yes != "Н" && yes != "н");

    if(yes == "Д" || yes == "д")
        ripeness = true;
    else
        ripeness = false;

    system("cls");
    cout << "Сорт: ";
    cin >> variety;
    cin.get();

    switch(type)
    {
        case 1:
            cout << "Пол арбуза (м/ж)";
            do
            {
                cin >> yes;
                cin.get();
            }while(yes != "м" && yes != "М" && yes != "ж" && yes != "Ж");
            if(yes == "М" || yes == "м")
                gender = false;
            else
                gender = true;
            return new watermelon(weight, ripeness, variety, gender);
        case 2:
            return new melon(weight, ripeness, variety);
        case 3:
            return new potato(weight, ripeness, variety);
        case 4:
            return new grapes(weight, ripeness, variety);
    }

}

void do_for_all_menu(seedbed ** array) // меню выбора метода базового класса
{
    if(array[0] == NULL)
    {
        cout << "Массив пуст" << endl;
        return;
    }

    int menu, i;
    do
    {
        cout << "Выберите действия над объектами" << endl;
        cout << "1. Съесть" << endl;
        cout << "2. Порезать" << endl;
        cout << "3. Собрать с грядки" << endl;
        cout << "4. Отмена" << endl;
        cin >> menu;
        cin.get();
    }while(menu < 1 || menu > 4);

    if(menu == 4)
        return;
    
    do_for_all(array, menu);
    return;
}

void do_for_all(seedbed ** array, int type ) // функция вызова методов базового класса для всех объектов
{
    for(int i = 0; i < SIZE; i++)
    {
        if(array[i] == NULL)
            break;
        switch(type)
        {
            case 1:
                cout << array[i]->get_class_name() << ":" << endl;
                array[i]->eat();
            case 2:
                cout << array[i]->get_class_name() << ":" << endl;
                array[i]->cut();
            case 3:
                cout << array[i]->get_class_name() << ":" << endl;
                array[i]->pick();  
        }
    }
    cout << "ENTER - для продолжения" << endl;
    while(cin.get() != '\n');
    return;
}

void show(seedbed ** array) // функция вывода данных обо всех объектах 
{
    if(array[0] == NULL)
    {
        cout << "Пустая грядка" << endl << "ENTER - для продолжения";
        while(cin.get() != '\n');
        return;
    }
    
    for(int i = 0; i < SIZE; i++)
    {
        if(array[i] == NULL)
            break;
        array[i]->class_info();
    }
    cout << "ENTER - для возварата в меню" << endl;
    while(cin.get() != '\n');
}

void choose(seedbed ** array) // функция вызова уникальных методов объектов классов
{
    int menu, i;

    do
    {
        for(i = 0; i < SIZE; i++)
        {
            if(array[i] == NULL)
                break;
            cout << i + 1 << ". " << array[i]->get_class_name() << endl;
        }
        cout << SIZE + 1 << ". " << "Отмена" << endl;
        cin >> menu;
        cin.get();
        menu--;
        if(menu == SIZE)
            break;
        if(array[menu] == NULL)
            continue;
        if(array[menu]->get_class_name() == "Арбуз")
            dynamic_cast< watermelon *>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "Дыня")
            dynamic_cast<melon*>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "Картошка")
            dynamic_cast<potato*>(array[menu])->earth_up();
        else if(array[menu]->get_class_name() == "Виноград")
            dynamic_cast<grapes*>(array[menu])->dry();
        cout << "ENTER - для продолжения" << endl;
        while(cin.get() != '\n');
    }while(1);
    return;
}