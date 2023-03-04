#include "supportFunc.h"

int toInt(char *num){                   
        int n = 0;                      
        while(*num != '\0'){            
                n = 10 * n + *num - '0';
		num++;
        }         
	return n;                                                                                                  
}  

int isStringEqual(char *str1, char *str2){
	while(*str1 != '\0' && *str2 != '\0'){
		if(*str1 != *str2){
			return 0;
		}
		str1++;
		str2++;
	}
	return *str1 == *str2;
}
