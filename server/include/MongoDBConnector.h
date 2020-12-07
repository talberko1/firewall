//
// Created by tal on 02/12/2020.
//

#ifndef SERVER_MONGODBCONNECTOR_H
#define SERVER_MONGODBCONNECTOR_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
class MongoDBConnector {
private:
    mongocxx::client m_Client;
public:
    explicit MongoDBConnector(const char *uri);
    mongocxx::database getDatabase(const char *databaseName)
};
#endif //SERVER_MONGODBCONNECTOR_H
