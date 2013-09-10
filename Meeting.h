/*---Meeting.h--------------------------
 * Meeting definition
 *------------------------------------*/

#ifndef MEETING_H
#define MEETING_H

#include "Date.h"
#include <string>

using std::string;
/*
 * define Meeting class
 */
class Meeting {
private:
	 string sponsor;  
     //发起者 
	 string participator; 
     //参会者 
	 Date   startDate; 
     //开始日期 
	 Date   endDate;   
     //结束日期 
	 string title;  
     //主题 

public:
	Meeting( string s, string p, Date st, Date et, string t );

	string getSponsor( ) ;
	void setSponsor(string s);

	string getParticipator( ) ;
	void setParticipator(string p);

	Date getStartDate( ) ;
	void setStartDate(Date st);

	Date getEndDate( ) ;
	void setEndDate(Date et);

	string getTitle( ) ;
	void setTitle(string t);

};


#endif
