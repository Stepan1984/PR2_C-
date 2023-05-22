#include "classes.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <cstdlib>
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
    setlocale(LC_ALL, "Rus"); // устанавливаем русский язык

    seedbed ** array = new seedbed * [SIZE]; // создаём массив из 4 элементов базового класса
    for(int i = 0; i < SIZE; i++) 
        array[i] = NULL; // для безопасности всем указателям присваиваем NULL
    
    int menu;
    do
    {
        // вывод меню
        system("cls");
        cout << "1. Добавить новый продукт" << endl;
        cout << "2. Выполнить действие для всех продуктов" << endl;
        cout << "3. Показать все продукты" << endl;
        cout << "4. Взаимодействовать с определённым продуктом" << endl;
        cout << "5. Завершить работу программы" << endl;
        cin >> menu; // запрос ключа от пользователя
        cin.get();

        switch(menu)
        { // выполнение в зависимости от введённого ключа
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

    for(int i = 0; i < SIZE; i++) // очистка памяти от массива перед завершением работы программы
        delete array[i];
    delete[] array;

    return 0;
}

void add_menu(seedbed ** array) // функция добавления продукта
{   
    int i;
    for(i = 0; i < SIZE; i++) // проверяем грядку на свободные места
    {
        if(array[i] == NULL) // если нашли свободное место
            break;
    }

    if(i == SIZE) // если мест на грядке нет
    {
        cout << "Грядка заполнена" << endl << "ENTER - для продолжения" << endl;
        while(cin.get() != '\n');
        return;
    }

    int menu;
    do
    {
        // вывод пунктов меню
        system("cls");
        cout << "Добавить:" << endl;
        cout << "1. Арбуз" << endl;
        cout << "2. Дыня" << endl;
        cout << "3. Картошка" << endl;
        cout << "4. Виноград" << endl;
        cout << "5. Отмена" << endl;
        cin >> menu; // запрос ключа от пользователя
        cin.get();

        if(menu >= 1 && menu <= 4) // если пользователь выбрал добавление одного из продуктов
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
    bool gender; // пол арбуза
    string yes, dump; // всопогательные переменные

    do
    { // запрашиваем у пользователя вес продукта, пока он вводит некорректные значения
        system("cls");
        cout << "Вес: ";
        cin >> weight;
    }while(weight < 0);

    cout << "Спелый? (y/n)" << endl;
    do // запрашиваем у пользователя спелость продукта, пока он вводит не корректные ответы
    {
        cin >> yes;
        cin.get();
    }while(yes != "y" && yes != "Y" && yes != "N" && yes != "n");

    if(yes == "Y" || yes == "y") // устанавливаем спелость в зависимости от ответа пользователя
        ripeness = true;
    else
        ripeness = false;

    //system("cls");
    cout << "Сорт: ";
    cin >> variety; // запрашиваем у пользователя название сорта 
    cin.get();

    switch(type)
    {
        case 1: // если добавляем арбуз
            cout << "Пол арбуза (m/f)";
            do // запрашиваем пол арбуза
            {
                cin >> yes;
                cin.get();
            }while(yes != "m" && yes != "M" && yes != "f" && yes != "F");
            if(yes == "M" || yes == "m")
                gender = false;
            else
                gender = true;
            return new watermelon(weight, ripeness, variety, gender); // создаём объект арбуз с помощью конструктора с параметрами
        case 2: // если добавляем дыню
            return new melon(weight, ripeness, variety); // создаём дыню 
        case 3: // если добавляем картофель
            return new potato(weight, ripeness, variety); // создаём картофель
        case 4: // если добавляем виноград
            return new grapes(weight, ripeness, variety); // создаём виноград
    }

}

void do_for_all_menu(seedbed ** array) // меню выбора метода базового класса
{
    system("cls");
    if(array[0] == NULL) // если массив продуктов пуст
    {
        cout << "Массив пуст" << endl;
        return;
    }

    int menu, i; // вспомогательные переменные
    do
    {   // вывод пунктов меню
        system("cls");
        cout << "Выберите действия над объектами" << endl;
        cout << "1. Съесть" << endl;
        cout << "2. Порезать" << endl;
        cout << "3. Собрать с грядки" << endl;
        cout << "4. Отмена" << endl;
        cin >> menu; // запрашиваем ключ у пользователя
        cin.get();
    }while(menu < 1 || menu > 4);

    if(menu == 4) // если пользователь выбрал 4 пункт
        return; // выходим в меню
        
    system("cls");
    do_for_all(array, menu); // применяем выбранное пользователем действие ко всем продуктам
    return;
}

void do_for_all(seedbed ** array, int type ) // функция вызова методов базового класса для всех объектов
{
    for(int i = 0; i < SIZE; i++) // перебираем элементы массива
    {
        if(array[i] == NULL) // если ячейка массива пустая
            break; // выходим из цикла
        switch(type) // выполняем действие над продуктом в зависимости от выбора пользователем
        {
            case 1:
                cout << array[i]->get_class_name() << ":" << endl; // выводим имя класса объекта
                array[i]->eat(); // вызываем метод "съесть"
            case 2:
                cout << array[i]->get_class_name() << ":" << endl;
                array[i]->cut(); // вызов метода "разрезать"
            case 3:
                cout << array[i]->get_class_name() << ":" << endl;
                array[i]->pick();// вызов метода "собрать с грядки"
        }
    }
    cout << "ENTER - для продолжения" << endl;
    while(cin.get() != '\n');
    return;
}

void show(seedbed ** array) // функция вывода данных обо всех объектах 
{
    system("cls");
    if(array[0] == NULL) // если массив пустой
    {
        cout << "Пустая грядка" << endl << "ENTER - для продолжения";
        while(cin.get() != '\n');
        return;
    }
    
    for(int i = 0; i < SIZE; i++) // перебор элементов массива
    {
        if(array[i] == NULL)
            break;
        array[i]->class_info(); // вызов метода вывода информации об объекте 
    }
    cout << "ENTER - для возварата в меню" << endl;
    while(cin.get() != '\n');
}

void choose(seedbed ** array) // функция вызова уникальных методов объектов классов
{
    int menu, i;

    do
    {   
        system("cls");
        for(i = 0; i < SIZE; i++) // перебор элементов массива
        {
            if(array[i] == NULL)
                break;
            cout << i + 1 << ". " << array[i]->get_class_name() << endl; // вывод названия класса
        }
        cout << SIZE + 1 << ". " << "Отмена" << endl;
        cin >> menu; // запрос ключа от пользователя
        cin.get();
        menu--;
        system("cls");
        if(menu == SIZE)
            break;
        // вызов уникальных методов классов в зависимости от выбора пользователя
        if(array[menu]->get_class_name() == "Арбуз")
            dynamic_cast< watermelon *>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "Дыня")
            dynamic_cast<melon*>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "Картошка")
            dynamic_cast<potato*>(array[menu])->earth_up();
        else if(array[menu]->get_class_name() == "Виноград" || array[menu]->get_class_name() == "Изюм")
            dynamic_cast<grapes*>(array[menu])->dry();
        cout << "ENTER - для продолжения" << endl;
        while(cin.get() != '\n');
    }while(1);
    return;
}