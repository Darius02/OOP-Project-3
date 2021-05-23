// Tema 1 POO - Lista Plati

// Boroseanu Darius-Ilie  Grupa 144, Semigrupa 2

#include <iostream>
#include <fstream>
#include <cstring>
#include <typeinfo>

using namespace std;

struct Date
{
    int year = 2021, month = 4, day = 30; ///, hour 20, minute = 41, second = 47
    Date (int y, int m, int d);
    ~Date();
    Date & operator= (const Date & other);
    friend istream & operator>> (istream & in, Date & d);
    friend ostream & operator<< (ostream & out, const Date & d);
    void test();
};
Date::Date (int y = 2021, int m = 4, int d = 20): year (y), month (m), day (d)
{
    test();
}
Date::~Date() {}
Date & Date:: operator= (const Date & other)
{
    year = other.year;
    month = other.month;
    day = other.day;
    return *this;
}
void Date::test ()
{
    try {
        if (year <= 0 || month <= 0 || day <= 0) throw '1';
        if (month > 12) throw 1.0;
        if (month == 4 || month == 6 || month == 9 || month == 1) {if (day > 30) throw 1;}
        else if (month != 2) {if (day > 31) throw 1;}
            else if(day > 28 + (year%4 == 0 && year % 100 != 0)) throw 1;
    }
    catch (char c) {cout << "Negative values...\n";}
    catch (double d) {cout << "It's a new year...\n";}
    catch (int i) {cout << "It's a new month...\n";}
    catch (...) {cout << "Unknown Error\n";}
}
istream & operator>> (istream & in, Date & d)
{
    in >> d.year >> d.month >> d.day;
    d.test();
    return in;
}
ostream & operator<< (ostream & out, const Date & d)
{
    return (out << d.year << " " << d.month << " " << d.day);
}

template <class TS, class TD> class Plata;
template <class TS, class TD> istream & operator>> (istream & in, Plata <TS, TD> & p)
{
    return (in >> p.sum >> p.date);
}

template <class TS, class TD> class Plata
{
    TS sum;
    TD date;
public:
    Plata (TS s, TD d): sum (s), date (d) {};
    virtual ~Plata () {};
    Plata <TS, TD> & operator= (const Plata <TS, TD> & other);
    friend istream & operator>> <TS, TD> (istream & in, Plata <TS, TD> & p);
    virtual void print (ostream & out, Plata <TS, TD> & p) = 0;
    TS getS ();
    TD getD ();
};
template <class TS, class TD> Plata <TS, TD> & Plata<TS, TD>:: operator= (const Plata <TS, TD> & other)
{
    sum = other.sum;
    date = other.date;
    return *this;
}
template <class TS, class TD> TS Plata<TS, TD>:: getS ()
{
    return sum;
}
template <class TS, class TD> TD Plata<TS, TD>:: getD ()
{
    return date;
}

template <> class Plata <int, char*>
{
    int sum;
    char* date;
public:
    Plata (int s, char* d);
    ~Plata ();
    Plata <int, char*> & operator= (const Plata <int, char*> & other);
    friend istream & operator>> <int, char*> (istream & in, Plata <int, char*> & p);
    virtual void print (ostream & out, Plata <int, char*> & p) = 0;
};
Plata <int, char*>:: Plata (int s, char* d)
{
    sum = s;
    date = new char [17];
    strcpy(date, "asdfg");
}
Plata <int, char*>:: ~Plata ()
{
    delete date;
}
Plata <int, char*> & Plata <int, char*>:: operator= (const Plata <int, char*> & other)
{
    sum = other.sum;
    strcpy(date, other.date);
    return *this;
}

template <class TS, class TD> class Cash;
template <class TS, class TD> istream & operator>> (istream & in, Cash <TS, TD> & p)
{
    return (in >> (static_cast <Plata <TS, TD> &> (p)) >> p.location.first >> p.location.second);
}

template <class TS, class TD> class Cash: public Plata <TS, TD>
{
    pair <int, int> location;
public:
    Cash (TS s, TD d, pair <int, int> l = {0, 0}): Plata <TS, TD> (s, d), location (l){}
    ~Cash () {}
    Cash <TS, TD> & operator= (const Cash <TS, TD> & other);
    friend istream & operator>> <TS, TD> (istream & in, Cash <TS, TD> & p);
    virtual void print (ostream & out, Plata <TS, TD> & p);
};
template <class TS, class TD> Cash <TS, TD> & Cash <TS, TD>:: operator= (const Cash <TS, TD> & other)
{
    static_cast <Plata <TS, TD> &> (*this) = other;
    location = other.location;
    return *this;
}
template <class TS, class TD> void Cash <TS, TD>:: print (ostream & out, Plata <TS, TD> & p)
{
    Cash *a = dynamic_cast <Cash*> (&p);
    out << a->getS() << "$ paid on " << a->getD() << " at location: " << a->location.first << " " << a->location.second << "\n";
}

template <class TS, class TD> class Person;
template <class TS, class TD> istream & operator>> (istream & in, Person <TS, TD> & p)
{
    return (in >> (static_cast <Plata <TS, TD> &> (p)) >> p.surname >> p.name);
}

template <class TS, class TD> class Person: public Plata <TS, TD>
{
    string name, surname;
public:
    Person (TS s, TD d, string nam = "", string sur = ""): Plata <TS, TD> (s, d) {name = nam; surname = sur;}
    ~Person () {}
    Person <TS, TD> & operator= (const Person <TS, TD> & other) {static_cast <Plata <TS, TD> &> (*this) = other; name = other.name; surname = other.surname; return *this;}
    friend istream & operator>> <TS, TD> (istream & in, Person <TS, TD> & p);
    virtual void print (ostream & out, Plata <TS, TD> & p) = 0;
    string getName() {return name;}
    string getSurname() {return surname;}
};

