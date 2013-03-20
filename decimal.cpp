// IEEE 754 Decimal32 floating-point format implementation
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <cstring>
#include <math.h>
#include <stdlib.h>

using namespace std;

class Decimal {
    private:
        bool sign;
        bitset <8> exponent;
        bitset <23> fraction;
        friend ostream& operator<<(ostream& out, Decimal& d);
        void dec2bin(int num, char *str) {
            str[23] = '\0';
            int mask = 0x10 << 1;
            while(mask >>= 1)
              *str++ = !!(mask & num) + '0';
        }
    public:
        Decimal operator +  (const Decimal&);
        Decimal operator *  (const Decimal&);
        Decimal operator == (const Decimal&);

        Decimal(const char *number) {
            if (number[0] == '-') {
                this->sign = 0;
                number = number + 1;
            } else this->sign = 1;

            // consider a real number with an integer and a fraction part such as 12.375
            // https://en.wikipedia.org/wiki/Single-precision_floating-point_format

            int integer_part = 0, fractional_part = 0, exponent = 1;

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
            char precision_integer_part, accumulator[23] = "";
            while (fractional_part != 0 && exponent < 23) {
                printf("%d\n", fractional_part);
                // get the fractional part of this iteration as a char array
                char precision[16];
                sprintf(precision, "%d", fractional_part);
                // get the length to make it a fraction from an int
                int fractional_length = (int) strlen(precision);
                // get the fraction multiple
                double multiple = ((double) fractional_part / (pow(10, fractional_length))) * 2;
                printf("%f\n", multiple);
                // put the result inside a char array
                sprintf(precision, "%f", multiple);
                // so we can split it again here
                sscanf(precision, "%c.%d", &precision_integer_part, &fractional_part);
                // add the integer part to the accumulator
                accumulator[exponent - 1] = precision_integer_part;
                // if the fractional_part is 0, we've encoded full number
                if (fractional_part == 0) break;
                exponent++;
            }
            // The single-precision binary floating-point exponent is encoded
            // using an offset-binary representation, with the zero offset
            // being 127; also known as exponent bias in the IEEE 754 standard.
            exponent += 127;
            this->exponent = exponent;

            // Add integer and fraction, normalize, and write to the bitsets
            char conversion[23];
            char *ps = conversion;
            this->dec2bin(integer_part, conversion);
            strcat(conversion, accumulator);
            while (conversion[0] == '0')
                for (; *ps != '\0'; ps++)
                    *ps = *(ps + 1);
            printf("test: %s\n", conversion);
            for (int i = 0; i < 23 && conversion[i] != '\0'; i++)
                this->fraction[23 - i] = conversion[i] == '1' ? 1 : 0;
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
    //Decimal test = Decimal("12.375");
    Decimal test = Decimal("1.375");
    //printf("%d", test);
    cout << test;
}
