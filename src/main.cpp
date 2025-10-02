
#include <iostream>
using namespace std;

// Une fonction classique
int add(int a, int b) {
    return a + b;
}

// Une fonction qui prend un pointeur de fonction en paramètre
int compute(int x, int y, int (*func)(int, int)) {
    return func(x, y);
}

int main() {
    cout << compute(5, 3, add) << endl; // appelle add(5,3)
}

