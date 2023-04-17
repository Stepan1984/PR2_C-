#include "classes.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <cstdlib>  

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
    system("chcp 1251");
    /* SetConsoleCP(1251);
    SetConsoleOutputCP(1251);  */ 

    seedbed ** array = new seedbed * [SIZE]; // ������ ������ �� 4 ��������� �������� ������
    for(int i = 0; i < SIZE; i++) 
        array[i] = NULL;
    
    int menu;
    do
    {
        system("cls");
        cout << "1. �������� ����� �������" << endl;
        cout << "2. ��������� �������� ��� ���� ���������" << endl;
        cout << "3. �������� ��� ��������" << endl;
        cout << "4. ����������������� � ����������� ���������" << endl;
        cout << "5. ��������� ������ ���������" << endl;
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

    for(int i = 0; i < SIZE; i++)
        delete array[i];
    delete[] array;

    return 0;
}

void add_menu(seedbed ** array) // ������� ���������� ��������
{   
    int i;
    for(i = 0; i < SIZE; i++) // ��������� ������ �� ��������� �����
    {
        if(array[i] == NULL) // ���� ����� ��������� �����
            break;
    }

    if(i == SIZE) // ���� ���� �� ������ ���
    {
        cout << "������ ���������" << endl << "ENTER - ��� �����������" << endl;
        while(cin.get() != '\n');
        return;
    }

    int menu;
    do
    {
        system("cls");
        cout << "��������:" << endl;
        cout << "1. �����" << endl;
        cout << "2. ����" << endl;
        cout << "3. ��������" << endl;
        cout << "4. ��������" << endl;
        cout << "5. ������" << endl;
        cin >> menu;
        cin.get();

        if(menu >= 1 && menu <= 4)
        {
            array[i] = init_obj(menu); // ������ ������ � ��������� ��� � ������
            if(i < SIZE - 1 ) // ���� � ������� ��� ���� �����
                i++;
            break;
        }

    }while(menu != 5);
    return;
}

seedbed * init_obj(int type) // ������� ������������� �������
{
    double weight; // ���
    bool ripeness; // ��������
    string variety; // ����
    bool gender;
    string yes, dump;

    do
    {
        system("cls");
        cout << "���: ";
        cin >> weight;
    }while(weight < 0);

    cout << "������? (y/n)" << endl;
    do
    {
        cin >> yes;
        cin.get();
    }while(yes != "y" && yes != "Y" && yes != "N" && yes != "n");

    if(yes == "Y" || yes == "y")
        ripeness = true;
    else
        ripeness = false;

    //system("cls");
    cout << "����: ";
    cin >> variety;
    cin.get();

    switch(type)
    {
        case 1:
            cout << "��� ������ (m/f)";
            do
            {
                cin >> yes;
                cin.get();
            }while(yes != "m" && yes != "M" && yes != "f" && yes != "F");
            if(yes == "M" || yes == "m")
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

void do_for_all_menu(seedbed ** array) // ���� ������ ������ �������� ������
{
    system("cls");
    if(array[0] == NULL)
    {
        cout << "������ ����" << endl;
        return;
    }

    int menu, i;
    do
    {
        system("cls");
        cout << "�������� �������� ��� ���������" << endl;
        cout << "1. ������" << endl;
        cout << "2. ��������" << endl;
        cout << "3. ������� � ������" << endl;
        cout << "4. ������" << endl;
        cin >> menu;
        cin.get();
    }while(menu < 1 || menu > 4);

    if(menu == 4)
        return;
        
    system("cls");
    do_for_all(array, menu);
    return;
}

void do_for_all(seedbed ** array, int type ) // ������� ������ ������� �������� ������ ��� ���� ��������
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
    cout << "ENTER - ��� �����������" << endl;
    while(cin.get() != '\n');
    return;
}

void show(seedbed ** array) // ������� ������ ������ ��� ���� �������� 
{
    system("cls");
    if(array[0] == NULL)
    {
        cout << "������ ������" << endl << "ENTER - ��� �����������";
        while(cin.get() != '\n');
        return;
    }
    
    for(int i = 0; i < SIZE; i++)
    {
        if(array[i] == NULL)
            break;
        array[i]->class_info();
    }
    cout << "ENTER - ��� ��������� � ����" << endl;
    while(cin.get() != '\n');
}

void choose(seedbed ** array) // ������� ������ ���������� ������� �������� �������
{
    int menu, i;

    do
    {   
        system("cls");
        for(i = 0; i < SIZE; i++)
        {
            if(array[i] == NULL)
                break;
            cout << i + 1 << ". " << array[i]->get_class_name() << endl;
        }
        cout << SIZE + 1 << ". " << "������" << endl;
        cin >> menu;
        cin.get();
        menu--;
        system("cls");
        if(menu == SIZE)
            break;
        if(array[menu]->get_class_name() == "�����")
            dynamic_cast< watermelon *>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "����")
            dynamic_cast<melon*>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "��������")
            dynamic_cast<potato*>(array[menu])->earth_up();
        else if(array[menu]->get_class_name() == "��������" || array[menu]->get_class_name() == "����")
            dynamic_cast<grapes*>(array[menu])->dry();
        cout << "ENTER - ��� �����������" << endl;
        while(cin.get() != '\n');
    }while(1);
    return;
}