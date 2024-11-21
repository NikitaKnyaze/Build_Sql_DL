#pragma once
#include <pqxx/pqxx> 
#include <map>
#include <vector>
#include <string>
#include <iostream>

struct Table
{
   std::string name_table{ "FirstName" };
   std::vector<std::string> columns{ "id" };
   std::map<std::string, std::string> add_data;
};

class SqlSelectQueryBuilder
{
private:
   Table table;
   pqxx::connection conn;
   bool flag{ false };

public:
   SqlSelectQueryBuilder();

   SqlSelectQueryBuilder& AddColumn(const std::vector<std::string>& new_column) noexcept;
   SqlSelectQueryBuilder& AddFrom(const std::string& new_name_table) noexcept;
   SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
   Table BuildTable();
   void BuildSelect();
};

