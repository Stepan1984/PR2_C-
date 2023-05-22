#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


class seedbed // базовый класс "грядка"
{
    private:
        double weight; // вес
        bool ripeness; // спелость
        string variety; // сорт
        int parts; // количество частей
        bool full; // целый 
        bool on_seedbed; // flag на грядке?
        
    public:
        seedbed() // конструктор без параметров
        {
            weight = ripeness = parts = on_seedbed = full = 0;
            // variety - объект класса string, он инициализируется его конструктором
        }

        seedbed(double w, bool r, string v) // конструктор с параметрами
        {
            weight = w; // устанавливаем вес
            ripeness = r; // устанавливаем спелость (0/1)
            variety = v; // устанавливаем сорт
            on_seedbed = true; // говорим, что оно есть на грядке
            parts = 0; // продукт на грядке, поэтому у нас в "холодильнике его нет"
            full = true; // целый 
        }

        ~seedbed(){} // деструктор

        virtual void class_info() /* метод вывода информации об объекте */
        {
            cout << "Вес: " << weight << endl << "Спелый: " << (ripeness? "да" : "нет" ) << endl << "Сорт: " << variety << endl;
            if(on_seedbed == 1)
                cout << "Продукт на грядке" << endl;
            else if(!parts && !full)
                cout << "Всё съели" << endl;
            else if(parts == 1 && full)
                cout << "Продукт целый" << endl;
            else
                cout << "Продукт разрезан на " << parts << " частей" << endl;
            cout << endl;   
        }

        virtual void eat() // метод "съесть"
        {
            if(!parts && on_seedbed) // если есть только на грядке
            {
                cout << "Вы отравились" << endl;
                on_seedbed = full = 0;
                return;
            }

            if(parts > 0) // если есть не на грядке
            {
                parts--;
                if(!parts) // если частей 0
                {
                    cout << "Доели" << endl;
                    return;
                }
                else 
                    cout << "Съели кусочек" << endl;
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
            if(!parts && on_seedbed)
            {
                cout << "Резать нечего, соберите с грядки" << endl;;
                return;
            }
            if(!parts && !full)
            {
                cout << "Уже всё скушали" << endl;
            }
            else
            {
                full = false;
                parts++;
                cout << "Кусочков стало на 1 больше" << endl;
            }
        }

        virtual void pick() // метод "собрать с грядки" 
        {
            if(on_seedbed == 0)
            {
                cout << "На грядке ничего нет" << endl;
                return;
            }

            on_seedbed = 0;
            parts = 1;
        }

        virtual string get_class_name() = 0; /* метод вывода имени класса */

        bool get_on_seedbed() // геттер флага "на грядке?"
        {
            return on_seedbed;
        }

        bool get_full()
        {
            return full;
        }

        void add_parts(int k) // сеттер количества частей 
        {
            parts += k;
        }

        void set_full(bool b)
        {
            full = b;
        }     
};

class watermelon: public seedbed // класс "арбуз"
{
    private:
        bool gender; // пол арбуза (0 - male, 1 - female)
    public:

        ~watermelon(){} // деструктор

        watermelon(): seedbed() {gender = 0;} // конструктор без параметров
        
        watermelon(double w, char r, string v, bool g): seedbed(w,r,v) {gender = g;} // конструктор с параметрами
        
        string get_class_name() override /* вывод имени класса */
        {
            return "Арбуз";
        }

        void knock() /* метод "постучать" */
        {
            if(seedbed::get_full())
                cout << "Knock" << endl;
            else
                cout << "Не во что стучать" << endl;
        } 

        void class_info() override /*матод вывода информации об объекте*/ 
        {
            cout << get_class_name() << endl;
            if(gender)
                cout << "Арбуз-девочка" << endl;
            else
                cout << "Арбуз-мальчик" << endl;
            seedbed::class_info();
            

            
        }

        void eat() override  /* съесть кусочек арбуза */
        {
            seedbed::eat();
        }
        
        void pick() override // метод "собрать с грядки"
        {
            seedbed::pick();
        }

        void cut() override // метод "разрезать"
        {
            seedbed::cut();
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
            if(seedbed::get_full())
                cout << "- Knock knock" << endl << "- Who is there?" << endl;
            else
                cout << "Не во что стучать" << endl;
        }

        string get_class_name() override // метод вывода названия класса
        {
            return "Дыня";
        }

        void eat() override // метод "съесть"
        {
            seedbed::eat();
        }

        void pick() override // метод "собрать с грядки"
        {
            seedbed::pick();
        }

        void cut() override // метод разрезать
        {
            seedbed::cut();
        }
};

class potato: public seedbed
{   
    private:
        bool earthed_up; // поле "окучено"
    public:
        potato(): seedbed(){earthed_up = false;} // конструктор без параметров 

        potato(double w, bool r, string v): seedbed(w, r, v){earthed_up = false;} // констуктор с парматрами 

        ~potato(){} // деструктор

        string get_class_name() override // метод вывода названия класса
        {
            return "Картошка";
        }

        void class_info() override // метод вывода всех данных о продукте
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
        }   

        void earth_up() // метод "окучить"
        {
            if(get_on_seedbed()) 
            {
                if(!earthed_up)
                {
                    cout << "Окучили" << endl;
                    earthed_up = true;
                }
                else
                    cout << "Уже окучено" << endl;
            }
            else
                cout << "Нечего окучивать" << endl;
        }

        void eat() override // метод "съесть"
        {
            seedbed::eat();
        }

        void pick() override // метод "собрать с грядки"
        {
            seedbed::pick();
        }

        void cut() override // метод "разрезать"
        {
            seedbed::cut();
        }
};

class grapes: public seedbed
{   private:
        bool is_dried;
    public:
        grapes():seedbed() // конструктор без параметров
        {
            is_dried = false;
        }

        grapes(double w, bool r, string v): seedbed(w, r, v) // конструктор с параметрами
        {
            is_dried = false;
        }

        ~grapes(){} // деструктор

        string get_class_name() override // метод получения названия класса
        {
            if(!is_dried)
                return "Виноград";
            else
                return "Изюм";
        }

        void class_info() override // вывод информации об объекте
        {
            cout << get_class_name() << endl;
            seedbed::class_info();
        }

        void eat() override // метод съесть
        {  
            seedbed::eat();
        }

        void dry() // метод "высушить"
        {   
            if(is_dried) // если уже высушен
                cout << "Сушить изюм?" << endl;
            else
            {
                cout << "Теперь это изюм" << endl;
                is_dried = true;
            }
        }

        void cut() override // метод "разрезать"
        {
            cout << "Пожалуй не стоит" << endl;
        }

        void pick() override // метод "собрать"
        {
            seedbed::pick();
            seedbed::add_parts(14);
            cout << "Сорвали гроздь с 15 виноградинами" << endl;
            seedbed::set_full(false);
        }
};
 

