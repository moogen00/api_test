
#include <iostream>
#include <vector>
#include <cstring>


class StrParser
{

    public:
	StrParser();
        virtual ~StrParser();

        std::string replaceAll(std::string &str, const std::string& from, const std::string& to);
        std::string replaceAll1(std::string &str, const std::string& from, const std::string& to);
        std::vector<std::string> readApi(const std::string& api, const std::string& delimiter);
        std::string writeApi(std::vector<std::string> mid_api_str);
        std::vector<std::string> readApi(const std::string& api, std::vector<std::string> delim_vector);

    private:
        typedef enum _DELIM_TYPE {
          DELIM_START,
          DELIM_OPTION,
          DELIM_END
        } DELIM_TYPE;

        // 토큰 구조체
        struct _DELIMITER {
            DELIM_TYPE type;   // 토큰 종류
            std::string delimiter;     // 문자열 포인터
            //char isOption;      // 현재 토큰이 배열인지 표시
        };

        typedef std::vector<_DELIMITER> DELIMITER_LIST;
};
