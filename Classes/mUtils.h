//
//  mUtils.h
//  demo
//
//  Created by AlexDao on 5/25/14.
//
//

#ifndef demo_mUtils_h
#define demo_mUtils_h

#include "cocos2d.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>
//#include <boost/date_time/gregorian/gregorian.hpp>
#include <locale>
#include <ctime>

using namespace cocos2d;
using namespace std;

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())

class mUtils{
public:
    //Số bắt đầu của GameID
    static const int numBeginGameID = 100;
    //Số lượng game
    static const int numOfGame = 10;
    //Lấy tên game dựa vào gameID
    static CCString* getGameNameByID(int gid){
        switch(gid) {
            case 100:
                return ccs("Ba Cây Thường");
            case 101:
                return ccs("Ba Cây Chương");
            case 102:
                return ccs("Phỏm");
            case 103:
                return ccs("Xì Tố");
            case 104:
                return ccs("Tiến lên miền bắc");
            case 105:
                return ccs("Tiến lên miền nam");
            case 107:
                return ccs("Cờ tướng");
            case 108:
                return ccs("Tôm Cua Cá");
            case 109:
                return ccs("Chắn");
            case 106:
                return ccs("Liêng");
            default:
                break;
        }
        return CCString::createWithFormat("Unknown gid: %d", gid);
    }
    //Lấy tên game dựa vào gameID
    static CCString* getGameNameUpperCaseByID(int gid){
        switch(gid) {
            case 100:
                return ccs("BA CÂY THƯỜNG");
            case 101:
                return ccs("BA CÂY CHƯƠNG");
            case 102:
                return ccs("PHỎM");
            case 103:
                return ccs("XÌ TỐ");
            case 104:
                return ccs("TIẾN LÊN MIỀN BẮC");
            case 105:
                return ccs("TIẾN LÊN MIỀN NAM");
            case 107:
                return ccs("CỜ TƯỚNG");
            case 108:
                return ccs("TÔM CUA CÁ");
            case 109:
                return ccs("CHẮN");
            case 106:
                return ccs("LIÊNG");
            default:
                break;
        }
        return CCString::createWithFormat("Unknown gid: %d", gid);
    }
    /*
     Format money
     */
    static CCString* format_money(long money){
        char sMoneyTmp[30], sMoney[30], s[30];
        
        sprintf( sMoneyTmp, "%ld", money );
        int len = strlen(sMoneyTmp);
        
        int i = len-1, counterSeg = 0, counter = 0;
        
        while( i>=0 ){
            sMoney[counter++] = sMoneyTmp[i];
            counterSeg++;
            if( counterSeg == 3 ){
                counterSeg = 0;
                if( i!=0 )
                    sMoney[counter++] = ',';
            }
            i--;
        }
        
        for( i = counter-1; i>=0; i-- ){
            s[counter-i-1] = sMoney[i];
        }
        
        return ccs(s);
    }
    /*
     is charactor
     */
    static bool isCharacter(const char Character)
    {
        return ( (Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z'));
    }
    /*
     is email invalid
     */
    static bool isValidEmailAddress(const char * email)
    {
        if(!email)
            return 0;
        if(!mUtils::isCharacter(email[0]))
            return 0;
        int AtOffset = -1;
        int DotOffset = -1;
        unsigned int Length = strlen(email);
        
        for(unsigned int i = 0; i < Length; i++)
        {
            if(email[i] == '@')
                AtOffset = (int)i;
            else if(email[i] == '.')
                DotOffset = (int)i;
        }
        
        if(AtOffset == -1 || DotOffset == -1)
            return 0;
        if(AtOffset > DotOffset)
            return 0;
        return !(DotOffset >= ((int)Length-1));
        
    }
    /*
     Tach xau
     */
    static vector<string> splitString(string &S,const char &str){
        vector<string> arrStr;
        string::iterator t,t2;
        for(t=S.begin();t<S.end();){
            // Lặp từ vị trí bắt đầu
            t2=find(t, S.end(),str); // Tìm vị trí space ' ' đầu tiên
            //kể từ vị trí t
            if(t!=t2)
                arrStr.push_back(string(t,t2));
			if( t2 == S.end() )
				break;
            t=t2+1; // chuyển sang vị trí sau
        }
        return arrStr;
    }
    /*
     Get current date time
     */
    static string getCurrentDateTime( const char* fmt)
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];
        
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        
        strftime(buffer, 80, fmt, timeinfo);
        std::string str(buffer);
        return str;
    }
    /*
     Get name of trans type
     */
    static string getExplainOfTransType( const char* fmt )
    {
        /*
         regiser:	DK accountID pass // Đăng ký
         resetpwd:	MK accountID// Reset mật khẩu
         query:		TC accountID pass// Truy vấn tiền
         Transfer:	CT accountID pass accountID2 money// Chuyển tiền
         Recharge:	NT accountID money// nạp tiền – Nhận tiền
         Liquit:		TT accountID pass money// Thanh toán
         Unregister:	HT accountID pass// Hủy đăng ký
         */
        if( strcmp( fmt, "VT" ) ){
            return "Vay tiền";
        }else if( strcmp( fmt, "CT" ) ){
            return "Chuyển tiền";
        }else if( strcmp( fmt, "TT" ) ){
            return "Thanh toán khoản vay";
        }else if( strcmp( fmt, "NT" ) ){
            return "Nạp/Nhận tiền";
        }
        return "Unknown";
    }

