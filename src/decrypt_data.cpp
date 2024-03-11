
namespace decrypt
{
    void data_segmentation (std::string data, struct ddf_table *ddf_table, int cells)
    {
        switch (a)
            {
            case 1:
                for (int i = 0 ; i < (cells + 1)*4; i++)
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
                for (int i = ROW_2 ; i < ROW_2 + (std::pow(cells, 2) + 1)*4 ; i++)
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
}