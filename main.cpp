#include <iostream>
#include "MyList.h"

using std::cout;
using std::cin;
using std::endl;

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

int CheckNonNeg() {
    int m;
    while (true) {
        cin >> m;
        if (cin.fail() || m < 0) {
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
    cout << "1. Size of list" << endl;
    cout << "2. Clean list" << endl;
    cout << "3. Is list empty?" << endl;
    cout << "4. Find the value in list" << endl;
    cout << "5. Find the value by position" << endl;
    cout << "6. Change the value in certain position" << endl;
    cout << "7. Get position by value" << endl;
    cout << "8. Add new value" << endl;
    cout << "9. Add new value in certain position" << endl;
    cout << "10. Delete certain value" << endl;
    cout << "11. Delete certain element by position" << endl;
    /*cout << "12. Request straight iterator" << endl;
    cout << "13. Request reverse iterator" << endl;
    cout << "14. Request end() iterator" << endl;
    cout << "15. Request rend() iterator" << endl;
    16. операции с итераторами  */
    cout << "12. Show list" << endl;
    cout << "13. Show list in reverse order" << endl;
    cout << "14. Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter the command:";

    return Check();
}

void Menu() {
    int k, j;
    bool f = true;
    cout << "Enter the size of list (positive integer number):";
    k = CheckNonNeg();

    MyList <int> a;
    for (int i = 0; i < k; i++) {
        a.AddValue(i);
    }
    // MyList <int> a(a1);
    while (f) {
        switch (Options()) {
            case 1:
                cout << "Size of list = " << a.GetSize() << endl;
                break;
            case 2:
                cout << "List is cleaned" << endl;
                a.Clean();
                break;
            case 3:
                if (a.IsEmpty()) {
                    cout << "List is empty" << endl;
                } else {
                    cout << "List isn't empty" << endl;
                }
                break;
            case 4:
                cout << "Enter value to find in list:" << endl;
                j = Check();
                if (a.IsThere(j)) {
                    cout << "Value is in the list" << endl;
                } else {
                    cout << "Value isn't in the list" << endl;
                }
                cout << "Statistics: " << a.ShowNumOfViews() << endl;
                break;
            case 5:
                cout << "Enter position to find in list:" << endl;
                j = CheckNonNeg();
                cout << "The value: " << a.FindValue(j) << endl;
                break;
            case 6:
                cout << "Enter position to change:" << endl;
                j = CheckNonNeg();
                cout << "Enter value to replace:" << endl;
                k = Check();
                if (a.ChangeValue(j, k))
                    cout << "Position was successfully replaced" << endl;
                break;
            case 7:
                cout << "Enter value to find its position:" << endl;
                j = Check();
                k = a.FindPos(j);
                if (k != -1) {
                    cout << "Position was found: " << k << endl;
                } else {
                    cout << "Position wasn't found" << endl;
                }
                break;
            case 8:
                cout << "Enter value to add:" << endl;
                j = Check();
                a.AddValue(j);
                cout << "Value was successfully added" << endl;
                break;
            case 9:
                cout << "Enter position to add:" << endl;
                j = CheckNonNeg();
                cout << "Enter value to add:" << endl;
                k = Check();
                if (a.AddValueToPos(j, k)) {
                    cout << "Position was successfully added" << endl;
                    cout << "Statistics: " << a.ShowNumOfViews() << endl;
                }
                break;
            case 10:
                cout << "Enter value to remove:" << endl;
                j = Check();
                k = a.DeleteValue(j);
                if (j == k) {
                    cout << "Value was successfully removed" << endl;
                } else {
                    cout << "Value wasn't removed" << endl;
                }
                break;
            case 11:
                cout << "Enter position to remove:" << endl;
                j = CheckNonNeg();
                cout << "Deleted position's value: " << a.DeletePos(j) << endl;
                cout << "Statistics: " << a.ShowNumOfViews() << endl;
                break;
            case 12:
                a.PrintList();
                //a.PrintListIt();
                break;
            case 13:
                a.PrintListReverse();
                //a.PrintListReverseIt();
                break;
            case 14:
                f = false;
                break;
            default:
                cout << "Command with this number doesn't exist. Try 1 to 14" << endl;
                break;
        }
    }
}

int main() {
    Menu();
    return 0;
}
