/*-------AgendaControl.cpp---------------
 *
 *-----------------------------------*/

#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include "AgendaController.h"

using namespace std;
using std::list;

//��������
bool AgendaController::executeOperation(string op)
{
    if (op == "q")
        return 0;

    else if (op == "r")
        userRegister();
    else if (op == "l")
        userLogIn();
    else if (op == "o")
        userLogOut();
    else if (op == "dc")
        deleteUser();
    else if (op == "lu")
        listAllUsers();
    else if (op == "cm")
        createMeeting();
    else if (op == "la")
        listAllMeetings();
    else if (op == "las")
        listAllSponsorMeetings();
    else if (op == "lap")
        listAllParticipateMeetings();
    else if (op == "qm")
        queryMeetingByTitle();
    else if (op == "qt")
        queryMeetingByTimeInterval();
    else if (op == "dm")
        deleteMeetingByTitle();
    else if (op == "da")
        deleteAllMeetings();
    else if (op == "uup")
        updateUserPassword();
    else if (op == "uue")
        updateUserEmail();
    else if (op == "uuph")
        updateUserPhone();
    else if (op == "ump")
        updateMeetingParticipator();
    else if (op == "ums")
        updateMeetingStartDate();
    else if (op == "ume")
        updateMeetingEndDate();
    else if (op == "umt")
        updateMeetingTitle();
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::userLogIn()
{

    if (currentUser != NULL)
    {
        cout << "[error] command illegal\n";
        getOperation();
    }

    else
    {

        cout << "[log in] [user name] [password]\n";
        cout << "[log in] ";

        string username, password;
        cin >> username >> password;

        if ((currentUser = agendaService.userLogIn(username, password)) == NULL)
        {
            printf("[error] log in fail!\n");
            getOperation();
        }

        else
        {
            printf("[log in] succeed!\n");
            cout << "----------------------- Agenda -------------------------------\n"
                 << "Action :                                                      \n"
                 << "o   - log out Agenda account                                  \n"
                 << "dc  - delete Agenda account                                   \n"
                 << "lu  - list all Agenda user                                    \n"
                 << "cm  - create a meeting                                        \n"
                 << "la  - list all meetings                                       \n"
                 << "las - list all sponsor meetings                               \n"
                 << "lap - list all participate meetings                           \n"
                 << "qm  - query meeting by title                                  \n"
                 << "qt  - query meeting by time interval                          \n"
                 << "dm  - delete meeting by title                                 \n"
                 << "da  - delete all meetings                                     \n"
                 << "uup - update user password                                    \n"
                 << "uue - update user email                                       \n"
                 << "uuph - update user phone                                      \n"
                 << "ump - update meeting participator                             \n"
                 << "ums - update meeting startDate                                \n"
                 << "ume - update meeting endDate                                  \n"
                 << "umt - uodate meeting title                                    \n"
                 << "-----------------------------------------------------------\n\n";

            getOperation();
        }
    }
}

void AgendaController::userRegister()
{

    if (currentUser != NULL)
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
    //δ��¼
    else
    {

        cout << "[register] [user name] [password] [email] [phone]\n";
        cout << "[register] ";

        string username, password, email, phone;
        cin >> username >> password >> email >> phone;

        if (agendaService.userRegister(username, password, email, phone))
        {
            printf("[register] succeed!\n");
            getOperation();
        }

        else
        {
            printf("register fail\n");
            getOperation();
        }
    }
}

void AgendaController::userLogOut()
{

    if (currentUser != NULL)
    {
        currentUser = NULL;
        getOperation();
    }

    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::deleteUser()
{

    if (currentUser != NULL)
    {

        if (agendaService.deleteUser(*currentUser))
        {
            cout << endl;
            cout << "[delete agenda account] succeed!" << endl;
            userLogOut();
        }

        else
        {
            cout << "\n[error] delete agenda account fail!" << endl;
            getOperation();
        }
    }

    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::listAllUsers()
{
    if (currentUser != NULL)
    {
        list<User> userslist;
        list<User>::iterator it;
        userslist = agendaService.listAllUsers();

        printf("\n");
        printf("[list all users]\n");
        cout << left << setw(8) << "name" << setw(17) << "email" << setw(11) << "phone" << endl;

        for (it = userslist.begin(); it != userslist.end(); it++)
            cout << left << setw(8) << it->getName() << setw(17) << it->getEmail() << setw(11) << it->getPhone() << endl;

        getOperation();
    }

    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::createMeeting()
{

    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[create meeting] [title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << '\n'
             << "[create meeting] ";

        string title, participator, stime, etime;

        cin >> title >> participator >> stime >> etime;

        UserManage *userManage = UserManage::getInstance();

        if ((userManage->findUserByName(participator)) != NULL)
        {

            if (agendaService.createMeeting(currentUser->getName(), title, participator, Date::convertStringToDate(stime), Date::convertStringToDate(etime)))
            {
                cout << "[create meeting] succeed!" << endl;
                getOperation();
            }

            else
            {
                cout << "[error] create meeting fail!" << endl;
                getOperation();
            }
        }

        else
        {
            cout << "[error] create meeting fail!" << endl;
            getOperation();
        }
    }

    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

//��ӡ�������ػ���
void AgendaController::listAllMeetings()
{
    if (currentUser != NULL)
    {
        cout << endl;
        //��ӡ��ͷ
        cout << "[list all meetings]" << endl
             << endl;
        cout << left << setw(13) << "title" << setw(13) << "sponsor" << setw(17) << "participator"
             << setw(17) << "start time" << setw(17) << "end time" << endl;

        MeetingManage *m = MeetingManage::getInstance();
        list<Meeting> meetings;
        meetings = m->listAllMeetings(currentUser->getName());
        printMeetings(meetings);
        //��ӡMeeting�б�

        getOperation();
    }
    //����δ��¼������������Ч�����»��ò˵�����
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
//��ӡ���з������б�
void AgendaController::listAllSponsorMeetings()
{
    if (currentUser != NULL)
    {
        cout << endl;
        //��ӡ��ͷ
        cout << "[list all sponsor meetings]" << endl
             << endl;
        cout << left << setw(13) << "title" << setw(13) << "sponsor" << setw(17) << "participator"
             << setw(17) << "start time" << setw(17) << "end time" << endl;

        MeetingManage *m = MeetingManage::getInstance();
        list<Meeting> meetings;
        meetings = m->listAllSponsorMeetings(currentUser->getName());
        printMeetings(meetings);
        //��ӡ������Meeting�б�
        getOperation();
    }
    //����δ��¼������������Ч�����»��ò˵�����
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
//��ӡ�λ���Meeting�б�
void AgendaController::listAllParticipateMeetings()
{
    if (currentUser != NULL)
    {
        cout << endl;
        //��ӡ��ͷ
        cout << "[list all participate meetings]" << endl
             << endl;
        cout << left << setw(13) << "title" << setw(13) << "sponsor" << setw(17) << "participator"
             << setw(17) << "start time" << setw(17) << "end time" << endl;

        MeetingManage *m = MeetingManage::getInstance();
        list<Meeting> meetings;
        meetings = m->listAllParticipateMeetings(currentUser->getName());
        printMeetings(meetings);
        //��ӡ�λ���Meeting�б�
        getOperation();
    }
    //����δ��¼������������Ч�����»��ò˵�����
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
//����Title��ѯ����
void AgendaController::queryMeetingByTitle()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[query meeting] [title]:" << endl;
        cout << "[query meeting] ";

        string title;
        cin >> title;

        cout << left << setw(15) << "sponsor" << setw(15) << "participator"
             << setw(25) << "start time" << setw(25) << "end time";

        Meeting *meeting = NULL;
        //����Title�����Ļ�
        if ((meeting = agendaService.meetingQuery(title)) != NULL)
        {

            cout << left << setw(15) << meeting->getSponsor() << setw(15) << meeting->getParticipator()
                 << setw(25) << Date::convertDateToString(meeting->getStartDate()) << setw(25)
                 << Date::convertDateToString(meeting->getEndDate()) << endl;

            getOperation();
        }
        //û�и�Title�����Ļ�
        else
        {
            cout << endl
                 << endl;
        }

        getOperation();
    }
    //����δ��¼������������Ч�����»��ò˵�����
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
//����ʱ����ѯ����
void AgendaController::queryMeetingByTimeInterval()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
        cout << "[query meetings] ";

        string stime, etime;

        cin >> stime >> etime;
        //����ʱ�䲻�Ϸ�
        if (stime > etime || stime == etime)
        {
            cout << "[checked date illegal]!" << endl;
            getOperation();
        }

        else
        {
            cout << endl
                 << "[query meetings]" << endl;
            cout << left << setw(13) << "title" << setw(13) << "sponsor" << setw(17) << "participator"
                 << setw(17) << "start time" << setw(17) << "end time" << endl;
            //��ӡ�����б�
            printMeetings(agendaService.meetingQuery(currentUser->getName(), Date::convertStringToDate(stime), Date::convertStringToDate(etime)));
            getOperation();
        }
    }
    //����δ��¼������������Ч�����»��ò˵�����
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
//����Titleɾ������
void AgendaController::deleteMeetingByTitle()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[delete meeting] [title]" << '\n'
             << "[delete meeting] ";

        string title;
        cin >> title;
        //ɾ���ɹ�
        if (agendaService.deleteMeeting(currentUser->getName(), title))
        {
            cout << endl
                 << "[delete meeting by title] succeed!" << endl;
            getOperation();
        }
        //ɾ��ʧ��
        else
        {
            cout << endl
                 << "[error] delete meeting fail!" << endl;
            getOperation();
        }
    }
    //����δ��¼������������Ч�����»��ò˵�����
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
//ɾ�����л���
void AgendaController::deleteAllMeetings()
{
    if (currentUser != NULL)
    {
        cout << endl;
        //ɾ���ɹ�
        if (agendaService.deleteAllMeetings(currentUser->getName()))
        {
            cout << "[delete all meetings] succeed!" << endl;
            getOperation();
        }
        //ɾ��ʧ��
        else
        {
            cout << endl
                 << "[error] delete all meetings fail!" << endl;
            getOperation();
        }
    }
    //����δ��¼������������Ч�����»��ò˵�����
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::printMeetings(list<Meeting> meetings)
{
    //�б�Ϊ��
    if (meetings.empty())
    {
        cout << endl;
    }
    //�б���Ϊ��
    else
    {
        list<Meeting>::iterator it;
        for (it = meetings.begin(); it != meetings.end(); it++)
        {
            // ��ӡ
            cout << left << setw(13) << it->getTitle() << setw(13) << it->getSponsor() << setw(17) << it->getParticipator()
                 << setw(17) << Date::convertDateToString(it->getStartDate()) << setw(17)
                 << Date::convertDateToString(it->getEndDate()) << endl;
        }
    }
}

AgendaController::AgendaController()
{
    currentUser = NULL;
}

//���ò˵�����
void AgendaController::getOperation()
{
    if (currentUser == NULL)
    {
        cout << "\n-------------------------Agenda-----------------------------\n";
        cout << "Action:\n";
        cout << "l   - log in Agenada by user name and password\n";
        cout << "r   - register an Agenda account\n";
        cout << "q   - quit Agenda\n";
        cout << "--------------------------------------------------------------\n";
        cout << "\nAgenda : ~$ ";
    }
    else
    {
        cout << endl
             << "Agenda@" << currentUser->getName() << " : # ";
    }

    string input;
    input = "";
    cin >> input;
    if (input == "")
    {
        cin.clear();
        cin.rdstate();
        cin.fixed;
        fclose(stdin);
        fclose(stdout);
    }
    //����ָ��
    executeOperation(input);
    //��������
}

void AgendaController::updateUserPassword()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[update user] [password]" << '\n'
             << "[update user] ";

        string password;
        cin >> password;

        if (agendaService.updateUserPassword(*currentUser, password))
        {
            cout << "update password succeed!" << endl;
            getOperation();
        }
        else
        {
            cout << "[error] update password fail!" << endl;
            getOperation();
        }
    }
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::updateUserEmail()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[update user] [email]" << '\n'
             << "[update user] ";

        string Email;
        cin >> Email;

        if (agendaService.updateUserEmail(*currentUser, Email))
        {
            cout << "update email succeed!" << endl;
            getOperation();
        }
        else
        {
            cout << "[error] update email fail!" << endl;
            getOperation();
        }
    }
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
void AgendaController::updateUserPhone()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[update user] [phone]" << '\n'
             << "[update user] ";

        string phone;
        cin >> phone;

        if (agendaService.updateUserPhone(*currentUser, phone))
        {
            cout << "update phone succeed!" << endl;
            getOperation();
        }
        else
        {
            cout << "[error] update phone fail!" << endl;
            getOperation();
        }
    }
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::updateMeetingParticipator()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[update meeting] [title] [participator]" << '\n'
             << "[update meeting] ";

        string participator, title;
        cin >> title >> participator;

        if (agendaService.meetingQuery(title) != NULL)
        {
            UserManage *userManage = UserManage::getInstance();
            //�λ��ߴ��ڸ��û��Ļ�
            if ((userManage->findUserByName(participator)) != NULL)
            {

                if (agendaService.updateMeetingParticipator(title, participator))
                {
                    cout << "update participator succeed!" << endl;
                    getOperation();
                }
                else
                {
                    cout << "[error] update participator fail!" << endl;
                    getOperation();
                }
            }
            else
            {
                cout << "[error] update participator fail!" << endl;
                getOperation();
            }
        }
        else
        {
            cout << "[error] unavailable meeting!" << endl;
            getOperation();
        }
    }
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::updateMeetingStartDate()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[update meeting] [title] [statrDate]" << '\n'
             << "[update meeting] ";

        string title, startDate;
        cin >> title >> startDate;

        if (agendaService.meetingQuery(title) != NULL)
        {

            if (Date::isValid(Date::convertStringToDate(startDate)) && Date::convertStringToDate(startDate) < (agendaService.meetingQuery(title))->getEndDate())
            {
                list<Meeting> smeeting;
                list<Meeting> pmeeting;
                MeetingManage *meetingManage = MeetingManage::getInstance();

                pmeeting = agendaService.meetingQuery((meetingManage->queryMeetingByTitle(title))->getParticipator(), Date::convertStringToDate(startDate), (agendaService.meetingQuery(title))->getStartDate());

                smeeting = agendaService.meetingQuery(currentUser->getName(), Date::convertStringToDate(startDate), (agendaService.meetingQuery(title))->getStartDate());

                if (smeeting.empty() && pmeeting.empty())
                {

                    if (agendaService.updateMeetingStartDate(title, startDate))
                    {
                        cout << "update startDate succeed!" << endl;
                        getOperation();
                    }
                    else
                    {
                        cout << "[error] update startDate fail!" << endl;
                        getOperation();
                    }
                }
                else
                {
                    cout << "[error] update startDate fail!" << endl;
                    getOperation();
                }
            }

            else
            {
                cout << "[error] update startDate fail!" << endl;
                getOperation();
            }
        }
        else
        {
            cout << "[error] unavailable meeting!" << endl;
            getOperation();
        }

    } //end if
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::updateMeetingEndDate()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[update meeting] [title] [endDate]" << '\n'
             << "[update meeting] ";

        string title, endDate;
        cin >> title >> endDate;

        if (agendaService.meetingQuery(title) != NULL)
        {
            if (Date::isValid(Date::convertStringToDate(endDate)) && Date::convertStringToDate(endDate) > (agendaService.meetingQuery(title))->getStartDate())
            {
                list<Meeting> smeeting;
                list<Meeting> pmeeting;
                MeetingManage *meetingManage = MeetingManage::getInstance();

                pmeeting = agendaService.meetingQuery((meetingManage->queryMeetingByTitle(title))->getParticipator(), (agendaService.meetingQuery(title))->getEndDate(), Date::convertStringToDate(endDate));

                smeeting = agendaService.meetingQuery(currentUser->getName(), (agendaService.meetingQuery(title))->getEndDate(), Date::convertStringToDate(endDate));
                if (smeeting.empty() && pmeeting.empty())
                {

                    if (agendaService.updateMeetingStartDate(title, endDate))
                    {
                        cout << "update endDate succeed!" << endl;
                        getOperation();
                    }
                    else
                    {
                        cout << "[error] update endDate fail!" << endl;
                        getOperation();
                    }
                }
                else
                {
                    cout << "[error] update endDate fail!" << endl;
                    getOperation();
                }
            }

            else
            {
                cout << "[error] update endDate fail!" << endl;
                getOperation();
            }
        }
        else
        {
            cout << "[error] unavailable meeting!";
            getOperation();
        }

    } //end if
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}

void AgendaController::updateMeetingTitle()
{
    if (currentUser != NULL)
    {
        cout << endl;
        cout << "[update meeting] [title] [newTitle]" << '\n'
             << "[update meeting] ";

        string title, newtitle;
        cin >> title >> newtitle;

        if (agendaService.meetingQuery(title) != NULL)
        {

            if (agendaService.updateMeetingTitle(title, newtitle))
            {
                cout << "update title succeed!" << endl;
                getOperation();
            }
            else
            {
                cout << "[error] update title fail!" << endl;
                getOperation();
            }
        }
        else
        {
            cout << "[error] unavailable meeting!";
            getOperation();
        }
    }
    else
    {
        cout << "[error] command illegal\n";
        getOperation();
    }
}
