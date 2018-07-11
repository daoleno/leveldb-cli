#include "db.h"
#include <cassert>

DB::DB() { leveldb::DB* db; }
DB::~DB() { delete db; }

leveldb::Status DB::Create(const std::string dbname) {
  leveldb::Options options;
  options.create_if_missing = true;
  std::string dbfile = "../dbfile/" + dbname;

  leveldb::Status s = leveldb::DB::Open(options, dbfile, &db);
  assert(s.ok());

  return s;
}

leveldb::Status DB::Put(const std::string& key, const std::string& value) {
  leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
  assert(s.ok());
  return s;
}

leveldb::Status DB::Get(const std::string key, std::string* value) {
  leveldb::Status s = db->Get(leveldb::ReadOptions(), key, value);

  return s;
}

leveldb::Status DB::Delete(const std::string key) {
  leveldb::Status s = db->Delete(leveldb::WriteOptions(), key);
  return s;
}