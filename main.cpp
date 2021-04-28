//
// Created by Chuying He on 07.04.21.
//

#include "duckdb.hpp"
#include "imdb_constants.hpp"
#include "timer.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <string>
#include <chrono>



using namespace duckdb;

/*std::string getRootPath() {
    const int MAXPATH=250;
    char buffer[MAXPATH];
    getcwd(buffer, MAXPATH);
    int endPos;
    for (int i = 0; i < string_t(buffer).GetString().size(); i++) {
        if (buffer[i] == '/')  {
            endPos = i;
        }
    }
    std::string rootPath = string_t(buffer).GetString().substr(0,endPos);
    std::cout << rootPath <<std::endl;
    return rootPath;
}*/

string readFileIntoString(const string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"<< path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void loadTables(Connection con) {
    /*std::string pathSchema = getRootPath() + "/schema.sql";
    con.Query(readFileIntoString(pathSchema));*/


    for (int t = 0; t < IMDB_TABLE_COUNT; t++) {

        /*std::string table_name = std::string(IMDB_TABLE_NAMES[t]);
        std::string data_file_name = "/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/"+table_name+".csv";

        auto file_system = make_unique<FileSystem>();
        if (!file_system->FileExists(data_file_name)) {
            throw Exception(StringUtil::Format("CSV %s data file missing", table_name));
        }*/
        con.Query(IMDB_TABLE_CREATE_SQL[t]);
        con.Query(IMDB_TABLE_FROM_CSV_SQL[t]);
        auto test = con.Query(TEST_QUERY[t]);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << IMDB_TABLE_NAMES[t] << ": ";
        test->Print();
        /*std::string qr = "COPY " + table_name + " FROM '" + getRootPath() + "/imdb/" + table_name + ".csv' DELIMITER ',' HEADER 0 ESCAPE '\' ENCODING 'UTF8';";
        std::cout << "QUERY: " << qr << std::endl;
        con.Query(qr);*/
    }


}



void runJOBQuerys(Connection con) {
    // std::string path = "/Users/chuyinghe/CLionProjects/duckdb-rl/job-query";
    std::string path = getRootPath() + "/job-query";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        /*disable DuckDB optimizer*/
        /*con.Query("PRAGMA disable_optimizer;");*/

        /*enable duckdb profiling*/
        std::string str_pragma = "PRAGMA profile_output='/Users/chuyinghe/CLionProjects/duckdb-rl/query-graph/profiling/";
        std::string str_profiling = str_pragma + entry.path().filename().string() + ".json';";
        std::cout<<str_profiling<<std::endl;
        con.Query("PRAGMA enable_profiling='json';" + str_profiling);



        timer timerCurrentQuery;
        auto result = con.Query(readFileIntoString(entry.path()));
        result->Print();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}




int main(){
    /*importcsv(con);
    auto test = con.Query("SELECT * FROM aka_name;");
    test->Print();// 1. create a table
    con.Query("CREATE TABLE integers(i INTEGER, j INTEGER)");
    con.Query("INSERT INTO integers VALUES (3, 4), (5, 6), (7, NULL)");
    auto result1 = con.Query("SELECT * FROM integers;");
    result1->Print();

    // 2. import a table
    auto test2 = con.Query("CREATE TABLE role AS SELECT * FROM read_csv_auto('/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/role_type.csv');");
    auto result2 = con.Query("SELECT * FROM role;");
    result2->Print();


    // 3. create table, and copy it from csv
    auto test3 = con.Query("CREATE TABLE role_type (\n"
                           "    id integer NOT NULL PRIMARY KEY,\n"
                           "    role character varying(32) NOT NULL\n"
                           ");");
    auto test31 =con.Query("INSERT INTO role_type SELECT * FROM read_csv_auto('/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/role_type.csv');");
    auto result3 = con.Query("SELECT * FROM role_type;");

    result3->Print();*/

    DuckDB db(nullptr);
    Connection con(db);

    loadTables(con);
    runJOBQuerys(con);

    /*test EXPLAIN*/
    /*con.Query("PRAGMA explain_output='all';");  // show all instead of optimized-only plan
    auto testExplain = con.Query("EXPLAIN SELECT MIN(mc.note) AS production_note,\n"
              "       MIN(t.title) AS movie_title,\n"
              "       MIN(t.production_year) AS movie_year\n"
              "FROM company_type AS ct,\n"
              "     info_type AS it,\n"
              "     movie_companies AS mc,\n"
              "     movie_info_idx AS mi_idx,\n"
              "     title AS t\n"
              "WHERE ct.kind = 'production companies'\n"
              "  AND it.info = 'top 250 rank'\n"
              "  AND mc.note NOT LIKE '%(as Metro-Goldwyn-Mayer Pictures)%'\n"
              "  AND (mc.note LIKE '%(co-production)%'\n"
              "       OR mc.note LIKE '%(presents)%')\n"
              "  AND ct.id = mc.company_type_id\n"
              "  AND t.id = mc.movie_id\n"
              "  AND t.id = mi_idx.movie_id\n"
              "  AND mc.movie_id = mi_idx.movie_id\n"
              "  AND it.id = mi_idx.info_type_id;\n"
              "");
    testExplain->Print();*/

    /*con.Query("COMMIT");*/

}

