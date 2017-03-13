#include "UserManage.h"
#include <fstream>
using namespace std;

bool UserManage::instanceFlag = false;
UserManage* UserManage::instance = NULL;
 
UserManage* UserManage::getInstance()
    {
        if(instanceFlag)
           return instance;
        else
          {
             instance = new UserManage();
             instanceFlag = true;
             return instance;
          }   
    }

UserManage::UserManage(){
	
}

UserManage::~UserManage()
	{
    if(instanceFlag == true){
        instanceFlag = false;
        delete instance;
       }
    }
 
User* UserManage::findUserByName( string name )
{
    list<User>::iterator it;
    
    for(it = users.begin(); it != users.end();it++){
        if( (*it).getName() == name ){
            return &(*it);
        }
    } 
    
    return NULL;
}
 
bool UserManage:: createUser( string name, string password, string email, string phone ){
	  
    if( findUserByName(name) != NULL )
		return false;

	User newUser( name, password, email, phone );
	users.insert( users.end(), newUser );
	return true;
}
 
bool UserManage::deleteUser( User u )
{
    
    if(!((u.getAllMeetings()).empty()))
          return false;
    else
    {   
    
    list<User>::iterator it;
    
    for(it = users.begin(); it != users.end();it++){
        if( (*it).getName() == u.getName() ){
            users.erase(it);
            return true;
        }
    }
    
    return false;  
    }
}



 
bool UserManage::updateUserPassword( User u, string newPassword ){
	list<User>::iterator it;

	for(it = users.begin(); it != users.end();it++){
		if( (*it).getName() == u.getName() ){
			(*it).setPassword( newPassword );
			return true;
		}
	}

	return false;
}
 
bool UserManage::updateUserEmail( User u, string newEmail )
{
    list<User>::iterator it;
    
	for(it = users.begin(); it != users.end();it++){
		if( (*it).getName() == u.getName() ){
			(*it).setEmail( newEmail );
			return true;
		}
	}

	return false;
}
 
bool UserManage::updateUserPhone( User u, string newPhone )
{
   	list<User>::iterator it;

	for(it = users.begin(); it != users.end();it++){
		if( (*it).getName() == u.getName() ){
			(*it).setPhone( newPhone );
			return true;
		}
	}

	return false; 
}
 
list<User> UserManage::listAllUsers( )
{
   return users;
    
}


bool UserManage::load(){
    ifstream infile;
	infile.open("users.txt",ios::in);

	if(!infile.is_open()){
		return false;
	}
	
	string username ,password,email,phone;
	
	while(infile >> username >> password >> email >> phone)
  {	
    createUser(username,password,email,phone);
   }
	infile.close();
	return true;
}

bool UserManage::save(){
	ofstream outfile;
	outfile.open("users.txt",ios::out);
	if(outfile)
	{
		for(list<User>::iterator it=users.begin();it!=users.end();it++){
			outfile<<it->getName()<<' '<<it->getPassword()<<' '<<it->getEmail()<<' '<<it->getPhone()<<endl;
		}
	    
		outfile.close();
		return true;
	}
	else{
		return false;
	}	
}
