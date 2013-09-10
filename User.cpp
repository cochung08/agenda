/*---User.cpp--------------------------
 * 
 *---------------------------------*/

#include "User.h"

User::User(string n, string pw, string e, string ph){
	setName( n );
	setPassword( pw );
	setEmail( e );
	setPhone( ph );
	meetingManage = MeetingManage::getInstance();
}

string User::getName( ) {
	return name;
}

void User::setName( string n ){
	name = n;
}

string User::getPassword( ) {
	return password;
}

void User::setPassword( string p ){
	password = p;
}

string User::getEmail( ) {
	return email;
}

void User::setEmail( string e ){
	email = e;
}

string User::getPhone( ) {
	return phone;
}

void User::setPhone( string p ){
	phone = p;
}
//获得用户会议列表 
list<Meeting> User::getAllMeetings() {
	return (*meetingManage).listAllMeetings(name);
}

list<Meeting> User::getAllSponsorMeetings() {
	return (*meetingManage).listAllSponsorMeetings(name);
}

list<Meeting> User::getAllParticipateMeetings() {
	return (*meetingManage).listAllParticipateMeetings(name);
}

