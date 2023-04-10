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
        int seeds_amount; // количество семечек
        int parts;
    
    public:
        seedbed() // конструктор без параметров
        {
            weight = ripeness = seeds_amount = parts = 0;
            // variety - объект класса string, он инициализируется его конструктором
        }
        seedbed(double w, char r, string v, int a) // конструктор с параметрами
        {
            weight = w;
            ripeness = r;
            variety = v;
            seeds_amount = a;
        }
        ~seedbed() // деструктор
        {}
        void class_name()
        {
            cout << "seedbed" << endl;
        }
        virtual void info()
        {
            cout << "Вес: " << weight << endl << "Спелый: " << (ripeness? "да" : "нет" ) << endl << "Сорт: " << variety << endl 
                << "Количество семян: " << seeds_amount << endl;
            parts? (cout << "Разрезан на " << (parts + 1) << "частей" << endl ) : (cout << ""); // если разрезан на несколько частей
        }
        virtual void eat() = 0; // метод "съесть"

        void cut() // метод "разрезать"
        {
            parts++;
        }

        void pick() // метод "собрать с грядки"
        {
            this->~seedbed(); // уничтожаем объект, т.к. его больше нет на грядке
        }
};

class watermelon: public seedbed // класс "арбуз"
{
    private:
        char gender;
    public:
        watermelon(): seedbed() // конструктор 
        {
            gender = 0;
        }
        watermelon(double w, char r, string v, int a, char g):seedbed(w,r,v,a) // конструктор с параметрами
        {
            gender = g;
        }
        ~watermelon() // деструктор
        {}

        void knock()
        {
            cout << "Бум" << endl;
        } // randomize output (fresh / not fresh)
}



int main(void)
{
    setlocale(LC_ALL, "Rus");
}

