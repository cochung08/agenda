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
    //实例标识 
	static MeetingManage *instance;
    //实例
	MeetingManage();

	list<Meeting> meetings;
    //会议列表 

public:
    //创建或返回实例 
	static MeetingManage *getInstance();
	~MeetingManage();
   
    //新增meeting 
	bool addMeeting( string sponspor, string participator, Date stime, Date etime, string title );
    //根据主题删除会议 
	bool deleteMeeting( string userName, string title );
	//删除用户所有会议 
	bool deleteAllMeetings( string userName );
    //更新信息 
	bool updateMeetingParticipator( string title, string newParticipator );
	bool updateMeetingStartDate( string title, Date newStartDate );
	bool updateMeetingEndDate( string title, Date newEndDate );
	bool updateMeetingTitle ( string title ,string newTitle);
    //根据主题查询会议 
	Meeting* queryMeetingByTitle( string title );
	//根据时间查询会议 
	list<Meeting> queryMeetingsByTime( string userName, Date stime, Date etime );
    //获得会议列表 
    list<Meeting> listAllMeetings( string userName ) ;
	list<Meeting> listAllSponsorMeetings( string userName ) ;
	list<Meeting> listAllParticipateMeetings( string userName ) ;
	
	bool save();
	bool load();
};

#endif
