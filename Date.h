/*---Date.h--------------------------
 * Date definition
 *----------------------------------*/

#ifndef Date_H
#define Date_H

#include <string>
using std::string;

class Date{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;

public:
	Date();
	Date( int y, int mo, int d, int h, int mu );
	Date(string in);

	int getYear( ) const;
	void setYear( int y );

	int getMonth( ) const;
	void setMonth( int m );

	int getDay( ) const;
	void setDay( int d );

	int getHour( ) const;
	void setHour( int h );

	int getMinute( ) const;
	void setMinute( int m );

	static string ToString(int x);
    //¾²Ì¬£¬Êý×Ö×ª×Ö·û 
	static bool isValid( Date d );
    //¾²Ì¬£¬ÅÐ¶ÏDateÊÇ·ñÓÐÐ§ 
	static Date convertStringToDate(string ds);
    //¾²Ì¬£¬string×ªDate 
	static string convertDateToString(Date d);
    //¾²Ì¬£¬Date×ªstring 

	Date& operator=( const Date& t );
	bool operator==( const Date& t ) const;
	bool operator>( const Date& t) const;
	bool operator<( const Date& t ) const;
	bool operator>=( const Date& t) const;
	bool operator<=( const Date& t ) const;
	
}; 

#endif
