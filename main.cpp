//
// Created by Chuying He on 07.04.21.
//

#include "duckdb.hpp"
#include "imdb_constants.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <chrono>

using namespace duckdb;

string readFileIntoString(const string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"<< path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void loadTables(Connection con) {
    std::cout <<"loadTables \n";
    for (int t = 0; t < IMDB_TABLE_COUNT; t++) {
        std::cout << IMDB_TABLE_NAMES[t] << ": ";

        con.Query(IMDB_TABLE_CREATE_SQL[t]);
        con.Query(IMDB_TABLE_FROM_CSV_SQL[t]);

        /*TODO: delet the following test code*/
        auto test = con.Query(TEST_QUERY[t]);
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        test->Print();
    }
}

void runJOBQuerys(Connection con) {
    std::cout <<"🀄️🀄️🀄️ runJOBQuerys \n";

    /*disable DuckDB optimizer*/
    con.Query("PRAGMA disable_optimizer;");
    /*config profiling*/
    con.Query("PRAGMA enable_profiling='json';");

    // std::string path = "/Users/chuyinghe/CLionProjects/duckdb-rl/job-query";
    std::string path = getRootPath() + "/job-query";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::cout<< "🀄️JOBQuery:" << entry.path().filename().string()<<std::endl;
        /*start duckdb profiling*/
        std::string str_profiling = "PRAGMA profile_output='" + getRootPath() +"/visualization/profiling/" + entry.path().filename().string() + ".json';";
        std::cout <<"str_profiling = " << str_profiling<<"\n";
        con.Query(str_profiling);

        auto sql_from_file = readFileIntoString(entry.path());
        std::cout << "sql_from_file = " << sql_from_file <<"\n";
        con.Query(sql_from_file);
        // auto result =
        // result->Print();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    /*disable DuckDB optimizer*/
    con.Query("PRAGMA enable_optimizer;");
}

int main(){
    std::cout <<"main \n";
    std::string persistent_db = "imdb.db";

    DuckDB db(nullptr);
    Connection con(db);

    loadTables(con);
    runJOBQuerys(con);

    //test EXPLAIN
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

    //test (1) with all optimizer; (2) without any optimizer; (3) only without join-order optimizer
    /*con.Query("PRAGMA disable_optimizer");
    con.Query("PRAGMA enable_profiling='json';");
	con.Query("PRAGMA profile_output='/Users/chuyinghe/CLionProjects/duckdb-master/chuying/profiling/profil.json'");

    con.Query("CREATE TABLE integers(i INTEGER);");
	con.Query("INSERT INTO integers VALUES (5);");
    con.Query("INSERT INTO integers VALUES (8);");

    con.Query("CREATE TABLE students(matri INTEGER, nachname STRING, vorname STRING);");
    con.Query("INSERT INTO students VALUES (3, 'He', 'Chuying');");
    con.Query("INSERT INTO students VALUES (5, 'John', 'Doe');");

    con.Query("CREATE TABLE professors(profnr INTEGER, nachname STRING, vorname STRING, lecture STRING);");
	con.Query("INSERT INTO professors VALUES(1, 'Neumann', 'Thomas', 'Query Optimization');");
    con.Query("INSERT INTO professors VALUES(5, 'Martin', 'Bichler', 'IT Consulting');");
    con.Query("INSERT INTO professors VALUES(7, 'James', 'Smith', 'How to be cool');");
	auto result = con.Query("SELECT * FROM integers");
	result->Print();
    result = con.Query("SELECT * FROM students");
    result->Print();
    result = con.Query("SELECT * "
	                        "FROM integers, students, professors "
	                        "WHERE integers.i = students.matri AND professors.profnr = students.matri AND students.nachname = 'John' AND professors.nachname = 'Martin' "
	                        "ORDER BY integers.i");
    result->Print();*/

}

