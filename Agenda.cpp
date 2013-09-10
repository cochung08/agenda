#include "AgendaController.h"
#include<fstream>
#include <iostream>

using namespace std;

int main(){
    while(1){
    cout << "你想用批处理吗？(Y/N)" << endl;
    string choice;
    cin >> choice;
    
    if(choice == "N") break;  
    //选择N  仍进入命令的输入 
    else if( choice == "Y")  
    //选择Y   则进行批处理文本命令输入 
    {
        freopen("in.txt","r",stdin);
		freopen("out.txt","w",stdout);
		break;
    }
    //其他的视为非法输入，重新进行输入 
    else
    {
       cout << "command illegal!" << endl;
    }
    }
    
	AgendaController agendaController;   
    // 生成UI层的对象 

	agendaController.getOperation();  
     // Agenda会议系统的接口 
	

	return 0;
}
