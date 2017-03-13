#include "MeetingManage.h"
#include <fstream>
#include <iostream>
bool MeetingManage::instanceFlag = false;
MeetingManage *MeetingManage::instance = NULL;
using namespace std;

//ֻʵ����һ�����������Ѿ������˶����ͷ��ظö���
MeetingManage *MeetingManage::getInstance()
{
    if (instanceFlag)
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

    if (instanceFlag == true)
    {
        instanceFlag = false;
        delete instance;
    }
}

bool MeetingManage::addMeeting(string sponsor, string participator, Date stime, Date etime, string title)
{
    list<Meeting>::iterator it;

    if ((!Date::isValid(stime)) || (!Date::isValid(etime)) || stime >= etime)
        return false;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getTitle() == title)
            return false;

        if (((*it).getParticipator() == participator) && (!((*it).getStartDate() > etime || (*it).getEndDate() < stime)))
            return false;

        if (((*it).getSponsor() == sponsor) && (!((*it).getStartDate() > etime || (*it).getEndDate() < stime)))
            return false;
    }

    Meeting newMeeting(sponsor, participator, stime, etime, title);
    meetings.push_back(newMeeting);
    return true;
}

bool MeetingManage::deleteMeeting(string userName, string title)
{

    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if (((*it).getSponsor() == userName) && ((*it).getTitle() == title))
        {
            meetings.erase(it);
            return true;
        }
    }
    return false;
}

bool MeetingManage::deleteAllMeetings(string userName)
{

    list<Meeting>::iterator it;
    int ok = 0;
    for (it = meetings.begin(); it != meetings.end();)
    {
        if ((*it).getSponsor() == userName)
        {
            it = meetings.erase(it);
            ok++;
        }
        else
            it++;
    }
    if (ok)
        return true;
    else
        return false;
}

bool MeetingManage::updateMeetingParticipator(string title, string newParticipator)
{
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {

        if (((*it).getParticipator() == newParticipator) && (!((*it).getStartDate() > queryMeetingByTitle(title)->getEndDate() || (*it).getEndDate() < queryMeetingByTitle(title)->getStartDate())))
            return false;

        if (((*it).getSponsor() == newParticipator) && (!((*it).getStartDate() > queryMeetingByTitle(title)->getEndDate() || (*it).getEndDate() < queryMeetingByTitle(title)->getStartDate())))
            return false;
    }

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getTitle() == title)
        {
            (*it).setParticipator(newParticipator);
            return true;
        }
    }
    return false;
}

bool MeetingManage::updateMeetingStartDate(string title, Date newStartDate)
{
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getTitle() == title)
        {
            (*it).setStartDate(newStartDate);
            return true;
        }
    }
    return false;
}

bool MeetingManage::updateMeetingEndDate(string title, Date newEndDate)
{
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getTitle() == title)
        {
            (*it).setEndDate(newEndDate);
            return true;
        }
    }
    return false;
}

bool MeetingManage::updateMeetingTitle(string title, string newTitle)
{
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getTitle() == title)
        {
            (*it).setTitle(newTitle);
            return true;
        }
    }
    return false;
}

Meeting *MeetingManage::queryMeetingByTitle(string title)
{
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getTitle() == title)
            return &(*it);
    }
    return NULL;
}

list<Meeting> MeetingManage::queryMeetingsByTime(string userName, Date stime, Date etime)
{
    list<Meeting> MeetingBytime;
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((((*it).getSponsor() == userName) || ((*it).getParticipator() == userName)) && !((*it).getStartDate() >= etime || (*it).getEndDate() <= stime))
            MeetingBytime.push_back(*it);
    }
    if (stime >= etime)
        MeetingBytime.clear();
    return MeetingBytime;
}

list<Meeting> MeetingManage::listAllMeetings(string userName)
{
    list<Meeting> AllMeetings;
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if (((*it).getSponsor() == userName) || ((*it).getParticipator() == userName))
            AllMeetings.push_back(*it);
    }
    return AllMeetings;
}

list<Meeting> MeetingManage::listAllSponsorMeetings(string userName)
{
    list<Meeting> AllSponsorMeetings;
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getSponsor() == userName)
            AllSponsorMeetings.push_back(*it);
    }
    return AllSponsorMeetings;
}

list<Meeting> MeetingManage::listAllParticipateMeetings(string userName)
{
    list<Meeting> AllParticipatorMeetings;
    list<Meeting>::iterator it;

    for (it = meetings.begin(); it != meetings.end(); it++)
    {
        if ((*it).getParticipator() == userName)
            AllParticipatorMeetings.push_back(*it);
    }
    return AllParticipatorMeetings;
}

bool MeetingManage::load()
{
    ifstream infile;
    infile.open("meetings.txt", ios::in);

    if (!infile.is_open())
    {
        return false;
    }

    string sponsor, participator, stime, etime, title;

    while (infile >> sponsor >> participator >> stime >> etime >> title)
    {

        addMeeting(sponsor, participator, Date::convertStringToDate(stime), Date::convertStringToDate(etime), title);
    }
    infile.close();
    return true;
}

bool MeetingManage::save()
{
    ofstream outfile;
    outfile.open("meetings.txt", ios::out);

    if (outfile)
    {
        for (list<Meeting>::iterator it = meetings.begin(); it != meetings.end(); it++)
        {
            outfile << it->getSponsor() << ' ' << it->getParticipator() << ' ' << Date::convertDateToString(it->getStartDate()) << ' ' << Date::convertDateToString(it->getEndDate()) << ' ' << it->getTitle() << endl;
        }

        outfile.close();
        return true;
    }
    else
    {
        return false;
    }
}
