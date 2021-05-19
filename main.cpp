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
    std::cout <<"\n loadTables \n";
    for (int t = 0; t < IMDB_TABLE_COUNT; t++) {
        std::cout <<"🐱"<< IMDB_TABLE_NAMES[t] << ": ";

        con.Query(IMDB_TABLE_CREATE_SQL[t]);
        con.Query(IMDB_TABLE_FROM_CSV_SQL[t]);

        /*TODO: delet the following test code*/
        auto test = con.Query(TEST_QUERY[t]);
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        test->Print();
    }
    return;
}

void addIndexes(Connection con) {
    std::cout <<"\n addIndexes \n";
    for (int i=0; i < IMDB_TABLE_INDEX.size(); i++) {
        std::cout << i<<"/"<< IMDB_TABLE_INDEX.size() <<" " << IMDB_TABLE_INDEX[i] << "\n";
        con.Query(IMDB_TABLE_INDEX[i]);

    }
    return;
}

void runJOBQuerys(Connection con) { 
    std::cout << "\n runJOBQuerys \n\n\n";
    std::string job_folder = getRootPath() + "/job-query";
    for (const auto & entry:std::filesystem::directory_iterator(job_folder)) {
        std::string job_file = entry.path().filename().string();
        if (job_file.substr(job_file.find_last_of(".") + 1) == "sql") {
            con.Query("PRAGMA disable_optimizer");
            con.Query("PRAGMA enable_progress_bar");
            con.Query("PRAGMA enable_profiling='json'");

            std::cout<< "\n 🎰 "<< job_file;
            std::string job_profiling = "PRAGMA profile_output='"+getRootPath()+"/visualization/profiling/"+entry.path().filename().string()+".json';\n";
            con.Query(job_profiling);
//	    std::cout<<"\n performed profiling pragma";
//            std::string job_query = readFileIntoString(entry.path());
//	    std::string job_query = "SELECT * FROM comp_cast_type;";
//	    std::string job_query = "SELECT MIN(chn.name) AS uncredited_voiced_character FROM char_name AS chn;";

	    std::string job_query = readFileIntoString(entry.path());
	    std::cout <<"job_query = " <<job_query;
        std::cout <<"\n query result: ";
        auto result = con.Query(job_query);
        result->Print();
        }
    }
    return;
}

bool existDB(std::string db) {
    std::string db_dir = getBuildPath() + "/" + db ;
    //std::cout << "test = " <<db_dir << "\n";
    if (std::filesystem::exists(db_dir)) {
        std::cout<< "the db already exists";
        return true;
    }
    return false;
}

int main(){
    std::cout <<"main \n";
    std::string persistent_db = "imdb.db";

    DuckDB db(persistent_db);
    Connection con(db);

    std::cout <<"🌈checkpoint \n";
    if (!existDB(persistent_db)) {
        loadTables(con);
    }

    addIndexes(con);
    runJOBQuerys(con);

    /*con.Query("PRAGMA profile_output='/Users/chuyinghe/CLionProjects/duckdb-rl/visualization/profiling/test.sql.json';");
    con.Query("SELECT * FROM info_type;");*/

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

