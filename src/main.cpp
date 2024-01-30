#include <utils.h>
#include <stdint.h>
#include <string>
#include <iostream>

#define cells 80
#define SUB_SIZE 2
#define SIZE_BINS 9
bool is_first_row = true;
std::string rxData = "0100006400C8012C019001F4025802BC0320038403E82E0101012C000100020003000500060004000700080009000A3201020258000B000C000D000F0010000E001100120013001432010303840015001600170019001A0018001B001C001D001E32010404B0001F00200021002300240022002500260027002832010505DC0029002A002B002D002E002C002F00300031003232010607080033003400350037003800360039003A003B003C3201070834003D003E003F00410042004000430044004500463201080960004700480049004B004C004A004D004E004F005032";
//int a = 1;
typedef enum ddf_bins {
  ROW_1 = 46,
  ROW_2 = 96,
  ROW_3 = 146,
  ROW_4 = 196,
  ROW_5 = 246,
  ROW_6 = 296,
  ROW_7 = 346,
  ROW_8 = 396,
  ROW_9 = 446,
}ddf_bins;

typedef struct table_cell {
    uint16_t throttle;
    uint16_t rpm;
    uint16_t injection;
}table_cell;

table_cell table[cells];

uint8_t index = 0; //buff
uint16_t temp_rpm = 0;
uint8_t throttle_index = 0;
uint8_t injection_index = 0;
char buff[4];

int a = 1;

void decrypt_data (std::string data, ddf_bins bins);
void print_table_map();

int main ()
{
    //std::cout<<"size : "<<sizeof(table)<<std::endl
    for (int i = 0 ; i < 9; i++)
    {
        decrypt_data(rxData, ROW_1);
        a++;
    }
    print_table_map();
    return 0;
}

void decrypt_data (std::string data, ddf_bins bins)
{
    switch (a)
        {
        case 1:
            for (int i = 0 ; i < ROW_1; i++)
            {
                if(i<2)
                {}    //td::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 && i <=4)
                {}    //std::cout<<"row num : "<<i<<std::endl;
                else if(i >= ROW_1 - 2 && i < ROW_1)
                {}    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        //collumn input
                        for(int j = 0; j < 8; j++)
                        {
                            table[throttle_index + j*10].throttle = utils::hex2dec(buff);
                        }
                        index = 0;
                        throttle_index += 1;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 2:
            for (int i = ROW_1 ; i < ROW_2; i++)
            {
                if(i<2 + ROW_1)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_1 && i <=4 + ROW_1)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_1 && i <=7 + ROW_1)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_2 - 2 && i < ROW_2)
                    std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 3:
            for (int i = ROW_2 ; i < ROW_3; i++)
            {
                if(i<2 + ROW_2)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_2 && i <=4 + ROW_2)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_2 && i <=7 + ROW_2)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_3 - 2 && i < ROW_3)
                {}    
                    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 4:
            for (int i = ROW_3 ; i < ROW_4; i++)
            {
                if(i<2 + ROW_3)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_3 && i <=4 + ROW_3)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_3 && i <=7 + ROW_3)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_4 - 2 && i < ROW_4)
                {}    
                    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 5:
            for (int i = ROW_4 ; i < ROW_5; i++)
            {
                if(i<2 + ROW_4)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_4 && i <=4 + ROW_4)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_4 && i <=7 + ROW_4)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_5 - 2 && i < ROW_5)
                {}    
                    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 6:
            for (int i = ROW_5 ; i < ROW_6; i++)
            {
                if(i<2 + ROW_5)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_5 && i <=4 + ROW_5)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_5 && i <=7 + ROW_5)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_6 - 2 && i < ROW_6)
                {}    
                    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 7:
            for (int i = ROW_6 ; i < ROW_7; i++)
            {
                if(i<2 + ROW_6)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_6 && i <=4 + ROW_6)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_6 && i <=7 + ROW_6)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_7 - 2 && i < ROW_7)
                {}    
                    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 8:
            for (int i = ROW_7 ; i < ROW_8; i++)
            {
                if(i<2 + ROW_7)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_7 && i <=4 + ROW_7)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_7 && i <=7 + ROW_7)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_8 - 2 && i < ROW_8)
                {}    
                    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        case 9:
            for (int i = ROW_8 ; i < ROW_9; i++)
            {
                if(i<2 + ROW_8)
                {}
                    //std::cout<<"r/w : "<<i<<std::endl;
                else if(i > 2 + ROW_8 && i <=4 + ROW_8)
                    //std::cout<<"row num : "<<i<<std::endl;
                {}
                else if(i > 4 + ROW_8 && i <=7 + ROW_8)
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur rpm : "<<utils::hex2dec(buff)<<std::endl;
                        //row input
                        temp_rpm = utils::hex2dec(buff);
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
                else if(i >= ROW_9 - 2 && i < ROW_9)
                {}    
                    //std::cout<<"ur code : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        table[injection_index].injection = utils::hex2dec(buff);
                        table[injection_index].rpm = temp_rpm;
                        injection_index += 1; 
                        index = 0;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            break;
        default:
            break;
    }
}

void print_table_map()
{
    for (int i = 0; i < cells; i++)
    {
        std::cout<<"TPS : "<<table[i].throttle<<"  RPM : "<<table[i].rpm<<"  Injection : "<<table[i].injection<<std::endl;
    }
}