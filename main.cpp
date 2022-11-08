#include <iostream>
#include <list>
#include "MyBST.h"
#include <ctime>
#include <cmath>

typedef unsigned long long INT_64;

using std::cout;
using std::cin;
using std::endl;

static INT_64 RRand = 15750; // переменная и константы генератора LineRand()
const INT_64 mRand = (1<<63) -1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

void sRand() { //функция установки первого случайного числа от часов компьютера
    srand(time(0));
    RRand = (INT_64)rand();
}

INT_64 LineRand() { //функция генерации случайного числа
    INT_64 y1,y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL)>>32;
    return RRand;
}

void test_rand(int n) { //Тест трудоёмкости операций случайного BST-дерева
    MyBST<INT_64, int> tree; //создание дерева для 64 – разрядных ключей типа INT_64
    auto* m = new INT_64 [n]; //массив для ключей, которые присутствуют в дереве
    sRand();  //установка первого случайного числа

    bool *ins = new bool;

    for (int i = 0; i < n; i++) { //заполнение дерева и массива элементами со случайными ключами
        m[i] = LineRand();
        tree.Insert(tree.GetRoot(),m[i],1, ins);
        tree.SetNum();
    }

    cout << "items count: " << tree.GetSize() << endl; //вывод размера дерева до теста

    double I = 0; // обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double D = 0;
    double S = 0;

    for (int i = 0; i < n/2; i++) //генерация потока операций, 10% - промахи операций
        if (i % 10 == 0) { //10% промахов
            tree.Delete(tree.GetRoot(), LineRand(), ins);
            D += tree.GetNum();
            tree.SetNum();
            tree.Insert(tree.GetRoot(), m[rand() % n], 1, ins);
            I += tree.GetNum();
            tree.SetNum();
            tree.Search(tree.GetRoot(),LineRand());
            S += tree.GetNum();
            tree.SetNum();
        }
        else { // 90% успешных операций
            int ind = rand() % n;
            tree.Delete(tree.GetRoot(), m[ind], ins);
            D += tree.GetNum();
            tree.SetNum();
            INT_64 key = LineRand();
            tree.Insert(tree.GetRoot(), key, 1, ins);
            I += tree.GetNum();
            tree.SetNum();
            m[ind] = key;
            tree.Search(tree.GetRoot(), m[rand() % n]);
            S += tree.GetNum();
            tree.SetNum();
        }

    cout << "items count: " << tree.GetSize() << endl; //вывод размера дерева после теста
    cout << "1.39 * log2(n) = " << 1.39 * (log((double)n) / log(2.0)) << endl; //теоретической оценки трудоёмкости операций BST
    cout << "count insert: " << I/(n/2) << endl; //экспериментальной оценки трудоёмкости вставки
    cout << "count delete: " << D/(n/2) << endl; //экспериментальной оценки трудоёмкости удаления
    cout << "count search: " << S/(n/2) << endl; //экспериментальной оценки трудоёмкости поиска
    delete[] m;
}

void test_ord(int n) { //Тест трудоёмкости операций вырожденного BST-дерева
    MyBST<INT_64,int> tree; //создание дерева для 64 – разрядных ключей типа INT_64
    INT_64* m = new INT_64 [n];//массив для ключей, которые присутствуют в дереве

    bool *ins = new bool;

    for (int i = 0; i < n; i++) {//заполнение дерева и массива элементами с возрастающими чётными ключами на интервале [0, 10000, 20000, ... ,10000*n]
        m[i] = i * 10000;
        tree.Insert(tree.GetRoot(),m[i],1, ins);
        tree.SetNum();
    }

    cout << "items count: " << tree.GetSize() << endl; // вывод размера дерева до теста

    double I = 0;// обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double D = 0;
    double S = 0;

    sRand(); // установка первого случайного числа

    for (int i = 0; i < n/2; i++) { // генерация потока операций, 10% - промахи операций
        if (i % 10 == 0) { // 10% промахов
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2); //случайный нечётный ключ
            tree.Delete(tree.GetRoot(), k, ins);
            D += tree.GetNum();
            tree.SetNum();
            tree.Insert(tree.GetRoot(), m[rand() % n], 1, ins);
            I += tree.GetNum();
            tree.SetNum();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2); // случайный нечётный ключ
            tree.Search(tree.GetRoot(), k);
            S += tree.GetNum();
            tree.SetNum();
        } else { // 90% успешных операций
            int ind = rand() % n;
            tree.Delete(tree.GetRoot(), m[ind], ins);
            D += tree.GetNum();
            tree.SetNum();
            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            tree.Insert(tree.GetRoot(), k, 1, ins);
            I += tree.GetNum();
            tree.SetNum();
            m[ind] = k;
            tree.Search(tree.GetRoot(), m[rand() % n]);
            S += tree.GetNum();
            tree.SetNum();
        }
    }

    cout << "items count: " << tree.GetSize() << endl; //вывод размера дерева после теста
    cout << "n/2 = " << n/2 << endl; //теоретической оценки трудоёмкости операций BST
    cout << "count insert: " << I/(n/2) << endl; //экспериментальной оценки трудоёмкости вставки
    cout << "count delete: " << D/(n/2) << endl; //экспериментальной оценки трудоёмкости удаления
    cout << "count search: " << S/(n/2) << endl; //экспериментальной оценки трудоёмкости поиска
    delete[] m;
}

