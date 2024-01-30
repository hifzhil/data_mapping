// c system
#include <utils.h>
namespace utils {
    uint16_t hex2dec (std::string hexData)
    {
        uint8_t cnt = 3;  
        uint16_t decimalNumber = 0; 
        for (int i = 0; i < 4; i++)
        {
            hexData[i] = CharToDec(hexData[i]);
            decimalNumber = decimalNumber + (hexData[i])*pow(16, cnt); 
            cnt--;
        }
        return decimalNumber;
    }

    uint16_t CharToDec(char c)
    {
        if(c>='0' && c<='9') return c-'0';
        if(c>='a' && c<='f') return c-'a'+10;
        if(c>='A' && c<='F') return c-'A'+10;
        return 0;
    }    
}


    /**
    @brief : after completing hex2dec, i realyze that we can do it just by 
             strtoul(hex.c_str(), NULL, 16) :) :)
    */