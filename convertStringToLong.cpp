/* Code for converting String to Long 
 * This program call test function to test the conversion from string 
 * to long is performed correctly. The stringToLong() function performs 
 * the conversion and throws exception if the given string "number" is 
 * to big to be converted as long. If the string "number" is negative number, 
 * the stringToLong() function multiplies -1 to change the result as negative 
 * long. 

 * Limitation: If the input stirng number contains comma, such as "112,304,22", 
 * the stringToLong() function will not correctly perform the conversion because 
 * I assumed that the input string does not contain commas and the problem did not 
 * specify about the format of the input string. If comma is valid part of the
 * input, the stringToLong() function can handle this issue by parsing commas 
 * from the input string. 
 */

#include <iostream>
#include <exception>
long stringToLong(std::string);
void test();

int main(int argc, const char * argv[]) {
    test();
    return 0;
}

void test()
{
    std::string input = "123";
    long i = 0;
    try {
        i = stringToLong(input);
    } catch (std::exception& e) {       // handles if input is out of range to be a long
        std::cout << e.what() << ": The range of input is invalid to be a long" << std::endl;
    }
    if( i == 123)
    {
        std::cout << i << std::endl;        // success
    }
    else
    {
        std::cout << "The conversion is not correct" << std::endl; // failure
    }
    
}

long stringToLong(std::string str)
{
    long answer, nextNum =0;
    long factor = 1;
    long max = std::numeric_limits<long>::max();
    
    for(long i = str.length() -1; i >= 0; i--)
    {
        nextNum = (str.at(i) - '0') * factor;
        if(i == 0)
        {
            if(str.at(i) == '-')        // handle negative number
            {
                answer *= -1;
                return answer;
            }
        }
        {
            if(answer > max - nextNum)      // handles underflow/overflow 
            {
                throw std::overflow_error("Long overflow");
            }
            answer += nextNum;
        }
        factor *= 10;
    }
    return answer;
}