int Check() {
    int m;
    while (true) {
        cin >> m;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "You entered wrong value, try again" << endl;
        } else {
            break;
        }
    }
    return m;
}

int Options() {
    cout << "================= Options ==================" << endl;
    cout << "1. Size of tree" << endl;
    cout << "2. Clear tree" << endl;
    cout << "3. Is tree empty?" << endl;
    cout << "4. Height of tree" << endl;
    cout << "5. Find the value by key" << endl;
    cout << "6. Replace the value by key" << endl;
    cout << "8. Insert new value" << endl;
    cout << "9. Delete by key" << endl;
    cout << "10. Show tree" << endl;
    cout << "11. Show list of tree keys" << endl;
    cout << "12. Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter the command:";

    return Check();
}

void Stat(MyBST<int,int>* G) {
    cout << "statistics = " << G->GetNum() << endl;
    G->SetNum();
}

void Menu() {
    int k, j; bool f = true;

    MyBST<int, int> G;

    //MyBST<int, int> V(&G);

    std::list<int> p;
    bool *ins = new bool;
    NodeBST<int, int> *t = nullptr;

    G.Insert(G.GetRoot(), 15, 45, ins);
    G.Insert(G.GetRoot(), 10, 48, ins);
    G.Insert(G.GetRoot(), 5, 41, ins);
    G.Insert(G.GetRoot(), 50, 1, ins);
    G.Insert(G.GetRoot(), 11, 11, ins);
    G.Insert(G.GetRoot(), 21, 4, ins);
    G.Insert(G.GetRoot(), 25, 41, ins);
    G.Insert(G.GetRoot(), 52, 55, ins);
    G.Insert(G.GetRoot(), 30, 30, ins);
    G.SetNum();

    /*MyBST<int,int>::Iterator it(G.GetRoot(), &G);
    cout << "Value of next node after root = " << *it.operator++() << endl;
    cout << "Value of previous node = " << *it.operator--() << endl;*/

    //test_rand(100000);
    //test_ord(20000);

    while (f) {
        switch (Options()) {
            case 1:
                cout << "size of tree = " << G.GetSize() << endl;
                //cout << "size of tree = " << V.GetSize() << endl;
                break;
            case 2:
                cout << "tree is cleared" << endl;
                G.Clear(G.GetRoot());
                Stat(&G);
                break;
            case 3:
                if (G.IsEmpty()) {
                    cout << "tree is empty" << endl;
                } else {
                    cout << "tree is not empty" << endl;
                }
                break;
            case 4:
                cout << "height of tree = " << G.Height(G.GetRoot()) << endl;
                Stat(&G);
                break;
            case 5:
                cout << "Enter key to find in tree:" << endl;
                k = Check();
                t = G.Search(G.GetRoot(), k);
                if (t) cout << "The value: " << t->value << endl;
                Stat(&G);
                break;
            case 6:
                cout << "Enter key:" << endl;
                k = Check();
                cout << "Enter value to replace:" << endl;
                j = Check();
                if (G.ReplaceByKey(k, j))
                    cout << "Position was successfully replaced" << endl;
                Stat(&G);
                break;
            case 8:
                cout << "Enter key:" << endl;
                k = Check();
                cout << "Enter value to insert:" << endl;
                j = Check();
                G.Insert(G.GetRoot(), k, j, ins);
                if (*ins) cout << "Value was successfully added" << endl;
                Stat(&G);
                break;
            case 9:
                cout << "Enter key to delete:" << endl;
                k = Check();
                G.Delete(G.GetRoot(), k, ins);
                Stat(&G);
                break;
            case 10:
                G.Show(G.GetRoot(), 0);
                Stat(&G);
                break;
            case 11:
                G.t_L_R(G.GetRoot(), &p);
                for (auto const &i: p) cout << i << " ";
                cout << endl;
                Stat(&G);
                break;
            case 12:
                f = false;
                break;
            default:
                cout << "Command with this number doesn't exist. Try 1 to 12" << endl;
                break;
        }
    }
}

int main() {
    Menu();
    return 0;
}
