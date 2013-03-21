#include "Decimal.h"

int main(int argc, char *argv[]) {
    puts("testing initialization...");
    Decimal test = Decimal("1");
//    puts("\n-2.5");
//    test= Decimal("-2.5");
//    cout << test << endl;
//    puts("\n12.375");
//    test = Decimal("12.375");
//    cout << test << endl;
//    puts("\n1.375");
//    test = Decimal("1.375");
//    cout << test << endl;
    puts("\n1");
    test = Decimal("1");
    cout << test << endl;
//    puts("\n.25");
//    test = Decimal("0.25");
//    cout << test << endl;
//    puts("\n.375");
//    test = Decimal("0.375");
//    cout << test << endl;

    puts("testing equality...");
//    Decimal a = Decimal("1");
//    cout << a << endl;
//    Decimal b = Decimal("2");
//    cout << b << endl;
//    Decimal c = Decimal("1");
//    cout << c << endl;
//    if (a == b) puts("\nuh-oh");
//    if (a == c) puts("\nok");
//
    puts("testing arithmatic operators...");
    Decimal a = Decimal("12.375");
    Decimal b = Decimal("1");
    Decimal c = a + b;
    cout << b << endl;
    cout << test << endl;
}
