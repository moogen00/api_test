
#include <iostream>
#include <vector>
#include <cstring>

	enum{
        kActionGet = 0x00,
        kActionSet,
        kActionSubscribe,
        kActionUnsubscribe
    };

    enum{
        kResponseSuccess = 0x00,
        kResponseFailure
    };

    enum{
        kUriIdx = 0x00,
		kMethodIdx,
		kRespStateIdx
    };

class ApiParser {

    public:
        ApiParser();
        virtual ~ApiParser();

        std::string replaceAll(std::string &str, const std::string& from, const std::string& to);
        //std::vector<std::string> readApi(const std::string& api, const std::string& delimiter);
        // std::string writeApi(std::vector<std::string> mid_api_str);
        //std::vector<std::string> readApi(const std::string& api, std::vector<std::string> delim_vector);

        void readApi(const std::string& api, const std::string& delimiter);
        std::string writeApi(const std::string& uri, const std::string& method, std::vector<std::string> args, int unit_idx);
        std::string writeApi(const std::string& uri, const std::string& action, std::vector<std::string> values, std::vector<std::string> unit);

        std::string replaceStrAll(std::string str);
        std::string testWriteApi();

        std::string getApiUri();
        int getApiMethod();
        int getApiRespState();

        void setApiUri(std::string uri);
        void setApiAction(int action);
        void setApiRespState(int respState);
        int convertType(std::string value);

        std::string startApi();
        std::string endApi();
        std::string buildUri(std::string uri);
        std::string buildAction(std::string action);

        //
        std::string buildValue(std::vector<std::string> args, int unit_cnt);
        std::string buildUnit(std::vector<std::string> args, int unit_cnt);

        //
        std::string buildValueDiv(std::vector<std::string> values, int unit_cnt);
        std::string buildUnit(std::vector<std::string> unit);

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

        const char* uri_;
        int action_;
        int resp_state_;
        std::vector<std::string> resp_;
};