	static string convertMoneyEx(int money){
		//ostringstream oss;
		//oss<<money;
		//return oss.str();

		ostringstream oss;
		// 	oss<<money;
		// 	return oss.str();

		/// 
		if (money < 1000) {
			oss.clear();
			oss<<money;
			return (oss.str() + "");
		}
		else if (money >= 1000 && money <= 999999) {
			string hangTram;
			string hangNghin;

			ostringstream oss1;
			// Nghin
			oss1.clear();
			oss1<<(money / 1000);
			hangNghin = oss1.str();

			ostringstream oss2;
			// tram
			int hTram = (money % 1000);
			oss2.clear();
			oss2<<hTram;
			if (hTram < 10) {
				hangTram = "00";
			}
			else if (hTram >= 10 && hTram < 100) {
				hangTram = "0";
			}
			hangTram += oss2.str();

			return (hangNghin + "," + hangTram + "");
		}
		else if (money >= 1000000) {
			string hangTrieu;
			string hangNghin;
			string hangTram;

			ostringstream oss1;
			// Trieu
			oss1.clear();
			oss1<<(money / 1000000);
			hangTrieu = oss1.str();

			// Nghin
			int hNghin = (money - (money / 1000000) * 1000000) / 1000;
			ostringstream oss2;
			oss2.clear();
			oss2<<hNghin;

			if (hNghin < 10)
			{
				hangNghin = "00";
			}
			else if (hNghin >= 10 && hNghin < 100)
			{
				hangNghin = "0";
			}
			hangNghin += oss2.str();

			// Tram
			int hTram = (money % 1000);
			ostringstream oss3;
			oss3.clear();
			oss3<<hTram;

			if (hTram < 10)
			{
				hangTram = "00";
			}
			else if (hTram >= 10 && hTram < 100)
			{
				hangTram = "0";
			}
			hangTram += oss3.str();

			return (hangTrieu + "," + hangNghin + "," + hangTram + "");
		}

		return "";
	}

	static CCAction* getActionOpenPopup(){
		return CCSequence::create(CCScaleTo::create(0.0, 0.0),
			CCScaleTo::create(0.06f, 1.05f),
			CCScaleTo::create(0.08f, 0.95f),
			CCScaleTo::create(0.08f, 1.0f), NULL);
	}

	static vector<string> splitStringByListRegex(string S, vector<string> lstRegex){
		vector<string> arrStr;
		do{
			//Tìm substr gần nhất
			int minPos = INT_MAX; 
			string currRegx = "";
			//Find
			for( int i = 0; i<(int)lstRegex.size(); i++ ){
				std::size_t vt1 = S.find(lstRegex.at(i));
				if (vt1!=std::string::npos && minPos>(int)vt1){ //Find it
					minPos = vt1;
					currRegx = lstRegex.at(i);
				}
			}
			if( minPos == INT_MAX ){
				//End
				arrStr.push_back( S );
				break;
			}else{
				//Push to vector and continues
				if( minPos!=0 )
					arrStr.push_back( S.substr( 0, minPos ) );
				arrStr.push_back(currRegx);
				S = S.substr( minPos+currRegx.length(), S.length()-minPos-currRegx.length() );
			}
		}while(S.length()>=4);

		return arrStr;
	}
	static bool isSoundOn(){
		CCUserDefault *def=CCUserDefault::sharedUserDefault();
		return def->getBoolForKey("sound", true);
	}
	static bool isVibrateOn(){
		CCUserDefault *def=CCUserDefault::sharedUserDefault();
		return def->getBoolForKey("vibrate", true);
	}
};
#endif
