//
// Created by tal on 10/13/20.
//

#ifndef SERVER_RULESDB_H
#define SERVER_RULESDB_H
#include <vector>
#include <pcapplusplus/IpAddress.h>
#include <pcapplusplus/ProtocolType.h>
#include "SqliteDB.h"

struct Rule {
    const char *name;
    enum action {
        FORWARD,
        DROP
    };
    pcpp::IPAddress* srcIp;
    pcpp::IPAddress* mask;
    pcpp::IPAddress* dstIp;
    uint16_t srcPort;
    uint16_t dstPort;
    pcpp::ProtocolType protocol;
};
class RulesDB : SqliteDB {
public:
    RulesDB(const char *name);

    Rule& getRule(int ruleId);

    std::vector<Rule> getRules();

    int addRule(struct Rule);

    int removeRule();
};
#endif //SERVER_RULESDB_H
