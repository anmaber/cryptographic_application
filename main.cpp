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

std::map<char,char> createKey();
std::string encrypt(std::string& messageToEncrypt,std::map<char,char> key);
std::string decrypt(std::string& messageToDecrypt,std::map<char,char> key);



int main()

{
    std::map<char,char> key=createKey();
    std::string a="zdanie ma sens";
    std::string toencrypt,toDecrypt;
    toencrypt=encrypt(a,key);
    std::cout<<toencrypt<<std::endl;
    std::cout<<decrypt(toencrypt,key);

    return 0;
}

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
    //std::generate_n(std::back_inserter(encrypted), messageToEncrypt.size(), [&](){ });
    for(unsigned int i=0; i<messageToEncrypt.size(); ++i)
    {
        encrypted.push_back(key[messageToEncrypt[i]]);
    }
    return encrypted;
}

std::string decrypt(std::string& messageToDecrypt,std::map<char,char> key)
{
    std::string decrypted;
    for(unsigned int i=0; i<messageToDecrypt.size(); ++i)
    {
        auto findLetter = std::find_if(std::begin(key), std::end(key), [&](const std::pair<char,char> &pair)
        {
            return pair.second == messageToDecrypt[i];
        });

        decrypted.push_back(findLetter->first);
    }
    return decrypted;
}

