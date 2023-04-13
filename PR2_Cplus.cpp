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
        int parts; // ���������� ������
        bool on_seedbed; // flag �� ������?
    
    public:
        seedbed() // ����������� ��� ����������
        {
            weight = ripeness = parts = on_seedbed = 0;
            // variety - ������ ������ string, �� ���������������� ��� �������������
        }

        seedbed(double w, bool r, string v) // ����������� � �����������
        {
            weight = w; // ������������� ���
            ripeness = r; // ������������� �������� (0/1)
            variety = v; // ������������� ����
            on_seedbed = 1; // �������, ��� ��� ���� �� ������
            parts = 0; // ������� �� ������, ������� � ��� � "������������ ��� ���"
        }

        ~seedbed(){} // ����������

        void info() /* ����� ������ ���������� �� ������� */
        {
            cout << "���: " << weight << endl << "������: " << (ripeness? "��" : "���" ) << endl << "����: " << variety << endl;
            if(parts == 1)
                cout << "������� �����" << endl;
            else
                cout << "������� �������� �� " << parts << "�����/������/�����" << endl; 
                /*2,3,4
                5-20 */  
        }

        bool eat() // ����� "������"
        {
            if(!parts && on_seedbed) // ���� ���� ������ �� ������
            {
                cout << "�� ����������" << endl;
                on_seedbed = 0;
                return 1; // 1 - ����� � ����������
            }

            if(parts > 0) // ���� ���� �� �� ������
            {
                parts--;
                if(!parts) // ���� ������ 0
                {
                    cout << "�����";
                    return 1;
                }
                else 
                    cout << "����� �������";
                return 0;
            }
            
            if(!parts && !on_seedbed) // ���� ��� �� �� ������ �� � "������������"
            {
                cout << "������ ������";
                return 1;
            }
        }

        void cut() // ����� "���������"
        {
            if(!parts)
                cout << "������ ������";
            else
            {
                parts++;
                cout << "�������� ����� �� 1 ������";
            }
        }

        void pick() // ����� "������� � ������" 
        {
            on_seedbed = 0;
            parts = 1;
        }

        virtual void get_class_name() = 0; /* ����� ������ ����� ������ */

        bool get_on_seedbed() // ������ ����� "�� ������?"
        {
            return on_seedbed;
        }
        
};

class watermelon: public seedbed // ����� "�����"
{
    private:
        bool gender; // ��� ������ (0 - male, 1 - female)
    public:

        watermelon(): seedbed() // ����������� 
        {
            gender = 0;
        }

        watermelon(double w, char r, string v, char g): seedbed(w,r,v) // ����������� � �����������
        {
            gender = g;
        }

        void get_class_name() override /* ����� ����� ������ */
        {
            cout << "�����" << endl;
        }

        ~watermelon(){} // ����������

        void knock() /* ����� "���������" */
        {
            cout << "���" << endl;
        } 

        void inf() /*����� ������ ���������� �� �������*/ 
        {
            get_class_name();
            info();
        }

        void eat_watermelon() /* ������ ������� ������ */
        {
            if(eat()) // ���� ����� �������
                this->~watermelon();
        }
        
        void set_gender() // ������ ���� ������
        {
            char ans;
            cout << "�������� ��� ��������: �/�";
            do
            {
                cin >> ans;
                cin.get();
            }while(ans != '�' && ans != '�' && ans != '�' && ans != '�');

            if(ans == '�' || ans == '�' )
                gender = 1;
            else
                gender = 0;
        }
};

class melon: public seedbed
{
    public:
        ~melon(){} // ����������

        melon(): seedbed(){} // ����������� ��� ����������

        melon(double w, char r, string v):seedbed(w,r,v){} // ����������� � �����������
        
        void inf()
        {
            get_class_name();
            info();
        }

        void knock() // ����� "���������"
        {
            cout << "- Knock knock" << endl << "- Who is there?" << endl;
        }

        void get_class_name() override // ����� ������ �������� ������
        {
            cout << "����" << endl;
        }

        void eat_melon() // ����� "������ ����"
        {
            if(eat()) // ���� ����� �������
                this->~melon();
        }

};

class potato: public seedbed
{
    private:
        bool cooked;
    public:
        potato(): seedbed() // ����������� ��� ����������
        {
            cooked = 0;
        } 

        potato(double w, bool r, string v): seedbed(w, r, v) // ���������� � ����������
        {
            cooked = 0;
        } 

        ~potato(){} // ����������

        void get_class_name() override // ����� ������ �������� ������
        {
            cout << "��������" << endl;
        }

        void inf() // ����� ������ ���� ������ � ��������
        {
            this->get_class_name();
            this->info();
            if(cooked)
                cout << "��������������" << endl;
            else
                cout << "�����" << endl;
        }   

        void earth_up() // ����� "�������"
        {
            if(get_on_seedbed())
                cout << "�������" << endl;
            else
                cout << "������ ���������" << endl;
        }

        void eat_potato() // ����� "������ ��������"
        {
            // ���������� ������� �������� (������� virtual)
            if(eat()) // ���� ����� �������
                this->~potato();
        }

};

int main(void)
{
    setlocale(LC_ALL, "Rus");
}

