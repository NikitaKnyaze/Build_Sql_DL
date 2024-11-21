#include "sql_query_builder.h"
#include <Windows.h>

int main()
{
   SetConsoleCP(CP_UTF8);
   SetConsoleOutputCP(CP_UTF8);
   SqlSelectQueryBuilder query_builder;
   query_builder.AddColumn({ "name","phone" });
   query_builder.AddFrom("students");
   query_builder.AddWhere({ { "id","42" }, { "name", "John" } });

   query_builder.BuildTable();
   query_builder.BuildSelect();
  

   return EXIT_SUCCESS;
}