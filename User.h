/*---User.h--------------------------
 * User definition
 *---------------------------------*/

#ifndef USER_H
#define USER_H

#include <string>
#include <list>
#include "MeetingManage.h"
#include "Meeting.h"

using std::string;
using std::list;
/*
 * define User class
 */
class User {
private:
	string name;
	string password;
	string email;
	string phone;

	MeetingManage *meetingManage; 
   

public:
	User( string n, string pw, string e, string ph );

	string getName( ) ;
	void setName( string n );

	string getPassword( ) ;
	void setPassword( string p );

	string getEmail( ) ;
	void setEmail( string e );

	string getPhone( ) ;
	void setPhone( string p );
  
	list<Meeting> getAllMeetings() ;
	list<Meeting> getAllSponsorMeetings() ;
	list<Meeting> getAllParticipateMeetings() ;

};

#endif
