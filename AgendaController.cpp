/*-------AgendaControl.cpp---------------
 *
 *-----------------------------------*/


#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include "AgendaController.h"

using namespace std;
using std::list;

   //解析输入 
	bool AgendaController::executeOperation( string op )
	{
             if(op == "q")       return 0;   
             // q命令退出系统 
		else if(op == "r")       userRegister();
		else if(op == "l")       userLogIn();
        else if ( op == "o" )    userLogOut();
	    else if ( op == "dc" )   deleteUser();
	    else if ( op == "lu" )	 listAllUsers();
	    else if ( op == "cm" )   createMeeting();
	    else if ( op == "la" )   listAllMeetings();
	    else if ( op == "las" )  listAllSponsorMeetings();
	    else if ( op == "lap" )  listAllParticipateMeetings();
	    else if ( op == "qm" )   queryMeetingByTitle();
	    else if ( op == "qt" )   queryMeetingByTimeInterval();
	    else if ( op == "dm" )   deleteMeetingByTitle();
	    else if ( op == "da" )   deleteAllMeetings();
        else if ( op == "uup")   updateUserPassword();
        else if ( op == "uue")   updateUserEmail();
        else if ( op == "uuph")  updateUserPhone();
        else if ( op == "ump" )	 updateMeetingParticipator();
        else if ( op == "ums")   updateMeetingStartDate();
        else if ( op == "ume" )	 updateMeetingEndDate();
        else if ( op == "umt")   updateMeetingTitle();
		else{
			cout << "[error] command illegal\n";
			getOperation();
	    // 如果不是以上命令，则默认为非法输入，无效，重新获得菜单输入 
		}
	}
   //用户登录 
	void AgendaController::userLogIn( )
	{
       //如果已经登录，则该命令无效，重新获得菜单输入 
       if(currentUser != NULL) 
       {
           cout << "[error] command illegal\n";
           getOperation();  
       }
       
       else
       { 
         //打印提示 
          cout << "[log in] [user name] [password]\n";
	      cout << "[log in] ";
          
          string username,password;
          cin >> username >> password;

         //登录失败 
          if((currentUser = agendaService.userLogIn(username,password)) == NULL)
		  {
            printf("[error] log in fail!\n");
			getOperation();
		  }
		  //登录成功 
          else
          {
            printf("[log in] succeed!\n"); 
            cout<<"----------------------- Agenda -------------------------------\n"
				<<"Action :                                                      \n"
				<<"o   - log out Agenda account                                  \n"
				<<"dc  - delete Agenda account                                   \n"
				<<"lu  - list all Agenda user                                    \n"
				<<"cm  - create a meeting                                        \n"
				<<"la  - list all meetings                                       \n"
				<<"las - list all sponsor meetings                               \n"
				<<"lap - list all participate meetings                           \n"
				<<"qm  - query meeting by title                                  \n"
				<<"qt  - query meeting by time interval                          \n"
				<<"dm  - delete meeting by title                                 \n"
				<<"da  - delete all meetings                                     \n"
				<<"uup - update user password                                    \n"
				<<"uue - update user email                                       \n"
				<<"uuph - update user phone                                      \n"
				<<"ump - update meeting participator                             \n"
				<<"ums - update meeting startDate                                \n"
				<<"ume - update meeting endDate                                  \n"
				<<"umt - uodate meeting title                                    \n"
				<<"-----------------------------------------------------------\n\n";
			//获得登录进去了的界面菜单 
            getOperation();
        }  
      }
    }
    
	void AgendaController::userRegister( )
	{  
       //如果已经登录，则该命令无效，重新获得菜单输入
        if(currentUser != NULL) 
        {
              cout << "[error] command illegal\n";
              getOperation();  
        }
        //未登录 
        else{
            
             cout << "[register] [user name] [password] [email] [phone]\n";
	         cout << "[register] ";
             
             string username,password,email,phone;
             cin >> username >> password >> email >> phone;
       
         // 注册成功 
            if(agendaService.userRegister(username,password,email,phone))
            {
               printf("[register] succeed!\n");
               getOperation();
            }
        // 注册失败 
            else
            {
               printf("register fail\n");
               getOperation();
            }
        }
    }
    
    //登出 
	void AgendaController::userLogOut( )
	{
      
       if(currentUser!=NULL)
       {
          currentUser = NULL;  //把当前用户指针设为空 
          getOperation();
       }
       //如果未登录，则该命令无效，重新获得菜单输入
       else
       {
              cout << "[error] command illegal\n";
              getOperation();                
       }
    }
    
    void AgendaController::deleteUser(){
        
	if(currentUser!=NULL){
        //删除成功 
		    if(agendaService.deleteUser(*currentUser)){
			   cout<<endl;
			   cout<<"[delete agenda account] succeed!"<<endl;
			   userLogOut();  //删除成功同时还要执行登出操作 
		    }
		//删除失败   
		   else{
		      cout<<"\n[error] delete agenda account fail!"<<endl;
			  getOperation();
		    }
	}
	////如果未登录，则该命令无效，重新获得菜单输入 
	else{
              cout << "[error] command illegal\n";
              getOperation(); 
	}
}
    
	void AgendaController::listAllUsers()
	{
        if(currentUser!=NULL)
       {
          list <User> userslist;
          list <User>::iterator it;
          userslist = agendaService.listAllUsers();//通过Service层赋值User列表 
         //打印标头     
          printf("\n");
          printf("[list all users]\n");
          cout<<left<<setw(8)<<"name"<<setw(17)<<"email"<<setw(11)<<"phone"<<endl;
         //打印列表 
          for(it = userslist.begin();it!=userslist.end();it++)
            cout<<left<<setw(8)<<it->getName()<<setw(17)<<it->getEmail()<<setw(11)<<it->getPhone()<<endl;
     
          getOperation();
    }
    //如果未登录，则该命令无效，重新获得菜单输入
    else
    {
              cout << "[error] command illegal\n";
              getOperation();         
    }
   }
	
    void AgendaController::createMeeting( ){
	
       if(currentUser!=NULL){
	          cout<<endl;
		      cout<<"[create meeting] [title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<'\n'
		          <<"[create meeting] ";
	
	    string title,participator,stime,etime;
	    
	    cin>>title>>participator>>stime>>etime;

		UserManage *userManage = UserManage::getInstance();
       //参会者存在该用户的话 
		if((userManage->findUserByName(participator)) != NULL){
            
            //成功create  
		      if(agendaService.createMeeting(currentUser->getName(),title,participator,Date::convertStringToDate(stime),Date::convertStringToDate(etime)))
	         {
			    cout<<"[create meeting] succeed!"<<endl;
			    getOperation();
		     }
		     //create失败 
		     else{
			    cout<<"[error] create meeting fail!"<<endl;
			    getOperation();
		    }
		}
		//不存在该用户，create无效 
		else{
		    	cout<<"[error] create meeting fail!"<<endl;
			    getOperation();
		   }
			
		}
		//如果未登录，则该命令无效，重新获得菜单输入
	   else{
              cout << "[error] command illegal\n";
              getOperation(); 
	    }
   }

   //打印所有相关会议 
	void AgendaController::listAllMeetings( )
	{
     	if(currentUser!=NULL){
		   cout<<endl;
		   //打印标头 
		   cout<<"[list all meetings]"<<endl<<endl;
		   cout<<left<<setw(13)<<"title"<<setw(13)<<"sponsor"<<setw(17)<<"participator"
			   <<setw(17)<<"start time"<<setw(17)<<"end time"<<endl;   
		   
           MeetingManage* m = MeetingManage::getInstance();
           list<Meeting> meetings;
		   meetings = m->listAllMeetings( currentUser->getName());
		   printMeetings(meetings);
		   //打印Meeting列表 
		   
		   getOperation();
       }	
       //如果未登录，则该命令无效，重新获得菜单输入
       else
       {
              cout << "[error] command illegal\n";
              getOperation(); 
        }
    }
    //打印所有发起者列表 
	void AgendaController::listAllSponsorMeetings( )
	{
        if(currentUser!=NULL){
	 	  cout<<endl;
	 	  //打印标头 
		  cout<<"[list all sponsor meetings]"<<endl<<endl;
		  cout<<left<<setw(13)<<"title"<<setw(13)<<"sponsor"<<setw(17)<<"participator"
			  <<setw(17)<<"start time"<<setw(17)<<"end time"<<endl;
			  
           MeetingManage* m = MeetingManage::getInstance();
           list<Meeting> meetings;
		   meetings = m->listAllSponsorMeetings( currentUser->getName());
		   printMeetings(meetings);
		   //打印发起者Meeting列表 
		   getOperation();
        }
        //如果未登录，则该命令无效，重新获得菜单输入
        else
        {
              cout << "[error] command illegal\n";
              getOperation(); 
        }
    }
    //打印参会者Meeting列表 
	void AgendaController::listAllParticipateMeetings( )
    {
     	if(currentUser!=NULL){
		  cout<<endl;
		  //打印标头 
		  cout<<"[list all participate meetings]"<<endl<<endl;
		  cout<<left<<setw(13)<<"title"<<setw(13)<<"sponsor"<<setw(17)<<"participator"
			  <<setw(17)<<"start time"<<setw(17)<<"end time"<<endl;
			  
           MeetingManage* m = MeetingManage::getInstance();
           list<Meeting> meetings;
		   meetings = m->listAllParticipateMeetings( currentUser->getName());
		   printMeetings(meetings);
           //打印参会者Meeting列表 
           getOperation(); 
        }   
        //如果未登录，则该命令无效，重新获得菜单输入        
        else
        {
              cout << "[error] command illegal\n";
              getOperation();    
        }     
    }
    //根据Title查询会议 
	void AgendaController::queryMeetingByTitle( )
	{
       	if(currentUser!=NULL){
		   cout<<endl;
		   cout<<"[query meeting] [title]:"<<endl;
		   cout<<"[query meeting] ";
		   
		   string title;
		   cin >> title;
		   
		   cout<<left<<setw(15)<<"sponsor"<<setw(15)<<"participator"
			   <<setw(25)<<"start time"<<setw(25)<<"end time";
			   
		   Meeting* meeting = NULL;
		 //存在Title会议的话 
		  if( (meeting = agendaService.meetingQuery(title) ) != NULL ){
            
			cout<<left<<setw(15)<<meeting->getSponsor()<<setw(15)<<meeting->getParticipator()
				<<setw(25)<<Date::convertDateToString(meeting->getStartDate())<<setw(25)
				<<Date::convertDateToString(meeting->getEndDate())<<endl;
		  		
			getOperation();
           }
           //没有该Title会议的话 
           else
           {cout << endl << endl;}
           
           getOperation();
       }
       //如果未登录，则该命令无效，重新获得菜单输入
       else
       {
              cout << "[error] command illegal\n";
              getOperation();     
        }
			             
    }
    //根据时间查询会议 
	void AgendaController::queryMeetingByTimeInterval( )
	{
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
		    cout<<"[query meetings] ";  
		    
		string stime,etime;
		
		cin>>stime>>etime;
		//输入时间不合法
		if(stime>etime||stime==etime)
			{cout << "[checked date illegal]!"<<endl;
		     getOperation();
		     }
      
		else
		{
		cout<<endl<<"[query meetings]"<<endl;
		cout<<left<<setw(13)<<"title"<<setw(13)<<"sponsor"<<setw(17)<<"participator"
			<<setw(17)<<"start time"<<setw(17)<<"end time"<<endl;
		//打印会议列表 
        printMeetings(agendaService.meetingQuery(currentUser->getName(),Date::convertStringToDate(stime),Date::convertStringToDate(etime)));
        getOperation();
        }
	   }
	   //如果未登录，则该命令无效，重新获得菜单输入
       else
       {
              cout << "[error] command illegal\n";
              getOperation();     
        }
    }
    //根据Title删除会议 
	void AgendaController::deleteMeetingByTitle()
	{
     	if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[delete meeting] [title]"<<'\n'
			    <<"[delete meeting] ";

		    string title;
		    cin>>title;
            //删除成功 
            if( agendaService.deleteMeeting(currentUser->getName(),title) ){
			      cout<<endl<<"[delete meeting by title] succeed!"<<endl;
                  getOperation();			
		     }
		     //删除失败 
		    else{
			      cout<<endl<<"[error] delete meeting fail!"<<endl;
			      getOperation();
		     }
		
	    }
	    //如果未登录，则该命令无效，重新获得菜单输入
	   else{
		      cout << "[error] command illegal\n";
              getOperation(); 
       }  
    }
    //删除所有会议 
	void AgendaController::deleteAllMeetings()
	{
        if(currentUser != NULL){
		      cout<<endl;
		 //删除成功 
		   if( agendaService.deleteAllMeetings(currentUser->getName()) ){
			  cout<<"[delete all meetings] succeed!"<<endl;
			  getOperation();
		   }
		 //删除失败 
		   else{
		     cout << endl << "[error] delete all meetings fail!" << endl;
		     getOperation();
           }
	    }
	    //如果未登录，则该命令无效，重新获得菜单输入
	    else
	       {
              cout << "[error] command illegal\n";
              getOperation();     
            }
    }

	void AgendaController::printMeetings( list<Meeting> meetings )
	{
        //列表为空 
        if(meetings.empty())
        {
           cout << endl;    
        }
        //列表不为空 
        else
        {   
            list<Meeting>::iterator it;
            for(it = meetings.begin();it != meetings.end();it++)
           {
			  // 打印 
			    cout<<left<<setw(13)<<it->getTitle()<<setw(13)<<it->getSponsor()<<setw(17)<<it->getParticipator()
				    <<setw(17)<<Date::convertDateToString(it->getStartDate())<<setw(17)
				    <<Date::convertDateToString(it->getEndDate())<<endl;   
           }
        }
    }
	
	AgendaController::AgendaController( )
	{
        currentUser = NULL;
    }
    
    //获得菜单输入 
	void AgendaController::getOperation( )
    {
         if(currentUser == NULL){
               	cout << "\n-------------------------Agenda-----------------------------\n";
	            cout << "Action:\n";
	            cout << "l   - log in Agenada by user name and password\n";
	            cout << "r   - register an Agenda account\n";
	            cout << "q   - quit Agenda\n";
	            cout << "--------------------------------------------------------------\n";
	            cout << "\nAgenda : ~$ ";
        }  
        else
        {
                cout << endl << "Agenda@" <<currentUser->getName()<<" : # "; 
        }
         
        string input;
		input = "";
        cin >> input;
        if(input == ""){
        	cin.clear();
			cin.rdstate();
			cin.fixed;
			fclose(stdin);
			fclose(stdout);
        } 
        //输入指令 
        executeOperation(input);
        //解析命令 

    }
    
    
    void AgendaController::updateUserPassword()
    {
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[update user] [password]"<<'\n'
			    <<"[update user] ";
			    
			string password;
			cin >> password;
			
			if(agendaService.updateUserPassword(*currentUser,password))
			{
               cout << "update password succeed!"<< endl;
               getOperation();
            }
            else
            {
                cout << "[error] update password fail!" << endl;
                getOperation();    
            } 
            
        }
        else
        {
              cout << "[error] command illegal\n";
              getOperation();     
        }  
    }
    
    void AgendaController::updateUserEmail()
    {
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[update user] [email]"<<'\n'
			    <<"[update user] ";
			    
			string Email;
			cin >> Email;
			
			if(agendaService.updateUserEmail(*currentUser,Email))
			{
               cout << "update email succeed!"<< endl;
               getOperation();
            }
            else
            {
                cout << "[error] update email fail!" << endl;
                getOperation();    
            } 
            
        }
        else
        {
              cout << "[error] command illegal\n";
              getOperation();     
        }  
    }
    void AgendaController::updateUserPhone()
    {
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[update user] [phone]"<<'\n'
			    <<"[update user] ";
			    
			string phone;
			cin >> phone;
			
			if(agendaService.updateUserPhone(*currentUser,phone))
			{
               cout << "update phone succeed!"<< endl;
               getOperation();
            }
            else
            {
                cout << "[error] update phone fail!" << endl;
                getOperation();    
            } 
            
        }
        else
        {
              cout << "[error] command illegal\n";
              getOperation();     
        }  
    }
    
    void AgendaController::updateMeetingParticipator()
    {
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[update meeting] [title] [participator]"<<'\n'
			    <<"[update meeting] "; 
                
            string participator,title;
            cin >> title >> participator;
                      
        if(agendaService.meetingQuery (title )!=NULL)
		{
        UserManage *userManage = UserManage::getInstance();          
       //参会者存在该用户的话 
		if((userManage->findUserByName(participator)) != NULL){
            
        if(agendaService.updateMeetingParticipator(title,participator))
		{
               cout << "update participator succeed!"<< endl;
               getOperation();
          }
            else
            {
                cout << "[error] update participator fail!" << endl;
                getOperation();    
            } 
            
        }
        else
        {
                cout << "[error] update participator fail!" << endl;
                getOperation();   
        }
		}
		else
		{
                cout << "[error] unavailable meeting!" << endl;
                getOperation();    
        } 
		}
      else
        {
              cout << "[error] command illegal\n";
              getOperation();    
        } 
             
           

    }
      
  
    
    void AgendaController::updateMeetingStartDate()
    {
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[update meeting] [title] [statrDate]"<<'\n'
			    <<"[update meeting] "; 
                
            string title,startDate;
            cin >> title >> startDate;
         
		   if(agendaService.meetingQuery (title )!=NULL)
		{
         
        if(Date::isValid(Date::convertStringToDate(startDate))&& Date::convertStringToDate(startDate)<(agendaService.meetingQuery(title))->getEndDate())
        {  
            list <Meeting> smeeting;
            list <Meeting> pmeeting;
            MeetingManage *meetingManage = MeetingManage::getInstance();


             pmeeting = agendaService.meetingQuery((meetingManage->queryMeetingByTitle(title))->getParticipator(),Date::convertStringToDate(startDate),(agendaService.meetingQuery(title))->getStartDate());
                            
            smeeting = agendaService.meetingQuery(currentUser->getName(),Date::convertStringToDate(startDate),(agendaService.meetingQuery(title))->getStartDate());


            if(smeeting.empty()&&pmeeting.empty())               
        {
                        
            if(agendaService.updateMeetingStartDate(title,startDate)){
                  cout << "update startDate succeed!"<< endl;
               getOperation();
            } 
            else
            {
                cout << "[error] update startDate fail!" << endl;
                getOperation();    
            } 
           
        }
        else
        {
                cout << "[error] update startDate fail!" << endl;
                getOperation();       
        }   
            
        }
        
        else
        {
                cout << "[error] update startDate fail!" << endl;
                getOperation();  
        }
		 }
		 else
        {
                cout << "[error] unavailable meeting!" << endl;
                getOperation();  
        }

        } //end if
        else
        {
              cout << "[error] command illegal\n";
              getOperation();     
        }  
    }
    
    
    
    
    
    
    void AgendaController::updateMeetingEndDate()
    {
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[update meeting] [title] [endDate]"<<'\n'
			    <<"[update meeting] "; 
                
            string title,endDate;
            cin >> title >> endDate;
          
		  if(agendaService.meetingQuery (title )!=NULL)
		{   
        if(Date::isValid(Date::convertStringToDate(endDate))&&Date::convertStringToDate(endDate)>(agendaService.meetingQuery(title))->getStartDate())
        {  
            list <Meeting> smeeting;
            list <Meeting> pmeeting;
            MeetingManage *meetingManage = MeetingManage::getInstance();

             pmeeting = agendaService.meetingQuery((meetingManage->queryMeetingByTitle(title))->getParticipator(),(agendaService.meetingQuery(title))->getEndDate(),Date::convertStringToDate(endDate));
                            
             smeeting = agendaService.meetingQuery(currentUser->getName(),(agendaService.meetingQuery(title))->getEndDate(),Date::convertStringToDate(endDate));
            if(smeeting.empty()&&pmeeting.empty())               
        {
            
            
            
            if(agendaService.updateMeetingStartDate(title,endDate)){
                  cout << "update endDate succeed!"<< endl;
               getOperation();
            } 
            else
            {
                cout << "[error] update endDate fail!" << endl;
                getOperation();    
            } 
           
        }
        else
        {
                cout << "[error] update endDate fail!" << endl;
                getOperation();       
        }   
            
        }
        
        else
        {
                cout << "[error] update endDate fail!" << endl;
                getOperation();  
        }
             
		  }
		  else
	    {
              cout << "[error] unavailable meeting!";
              getOperation();     
        }  

		}//end if
        else
        {
              cout << "[error] command illegal\n";
              getOperation();     
        }  
    }
       
    void AgendaController::updateMeetingTitle()
    {
        if(currentUser != NULL){
		    cout<<endl;
		    cout<<"[update meeting] [title] [newTitle]"<<'\n'
			    <<"[update meeting] "; 
                
            string title,newtitle;
            cin >> title >> newtitle;

		  if(agendaService.meetingQuery (title )!=NULL)
		{   
            
        if(agendaService.updateMeetingTitle(title,newtitle))
		{
               cout << "update title succeed!"<< endl;
               getOperation();
           }
            else
            {
                cout << "[error] update title fail!" << endl;
                getOperation();    
            } 
            
        }
		  else
	   {
              cout << "[error] unavailable meeting!";
              getOperation();     
        }  

		}
        else
        {
              cout << "[error] command illegal\n";
              getOperation();     
        }  
    }    
