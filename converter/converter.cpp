#include "converter.hpp"
#include "../error/error.hpp"
#include <iostream>
#include <locale>
#include <algorithm>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h> 
using namespace std;
// This is the array that holds the values of two to the 32nd power starting from 1
const int lineLength = 32; // number of bits that make up each number
long long Bits[lineLength];

/*
  This is the method that takes in the int,
  multiplies it by the exponent of its 
  current position then adds them together
*/
long long test(long long val[] , int length)
{
    long long m = 0;
    int limit;
    bool negative;

    if(val[length-1]==1)
    {
        limit = length-1;
        negative = true;
    } else {
        limit = length;
        negative = false;
    }

    for (int i = 0; i < limit; i++)
    {
        m = m + (val[i] * Bits[i]);
    }

    if (negative){
        m = -m;
    }

    // cout << "Value to convert was " << val << endl;
    // cout << "Converted value is " << m << endl;

    return m;   
}
/*
  This is the method that helpes to calculate the exponent in the array
*/
long long exponent(int power)
{
    long long base = 1;
    
    long long ex =2;
    for (int i = 0; i < power; i++)
    {
       base = base * ex;
    }
    return base;
}
/**
 *The purpose of this method is to initialise the first 2 values of the array
 */
void Arrayinitilizer()
{
    Bits[0]=1;
    Bits[1]=2;
    for (int i = 2; i < lineLength; i++)
    {
        Bits[i] = exponent(i);
    }
    
}
/**
 * This is the method for the binary conversion 
 * It takes in a string and the length of the string then converts it to binary
 */
long long binaryToDecimal(string bi , int length)
{
    Arrayinitilizer();
    long long finalval = 0;
    long long dumb[lineLength];

    cout << "Converting binary to decimal..." << endl;
    cout << "Length is " << length << endl;
    for (int i = 0; i < length; i++)
    {
        int currentBit = (int)bi[i];
        dumb[i] = currentBit - 48; // using (int)bi[i] converts to ASCII of 1 or 0, this deals with that to turn into true 1 or 0
        cout << dumb[i];
    }
    cout << endl;

    finalval = test(dumb,length);

    cout << "Converted " << bi << " to decimal: " << finalval << endl;

    return finalval;
}


/*
Converts decimal to binary (string)
*/
string decimalToBinary(long long decimalNum, int numberOfBits)
{
    // initialise variables for conversion algorithm
    string convertedBinary;
    long long temp = abs(decimalNum);
    long long binaryVal;
    int i = 0;

    // while loop runs 'numberOfBits' times to allow return value to be specified bit length in binary form
    while (i < numberOfBits)
    {
        binaryVal = temp % 2; // get the binary value be getting the remainder of decimal number / 2
        temp = temp / 2;      // divide the decimal number by 2

        if (i < numberOfBits-1){ // check if i isn't last bit
            if (binaryVal == 0) // check if the binary value is 0
            {
                convertedBinary += "0"; // if so, add a 0 to the binary string
            }
            else if (binaryVal == 1) // check if the binary value is 1
            {
                convertedBinary += "1"; // if so, add a 1 to the binary string
            }
        } else { // if i is on the last bit
            if(decimalNum < 0){ // if the input number is negative
                convertedBinary += "1"; // use two's complement to store it correctly
            } else {
                convertedBinary += "0"; // don't use two's complement so value stays positive
            }
        }

        i++;
    }

    // cout << convertedBinary << endl;

    cout << "Converted " << decimalNum << " to binary: " << convertedBinary << endl;

    return convertedBinary; // return the converted binary as a string
}
