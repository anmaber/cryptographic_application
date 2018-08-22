#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <random>
#include <numeric>
#include <functional>
#include <fstream>

std::map<char,char> createKey();
std::map<char,char> key=createKey();
std::string encrypt(std::string& messageToEncrypt,std::map<char,char> key);
std::string decrypt(std::string& messageToDecrypt,std::map<char,char> key);



std::map<char,char> createKey()
{

    std::vector<char> ascii(94) ;
    std::iota (std::begin(ascii), std::end(ascii), 32);

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
    
    std::transform(messageToEncrypt.begin(), messageToEncrypt.end(), std::back_inserter(encrypted), 
                    [&](char letter) -> char {return key[(int)letter];});
    return encrypted;
}

std::string decrypt(std::string& messageToDecrypt,std::map<char,char> key)
{
    std::string decrypted;

   std::transform(std::begin(messageToDecrypt), std::end(messageToDecrypt),std::back_inserter(decrypted),
   [&](char x) -> char
   {
    auto findLetter = std::find_if(std::begin(key), std::end(key), [&](const std::pair<char,char> &pair)
        {
            return pair.second == x;
        });
    return findLetter->first;
   }
   
    );
    return decrypted;
}   
void exportToExternalFile(std::string encrypted, std::string decrypted)
{
    std::ofstream out ("data.txt");
    out << encrypted << std::endl;
    out << decrypted << std::endl;
    out.close();
}
std::string importEncryptDataFromExternalFile()
{
    std::string textFromFile;
    std::ifstream in("data.txt");
    if(in.is_open())
    {
        getline(in, textFromFile);
    }
    return textFromFile;
}
std::string importDecryptDataFromExternalFile()
{
    std::string textFromFile;
    std::ifstream in("data.txt");
    if(in.is_open())
    {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(in, textFromFile);
    }
    return textFromFile;
}
void show(std::string text)
{
    std::cout << text << std::endl;
}
int main()
{
    show("Load from file: ");
    show(importEncryptDataFromExternalFile());
    show(importDecryptDataFromExternalFile());
    show("With diffrent random key:");
    std::string insteandOfCin="This letter make sense and have special sign like ! @ # $ % ^ & * and more from ASCII.";
    std::string toEncrypt,toDecrypt;
    toEncrypt = encrypt(insteandOfCin,key);
    show(toEncrypt);
    toDecrypt = decrypt(toEncrypt,key);
    show(toDecrypt);
    exportToExternalFile(toEncrypt, toDecrypt);
    return 0;
}