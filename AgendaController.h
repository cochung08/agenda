/*-------AgendaControl.h---------------
 *
 *-----------------------------------*/

#ifndef AGENDACONTROLLER_H
#define AGENDACONTROLLER_H

#include <iostream>
#include "AgendaService.h"

using namespace std;

class AgendaController
{
  private:
    User *currentUser;
    AgendaService agendaService;

    bool executeOperation(string op);

    void userLogIn();

    void userRegister();

    void userLogOut();

    void deleteUser();

    void listAllUsers();

    void createMeeting();

    void listAllMeetings();

    void listAllSponsorMeetings();

    void listAllParticipateMeetings();

    void queryMeetingByTitle();

    void queryMeetingByTimeInterval();

    void deleteMeetingByTitle();

    void deleteAllMeetings();

    void printMeetings(list<Meeting> meetings);

    void updateUserPassword();
    void updateUserEmail();
    void updateUserPhone();
    void updateMeetingParticipator();
    void updateMeetingStartDate();
    void updateMeetingEndDate();
    void updateMeetingTitle();

  public:
    AgendaController();

    void getOperation();
};

#endif
