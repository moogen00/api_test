#include "ApiParser.h"

#include <stddef.h>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;

ApiParser::ApiParser() :
		uri_(NULL), action_(0), resp_state_(0), resp_() {
	std::cout << "ApiParser()" << endl;
}

ApiParser::~ApiParser() {
	std::cout << "~ApiParser()" << endl;
}

/* 사용안함 */
std::string ApiParser::replaceAll(std::string &str, const std::string& from,
		const std::string& to) {
	size_t start_pos = 0; //string처음부터 검사
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) //from을 찾을 수 없을 때까지
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
	}
	return str;
}


/* 제거할 문자를 전달하면 해당 문자를 제거한다.
 * 원본 str 을 수정한다.
 */
std::string ApiParser::replaceStrAll(std::string str) {
	size_t pos = 0; //string처음부터 검사

	/* " , {, } , 공백  제거 */
	const char* special_chars = "\"{} ";

	while ((pos = str.find_first_of(special_chars)) != std::string::npos) //from을 찾을 수 없을 때까지
	{
		//cout << pos << endl;
		str.erase(pos, 1);
	}
	return str;
}


std::string ApiParser::getApiUri() {
	return uri_;
}

int ApiParser::getApiMethod() {
	return action_;
}

int ApiParser::getApiRespState() {
	return resp_state_;
}


/*
 * Api String 에서 Uri 를 setting
 */
void ApiParser::setApiUri(std::string uri) {
	uri_ = uri.c_str();
	cout << "uri_ = " << uri_ << endl;
}

/*
 * Api String 에서 Uri 를 method
 *
        kActionGet = 0x00,
        kActionSet,
        kActionSubscribe,
        kActionUnsubscribe

 */

void ApiParser::setApiAction(int action) {
	action_ = action;
	cout << "method_ = " << action_ << endl;
}

/*
 * Api String 에서 Uri 를 state value setting
 *
 * kResponseSuccess = 0x00,
 * kResponseFailure
 */

void ApiParser::setApiRespState(int respState) {
	resp_state_ = respState;
	cout << "resp_state_ = " << resp_state_ << endl;
}

/*
 * Telematics module 로 전달 받은 api data 를 EF Server 로 전달하기 위해서
 * IEFInterface 에 전달한다.
 * IEFInterface 에 전달하기 위한 format 으로 변경해준다.
 */

void ApiParser::readApi(const std::string& api, const std::string &delimiter) {
	vector<string> tokens;
	string str = "";
	//str = api;
	//cout << str << endl;
	// stack 으로 copy 해서 data 변경
	str = replaceStrAll(api);

	size_t prev = 0, pos = 0;
	do {
		// 구분자의 첫번째 위치 찾기
		pos = str.find(delimiter, prev);
		// 마지막인지 확인
		if (pos == string::npos) {
			pos = str.length();
		}

		string token = str.substr(prev, pos - prev);
		cout << token << endl;

		if (!token.empty()) {
			tokens.push_back(token);
		}
		prev = pos + delimiter.length();
	} while (pos < str.length() && prev < str.length());

	// debug log start
	vector<string>::iterator it;
	cout << "tokens :";
	for (it = tokens.begin(); it < tokens.end(); it++) {
		cout << " " << *it;
	}
	cout << endl;


	cout << tokens.size() << endl;

	cout << kUriIdx << endl;
	cout << kMethodIdx << endl;
	cout << kRespStateIdx << endl;
	// debug log end

	for (int i = 0; i < tokens.size(); i++) {

		cout << tokens.at(i) << endl;

		if(i == kUriIdx) {
			setApiUri(tokens.at(i));
		} else if(i == kMethodIdx) {
			setApiAction(convertType(tokens.at(i)));
		} else if(i == kRespStateIdx) {
			setApiRespState(convertType(tokens.at(i)));
		} else {
			// tokens.at(i) 부터 끝까지 copy
			resp_.push_back(tokens.at(i));
		}
	}

	// debug log start
	if(!resp_.empty()){
		cout << "resp :";
		for (it = resp_.begin(); it < resp_.end(); it++) {
			cout << " " << *it;
		}
		cout << endl;
	}
	// debug log end

}

/* string type 을 json parsing 을 위해서 enum 값으로 변환해준다.
 * 내용이 많아지면 구조 변경
 */
