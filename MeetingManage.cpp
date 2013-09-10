#include "MeetingManage.h"
#include <fstream>
#include <iostream>
bool MeetingManage::instanceFlag = false;
MeetingManage* MeetingManage::instance = NULL;
using namespace std;

//只实例化一个，即如果已经创建了对象就返回该对象 
MeetingManage* MeetingManage::getInstance()
    {
        if(instanceFlag)
           return instance;
        else
          {
             instance = new MeetingManage();
             instanceFlag = true;
             return instance;
          }   
    }
    
    MeetingManage::MeetingManage()
    {          
    }
  
	MeetingManage::~MeetingManage()
	{
     //已经初始化实例的话，析构把标识重置并删除实例 
       if(instanceFlag == true)
       {
        instanceFlag = false;
        delete instance;
       }
    }
 //新加一个会议 
	bool MeetingManage::addMeeting( string sponsor, string participator, Date stime, Date etime, string title )
	{
        list<Meeting>::iterator it;
        //时间不合法，加入无效 
		if((!Date::isValid(stime))||(!Date::isValid(etime))||stime>=etime)
           return false;
	
   
    //会议主题冲突，加入无效 
    for(it = meetings.begin(); it != meetings.end();it++){
       if( (*it).getTitle() == title )
            return false;

    //发起者时间冲突，加入无效 
        if(((*it).getParticipator() == participator) && (!((*it).getStartDate()>etime || (*it).getEndDate() < stime))  )
           return false;
    //与受邀者时间冲突，加入无效 
        if(((*it).getSponsor() == sponsor) && (!((*it).getStartDate()>etime || (*it).getEndDate() < stime)))
           return false;
	
    }
    //创建会议并加入 
        Meeting newMeeting(sponsor,participator,stime,etime,title);
        meetings.push_back(newMeeting);
        return true; 
    }
 // 根据主题删除会议 
	bool MeetingManage::deleteMeeting( string userName, string title )
	{
        
        list<Meeting>::iterator it;
        //如果找到发起者名字的指定主题会议，则删除 
        for(it = meetings.begin();it != meetings.end(); it++){ 
            if(((*it).getSponsor() == userName) && ((*it).getTitle() == title)){
                meetings.erase(it);
                return true;
            }
        }
        return false;
    }  
    //删除用户所有会议 
	bool MeetingManage::deleteAllMeetings( string userName )
	{
        //如果找到发起者的名字，则删除所有他发起的会议 
        list<Meeting>::iterator it;
        int ok = 0;
        for(it = meetings.begin();it!=meetings.end();){
           if((*it).getSponsor()==userName){
               it = meetings.erase(it);
               ok++;
            }
           else
              it++;        
        }
        if(ok)  return true;
        else    return false;
    }
    
    
    
  //更新信息 
	bool MeetingManage::updateMeetingParticipator( string title, string newParticipator )
	{
       list<Meeting>::iterator it;
       //根据指定主题更新会议的受邀者信息 
    for(it = meetings.begin(); it != meetings.end();it++){

    //发起者时间冲突，加入无效 
        if(((*it).getParticipator() == newParticipator) && (!(    (*it).getStartDate()   > queryMeetingByTitle(title)->getEndDate()     ||    (*it).getEndDate() < queryMeetingByTitle(title)->getStartDate()   )) )
           return false;
    //与受邀者时间冲突，加入无效 
        if(((*it).getSponsor() == newParticipator) && (!((*it).getStartDate()>queryMeetingByTitle(title)->getEndDate()  || (*it).getEndDate() < queryMeetingByTitle(title)->getStartDate())))
           return false;
     }
          
       for(it = meetings.begin();it != meetings.end();it++){
            if((*it).getTitle() == title){            
               (*it).setParticipator(newParticipator);
               return true;
            }
        }
        return false;           
    }
	
	bool MeetingManage::updateMeetingStartDate( string title, Date newStartDate )
	{
       list<Meeting>::iterator it;
       //根据指定主题更新会议的开始日期 
       for(it = meetings.begin();it != meetings.end();it++){
            if((*it).getTitle() == title){
               (*it).setStartDate(newStartDate);
               return true;
            }
        }
        return false;           
    }
    
	bool MeetingManage::updateMeetingEndDate( string title, Date newEndDate )
	{
       list<Meeting>::iterator it;
       //根据指定主题更新会议的结束日期 
       for(it = meetings.begin();it != meetings.end();it++){
            if((*it).getTitle() == title){
               (*it).setEndDate(newEndDate);
               return true;
            }
        }
        return false;           
    }
    
    bool MeetingManage::updateMeetingTitle ( string title ,string newTitle)
    {
        list<Meeting>::iterator it;

       for(it = meetings.begin();it != meetings.end();it++){
            if((*it).getTitle() == title){
               (*it).setTitle(newTitle);
               return true;
            }
        }
        return false;      
    }

	Meeting* MeetingManage::queryMeetingByTitle( string title )
	{
       list<Meeting>::iterator it;
       //根据指定主题查询会议 
       for(it = meetings.begin();it != meetings.end();it++){
            if((*it).getTitle() == title)
                         return &(*it);
       }
       return NULL;
    }
    
	list<Meeting> MeetingManage::queryMeetingsByTime( string userName, Date stime, Date etime )
	{ 
             list<Meeting> MeetingBytime;
             list<Meeting>::iterator it;
             //根据参会者名字，开始时间，结束时间，找出时间内的所有会议 
             for(it = meetings.begin();it != meetings.end();it++){
                 if((((*it).getSponsor() == userName)||((*it).getParticipator() == userName))&&!((*it).getStartDate()>=etime || (*it).getEndDate() <= stime))
                     MeetingBytime.push_back(*it);
            }
            if(stime>=etime)
            MeetingBytime.clear();
            return MeetingBytime;
    }

    list<Meeting> MeetingManage::listAllMeetings( string userName ) 
    {
        list <Meeting> AllMeetings;
        list<Meeting>::iterator it;
        //根据名字列出所有会议 
             for(it = meetings.begin();it != meetings.end();it++){
                    if(((*it).getSponsor() == userName)||((*it).getParticipator() == userName))
                            AllMeetings.push_back(*it);
             }
        return AllMeetings;
    }
    
	list<Meeting> MeetingManage::listAllSponsorMeetings( string userName ) 
	{
        list<Meeting> AllSponsorMeetings;
        list<Meeting>::iterator it;
        //根据名字列出他所有发起的会议 
             for(it = meetings.begin();it != meetings.end();it++){
                    if((*it).getSponsor() == userName)
                       AllSponsorMeetings.push_back(*it);
            }
        return AllSponsorMeetings;
    }
    
	list<Meeting> MeetingManage::listAllParticipateMeetings( string userName ) 
	{
        list<Meeting> AllParticipatorMeetings;
        list<Meeting>::iterator it;
        //根据名字列出他所有参加的会议     
             for(it = meetings.begin();it != meetings.end();it++){
                    if((*it).getParticipator() == userName)
                       AllParticipatorMeetings.push_back(*it);
            }
        return AllParticipatorMeetings;
    }


bool MeetingManage::load(){
	ifstream infile;
	infile.open("meetings.txt",ios::in);
	
	if(!infile.is_open()){
		return false;
	}

	string sponsor ,participator,stime,etime,title;

	while(infile>>sponsor>>participator>>stime>>etime>>title){

			addMeeting(sponsor,participator,Date::convertStringToDate(stime),Date::convertStringToDate(etime),title);
	}
	infile.close();
	return true;

}

bool MeetingManage::save(){
	ofstream outfile;
	outfile.open("meetings.txt",ios::out);
	
	if(outfile)
	{
		for(list<Meeting>::iterator it=meetings.begin();it!=meetings.end();it++){
			outfile << it->getSponsor()<<' '<<it->getParticipator()<<' '<<Date::convertDateToString(it->getStartDate())<<' '<<Date::convertDateToString(it->getEndDate())<<' '<<it->getTitle()<<endl;
		}

		outfile.close();
		return true;
	}
	else{
		return false;
	}
}
