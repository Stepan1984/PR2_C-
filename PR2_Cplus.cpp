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

        void info() /* метод вывода информации об объекте */
        {
            cout << "Вес: " << weight << endl << "Спелый: " << (ripeness? "да" : "нет" ) << endl << "Сорт: " << variety << endl;
            if(parts == 1)
                cout << "Продукт целый" << endl;
            else
                cout << "Продукт разрезан на " << parts << "часть/частей/части" << endl; 
                /*2,3,4
                5-20 */  
        }

        bool eat() // метод "съесть"
        {
            if(!parts && on_seedbed) // если есть только на грядке
            {
                cout << "Вы отравились" << endl;
                on_seedbed = 0;
                return 1; // 1 - съели и отравились
            }

            if(parts > 0) // если есть не на грядке
            {
                parts--;
                if(!parts) // если частей 0
                {
                    cout << "Доели";
                    return 1;
                }
                else 
                    cout << "Съели кусочек";
                return 0;
            }
            
            if(!parts && !on_seedbed) // если нет ни на грядке ни в "холодильнике"
            {
                cout << "Кушать нечего";
                return 1;
            }
        }

        void cut() // метод "разрезать"
        {
            if(!parts)
                cout << "Резать нечего";
            else
            {
                parts++;
                cout << "Кусочков стало на 1 больше";
            }
        }

        void pick() // метод "собрать с грядки" 
        {
            on_seedbed = 0;
            parts = 1;
        }

        virtual void get_class_name() = 0; /* метод вывода имени класса */

        bool get_on_seedbed() // геттер флага "на грядке?"
        {
            return on_seedbed;
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

        void get_class_name() override /* вывод имени класса */
        {
            cout << "Арбуз" << endl;
        }

        ~watermelon(){} // деструктор

        void knock() /* метод "постучать" */
        {
            cout << "Бум" << endl;
        } 

        void inf() /*матод вывода информации об объекте*/ 
        {
            get_class_name();
            info();
        }

        void eat_watermelon() /* съесть кусочек арбуза */
        {
            if(eat()) // если доели продукт
                this->~watermelon();
        }
        
        void set_gender() // сеттер пола арбуза
        {
            char ans;
            cout << "Выберите пол растения: м/ж";
            do
            {
                cin >> ans;
                cin.get();
            }while(ans != 'Ж' && ans != 'ж' && ans != 'М' && ans != 'м');

            if(ans == 'ж' || ans == 'Ж' )
                gender = 1;
            else
                gender = 0;
        }
};

class melon: public seedbed
{
    public:
        ~melon(){} // деструктор

        melon(): seedbed(){} // конструктор без параметров

        melon(double w, char r, string v):seedbed(w,r,v){} // конструктор с параметрами
        
        void inf()
        {
            get_class_name();
            info();
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
    private:
        bool cooked;
    public:
        potato(): seedbed() // конструктор без параметров
        {
            cooked = 0;
        } 

        potato(double w, bool r, string v): seedbed(w, r, v) // констуктор с парматрами
        {
            cooked = 0;
        } 

        ~potato(){} // деструктор

        void get_class_name() override // метод вывода названия класса
        {
            cout << "Картошка" << endl;
        }

        void inf() // метод вывода всех данных о продукте
        {
            this->get_class_name();
            this->info();
            if(cooked)
                cout << "Приготовленная" << endl;
            else
                cout << "Сырая" << endl;
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
            // переписать функцию поедания (сделать virtual)
            if(eat()) // если доели продукт
                this->~potato();
        }

};

int main(void)
{
    setlocale(LC_ALL, "Rus");
}

