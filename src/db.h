#ifndef DB_H_
#define DB_H_

#include <string>
#include "leveldb/db.h"

class DB {
 public:
  DB();
  ~DB();

  leveldb::Status Create(const std::string dbname);
  leveldb::Status Get(const std::string key, std::string* value);
  leveldb::Status Put(const std::string& key, const std::string& value);
  leveldb::Status Delete(const std::string key);

 private:
  leveldb::DB* db;
};

#endif