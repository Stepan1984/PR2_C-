#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


class seedbed // ������� ����� "������"
{
    private:
        double weight; // ���
        bool ripeness; // ��������
        string variety; // ����
        int parts; // ���������� ������
        bool full; // ����� 
        bool on_seedbed; // flag �� ������?
        
    public:
        seedbed() // ����������� ��� ����������
        {
            weight = ripeness = parts = on_seedbed = full = 0;
            // variety - ������ ������ string, �� ���������������� ��� �������������
        }

        seedbed(double w, bool r, string v) // ����������� � �����������
        {
            weight = w; // ������������� ���
            ripeness = r; // ������������� �������� (0/1)
            variety = v; // ������������� ����
            on_seedbed = true; // �������, ��� ��� ���� �� ������
            parts = 0; // ������� �� ������, ������� � ��� � "������������ ��� ���"
            full = true; // ����� 
        }

        ~seedbed(){} // ����������

        virtual void class_info() /* ����� ������ ���������� �� ������� */
        {
            cout << "���: " << weight << endl << "������: " << (ripeness? "��" : "���" ) << endl << "����: " << variety << endl;
            if(on_seedbed == 1)
                cout << "������� �� ������" << endl;
            else if(!parts && !full)
                cout << "�� �����" << endl;
            else if(parts == 1 && full)
                cout << "������� �����" << endl;
            else
                cout << "������� �������� �� " << parts << " ������" << endl;
            cout << endl;   
        }

        virtual void eat() // ����� "������"
        {
            if(!parts && on_seedbed) // ���� ���� ������ �� ������
            {
                cout << "�� ����������" << endl;
                on_seedbed = full = 0;
                return;
            }

            if(parts > 0) // ���� ���� �� �� ������
            {
                parts--;
                if(!parts) // ���� ������ 0
                {
                    cout << "�����" << endl;
                    return;
                }
                else 
                    cout << "����� �������" << endl;
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
            if(!parts && on_seedbed)
            {
                cout << "������ ������, �������� � ������" << endl;;
                return;
            }
            if(!parts && !full)
            {
                cout << "��� �� �������" << endl;
            }
            else
            {
                full = false;
                parts++;
                cout << "�������� ����� �� 1 ������" << endl;
            }
        }

        virtual void pick() // ����� "������� � ������" 
        {
            if(on_seedbed == 0)
            {
                cout << "�� ������ ������ ���" << endl;
                return;
            }

            on_seedbed = 0;
            parts = 1;
        }

        virtual string get_class_name() = 0; /* ����� ������ ����� ������ */

        bool get_on_seedbed() // ������ ����� "�� ������?"
        {
            return on_seedbed;
        }

        bool get_full()
        {
            return full;
        }

        void add_parts(int k) // ������ ���������� ������ 
        {
            parts += k;
        }

        void set_full(bool b)
        {
            full = b;
        }     
};

class watermelon: public seedbed // ����� "�����"
{
    private:
        bool gender; // ��� ������ (0 - male, 1 - female)
    public:

        ~watermelon(){} // ����������

        watermelon(): seedbed() {gender = 0;} // ����������� ��� ����������
        
        watermelon(double w, char r, string v, bool g): seedbed(w,r,v) {gender = g;} // ����������� � �����������
        
        string get_class_name() override /* ����� ����� ������ */
        {
            return "�����";
        }

        void knock() /* ����� "���������" */
        {
            if(seedbed::get_full())
                cout << "Knock" << endl;
            else
                cout << "�� �� ��� �������" << endl;
        } 

        void class_info() override /*����� ������ ���������� �� �������*/ 
        {
            cout << get_class_name() << endl;
            if(gender)
                cout << "�����-�������" << endl;
            else
                cout << "�����-�������" << endl;
            seedbed::class_info();
            

            
        }

        void eat() override  /* ������ ������� ������ */
        {
            seedbed::eat();
        }
        
        void pick() override // ����� "������� � ������"
        {
            seedbed::pick();
        }

        void cut() override // ����� "���������"
        {
            seedbed::cut();
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
            if(seedbed::get_full())
                cout << "- Knock knock" << endl << "- Who is there?" << endl;
            else
                cout << "�� �� ��� �������" << endl;
        }

        string get_class_name() override // ����� ������ �������� ������
        {
            return "����";
        }

        void eat() override // ����� "������"
        {
            seedbed::eat();
        }

        void pick() override // ����� "������� � ������"
        {
            seedbed::pick();
        }

        void cut() override // ����� ���������
        {
            seedbed::cut();
        }
};

class potato: public seedbed
{   
    private:
        bool earthed_up; // ���� "�������"
    public:
        potato(): seedbed(){earthed_up = false;} // ����������� ��� ���������� 

        potato(double w, bool r, string v): seedbed(w, r, v){earthed_up = false;} // ���������� � ���������� 

        ~potato(){} // ����������

        string get_class_name() override // ����� ������ �������� ������
        {
            return "��������";
        }

        void class_info() override // ����� ������ ���� ������ � ��������
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
        }   

        void earth_up() // ����� "�������"
        {
            if(get_on_seedbed()) 
            {
                if(!earthed_up)
                {
                    cout << "�������" << endl;
                    earthed_up = true;
                }
                else
                    cout << "��� �������" << endl;
            }
            else
                cout << "������ ���������" << endl;
        }

        void eat() override // ����� "������"
        {
            seedbed::eat();
        }

        void pick() override // ����� "������� � ������"
        {
            seedbed::pick();
        }

        void cut() override // ����� "���������"
        {
            seedbed::cut();
        }
};

class grapes: public seedbed
{   private:
        bool is_dried;
    public:
        grapes():seedbed() // ����������� ��� ����������
        {
            is_dried = false;
        }

        grapes(double w, bool r, string v): seedbed(w, r, v) // ����������� � �����������
        {
            is_dried = false;
        }

        ~grapes(){} // ����������

        string get_class_name() override // ����� ��������� �������� ������
        {
            if(!is_dried)
                return "��������";
            else
                return "����";
        }

        void class_info() override // ����� ���������� �� �������
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
        }

        void eat() override // ����� ������
        {  
            seedbed::eat();
        }

        void dry() // ����� "��������"
        {   
            if(is_dried) // ���� ��� �������
                cout << "������ ����?" << endl;
            else
            {
                cout << "������ ��� ����" << endl;
                is_dried = true;
            }
        }

        void cut() override // ����� "���������"
        {
            cout << "������� �� �����" << endl;
        }

        void pick() override // ����� "�������"
        {
            seedbed::pick();
            seedbed::add_parts(14);
            cout << "������� ������ � 15 �������������" << endl;
            seedbed::set_full(false);
        }
};
 

