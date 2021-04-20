//
// Created by Chuying He on 18.04.21.
//

#ifndef DUCKDB_TEST_IMDB_CONSTANTS_HPP
#define DUCKDB_TEST_IMDB_CONSTANTS_HPP

// count for Table

const int IMDB_TABLE_COUNT = 21;

// Table name
const char *IMDB_TABLE_NAMES[] = {
        "aka_name", "aka_title", "cast_info", "char_name", "comp_cast_type", "company_name", "company_type", "complete_cast",
        "info_type", "keyword", "kind_type", "link_type", "movie_companies", "movie_info_idx", "movie_keyword", "movie_link",
        "name", "role_type", "title", "movie_info", "person_info"
};

// Table creation
const char *IMDB_TABLE_CREATE_SQL[] = {
        "CREATE TABLE aka_name (id integer NOT NULL PRIMARY KEY, person_id integer NOT NULL, name character varying, imdb_index character varying(3), name_pcode_cf character varying(11), name_pcode_nf character varying(11), surname_pcode character varying(11), md5sum character varying(65));",
        "CREATE TABLE aka_title (id integer NOT NULL PRIMARY KEY, movie_id integer NOT NULL, title character varying, imdb_index character varying(4), kind_id integer NOT NULL, production_year integer, phonetic_code character varying(5), episode_of_id integer, season_nr integer, episode_nr integer, note character varying(72), md5sum character varying(32));",
        "CREATE TABLE cast_info (id integer NOT NULL PRIMARY KEY, person_id integer NOT NULL, movie_id integer NOT NULL, person_role_id integer, note character varying, nr_order integer, role_id integer NOT NULL);",
        "CREATE TABLE char_name (id integer NOT NULL PRIMARY KEY, name character varying NOT NULL, imdb_index character varying(2), imdb_id integer, name_pcode_nf character varying(5), surname_pcode character varying(5), md5sum character varying(32));",
        "CREATE TABLE comp_cast_type (id integer NOT NULL PRIMARY KEY, kind character varying(32) NOT NULL);",
        "CREATE TABLE company_name (id integer NOT NULL PRIMARY KEY, name character varying NOT NULL, country_code character varying(6), imdb_id integer, name_pcode_nf character varying(5), name_pcode_sf character varying(5), md5sum character varying(32));",
        "CREATE TABLE company_type (id integer NOT NULL PRIMARY KEY, kind character varying(32));",
        "CREATE TABLE complete_cast (id integer NOT NULL PRIMARY KEY, movie_id integer, subject_id integer NOT NULL, status_id integer NOT NULL);",
        "CREATE TABLE info_type (id integer NOT NULL PRIMARY KEY, info character varying(32) NOT NULL);",
        "CREATE TABLE keyword (id integer NOT NULL PRIMARY KEY, keyword character varying NOT NULL, phonetic_code character varying(5));",
        "CREATE TABLE kind_type (id integer NOT NULL PRIMARY KEY, kind character varying(15));",
        "CREATE TABLE link_type (id integer NOT NULL PRIMARY KEY, link character varying(32) NOT NULL);",
        "CREATE TABLE movie_companies (id integer NOT NULL PRIMARY KEY, movie_id integer NOT NULL, company_id integer NOT NULL, company_type_id integer NOT NULL, note character varying);",
        "CREATE TABLE movie_info_idx (id integer NOT NULL PRIMARY KEY, movie_id integer NOT NULL, info_type_id integer NOT NULL, info character varying NOT NULL, note character varying(1));",
        "CREATE TABLE movie_keyword (id integer NOT NULL PRIMARY KEY, movie_id integer NOT NULL, keyword_id integer NOT NULL);",
        "CREATE TABLE movie_link (id integer NOT NULL PRIMARY KEY, movie_id integer NOT NULL, linked_movie_id integer NOT NULL, link_type_id integer NOT NULL);",
        "CREATE TABLE name (id integer NOT NULL PRIMARY KEY, name character varying NOT NULL, imdb_index character varying(9), imdb_id integer, gender character varying(1), name_pcode_cf character varying(5), name_pcode_nf character varying(5), surname_pcode character varying(5), md5sum character varying(32));",
        "CREATE TABLE role_type (id integer NOT NULL PRIMARY KEY, role character varying(32) NOT NULL);",
        "CREATE TABLE title (id integer NOT NULL PRIMARY KEY, title character varying NOT NULL, imdb_index character varying(5), kind_id integer NOT NULL, production_year integer, imdb_id integer, phonetic_code character varying(5), episode_of_id integer, season_nr integer, episode_nr integer, series_years character varying(49), md5sum character varying(32));",
        "CREATE TABLE movie_info (id integer NOT NULL PRIMARY KEY, movie_id integer NOT NULL, info_type_id integer NOT NULL, info character varying NOT NULL, note character varying);",
        "CREATE TABLE person_info (id integer NOT NULL PRIMARY KEY, person_id integer NOT NULL, info_type_id integer NOT NULL, info character varying NOT NULL, note character varying);"
};

