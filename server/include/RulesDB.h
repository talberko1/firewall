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

    pcpp::AndFilter *m_Filter;
    char *m_Action;
    Rule(pcpp::AndFilter *andFilter, char *action);
};

class RulesDB : public SqliteDB {
public:
    explicit RulesDB(const char *name);

    std::vector<Rule*> getRules();
};

#endif //SERVER_RULESDB_H
