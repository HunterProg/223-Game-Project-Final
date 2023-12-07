#include <iostream>                    
#include <string>            

using namespace std;      

class invalid_choice                    
{                                       
    public:                                 
        invalid_choice()                    
        {                                   
            message = "The amount you entered is negative.";   
        }                                   

        invalid_choice(string str)          
        {                                   
            message = str;                  
        }                                  

        string what()                       
        {                                
            return message;          
        }                               

    private:                              
        string message;                    
};  