template <class TS, class TD> class Cec;
template <class TS, class TD> istream & operator>> (istream & in, Cec <TS, TD> & p)
{
    return (in >> (static_cast <Person <TS, TD> &> (p)) >> p.cnp);
}

template <class TS, class TD> class Cec: public Person <TS, TD>
{
    string cnp;
public:
    Cec (TS s, TD d, string nam = "", string sur = "", string c = ""): Person <TS, TD> (s, d, nam, sur), cnp (c) {}
    ~Cec () {}
    Cec <TS, TD> & operator= (const Cec <TS, TD> & other);
    friend istream & operator>> <TS, TD> (istream & in, Cec <TS, TD> & p);
    virtual void print (ostream & out, Plata <TS, TD> & p);
};
template <class TS, class TD> Cec <TS, TD> & Cec <TS, TD>:: operator= (const Cec <TS, TD> & other)
{
    static_cast <Person <TS, TD> &> (*this) = other;
    cnp = other.cnp;
    return *this;
}
template <class TS, class TD>  void Cec <TS, TD>:: print (ostream & out, Plata <TS, TD> & p)
{
    Cec *c = dynamic_cast <Cec*> (&p);
    out << c->getS() << "$ paid on " << c->getD() << " by: " << c->getSurname() << " " << c->getName() << " with CNP: " << c->cnp << "\n";
}

template <class TS, class TD> class Card;
template <class TS, class TD> istream & operator>> (istream & in, Card <TS, TD> & p)
{
    return (in >> (static_cast <Person <TS, TD> &> (p)) >> p.id >> p.cvv);
}

template <class TS, class TD> class Card: public Person <TS, TD>
{
    string id;
    int cvv;
public:
    Card (TS s, TD d, string nam = "", string sur = "", string i = "", int c = 0): Person <TS, TD> (s, d, nam, sur) {id = i; cvv = c;}
    ~Card () {}
    Card <TS, TD> & operator= (const Card <TS, TD> & other);
    friend istream & operator>> <TS, TD> (istream & in, Card <TS, TD> & p);
    virtual void print (ostream & out, Plata <TS, TD> & p);
};
template <class TS, class TD> Card <TS, TD> & Card <TS, TD>:: operator= (const Card <TS, TD> & other) {static_cast <Person <TS, TD> &> (*this) = other; id = other.id; cvv = other.cvv; return *this;}
template <class TS, class TD> void Card <TS, TD>:: print (ostream & out, Plata <TS, TD> & p)
{
    Card *c = dynamic_cast <Card*> (&p);
    out << c->getS() << "$ paid on " << c->getD() << " by: " << c->getSurname() << " " << c->getName() << " with card ID: " << c->id << " and CVV: " << c->cvv << "\n";
}

class Gestiune
{
    Plata <int, Date> * info;
    Gestiune *next;
    static int objCount;
public:
    static void add(int n);
    static int get();
    Gestiune (Plata <int, Date> * i, Gestiune *n);
    ~Gestiune ();
    Gestiune& operator+= (Plata <int, Date> *p);
    void af();
};
void Gestiune:: add(int n = 1)
{
    objCount += n;
}
int Gestiune:: get()
{
    return objCount;
}
Gestiune:: Gestiune (Plata <int, Date> * i = NULL, Gestiune *n = NULL): info(i), next(n)
{
    add(1);
}
Gestiune:: ~Gestiune ()
{
    add(-1);
    delete info;
    delete next;
}
int Gestiune:: objCount = -1;
Gestiune& Gestiune:: operator+= (Plata <int, Date> *p)
{
    Gestiune *i = this;
    while (i->next != NULL) {i = i->next;}
    i->next = new Gestiune (p);
    return *this;
}
void Gestiune:: af()
{
    Gestiune* i = this->next;
    Date d;
    Cash <int, Date> obop1 (0, d);
    Cec <int, Date> obop2 (0, d);
    Card <int, Date> obop3 (0, d);
    while (i != NULL) {
        if (typeid(*i->info) == typeid(obop1)) {obop1.print(cout, *i->info);}
        else if (typeid(*i->info) == typeid(obop2)) {obop2.print(cout, *i->info);}
            else if (typeid(*i->info) == typeid(obop3)) {obop3.print(cout, *i->info);}
                else {cout << "Unknown\n";}
        i = i->next;
    }
}

int main()
{
    ifstream in ("date.in");
    Date d;
    int n, i, option;
    Gestiune *l = new Gestiune;
    Cash <int, Date> *obop1;
    Cec <int, Date> *obop2;
    Card <int, Date> *obop3;
    in >> n;

    cout << "\nnr of objects in list: " << Gestiune::get() << "\n";
    for (i = 0; i < n; ++i)
    {
        in >> option;
        switch (option)
        {
            case 1:
                obop1 = new Cash <int, Date>(0, d);
                in >> (*obop1);
                (*l) += static_cast <Plata <int, Date> *>  (obop1);
                break;
            case 2:
                obop2 = new Cec <int, Date>(0, d);
                in >> (*obop2);
                (*l) += static_cast <Plata <int, Date> *>  (obop2);
                break;
            case 3:
                obop3 = new Card <int, Date>(0, d);
                in >> (*obop3);
                (*l) += static_cast <Plata <int, Date> *>  (obop3);
                break;
            default:
                cout << "Unknown type of payment";
                delete l;
                return 0;
        }
    }
    cout << "\nnr of objects in list: " << Gestiune::get() << "\n\n";
    l->af();
    delete l;
    cout << "\nnr of objects in list: " << Gestiune::get() + 1 << "\n";
    return 0;
}
