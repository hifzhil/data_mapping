// c system
#include <utils.h>
namespace utils {
    int hex2dec (std::string hexData)
    {
        int cnt = 3;  
        int decimalNumber = 0; 
        for (int i = 0; i < 4; i++)
        {
            hexData[i] = CharToDec(hexData[i]);
            decimalNumber = decimalNumber + (hexData[i])*pow(16, cnt); 
            cnt--;
        }
        return decimalNumber;
    }

    int CharToDec(char c)
    {
        if(c>='0' && c<='9') return c-'0';
        if(c>='a' && c<='f') return c-'a'+10;
        if(c>='A' && c<='F') return c-'A'+10;
        return 0;
    }

    bool compare_2_char(char a[], char b[])
    {
        for(int i = 0; b[i] != '\0'; i++)
        {
            if(a[i]!=b[i])
            {
                return 0;
            }
        }
        return 1;
    }    
}


    /**
    @brief : after completing hex2dec, i realyze that we can do it just by 
             strtoul(hex.c_str(), NULL, 16) :) :)
    */