#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      std::vector<unsigned long long> w(5,0); //vector that contains the 6 letter substrings partitioned out of the word k
      int kindex=static_cast<int>(k.length())-1; //current index of k, starts with final
      int currSubstr=4; //starts from the end chunk of the word
      while(currSubstr>=0&&kindex>=0){
        unsigned long long val = 0; // value of each letter after being put through the w equation
        unsigned long long times = 1; //value of 36^i, i how far left the current letter is in the substring, starting from zero
        for(int i=0;i<6&&kindex>=0;i++,kindex--){
          unsigned long long formVal=letterDigitToNumber(k[kindex]);
          val+=formVal*times;
          times=times*36;
        }
      
        w[currSubstr]=val;
        currSubstr--;
      }
      unsigned long long hashofk=0;
      for(int i=0;i<5;i++){
      hashofk+=static_cast<unsigned long long>(rValues[i])*w[i];
        std::cout<<"w["<<i<<"] = "<<w[i]<<std::endl;
      }
      return static_cast<HASH_INDEX_T>(hashofk);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        letter=std::tolower(letter);
        HASH_INDEX_T count = 0;
        for(char l='a'; l<='z'; l++){
          if(l==letter){
            return count;
          }
          else{
            count++;
          }
        }
        for(char n='0'; n<='9'; n++){
          if(n==letter){
            return count;
          }
          else{
            count++;
          }
        }
      return count;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
