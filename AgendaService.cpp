#include"AgendaService.h"

  
    AgendaService::AgendaService( )
    {
        userManage = UserManage::getInstance();
        meetingManage = MeetingManage::getInstance();
        Load();
    }
 
    AgendaService::~AgendaService()
    {
        Save(); 
    } 
    
    void AgendaService::Load()
    {
        userManage->load();
        meetingManage->load();
    }
    
    void AgendaService::Save()
    {
        userManage->save();
        meetingManage->save();
    }
    
   
	User* AgendaService::userLogIn( string userName, string password )
	{
        User *u;
        
        if((u = userManage->findUserByName(userName))!=NULL && u->getPassword() == password)
              return u;
    
        else
              return NULL;
        
    }
    
	bool AgendaService::userRegister( string userName, string password, string email, string phone )
	{ 
          return userManage->createUser(userName,password,email,phone);        
    }

    // deleteUser
    bool AgendaService::deleteUser(User user)
    {
        return userManage->deleteUser(user);
    }
    //listAllUsers
	list<User> AgendaService::listAllUsers( )
	{
        return userManage->listAllUsers();
    }
    //createMeeting
	bool AgendaService::createMeeting( string userName, string title, string participator, Date stime, Date etime)
	{
        return meetingManage->addMeeting(userName,participator,stime,etime,title);
    }
    //meetingQuery
	Meeting* AgendaService::meetingQuery( string title )
	{
        return meetingManage->queryMeetingByTitle(title);
    }
    //meetingQuery
	list<Meeting> AgendaService::meetingQuery( string userName, Date stime, Date etime )
	{
        return meetingManage->queryMeetingsByTime(userName,stime,etime);
    }
	//deleteMeeting
	bool AgendaService::deleteMeeting( string userName, string title )
	{
        return meetingManage->deleteMeeting(userName,title);
    }
    //deleteAllMeetings
	bool AgendaService::deleteAllMeetings( string userName )
	{
        return meetingManage->deleteAllMeetings(userName);   
    }
    
    bool AgendaService::updateUserPassword(User u,string newPassword)
    {
        return userManage->updateUserPassword(u,newPassword);
     }
     
    bool AgendaService::updateUserEmail(User u,string newEmail)
    {
        return userManage->updateUserEmail(u,newEmail);
    }
    
    bool AgendaService::updateUserPhone(User u,string newPhone)
    {
        return userManage->updateUserPhone(u,newPhone);
    }
    
    bool AgendaService::updateMeetingParticipator(string title,string newParticipator)
    {
         return meetingManage->updateMeetingParticipator(title,newParticipator);    
    }
    
    bool AgendaService::updateMeetingStartDate(string title,string newStartDate)
    {   
        
         return meetingManage->updateMeetingStartDate(title,Date::convertStringToDate(newStartDate));    
    }
    
    bool AgendaService::updateMeetingEndDate(string title,string newEndDate)
    {
        return meetingManage->updateMeetingEndDate(title,Date::convertStringToDate(newEndDate));
    }
    
    bool AgendaService::updateMeetingTitle(string title,string newTitle)
    {
         return meetingManage->updateMeetingTitle(title,newTitle);
     }
