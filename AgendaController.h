/*-------AgendaControl.h---------------
 *
 *-----------------------------------*/

#ifndef AGENDACONTROLLER_H
#define AGENDACONTROLLER_H

#include <iostream>
#include "AgendaService.h"

using namespace std;

class AgendaController {
private:
	User *currentUser;
	AgendaService agendaService;

	bool executeOperation( string op );  
    //解析执行指令 

	void userLogIn( );   
    //用户登录 
	void userRegister( );
    // 用户注册 
	void userLogOut( );
    //用户登出 
	void deleteUser( );
    //删除当前用户 
	void listAllUsers( );
    //打印列出所有注册用户 
	
	void createMeeting( );
    //创建一个新的会议 
	void listAllMeetings( );
    //打印用户所有相关的会议 
	void listAllSponsorMeetings( );
    //打印所有 用户为发起者的会议 
	void listAllParticipateMeetings( );
    //打印所有 用户为参会者的会议 
	void queryMeetingByTitle( );
    //根据Title查询用户会议 
	void queryMeetingByTimeInterval( );
    //根据时间查询用户会议 
	void deleteMeetingByTitle( );
    //根据Title删除会议 
	void deleteAllMeetings( );
    //删除所有 用户作为发起者的会议 

	void printMeetings( list<Meeting> meetings );
    //打印会议 
	void updateUserPassword();
	void updateUserEmail();
	void updateUserPhone();
	void updateMeetingParticipator();
	void updateMeetingStartDate();
	void updateMeetingEndDate();
	void updateMeetingTitle();


public:
	AgendaController( );
    //默认构造函数 
	void getOperation( );
    //接口 

};

#endif
