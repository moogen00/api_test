#include "StrParser.h"

using namespace std;

StrParser::StrParser() {
	std::cout << "ApiParser()" << endl;
}

StrParser::~StrParser() {
	std::cout << "~ApiParser()" << endl;
}

std::string StrParser::replaceAll(std::string &str, const std::string& from,
		const std::string& to) {
	size_t start_pos = 0; //string처음부터 검사
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) //from을 찾을 수 없을 때까지
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
	}
	return str;
}

std::vector<std::string> StrParser::readApi(const std::string& api,
		const std::string& delimiter) {
	vector<string> tokens;
	string str;
	str = api;
	str = replaceAll(str, "\"","");
	str = replaceAll(str, "{", "");
	str = replaceAll(str, "}", "");

	cout << str << endl;

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
	return tokens;
}

std::string StrParser::replaceAll1(std::string &str, const std::string& from,
		const std::string& to) {
	size_t start_pos = 0; //string처음부터 검사

	start_pos = str.find(from, start_pos);
	cout << start_pos << endl;

#if 0
	do {
		start_pos = str.find(from, start_pos);
	} while (start_pos != std::string::npos);
#endif

	/*
	 while((start_pos = str.find(from, start_pos)) != std::string::npos)  //from을 찾을 수 없을 때까지
	 {
	 str.replace(start_pos, from.length(), to);
	 start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
	 }
	 */
	return str;
}

std::vector<std::string> StrParser::readApi(const std::string& api,
		std::vector<std::string> delim_vector) {
	size_t start_pos = 0; //string처음부터 검사
	std::vector<std::string> a;
	/*
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) //from을 찾을 수 없을 때까지
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
	}

	if (!token.empty()) {
		tokens.push_back(token);
	}

	return tokens;
	*/
	return a;
}

std::string StrParser::writeApi(std::vector<std::string> mid_api_str) {
	return NULL;
}
