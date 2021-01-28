#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

static int newreadRawVarint32(char* buf); 
static int readRawVarint32(char* buf);
void printCount(char* buf);
static void writeRawVarint32(int value);
static int computeRawVarint32Size(int value);


typedef signed char byte;


int main(){
	
	//char buf[5];
        char buf[] = {0xa1, 5, 8, 2, 0x1a, 0x9c, 5, 0xa, 0xa3, 1, 78,};
	int length =  newreadRawVarint32(buf);

        printf("buf[0] %x\n",buf[0]);
        printf("buf[1] %x\n",buf[1]);
        printf("length %d\n",length);

	int len = 1;
        writeRawVarint32(length);
        int changdu  = computeRawVarint32Size(length); 
        printf("changdu %d\n",changdu);
	
}


static void writeRawVarint32(int value) {
        char out;
        while((value & -128) != 0) {
            out = value & 127 |128;
	    printf("value & 127 |128 %x\n",out);
            value = value >>7;
	    printf("value>>>=7 %x\n",value);
        }
        char out_last = (char)value;
        printf("out_last %x\n",value);
    }

    static int computeRawVarint32Size(int value) {
        if ((value & -128) == 0) {
            return 1;
        } else if ((value & -16384) == 0) {
            return 2;
        } else if ((value & -2097152) == 0) {
            return 3;
        } else {
            return (value & -268435456) == 0 ? 4 : 5;
        }
    }




static int newreadRawVarint32(char* buf) {
	char lenchars[5];
        byte tmp;
        if (buf[0] == 0) {
            return 0;
        } else {
             tmp = buf[0];
            if (tmp >= 0) {
                return tmp;
            } else {
	   	 
                int result = tmp & 127;
                if (buf[1] == 0) {
	    	   
                    return 0;
                } else {
	    	    
                    if ((tmp = buf[1]) >= 0) {
	    	        
                        result |= tmp << 7;
                    } else {
	    		
                        result |= (tmp & 127) << 7;
                        if (buf[2] == 0) {
	    		    
                            return 0;
                        }

                        if ((tmp = buf[2]) >= 0) {
	                    
                            result |= tmp << 14;
                        } else {
	                    
                            result |= (tmp & 127) << 14;
                            if (buf[3] == 0) {
	                        
                                return 0;
                            }

                            if ((tmp = buf[3]) >= 0) {
	                        
                                result |= tmp << 21;
                            } else {
	                        
                                result |= (tmp & 0) << 21;
                                if ((tmp = buf[4]) == 0) {
	                   
                                    return 0;
                                }

                                result |= (tmp = buf[4]) << 28;
                                if (tmp < 0) {
				   return 0;
                                }
                            }
                        }
                    }

                    return result;
                }
            }
        }
    }
static int readRawVarint32(char* buf) {
	char lenchars[5];
        byte tmp;
        if (buf[0] == 0) {
	    printf("buf[0] = 0\n");
            return 0;
        } else {
	    printf("buf[0] > 0\n");
             tmp = buf[0];
            if (tmp >= 0) {
	    	printf("temp>=0\n");
                return tmp;
            } else {
	   	 printf("tmp <= 0\n");
                int result = tmp & 127;
                if (buf[1] == 0) {
	    	    printf("buf[1] == 0\n");
                    return 0;
                } else {
	    	    printf("buf[1] != 0\n");
                    if ((tmp = buf[1]) >= 0) {
	    	        printf("buf[1] >= 0\n");
                        result |= tmp << 7;
                    } else {
	    		printf("buf[1] <  0\n");
                        result |= (tmp & 127) << 7;
                        if (buf[2] == 0) {
	    		    printf("buf[0] == 0");
                            return 0;
                        }

                        if ((tmp = buf[2]) >= 0) {
	                    printf("buf[2] >= 0");
                            result |= tmp << 14;
                        } else {
	                    printf("buf[2] < 0");
                            result |= (tmp & 127) << 14;
                            if (buf[3] == 0) {
	                        printf("buf[0] == 0");
                                return 0;
                            }

                            if ((tmp = buf[3]) >= 0) {
	                        printf("buf[3] >= 0");
                                result |= tmp << 21;
                            } else {
	                        printf("buf[3] < 0");
                                result |= (tmp & 0) << 21;
                                if ((tmp = buf[4]) == 0) {
	                         printf("buf[4] == 0");
                                    return 0;
                                }

                                result |= (tmp = buf[4]) << 28;
                                if (tmp < 0) {
				   return 0;
                                }
                            }
                        }
                    }

                    return result;
                }
            }
        }
    }
  


void printCount(char* buf){
	int count;
	int i;
	for(i = 0; i< 1024;i++){
		if(buf[i] != 0){
			count++;
		}

	}
	printf("count: %d\n", count);

}





