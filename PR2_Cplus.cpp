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

        virtual void class_info() /* ����� ������ ���������� �� ������� */
        {
            cout << "���: " << weight << endl << "������: " << (ripeness? "��" : "���" ) << endl << "����: " << variety << endl;
            if(parts == 1)
                cout << "������� �����" << endl;
            else
                cout << "������� �������� �� " << parts << "�����/������/�����" << endl; 
                /*2,3,4
                5-20 */  
        }

        virtual void eat() // ����� "������"
        {
            if(!parts && on_seedbed) // ���� ���� ������ �� ������
            {
                cout << "�� ����������" << endl;
                on_seedbed = 0;
                return;
            }

            if(parts > 0) // ���� ���� �� �� ������
            {
                parts--;
                if(!parts) // ���� ������ 0
                {
                    cout << "�����";
                    return;
                }
                else 
                    cout << "����� �������";
                return;
            }
            
            if(!parts && !on_seedbed) // ���� ��� �� �� ������ �� � "������������"
            {
                cout << "������ ������";
                return;
            }
        }

        virtual void cut() // ����� "���������"
        {
            if(!parts)
                cout << "������ ������";
            else
            {
                parts++;
                cout << "�������� ����� �� 1 ������";
            }
        }

        virtual void pick() // ����� "������� � ������" 
        {
            on_seedbed = 0;
            parts = 1;
        }

        virtual string get_class_name() = 0; /* ����� ������ ����� ������ */

        bool get_on_seedbed() // ������ ����� "�� ������?"
        {
            return on_seedbed;
        }

        void set_parts(int k) // ������ ���������� ������ 
        {
            parts = k;
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

        string get_class_name() override /* ����� ����� ������ */
        {
            return "�����";
        }

        ~watermelon(){} // ����������

        void knock() /* ����� "���������" */
        {
            cout << "Knock" << endl;
        } 

        void class_info() override /*����� ������ ���������� �� �������*/ 
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
        }

        void eat() override  /* ������ ������� ������ */
        {
            seedbed::eat();
        }
        
        void set_gender(char i) // ������ ���� ������
        {
            gender = i;
        }
};

class melon: public seedbed
{
    public:
        ~melon(){} // ����������

        melon(): seedbed(){} // ����������� ��� ����������

        melon(double w, char r, string v):seedbed(w,r,v){} // ����������� � �����������
        
        void class_info() override
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
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
    public:
        potato(): seedbed(){} // ����������� ��� ���������� 

        potato(double w, bool r, string v): seedbed(w, r, v){} // ���������� � ���������� 

        ~potato(){} // ����������

        void get_class_name() override // ����� ������ �������� ������
        {
            cout << "��������" << endl;
        }

        void inf() // ����� ������ ���� ������ � ��������
        {
            get_class_name();
            info();
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
            if(eat()) // ���� ����� �������
                this->~potato();
        }

};

class grapes: public seedbed
{   
    public:
        grapes():seedbed(){} // ����������� ��� ����������

        grapes(double w, bool r, string v): seedbed(w, r, v){} // ����������� � �����������

        ~grapes(){} // ����������

        void get_class_name() override 
        {
            cout << "��������" << endl;
        }

        void inf() // ����� ���������� �� �������
        {
            get_class_name();
            info();
        }

        void eat_grapes()
        {  
            if(eat())
                this->~grapes();
        }

        void dry() // ����� "��������"
        {
            cout << "������ ��� ����" << endl;
        }
};
 

int main(void)
{
    setlocale(LC_ALL, "Rus");

    potato p;
    grapes g;
    melon m;
    watermelon w;

    return 0;
}

