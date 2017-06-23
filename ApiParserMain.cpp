#include "ApiParser.h"
//#include <regex>

using namespace std;

int main() {
    ApiParser parser;

    /* 차량 온도 조회 성공 */
    string sample_api_clmate_temp_get_success = "{\"/vehicle/clmateCtrl/temp\", \"Get\", \"Success\", \"30\", \"C\"}";

    /* 차량 온도 조회 실패 */ /* ErrorCode ex) 500, 1111, 1234, 5828 ....*/
    string sample_api_clmate_temp_get_failure = "{\"/vehicle/door/lock/state\", \"Get\", \"Failure\", \"3872\"}";

    /* 차량 온도 설정 성공 */
    string sample_api_clmate_temp_set_success = "{\"/vehicle/clmateCtrl/temp\", \"Set\", \"Success\", \"18\", \"C\"}";

    /* 차량 온도 설정 실패 */ /* ErrorCode ex) 500, 1111, 1234, 5828 ....*/
    string sample_api_clmate_temp_set_failure = "{\"/vehicle/clmateCtrl/temp\", \"Set\", \"Failure\", \"1938\"}";




    /* door lock state 조회 성공 */
    string sample_api_door_get_success = "{\"/vehicle/door/lock/state\", \"Get\", \"Success\", {\"lock\",\"lock\",\"unlock\",\"unlock\"}}";

    /* door lock state 조회 실패 */ /* ErrorCode ex) 500, 1111, 1234, 5828 ....*/
    string sample_api_door_get_failure = "{\"/vehicle/door/lock/state\", \"Get\", \"Failure\", \"1234\"}";


    /* door lock state Set 변경 성공 */
    string sample_api_door_set_success = "{\"/vehicle/door/lock/state\", \"Set\", \"Success\", {\"unlock\",\"unlock\",\"lock\",\"lock\"}}";

    /* door lock state Set 변경 실패 */ /* ErrorCode ex) 500, 1111, 1234, 5828 ....*/
    string sample_api_door_set_failure = "{\"/vehicle/door/lock/state\", \"Set\", \"Failure\", \"5342\"";


    /* speed 정보 요청 성공  */
    string sample_api_speed_set_success = "{\"/vehicle/speed\", \"Get\", \"Success\", \"70\", \"KM\"}";

    /* speed 정보 요청 실패  */ /* ErrorCode ex) 500, 1111, 1234, 5828 ....*/
    string sample_api_speed_set_failure = "{\"/vehicle/speed\", \"Get\", \"Failure\", \"500\"}";



    /* speed subscribe 정보 요청 성공  */
    string sample_api_speed_subscribe_success1 = "{\"/vehicle/speed\", \"Subscribe\", \"Success\", \"65\", \"KM\"}";

    /* speed subscribe 정보 요청 성공 주기적으로 전달  */
    string sample_api_speed_subscribe_success2 = "{\"/vehicle/speed\", \"Subscribe\", \"Success\", \"68\", \"KM\"}";

    /* speed subscribe 정보 요청 성공 주기적으로 전달  */
    string sample_api_speed_subscribe_success3 = "{\"/vehicle/speed\", \"Subscribe\", \"Success\", \"80\", \"KM\"}";

    /* speed subscribe 정보 요청 성공 주기적으로 전달  */
    string sample_api_speed_subscribe_success4 = "{\"/vehicle/speed\", \"Subscribe\", \"Success\", \"80\", \"KM\"}";


    /* speed unsubscribe 요청 성공  */
    string sample_api_speed_unsubscribe_success = "{\"/vehicle/speed\", \"Unsubscribe\", \"Success\"}";

    /* speed unsubscribe 요청 실패  */ /* ErrorCode ex) 500, 1111, 1234, 5828 ....*/
    string sample_api_speed_unsubscribe_failure = "{\"/vehicle/speed\", \"Unsubscribe\", \"Failure\", \"1111\"}";




    //string sample_api = "{\"/vehicle/door/lock/state\",\"Event\",{\"lock\",\"lock\",\"unlock\",\"unlock\"}}";
    string delimiter = ",";



    //string a = "hello";
    //string b = "Fellow $<world>$, full of $<smart>$ people";
    //std::cout << std::regex_replace(b, std::regex(R"(\$<[^<>]*>\$)"), a);


    //string input = "well, $<hello>$ there!";
    //std::regex reg("\\$<.+>\\$");
    // prints "well, fellow there!":
    //std::cout << '\n' << std::regex_replace(input, reg, "fellow") << '\n';


    //parser.readApi(sample_api, delimiter);

    //cout << parser.replaceStrAll(sample_api_clmate_temp_get_success) << endl;

    //cout << parser.replaceStrAll(sample_api_clmate_temp_get_success) << endl;
    parser.readApi(sample_api_clmate_temp_get_success, ",");
    vector<string> args;


    args.push_back("C");
    args.push_back("F");
    args.push_back("T");

    int unit_cnt = 4;
    args.push_back("lock");
    args.push_back("unlock");
    args.push_back("unlock");
    args.push_back("lock");

    vector<string> values;
    vector<string> unit;

    values.push_back("C");
    values.push_back("F");
    values.push_back("T");

    unit.push_back("lock");
    unit.push_back("unlock");
    unit.push_back("unlock");
    unit.push_back("lock");

    parser.writeApi("/vehicle/clmateCtrl/temp", "Get", args/* vaule */ , unit_cnt /*unit option */);

    cout << parser.writeApi("/vehicle/clmateCtrl/temp", "Get", args/* vaule */ , unit_cnt /*unit option */) << endl;

    cout << parser.writeApi("/vehicle/clmateCtrl/temp", "Get", values/* vaule */ , unit /*unit option */) << endl;
    //parser.writeApi("/vehicle/clmateCtrl/temp", "Get", args/* vaule */ , unit_idx /*unit option */);

    //parser.testWriteApi();
    /*
    if(parser.resp_.empty()) {
    	interface->sendResponse(parser.getApiUri(), parser.getApiMethod(), parser.getApiRespState());
    } else {
    	interface->sendResponse(parser.getApiUri(), parser.getApiMethod(), parser.getApiRespState(), parser.resp_);
    }


    ef::IEFInterface* interface = PlugInTarget::getInterface();

    if (interface){

    	if(parser->resp_)
          interface->sendResponse(parser.getApiUri(), parser.getApiMethod(), parser.getApiRespState());
    }
     */


    //parser.writeApi();
    return 0;
}