int ApiParser::convertType(std::string value) {
	if (value.compare("Get") == 0) {
		return kActionGet;
	} else if(value.compare("Set") == 0) {
		return kActionSet;
	} else if(value.compare("Subscribe") == 0) {
		return kActionSubscribe;
	} else if(value.compare("Unsubscribe") == 0) {
		return kActionUnsubscribe;
	} else if(value.compare("Success") == 0) {
		return kResponseSuccess;
	} else if(value.compare("Failure") == 0) {
		return kResponseFailure;
	}

	return -1;
}


////////////////////////////////////////////////////////////////////////////////////
// Writer


std::string ApiParser::startApi() {
	return "{";
}

std::string ApiParser::endApi() {
	return "}";
}

std::string ApiParser::buildUri(std::string uri) {
	return "\"" + uri + "\",";
}

std::string ApiParser::buildAction(std::string action) {
	return "\"" + action + "\",";
}


/*
 * vector 한개로 작업 할 경우
 */
std::string ApiParser::buildValue(std::vector<std::string> args, int unit_cnt) {

	string value;

	if(!args.empty()) {

		int length = args.size() - unit_cnt;

		for(int i = 0; i < length; i++) {
			/* value += "\"" + value + "\"" + ","; */
			value += "\"" + args.at(i) + "\"" + ",";
		}
		if(unit_cnt == 0) {
			/* 마지막에 들어가는 , 제거 */
			value.erase(value.length()-1, 1 );
		}
	}

	return value;
}


std::string ApiParser::buildValueDiv(std::vector<std::string> values, int unit_cnt) {

	string value;

	if(!values.empty()) {

		int length = values.size();

		for(int i = 0; i < length; i++) {
			/* value += "\"" + value + "\"" + ","; */
			value += "\"" + values.at(i) + "\"" + ",";
		}
		if(unit_cnt == 0) {
			/* 마지막에 들어가는 , 제거 */
			value.erase(value.length()-1, 1);
		}
	}

	return value;
}



/*
 * vector 한개로 작업 할 경우
 */
std::string ApiParser::buildUnit(std::vector<std::string> args, int unit_cnt) {

	string value;

	if(!args.empty() && unit_cnt != 0) {

		int length = args.size();
		int start_pos = args.size() - unit_cnt;

		value = "{";

		for(int i = start_pos; i < length; i++) {
			value += "\"" + args.at(i) + "\"" + ",";
		}

		if(unit_cnt != 0) {
			/* 마지막에 들어가는 , 제거 */
			value.erase(value.length()-1, 1);
		}
		value += "}";
	}

	return value;
}


/*
 *
 */
std::string ApiParser::buildUnit(std::vector<std::string> unit) {

	string value;

	if(!unit.empty()) {

		int length = unit.size();

		value = "{";

		for(int i = 0; i < length; i++) {
			value += "\"" + unit.at(i) + "\"" + ",";
		}

		/* 마지막에 들어가는 , 제거 */
		value.erase(value.length()-1, 1);

		value += "}";
	}

	return value;
}



/*
 * unit_cnt : unit 의 개수만 알려주면 된다.
 *
 */

std::string ApiParser::writeApi(const std::string& uri, const std::string& action, std::vector<std::string> args, int unit_cnt) {

	string api;
	api = startApi();
	api += buildUri(uri);
	api += buildAction(action);
	api += buildValue(args, unit_cnt);
	api += buildUnit(args, unit_cnt);
	api += endApi();

	return api;
}

/*
 * vector 를 values, unit 두개로 받는다.
 * 이미 uri 는 알고 있는 상태이고, 어떤 function 이 호출되었는지도 알고 있는 상태이다.
 *
 */
std::string ApiParser::writeApi(const std::string& uri, const std::string& action, std::vector<std::string> values, std::vector<std::string> unit) {

	string api;
	api = startApi();
	api += buildUri(uri);
	api += buildAction(action);
	api += buildValueDiv(values, unit.size());
	api += buildUnit(unit);
	api += endApi();

	return api;
}



std::string ApiParser::testWriteApi() {

	vector<string> tokens;
	tokens.push_back("AAAAAAAAA");
	tokens.push_back("BBBBBBBBB");
	tokens.push_back("CCCCCCCCC");


	 std::string s;
	 std::string result;

	 vector<string>::iterator it;
	 //cout << "tokens :";
	 for (it = tokens.begin(); it < tokens.end(); it++) {
		 result += *it;
	 }

	 cout << result << endl;

	return "";
}

