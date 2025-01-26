#include <drogon/drogon.h>

int main() {
    drogon::app().setThreadNum(10);
    drogon::app().loadConfigFile("./configs/config.json").run();
}
