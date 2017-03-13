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
class Meeting
{
  private:
    string sponsor;

    string participator;

    Date startDate;

    Date endDate;

    string title;

  public:
    Meeting(string s, string p, Date st, Date et, string t);

    string getSponsor();
    void setSponsor(string s);

    string getParticipator();
    void setParticipator(string p);

    Date getStartDate();
    void setStartDate(Date st);

    Date getEndDate();
    void setEndDate(Date et);

    string getTitle();
    void setTitle(string t);
};

#endif
