/*-------UserManage.h--------------------
 *
 *-------------------------------------*/

#ifndef USERMANAGE_H
#define USERMANAGE_H

#include "User.h"
#include <list>

using std::list;

class UserManage{
private:
	static bool instanceFlag;
    //实例标识 
	static UserManage *instance;
    //单一实例 
	UserManage();

	list<User> users;
    //用户列表 

public:
	static UserManage *getInstance();
	~UserManage();

	User* findUserByName( string name );
    //根据名字找用户 
	bool createUser( string name, string password, string email, string phone );
    //创建一个新的用户 
	bool deleteUser( User u );
    //删除用户
    
    //更新用户信息 
	bool updateUserPassword( User u, string newPassword );
	bool updateUserEmail( User u, string newEmail );
	bool updateUserPhone( User u, string newPhone );
	list<User> listAllUsers( );
    //所有用户信息 
    bool load();
    bool save();
};

#endif
