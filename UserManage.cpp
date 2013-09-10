#include "UserManage.h"
#include <fstream>
using namespace std;

bool UserManage::instanceFlag = false;
UserManage* UserManage::instance = NULL;
//只能实例化一次 
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
//根据名字找到User  返回指针 
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
//创建一个新的对象 
bool UserManage:: createUser( string name, string password, string email, string phone ){
	//如果名字存在，则不再创建 
    if( findUserByName(name) != NULL )
		return false;

	User newUser( name, password, email, phone );
	users.insert( users.end(), newUser );
	return true;
}
//删除用户 
bool UserManage::deleteUser( User u )
{
    //如果用户还有会议，则不执行删除操作 
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



//更新用户密码 
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
//更新用户Email 
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
//更新用户电话 
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
//返回所有用户信息 
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
