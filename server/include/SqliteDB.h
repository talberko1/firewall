//
// Created by tal on 10/13/20.
//
#include <exception>
#include "sqlite3.h"

#ifndef SERVER_SQLITEDB_H
#define SERVER_SQLITEDB_H

class SqliteException : public std::exception {
private:
    const char *m_Message;
public:
    SqliteException(const char *message);

    const char *what() const noexcept override;

};

class SqliteDB {
private:
    sqlite3 *m_Db;
    static int assertReturnCode(int rc, const char *message);
public:
    SqliteDB();

    int open(const char *name);

    int execute(const char *sql, int (*callback)(void *, int, char **, char **), void *data, char **errmsg);

    int close();
};

#endif //SERVER_SQLITEDB_H
