#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <iterator>

std::map<char,char> createKey();
std::string encrypt(std::string& messageToEncrypt,std::map<char,char> key);
std::string decrypt(std::string& messageToDecrypt,std::map<char,char> key);



int main()

{
    std::map<char,char> key=createKey();
    std::string a="zdanie ma sens";
    std::cout<<encrypt(a,key);

    return 0;
}

std::map<char,char> createKey()
{
    std::vector<char> ascii;

    for(unsigned int i=32; i<127; ++i)
    {
        ascii.push_back(char(i));
    }

    std::vector<int> shuffled(ascii.begin(),ascii.end());
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(shuffled.begin(), shuffled.end(), g);

    std::map<char,char> key;
    for(unsigned int i=0; i<ascii.size(); ++i)
    {

        key[ascii[i]]=shuffled[i];
    }

    return key;
}

std::string encrypt(std::string& messageToEncrypt,std::map<char,char> key)
{
    std::string encrypted;
    for(unsigned int i=0; i<messageToEncrypt.size(); ++i)
    {
        encrypted.push_back(key[messageToEncrypt[i]]);
    }
    return encrypted;
}

std::string decrypt(std::string& messageToDecrypt,std::map<char,char> key)
{
    return "rsdtf";
}

