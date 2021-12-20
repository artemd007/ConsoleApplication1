// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
using namespace std;

int coin_knot[2]; // 0 = наименьшее; 1 = наибольшее; -- кол узлов.
int chance_numbers[2]; // 0 = наименьшее; 1 = наибольшее; -- число узла.
int subscription[2]; // 0 = шанс под.; 1 = шанс отп.
int sknot[2]; // 0 = шанс сл. числа; 1 = шанс нов. узла;

int randd = 0;

struct Node { // узел
    int val;
    bool use;
    Node* next;
    Node* sub;

    Node(int _val, bool _use) : val(_val), use(_use), next(nullptr), sub(nullptr) {}
};

struct list { // список узлов
    Node* first;
    Node* end;
    Node* now;

    list() : first(nullptr), end(nullptr), now(nullptr) {}

    Node* operator[] (const int index) { //нахождение узла
        if (first == nullptr) return nullptr;
        Node* p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p) return nullptr;
        }
        return now = p;
    }

    void create(int _val, bool _use) // создание узла
    {
        Node* p = new Node(_val, _use);
        if (first == nullptr) {
            first = p;
            end = p;
            return;
        }
        end->next = p;
        p->sub = end;
        end = p;
    }

    void addcreate(int _val, bool _use) // добавление узла
    {
        Node* p = new Node(_val, _use);
        p->next = now->next;
        now->next = p;
        p->sub = now;
    }

    void addsubscription() // подписка
    {
        if (now == end || 0 == rand() % 2)
        {
            now->sub = first;
            return;
        }
        if (0 == rand() % 2 || now != end)
        {
            now->sub = now->next;
            return;
        }
        if (now == first)
        {
            now->sub = end;
            return;
        }
        Node* p = first;
        while (p->next != now)
            p = p->next;
        now->sub = p;
    }

    void outsubscription() // отписка
    {
        now->sub = nullptr;
    }

    void acceptsubscription() // проверка подписки
    {
        Node* p = first;
        while (p->next != end)
        {
            if (p->sub != nullptr)
            {
                p->use = true;
                p->sub->use = true;

                cout << p->val << "->" << p->sub->val << ": S =" << (p->val) + (p->sub->val) << endl;
            }
            p = p->next;
        }
    }

    void randomval() // изменение содержимого
    {
        now->val = chance_numbers[0] + rand() % (chance_numbers[1] - chance_numbers[0]);
    }

    void remove() { // !не работает удаление
        if (first == nullptr || now == nullptr) return;
        Node* p = now;
        cout << now << endl;
        if (p->use == true)
        {
            p->use == false;
            return;
        }
        if (p == first)
        {
            first = p->next;
            delete p;
            randd--;
            return;
        }
        if (p == end)
        {
            Node* c = first;
            if (first == end)
                return;
            while (c->next != p)
                c = c->next;
            c->next = nullptr;
            delete p;
            randd--;
            return;
        }

        Node* b = first;

        while (b->next != p )
            b = b->next;
            b->next = p->next;
        delete p;
        randd--;
    }

    void print() { // вывод всех узлов
        if (first == nullptr) return;
        Node* p = first;
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    void quantity() {  // счет узлов
        randd = 0;
        if (first == nullptr) return;
        Node* p = first;
        while (p) {
            randd++;
            p = p->next;
        }
        randd++;
        return;
    }
};

list l;

void rrannd()
{
    l.quantity();
    l.print();
    system("pause");

    for (int x = 0; x < randd; x++)
        if (sknot[0] > rand() % 100)
        {
            l[x];
            l.randomval();
        }
    for (int x = 0; x < randd; x++)
        if (subscription[1] > rand() % 100)
        {
            l[x];
            l.outsubscription();
        }
    for (int x = 0; x < randd; x++)
        if (subscription[0] > rand() % 100)
        {
            l[x];
            l.addsubscription();
        }
    for (int x = 0; x < randd; x++)
    {
        l[x];
        l.acceptsubscription();
    }
    for (int x = 0; x < randd; x++)
        if (sknot[1] > rand() % 100)
        {
            l[x];
            l.addcreate(chance_numbers[0] + rand() % (chance_numbers[1] - chance_numbers[0]), true);
        }
    for (int x = 0; x < randd; x++)
    {
        l[x];
        //l.remove();
    }
    rrannd();
}


void start()
{
    randd = coin_knot[0] + rand() % (coin_knot[1] - coin_knot[0]);
    for (int x = 0; x < randd; x++)
    {
        l.create(chance_numbers[0] + rand() % (chance_numbers[1] - chance_numbers[0]), false);
    }
    rrannd();
}


void setting();

void setting1()
{
    system("cls");
    cout << "количество узлов" << endl;
    cout << "min = ";
    cin >> coin_knot[0];
    cout << "max = ";
    cin >> coin_knot[1];
    setting();
}

void setting2()
{
    system("cls");
    cout << "случайное число" << endl;
    cout << "min = ";
    cin >> chance_numbers[0];
    cout << "max = ";
    cin >> chance_numbers[1];
    setting();
}

void setting3()
{
    system("cls");
    cout << "подписка" << endl;
    cout << "подписка = ";
    cin >> subscription[0];
    cout << "отписка = ";
    cin >> subscription[1];
    setting();
}

void setting4()
{
    system("cls");
    cout << "узел" << endl;
    cout << "число = ";
    cin >> sknot[0];
    cout << "появление = ";
    cin >> sknot[1];
    setting();
}

void setting()
{
    system("cls");
	cout << "-настройки-" << endl;
	cout << "1.количество узлов (" << coin_knot[0] << "," << coin_knot[1] << ")" << endl;
	cout << "2.случайное число  (" << chance_numbers[0] << "," << chance_numbers[1] << ")" << endl;
	cout << "3.подписка         (под." << subscription[0] << "%, отп." << subscription[1] << "%)" << endl;
	cout << "4.узел             (" << sknot[0] << "%," << sknot[1] << "%)"<< endl;
	cout << "5.запуск" << endl;

	double choicee; cin >> choicee;
	system("cls");
    if (choicee == 1)
    {
        setting1();
    }
    if (choicee == 2)
    {
        setting2();
    }
    if (choicee == 3)
    {
        setting3();
    }
    if (choicee == 4)
    {
        setting4();
    }
	if (choicee == 5)
	{
		start();
	}
	else {setting();}
}



int main()
{
    srand(time(0));
	coin_knot[0] = 10; coin_knot[1] = 20; coin_knot[2] = 0;
	chance_numbers[0] = -500; chance_numbers[1] = 500; chance_numbers[2] = 0;
	subscription[0] = 1; subscription[1] = 30; subscription[2] = 1; subscription[3] = 30;
	sknot[0] = 30; sknot[1] = 30;
	setlocale(LC_ALL, "RUS");
	setting();
}