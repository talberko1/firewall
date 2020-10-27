//
// Created by tal on 10/13/20.
//

#include "SqliteDB.h"

SqliteException::SqliteException(const char *message) : m_Message(message) {}

const char *SqliteException::what() const noexcept {
    return m_Message;
}

SqliteDB::SqliteDB() {
    m_Db = nullptr;
}

int SqliteDB::open(const char *name) {
    return assertReturnCode(sqlite3_open(name, &m_Db), "Failed to open database");
}

int SqliteDB::execute(const char *sql, int (*callback)(void *, int, char **, char **), void *data, char **errmsg) {
    return assertReturnCode(sqlite3_exec(m_Db, sql, callback, data, errmsg), "Failed to execute sql");
}

int SqliteDB::close() {
    return assertReturnCode(sqlite3_close(m_Db), "Failed to close database");
}

int SqliteDB::assertReturnCode(int rc, const char *message) {
    if (rc) {
        throw SqliteException(message);
    }
    return rc;
}