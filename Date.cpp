/*---Date.cpp--------------------------
 * Date definition
 *-----------------------------------*/

#include "Date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

Date::Date(){
	setYear( -1 );
	setMonth( -1 );
	setDay( -1 );
	setHour( -1 );
	setMinute( -1 );
}

Date::Date( int y, int mo, int d, int h, int mu ){    
	year = y;
	month = mo;
	day = d;
	hour = h;
	minute = mu;
}

//字符串的构造函数 
Date::Date(string in)     
{
   //把输入的字符串转为Date 
  Date a = convertStringToDate(in);    
  year = a.year;
  month = a.month;
  day = a.day;
  hour = a.hour;
  minute = a.minute;
}

int Date::getYear( ) const{
	return year;
}

void Date::setYear( int y ){
	year = y;
}

int Date::getMonth( ) const{
	return month;
}

void Date::setMonth( int m ) {
	month = m;
}

int Date::getDay( ) const{
	return day;
}

void Date::setDay( int d ){
	day = d;
}

int Date::getHour( ) const{
	return hour;
}

void Date::setHour( int h ){
	hour = h;
}

int Date::getMinute( ) const{
	return minute;
}

void Date::setMinute( int m ){
	minute = m;
}

bool Date::isValid( Date date ) {
    //判断年份合法性 
	if(date.year<1000||date.year>9999)
	   return false;
	
    bool isLeap=true;
    //判断是否为闰年 
	if(date.year%400==0||(date.year%4==0&&date.year%100!=0)){isLeap=true;}
    else{isLeap=false;}
    
    int leap[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    int nleap[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    if(date.month>12||date.month<1) return false;
    else{
             if(date.minute<0||date.minute>60)           return false;
        else if(date.hour<0||date.hour>23)               return false;
        else if(isLeap){if(date.day>leap[date.month-1])   return false;}
        else if(!isLeap){if(date.day>nleap[date.month-1]) return false;}  
        else return true;
		return true;
        }
		
}
    
    
Date Date::convertStringToDate(string ds){
/*
      按输入格式按位转化 
*/ 	
	Date d;
	d.year = (ds[0]-48)*1000+(ds[1]-48)*100+(ds[2]-48)*10+(ds[3]-48);
	d.month = (ds[5]-48)*10 + (ds[6] - 48);
	d.day =  (ds[8]-48)*10 + (ds[9] - 48);
	d.hour = (ds[11]-48)*10 + (ds[12] - 48);
	d.minute = (ds[14]-48)*10 + (ds[15] - 48);
	return d;
}
//数字转字符串 
string Date::ToString(int x)
{
  //逐个数位转化 
     if( x == 0 )
         return "0";
     string str = "";
       int tmp = x;
       char c;
      while(tmp)
     {
        c = (tmp % 10 + 48);
        str += c;
        tmp = tmp/10;
     }

     string s = "";
     for(int i=str.size()-1; i>=0; i--)
         s += str[i];
     return s;
}
//Date转字符串 
string Date::convertDateToString(Date date){
    string tmp = "";
    int y = date.getYear();
    int mo = date.getMonth();
    int d = date.getDay();
    int h = date.getHour();
    int mi = date.getMinute();

    tmp = ToString(y) + "-" + ToString(mo)+ "-" + ToString(d) + "/" + ToString(h) + ":" + ToString(mi);
    return tmp;
}

Date& Date::operator=( const Date& t ){
	setYear( t.getYear() );
	setMonth( t.getMonth() );
	setDay( t.getDay() );
	setHour( t.getHour() );
	setMinute( t.getMinute() );

	return *this;
}

bool Date::operator==( const Date& t ) const{
	if ( year   == t.getYear()  &&
		 month  == t.getMonth() &&
		 day    == t.getDay()   &&
		 hour   == t.getHour()  &&
		 minute == t.getMinute() )
		 return true;
	return false;
}
//转成字符串比较大小 
bool Date::operator>( const Date& t ) const{
         if ( year  > t.getYear()  ) return true;
    else if ( year  < t.getYear()  ) return false;
    else if ( month > t.getMonth() ) return true;
    else if ( month < t.getMonth() ) return false;
    else if ( day   > t.getDay()   ) return true;
    else if ( day   < t.getDay()   ) return false;
    else if ( hour  > t.getHour()  ) return true;
    else if ( hour  < t.getHour()  ) return false;
    else if ( minute> t.getMinute()) return true;
    else if ( minute< t.getMinute()) return false;
    else if ( minute==t.getMinute()) return false; 
}

bool Date::operator<( const Date& t ) const{
	if((*this) > t || (*this)==t)
	    return false;
    else
        return true;
}

bool Date::operator>=( const Date& t ) const{
	if( (*this) > t  || (*this) == t)
		return true;
	else
		return false;
}

bool Date::operator<=( const Date& t ) const{
    if((*this) > t || (*this) == t)
        return true;
    else 
        return false;
}
