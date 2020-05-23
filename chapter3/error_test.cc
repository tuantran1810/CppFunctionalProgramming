#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

struct ErrorCode {
    ErrorCode(int code) : code(code) {}
    ErrorCode(ErrorCode&& object) { code = object.code; }
    ErrorCode(const ErrorCode& object) { code = object.code; }

    operator bool() {
        return code == 200;
    }
private:
    int code;
};

struct Response {
    Response(ErrorCode&& result): result(std::forward<ErrorCode>(result)) {}
    Response(const Response& resp): result(resp.result) {}
    ErrorCode error() const {
        return result;
    }

private:
    ErrorCode result;
};

struct ErrorTest {
    ErrorTest(bool condition) : condition(condition) {}

    template<typename T>
    bool operator()(T&& object) {
        return condition == (bool)std::forward<T>(object).error();
    }

    ErrorTest operator==(bool test) {
        return ErrorTest(test ? condition : !condition);
    }

    ErrorTest operator!() {
        return ErrorTest(!condition);
    }

private:
    bool condition;
};

int main(void) {
    std::vector<Response> responses = {
        Response(ErrorCode(200)),
        Response(ErrorCode(300)),
        Response(ErrorCode(400)),
        Response(ErrorCode(200)),
        Response(ErrorCode(100)),
        Response(ErrorCode(500))
    };

    auto dotest  = [&responses]<typename T>(T&& pass, T&& fail) {
        int valid = std::count_if(responses.cbegin(), responses.cend(),
            [&pass] (const Response& response) {
                return pass(response);
            });

        int invalid = std::count_if(responses.cbegin(), responses.cend(),
            [&fail] (const Response& response) {
                return fail(response);
            });
        std::cout << "=============================================\n";
        std::cout << "Valid responses: " << valid << std::endl;
        std::cout << "Invalid responses: " << invalid << std::endl;
        std::cout << "=============================================\n";
    };

    ErrorTest testPass1 = ErrorTest(true);
    ErrorTest testFailed1 = ErrorTest(false);
    dotest(testPass1, testFailed1);

    ErrorTest testFailed2 = testPass1 == false;
    ErrorTest testPass2 = testFailed1 == false;
    dotest(testPass2, testFailed2);

    dotest(!testFailed2, !testPass2);
    return 0;
}
