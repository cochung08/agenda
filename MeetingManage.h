/*------MeetingManage.h--------------------
 *
 *---------------------------------------*/

#ifndef MEETINGMANAGE_H
#define MEETINGMANAGE_H

#include "Meeting.h"
#include "Date.h"
#include <list>

using std::list;

class MeetingManage {
private:
	static bool instanceFlag;
   
	static MeetingManage *instance;
 
	MeetingManage();

	list<Meeting> meetings;
  

public:
   
	static MeetingManage *getInstance();
	~MeetingManage();
   
     
	bool addMeeting( string sponspor, string participator, Date stime, Date etime, string title );
   
	bool deleteMeeting( string userName, string title );
	  
	bool deleteAllMeetings( string userName );
  
	bool updateMeetingParticipator( string title, string newParticipator );
	bool updateMeetingStartDate( string title, Date newStartDate );
	bool updateMeetingEndDate( string title, Date newEndDate );
	bool updateMeetingTitle ( string title ,string newTitle);
    
	Meeting* queryMeetingByTitle( string title );
 
	list<Meeting> queryMeetingsByTime( string userName, Date stime, Date etime );
    
    list<Meeting> listAllMeetings( string userName ) ;
	list<Meeting> listAllSponsorMeetings( string userName ) ;
	list<Meeting> listAllParticipateMeetings( string userName ) ;
	
	bool save();
	bool load();
};

#endif
