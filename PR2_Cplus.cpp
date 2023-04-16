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
    return 0;
}

void add_menu(seedbed ** array) // ������� ���������� ��������
{   
    bool flag = false;
    int i;
    for(i = 0; i < SIZE; i++) // ��������� ������ �� ��������� �����
    {
        if(array[i] == NULL)
            break;
        else
        {
            flag = true;
            break;
        }
    }

    if(flag) // ���� ���� �� ������ ���
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
    string yes;

    do
    {
        system("cls");
        cout << "���: ";
        cin >> weight;
    }while(weight < 0);

    cout << "������? (�/�)" << endl;
    do
    {
        cin >> yes;
        cin.get();
    }while(yes != "�" && yes != "�" && yes != "�" && yes != "�");

    if(yes == "�" || yes == "�")
        ripeness = true;
    else
        ripeness = false;

    system("cls");
    cout << "����: ";
    cin >> variety;
    cin.get();

    switch(type)
    {
        case 1:
            cout << "��� ������ (�/�)";
            do
            {
                cin >> yes;
                cin.get();
            }while(yes != "�" && yes != "�" && yes != "�" && yes != "�");
            if(yes == "�" || yes == "�")
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
    if(array[0] == NULL)
    {
        cout << "������ ����" << endl;
        return;
    }

    int menu, i;
    do
    {
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
        if(menu == SIZE)
            break;
        if(array[menu] == NULL)
            continue;
        if(array[menu]->get_class_name() == "�����")
            dynamic_cast< watermelon *>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "����")
            dynamic_cast<melon*>(array[menu])->knock();
        else if(array[menu]->get_class_name() == "��������")
            dynamic_cast<potato*>(array[menu])->earth_up();
        else if(array[menu]->get_class_name() == "��������")
            dynamic_cast<grapes*>(array[menu])->dry();
        cout << "ENTER - ��� �����������" << endl;
        while(cin.get() != '\n');
    }while(1);
    return;
}