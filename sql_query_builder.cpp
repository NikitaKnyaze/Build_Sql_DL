#include "sql_query_builder.h"

SqlSelectQueryBuilder::SqlSelectQueryBuilder()
   : conn("host=127.0.0.1 port=5432 dbname=dbbuilder1 user=postgres password=ads67") {};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::vector<std::string>& new_column)noexcept
{
   for (const auto& column : new_column) {
      table.columns.push_back(column);
   }
   flag = true;
   return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& new_name_table) noexcept
{
   table.name_table = new_name_table;
   return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept
{
   table.add_data = kv;
   return *this;
};

Table SqlSelectQueryBuilder::BuildTable()
{
   try {
      pqxx::work t(conn);

      t.exec("CREATE TABLE IF NOT EXISTS \"" + t.esc(table.name_table) + "\" ("
         "\"" + table.columns[0] + "\" SERIAL PRIMARY KEY)");

      for (const auto& column : table.columns) {
         if (column == "id") continue;

         t.exec("ALTER TABLE \"" + t.esc(table.name_table) + "\" "
            "ADD COLUMN \"" + t.esc(column) + "\" VARCHAR(40);");
      }

      std::string columns;
      std::string values;
      bool first = true;

      for (const auto& pair : table.add_data) {
         if (!first) {
            columns += ", ";
            values += ", ";
         }
         columns += "\"" + t.esc(pair.first) + "\"";
         values += "'" + t.esc(pair.second) + "'";
         first = false;
      }

      if (!columns.empty() && !values.empty()) {
         t.exec("INSERT INTO \"" + t.esc(table.name_table) + "\" (" + columns + ") "
            "VALUES (" + values + ");");
      }

      t.commit();
   }
   catch (const std::exception& e)
   {
      std::cerr << "Îøèáêà: " << e.what() << std::endl;
   }
   return table;
};

void SqlSelectQueryBuilder::BuildSelect()
{
   try {
      pqxx::work t(conn);
      if (flag)
      {
         t.exec("SELECT name, phone FROM students WHERE id=42 AND name='John';");
      }
      else
      {
         t.exec("SELECT * FROM students WHERE id=42 AND name='John';");
      }

      t.commit();
   }
   catch (const std::exception& e)
   {
      std::cerr << "Îøèáêà: " << e.what() << std::endl;
   }
};

