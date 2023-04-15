#include <iostream>
#include <stdio.h>
#include <string>
#include <locale>

using namespace std;

class seedbed // базовый класс "грядка"
{
    private:
        double weight; // вес
        bool ripeness; // спелость
        string variety; // сорт
        int parts; // количество частей
        bool on_seedbed; // flag на грядке?
    
    public:
        seedbed() // конструктор без параметров
        {
            weight = ripeness = parts = on_seedbed = 0;
            // variety - объект класса string, он инициализируется его конструктором
        }

        seedbed(double w, bool r, string v) // конструктор с параметрами
        {
            weight = w; // устанавливаем вес
            ripeness = r; // устанавливаем спелость (0/1)
            variety = v; // устанавливаем сорт
            on_seedbed = 1; // говорим, что оно есть на грядке
            parts = 0; // продукт на грядке, поэтому у нас в "холодильнике его нет"
        }

        ~seedbed(){} // деструктор

        virtual void class_info() /* метод вывода информации об объекте */
        {
            cout << "Вес: " << weight << endl << "Спелый: " << (ripeness? "да" : "нет" ) << endl << "Сорт: " << variety << endl;
            if(parts == 1)
                cout << "Продукт целый" << endl;
            else
                cout << "Продукт разрезан на " << parts << "часть/частей/части" << endl; 
                /*2,3,4
                5-20 */  
        }

        virtual void eat() // метод "съесть"
        {
            if(!parts && on_seedbed) // если есть только на грядке
            {
                cout << "Вы отравились" << endl;
                on_seedbed = 0;
                return;
            }

            if(parts > 0) // если есть не на грядке
            {
                parts--;
                if(!parts) // если частей 0
                {
                    cout << "Доели";
                    return;
                }
                else 
                    cout << "Съели кусочек";
                return;
            }
            
            if(!parts && !on_seedbed) // если нет ни на грядке ни в "холодильнике"
            {
                cout << "Кушать нечего";
                return;
            }
        }

        virtual void cut() // метод "разрезать"
        {
            if(!parts)
                cout << "Резать нечего";
            else
            {
                parts++;
                cout << "Кусочков стало на 1 больше";
            }
        }

        virtual void pick() // метод "собрать с грядки" 
        {
            on_seedbed = 0;
            parts = 1;
        }

        virtual string get_class_name() = 0; /* метод вывода имени класса */

        bool get_on_seedbed() // геттер флага "на грядке?"
        {
            return on_seedbed;
        }

        void set_parts(int k) // сеттер количества частей 
        {
            parts = k;
        }     
};

class watermelon: public seedbed // класс "арбуз"
{
    private:
        bool gender; // пол арбуза (0 - male, 1 - female)
    public:

        watermelon(): seedbed() // конструктор 
        {
            gender = 0;
        }

        watermelon(double w, char r, string v, char g): seedbed(w,r,v) // конструктор с параметрами
        {
            gender = g;
        }

        string get_class_name() override /* вывод имени класса */
        {
            return "Арбуз";
        }

        ~watermelon(){} // деструктор

        void knock() /* метод "постучать" */
        {
            cout << "Knock" << endl;
        } 

        void class_info() override /*матод вывода информации об объекте*/ 
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
        }

        void eat() override  /* съесть кусочек арбуза */
        {
            seedbed::eat();
        }
        
        void set_gender(char i) // сеттер пола арбуза
        {
            gender = i;
        }
};

class melon: public seedbed
{
    public:
        ~melon(){} // деструктор

        melon(): seedbed(){} // конструктор без параметров

        melon(double w, char r, string v):seedbed(w,r,v){} // конструктор с параметрами
        
        void class_info() override
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
        }

        void knock() // метод "постучать"
        {
            cout << "- Knock knock" << endl << "- Who is there?" << endl;
        }

        void get_class_name() override // метод вывода названия класса
        {
            cout << "Дыня" << endl;
        }

        void eat_melon() // метод "съесть дыню"
        {
            if(eat()) // если доели продукт
                this->~melon();
        }

};

class potato: public seedbed
{
    public:
        potato(): seedbed(){} // конструктор без параметров 

        potato(double w, bool r, string v): seedbed(w, r, v){} // констуктор с парматрами 

        ~potato(){} // деструктор

        void get_class_name() override // метод вывода названия класса
        {
            cout << "Картошка" << endl;
        }

        void inf() // метод вывода всех данных о продукте
        {
            get_class_name();
            info();
        }   

        void earth_up() // метод "окучить"
        {
            if(get_on_seedbed())
                cout << "Окучили" << endl;
            else
                cout << "Нечего окучивать" << endl;
        }

        void eat_potato() // метод "съесть картошку"
        {
            if(eat()) // если доели продукт
                this->~potato();
        }

};

class grapes: public seedbed
{   
    public:
        grapes():seedbed(){} // конструктор без параметров

        grapes(double w, bool r, string v): seedbed(w, r, v){} // конструктор с параметрами

        ~grapes(){} // деструктор

        void get_class_name() override 
        {
            cout << "Виноград" << endl;
        }

        void inf() // вывод информации об объекте
        {
            get_class_name();
            info();
        }

        void eat_grapes()
        {  
            if(eat())
                this->~grapes();
        }

        void dry() // метод "высушить"
        {
            cout << "Теперь это изюм" << endl;
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

