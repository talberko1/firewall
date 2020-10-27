//
// Created by tal on 10/14/20.
//

#include "RulesDB.h"
RulesDB::RulesDB(const char *name) : SqliteDB() {
    open(name);
}