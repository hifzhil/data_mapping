#include <utils.h>
#include <stdint.h>
#include <string>
#include <iostream>

#define SUB_SIZE 2
#define SIZE_BINS 9
bool is_first_row = true;


std::string rxData = "FFFA000003E807D00BB80FA0138817701B581F40232827102AF82EE032C836B0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB0000006400C8012C019001F4025802BC0320038403E8044C04B005140578FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC000100020003000400050006000700080009000A000B000C000D000E000F0010001100120013001400150016001700180019001A001B001C001D001E001F0020002100220023002400250026002700280029002A002B002C002D002E002F0030003100320033003400350036003700380039003A003B003C003D003E003F0040004100420043004400450046004700480049004A004B004C004D004E004F0050005100520053005400550056005700580059005A005B005C005D005E005F0060006100620063006400650066006700680069006A006B006C006D006E006F0070007100720073007400750076007700780079007A007B007C007D007E007F0080008100820083008400850086008700880089008A008B008C008D008E008F0090009100920093009400950096009700980099009A009B009C009D009E009F00A000A100A200A300A400A500A600A700A800A900AA00AB00AC00AD00AE00AF00B000B100B200B300B400B500B600B700B800B900BA00BB00BC00BD00BE00BF00C000C100C200C300C400C500C600C700C800C900CA00CB00CC00CD00CE00CF00D000D100D200D300D400D500D600D700D800D900DA00DB00DC00DD00DE00DF00E000E1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
//int a = 1;

typedef enum ddf_bins {
  ROW_1 = 124,
  ROW_2 = 248,
}ddf_bins;


struct ddf_table {
    double throttle;
    double rpm;
    double injection;
};
struct ddf_table ddf_table;

uint8_t index = 0; //buff
int cells = 0;
uint16_t temp_rpm = 0;
uint8_t throttle_index = 0;
uint8_t injection_index = 0;
uint8_t rpm_index = 0;
char buff[4];
char buff_check[4];
int a = 1;

void decrypt_data (std::string data, struct ddf_table *ddf_table);
void print_table_map(struct ddf_table *ddf_table);
int find_table_size (std::string data, char pattern1[], char pattern2[]);
int compare_2_char(char a[], char b[]);
int main (int argc, char *argv[])
{
    std::cout<<"size : "<<rxData.size()<<std::endl;
    cells = find_table_size(rxData, "FFFA", "FFFF");
    std::cout<<"cells : "<<cells<<std::endl;
    double cells_long = pow(cells,2);
    struct ddf_table parsed[225];
    for (int k = 0 ; k < 3; k++)
    {
        decrypt_data(rxData, &ddf_table);
        a++;
    }
    print_table_map(&ddf_table);
    return 0;
}

void decrypt_data (std::string data, struct ddf_table *ddf_table)
{
    switch (a)
        {
        case 1:
            for (int i = 0 ; i < (cells+1)*4; i++)
            {
                if(i<4)
                {
                    std::cout<<data[i];
                }    //td::cout<<"r/w : "<<i<<std::endl;
                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        //collumn input
                        for(int j = 0; j < cells; j++)
                        {
                            ddf_table[j*cells + throttle_index].throttle = utils::hex2dec(buff);
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
            std::cout<<"1 done"<<std::endl;
            break;
        
        case 2:
            for (int i = ROW_1 ; i < ROW_1 + (cells + 1)*4; i++)
            {
                if(i < 4 +ROW_1)
                {
                    std::cout<<data[i];
                }

                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        //collumn input
                        for(int j = 0; j < cells; j++)
                        {
                            ddf_table[rpm_index*cells + j].rpm = utils::hex2dec(buff);
                        }
                        index = 0;
                        rpm_index += 1;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            std::cout<<"2 done"<<std::endl;
            break;

        case 3:
            for (int i = ROW_2 ; i < ROW_2 + (pow(cells,2) + 1)*4 ; i++)
            {
                if(i<4 + ROW_2)
                {
                    std::cout<<data[i];
                }

                else
                {
                    buff[index] = data[i];
                    if (index == 3)
                    {
                        //std::cout<<"ur decimal : "<<utils::hex2dec(buff)<<std::endl;
                        ddf_table[injection_index].injection = utils::hex2dec(buff);
                        injection_index += 1; 
                        index = 0;
                        //std::cout<<table[injection_index].injection<<" index: "<<injection_index<<std::endl;
                    }
                    else
                    {   
                        index ++;
                    }
                }
            }
            std::cout<<"3 done"<<std::endl;
            break;
        
        default:
            break;
    }
}

void print_table_map(struct ddf_table *ddf_table)
{
    for (int i = 0; i < pow(cells,2); i++)
    {
        std::cout<<"TPS: "<<ddf_table[i].throttle<<"\t"<<"RPM: "<<ddf_table[i].rpm<<"\t"<<"Injection: "<<ddf_table[i].injection<<std::endl;
    }                
}
int find_table_size (std::string data, char pattern1[], char pattern2[])
{
    int check_index = 0;
    bool pattern1_found_ = false;
    bool pattern2_found_ = false;
    int i_for_pattern_1_ = 0;
    int i_for_pattern_2_ = 0;
    for(int i = 0; i < data.size(); i++)
    {
        buff_check[check_index] = data[i];
        if (check_index == 3)
        {
            if (compare_2_char(buff_check, pattern1) && pattern1_found_ == false)
            {
                i_for_pattern_1_ = i;
                pattern1_found_ = true;
            }
            else if (compare_2_char(buff_check, pattern2) && pattern2_found_ == false)
            {                
                i_for_pattern_2_ = i;
                pattern2_found_ = true;
            }
            else
            {
                //std::cout<<buff_check<<std::endl;
            }
            check_index = 0;
        }
        else
        {
            check_index++;
        }

    }
    return ((i_for_pattern_2_ - i_for_pattern_1_)/4 - 1); 
}

int compare_2_char(char a[], char b[])
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