#include <iostream>
#include <stdio.h>
#include <string>
#include <locale>

using namespace std;

class seedbed // ������� ����� "������"
{
    private:
        double weight; // ���
        bool ripeness; // ��������
        string variety; // ����
        int seeds_amount; // ���������� �������
        int parts;
    
    public:
        seedbed() // ����������� ��� ����������
        {
            weight = ripeness = seeds_amount = parts = 0;
            // variety - ������ ������ string, �� ���������������� ��� �������������
        }
        seedbed(double w, char r, string v, int a) // ����������� � �����������
        {
            weight = w;
            ripeness = r;
            variety = v;
            seeds_amount = a;
        }
        ~seedbed() // ����������
        {}
        void class_name()
        {
            cout << "seedbed" << endl;
        }
        virtual void info()
        {
            cout << "���: " << weight << endl << "������: " << (ripeness? "��" : "���" ) << endl << "����: " << variety << endl 
                << "���������� �����: " << seeds_amount << endl;
            parts? (cout << "�������� �� " << (parts + 1) << "������" << endl ) : (cout << ""); // ���� �������� �� ��������� ������
        }
        virtual void eat() = 0; // ����� "������"

        void cut() // ����� "���������"
        {
            parts++;
        }

        void pick() // ����� "������� � ������"
        {
            this->~seedbed(); // ���������� ������, �.�. ��� ������ ��� �� ������
        }
};

class watermelon: public seedbed // ����� "�����"
{
    private:
        char gender;
    public:
        watermelon(): seedbed() // ����������� 
        {
            gender = 0;
        }
        watermelon(double w, char r, string v, int a, char g):seedbed(w,r,v,a) // ����������� � �����������
        {
            gender = g;
        }
        ~watermelon() // ����������
        {}

        void knock()
        {
            cout << "���" << endl;
        } // randomize output (fresh / not fresh)
}



int main(void)
{
    setlocale(LC_ALL, "Rus");
}

