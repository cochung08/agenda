/*--------AgendaService.h----------------
 *
 *-------------------------------------*/

#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H

#include "UserManage.h"
#include "MeetingManage.h"

class AgendaService {
private:
	UserManage *userManage;
	MeetingManage *meetingManage;

public:
	AgendaService( );
	~AgendaService();
	void Load();
	void Save();
	User* userLogIn( string userName, string password );
    //LogIn
	bool userRegister( string userName, string password, string email, string phone );
    //Register
	bool deleteUser( User user );
    //deleteUser
	list<User> listAllUsers( );
    //listAllUsers

	bool createMeeting( string userName, string title, string participator, Date stime, Date etime);
    //createMeeting
	Meeting* meetingQuery( string title );
    //meetingQuery
	list<Meeting> meetingQuery( string userName, Date stime, Date etime );
    //meetingQuery
	bool deleteMeeting( string userName, string title );
    //deleteMeeting
	bool deleteAllMeetings( string userName );
    //deleteAllMeetings
    bool updateUserPassword(User u,string newPassword);
    bool updateUserEmail(User u,string newEmail);
    bool updateUserPhone(User u,string newPhone);
    bool updateMeetingParticipator(string title,string newParticipator);
    bool updateMeetingStartDate(string title,string newStartDate);
    bool updateMeetingEndDate(string title,string newEndDate);
    bool updateMeetingTitle(string title,string newTitle);
};

#endif
