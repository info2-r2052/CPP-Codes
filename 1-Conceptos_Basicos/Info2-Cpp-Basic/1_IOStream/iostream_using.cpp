#include <iostream>

//-----------------------------------------------------
using namespace std; 
//-----------------------------------------------------

// Con estas sentencias nos ahorramos de tipear std:: cada vez que envias datos a pantalla
// using std::cout;
// using std::cin;
// using std::endl;
//-----------------------------------------------------

int main() {
    int edad;
    cout << "Ingrese su edad: ";
    cin >> edad;
    cout << "Tienes " << edad << " años.\n";
    return 0;
}
