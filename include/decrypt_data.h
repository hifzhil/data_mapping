#include <string>
#include <iostream>

namespace decrypt
{
    struct ddf_table {
        uint16_t throttle;
        uint16_t rpm;
        uint16_t injection;
    };

    struct ddf_table ddf_table;
    
    int index = 0; //buff
    int temp_rpm = 0;
    int throttle_index = 0;
    int injection_index = 0;
    int rpm_index = 0;
    char buff[4];
    typedef enum ddf_bins {
        ROW_1 = 124,
        ROW_2 = 248,
    }ddf_bins;

    void data_segmentation (std::string data, struct ddf_table *ddf_table, int cells);
}