#include "AgendaController.h"
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    while (1)
    {
        cout << "����������������(Y/N)" << endl;
        string choice;
        cin >> choice;

        if (choice == "N")
            break;

        else if (choice == "Y")

        {
            freopen("in.txt", "r", stdin);
            freopen("out.txt", "w", stdout);
            break;
        }

        else
        {
            cout << "command illegal!" << endl;
        }
    }

    AgendaController agendaController;

    agendaController.getOperation();

    return 0;
}
