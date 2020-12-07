//
// Created by tal on 10/14/20.
//

#include <iostream>
#include "PcapFilter.h"
#include "RulesDB.h"

Rule::Rule(pcpp::AndFilter *andFilter, char *action) {
    m_Filter = andFilter;
    m_Action = action;
}

int callbackSelect(void *data, int argc, char *argv[], char *columnName[]) {
    auto rules = (std::vector<Rule*> *) data;
    pcpp::AndFilter *andFilter = new pcpp::AndFilter();
    if (argv[1] != std::string("ANY")) {
        andFilter->addFilter(new pcpp::IPFilter(std::string(argv[1]), pcpp::SRC));
    }
    if (argv[2] != std::string("ANY")) {
        andFilter->addFilter(new pcpp::IPFilter(std::string(argv[2]), pcpp::DST));
    }
    if (argv[3] != std::string("ANY")) {
        andFilter->addFilter(new pcpp::PortFilter(atoi(argv[3]), pcpp::SRC));
    }
    if (argv[4] != std::string("ANY")) {
        andFilter->addFilter(new pcpp::PortFilter(atoi(argv[4]), pcpp::DST));
    }
    if (argv[5] != std::string("ANY")) {
        andFilter->addFilter(new pcpp::ProtoFilter(atoi(argv[5])));
    }
    char *action = new char[10];
    memcpy(action, argv[6], strlen(argv[6]));
    rules->push_back(new Rule(andFilter, action));
    return 0;
}

RulesDB::RulesDB(const char *name) : SqliteDB() {
    open(name);
}

std::vector<Rule*> RulesDB::getRules() {
    const char *sql = "SELECT * FROM RULES;";
    std::vector<Rule*> rules;
    char *error = nullptr;
    execute(sql, callbackSelect, &rules, &error);
    return rules;
}