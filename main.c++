#include <iostream>
#include <limits>
using namespace std;

class Stack {
private:
    int* data;
    Stack* next;

public:
    // constructor pentru initializarea stivei
    Stack(int n) : data{ new int{ n } }, next{ nullptr } {}

    // pt stergerea int* data cand sterg un nod
    ~Stack() {
        delete data;
    }

    // functie pe care o folosim sa ajungem in varful stivei
    Stack* getStackTop() {
        Stack* current = this;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current;
    }

    // adauga un numar in varful stivei
    void push(int val)
    {
        Stack* top = getStackTop();
        Stack* newNode = new Stack(val);
        top->next = newNode;
    }

    // sterge elementul din varf
    void pop()
    {
        if (next == nullptr) {
            if (data == nullptr) {
                cerr << "Stack is empty." << endl;
                return;
            }
            delete data;
            data = nullptr;
            return;
        }

        Stack* topNode = getStackTop();
        Stack* prevNode = this;

        while (prevNode->next != topNode) {
            prevNode = prevNode->next;
        }

        prevNode->next = nullptr;
        delete topNode;
    }

    // returneaza valoarea din varful stivei
    int top() {
        Stack* top = this;

        while (top->next != nullptr)
        {
            top = top->next;
        }
        return *top->data;
    }

    // returneaza totalul de elemente din stiva
    int length() {
        int length = 0;
        Stack* current = this;

        while (current->next != nullptr)
        {
            current = current->next;
            length++;
        }
        return length;
    }

    // goleste stiva
    void empty() {
        int current = this->length();

        for (int i = 0; i <= current; i++)
        {
            this->pop();
        }
    }

    // printeaza intreg continutul stivei
    void print() {
        Stack* current = this->next;  // Parcurgem de la primul element, nu de la nodul inițial

        while (current != nullptr) {
            cout << *current->data << ' ';
            current = current->next;
        }
    }

    // printeaza top() pe ecran
    void printTop() {
        cout << this->top();
    }

    // ca sa putem da cout ca la un array normal gen stiva[numar]
    int operator[](int index)
    {
        Stack* current = this;

        if (index == 0 && current->data == nullptr) {
            cerr << "Out of stack." << endl;
            return -1;
        }

        for (int i = 0; i < index; i++)
        {
            if (current->next == nullptr) {
                cerr << "Out of stack." << endl;
                return -1;
            }
            current = current->next;
        }
        return *current->data;
    }
};
// functie care verifica daca un input poate corespunde jocului. (sa nu fie litera sau nr <= 0).
// usage reprezinta utilizarea functiei (F - From, T - to, N - numDisks)
int isValid(char usage)
{
    int input;
    if (!(cin >> input)) {
        cout << "Input invalid! Introduceti un numar intreg.\n";
        cin.clear();  // Reseteaza starea fluxului de intrare
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora restul liniilor
        switch (usage)
        {
        case 'F':
            cout << "De pe tija: ";
            break;
        case 'T':
            cout << "Pe tija: ";
            break;
        case 'N':
            cout << "\nIntroduceti numarul de discuri: \n";
            break;
        }
        return isValid(usage);
    }
    else if (input <= 0)
    {
        cout << "Numarul inserat trebuie sa fie mai mare decat 0! \n";
        switch (usage)
        {
        case 'F':
            cout << "De pe tija: ";
            break;
        case 'T':
            cout << "Pe tija: ";
            break;
        case 'N':
            cout << "\nIntroduceti numarul de discuri: ";
            break;
        }
        return isValid(usage);
    }
    return input;
}
int main()
{
    int numDisks;

    cout << "Turnurile din Hanoi\n\n";
    cout << "Introduceti numarul de discuri: ";
    numDisks = isValid('N');

    Stack towerA(numDisks);  // Turnul de pornire (turnul A)
    Stack towerB(0);        // Turnul intermediar (turnul B)
    Stack towerC(0);        // Turnul destinatie (turnul C)

    // Initializare stiva initiala (turnul A)
    for (int i = numDisks; i > 0; i--) {
        towerA.push(i);
    }

    int moves = 0;  // Contor pentru numarul de mutari efectuate

    while (true)
    {
        cout << "-------------------------\n";
        cout << "Starea curenta a turnurilor:\n";
        cout << "Turnul A: ";
        towerA.print();
        cout << "\nTurnul B: ";
        towerB.print();
        cout << "\nTurnul C: ";
        towerC.print();
        cout << "\n-------------------------\n";

        // Citirea mutarii de la utilizator
        int from, to;
        cout << "Mutare #" << moves + 1 << "\n";
        cout << "De pe tija: ";
        from = isValid('F');
        cout << "Pe tija: ";
        to = isValid('T');

        // Verificare mutare valida
        Stack* sourceTower;
        Stack* destTower;

        if (from == 1) {
            sourceTower = &towerA;
        }
        else if (from == 2) {
            sourceTower = &towerB;
        }
        else if (from == 3) {
            sourceTower = &towerC;
        }
        else {
            cout << "Tija sursa invalida!\n";
            continue;
        }

        if (to == 1) {
            destTower = &towerA;
        }
        else if (to == 2) {
            destTower = &towerB;
        }
        else if (to == 3) {
            destTower = &towerC;
        }
        else {
            cout << "Tija destinatie invalida!\n";
            continue;
        }

        // Verificare mutare legala
        if (sourceTower->length() == 0) {
            cout << "Tija sursa goala!\n";
            continue;
        }

        if (destTower->length() > 0 && sourceTower->top() > destTower->top()) {
            cout << "Nu poti pune o tija mai mare peste una mai mica!\n";
            continue;
        }

        // Efectuarea mutarii
        int disk = sourceTower->top();
        sourceTower->pop();
        destTower->push(disk);

        moves++;

        // Verificare daca jocul s-a terminat
        if (towerA.length() == 0 && towerB.length() == 0 && towerC.length() == numDisks)
        {
            cout << "-------------------------\n";
            cout << "Starea curenta a turnurilor:\n";
            cout << "Turnul A: ";
            towerA.print();
            cout << "\nTurnul B: ";
            towerB.print();
            cout << "\nTurnul C: ";
            towerC.print();
            cout << "\n-------------------------\n";
            cout << "Jocul s-a incheiat! Felicitari!\n";
            break;
        }
    }
    return 0;
}