// Table copy from csv file
const char *IMDB_TABLE_FROM_CSV_SQL[] = {
        "COPY aka_name FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/aka_name.csv' DELIMITER ';' ESCAPE '\';",
        "COPY aka_title FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/aka_title.csv' ESCAPE '\';",
        "COPY cast_info FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/cast_info.csv' ESCAPE '\';",
        "COPY char_name FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/char_name.csv' ESCAPE '\';",
        "COPY comp_cast_type FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/comp_cast_type.csv' ESCAPE '\';",
        "COPY company_name FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/company_name.csv' ESCAPE '\';",
        "COPY company_type FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/company_type.csv' ESCAPE '\';",
        "COPY complete_cast FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/complete_cast.csv' ESCAPE '\';",
        "COPY info_type FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/info_type.csv' ESCAPE '\';",
        "COPY keyword FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/keyword.csv' ESCAPE '\';",
        "COPY kind_type FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/kind_type.csv' ESCAPE '\';",
        "COPY link_type FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/link_type.csv' ESCAPE '\';",
        "COPY movie_companies FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/movie_companies.csv' ESCAPE '\';",
        "COPY movie_info_idx FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/movie_info_idx.csv' ESCAPE '\';",
        "COPY movie_keyword FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/movie_keyword.csv' ESCAPE '\';",
        "COPY movie_link FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/movie_link.csv' ESCAPE '\';",
        "COPY name FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/name.csv' ESCAPE '\';",
        "COPY role_type FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/role_type.csv' ESCAPE '\';",
        "COPY title FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/title.csv' ESCAPE '\';",
        "COPY movie_info FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/movie_info.csv' ESCAPE '\';",
        "COPY person_info FROM '/Users/chuyinghe/CLionProjects/duckdb-rl/imdb/person_info.csv' ESCAPE '\';"
};

/*Test*/
const char* TEST_QUERY[] = {
        "SELECT COUNT(*) FROM aka_name;",
        "SELECT COUNT(*) FROM aka_title;",
        "SELECT COUNT(*) FROM cast_info;",
        "SELECT COUNT(*) FROM char_name;",
        "SELECT COUNT(*) FROM comp_cast_type;",
        "SELECT COUNT(*) FROM company_name;",
        "SELECT COUNT(*) FROM company_type;",
        "SELECT COUNT(*) FROM complete_cast;",
        "SELECT COUNT(*) FROM info_type;",
        "SELECT COUNT(*) FROM keyword;",
        "SELECT COUNT(*) FROM kind_type;",
        "SELECT COUNT(*) FROM link_type;",
        "SELECT COUNT(*) FROM movie_companies;",
        "SELECT COUNT(*) FROM movie_info_idx;",
        "SELECT COUNT(*) FROM movie_keyword;",
        "SELECT COUNT(*) FROM movie_link;",
        "SELECT COUNT(*) FROM name;",
        "SELECT COUNT(*) FROM role_type;",
        "SELECT COUNT(*) FROM title;",
        "SELECT COUNT(*) FROM movie_info;",
        "SELECT COUNT(*) FROM person_info;"
};

/*TODO*/
// count for Query
const int IMDB_QUERIES_COUNT = 114;
// Query

#endif //DUCKDB_TEST_IMDB_CONSTANTS_HPP
