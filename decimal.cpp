// IEEE 754 Decimal32 floating-point format implementation
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <cstring>
#include <math.h>

using namespace std;

class Decimal {
    private:
        bool sign;
        bitset <8> exponent;
        bitset <23> fraction;
        friend ostream& operator<<(ostream& out, Decimal& d);
    public:
        Decimal operator +  (const Decimal&);
        Decimal operator *  (const Decimal&);
        Decimal operator == (const Decimal&);

        Decimal(const char *number) {
            if (number[0] == '-') {
                this->sign = 0;
                number = number + 1;
            } else { this->sign = 1; }

            // consider a real number with an integer and a fraction part such as 12.375
            // https://en.wikipedia.org/wiki/Single-precision_floating-point_format

            int integer_part = 0, fractional_part = 0, exponent = 0;

            // convert and normalize the integer part into binary
            sscanf(number, "%d.%d", &integer_part, &fractional_part);

            // convert the fraction part using the following technique, then
            // add the two results and adjust them to produce a proper final
            // conversion
            //
            // to convert it into a binary fraction, multiply the fraction
            // by 2, take the integer part and re-multiply new fraction by
            // 2 until a fraction of zero is found or until the precision
            // limit is reached which is 23 fraction digits for IEEE 754
            // binary32 format
            int accumulator = 0, precision_integer_part = 0;
            while (fractional_part != 0 && exponent < 5) {
                // get the fractional part of this iteration as a char array
                char precision[16];
                sprintf(precision, "%d", fractional_part);
                // get the length
                int fractional_length = (int) strlen(precision);
                double multiple = ((double) fractional_part / (pow(10, fractional_length))) * 2;
                sprintf(precision, "%f", multiple);
                sscanf(number, "%d.%d", &precision_integer_part, &fractional_part);
                accumulator += precision_integer_part;
                if (fractional_part == 0) continue;
                printf("%f\n", precision);
                exponent++;
            }

            this->exponent = integer_part;
            //this->fraction = fr;
        }
};

ostream& operator<<(ostream& out, Decimal& decimal) {
    return out << decimal.sign
               << " "
               << decimal.exponent
               << " . "
               << decimal.fraction;
}

int main(int argc, char *argv[]) {
    //Decimal test = Decimal("-2.5");
    Decimal test = Decimal("12.375");
    //printf("%d", test);
    cout << test;
}
