#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

namespace CQ 
{

    typedef struct Table_s
    {
        std::string name;
        std::string alias;
        bool is_subquery = false;
    } Table_t;

    typedef struct Reflector_s
    {
        std::string name;
        std::string alias;
        bool is_subquery = false;
    } Reflector_t;

    typedef struct Join_s
    {
        Table_t table;
        Reflector_t left;
        Reflector_t right;
    } Join_t;
    typedef Join_t InnerJoin_t;
    typedef Join_t LeftJoin_t;
    typedef Join_t RightJoin_t;
    typedef Join_t CrossJoin_t; // Doesn't use the conditionals, just the table
    typedef Join_t SelfJoin_t;  // ^ ditto

    template<typename T>
    struct Set_s
    {
        std::string column;
        T value;
    };
    typedef Set_s<int> iSet_t;
    typedef Set_s<unsigned int> uiSet_t;
    typedef Set_s<bool> bSet_t;
    typedef Set_s<float> fSet_t;
    typedef Set_s<std::string> sSet_t;



    class QueryBuilder {
    private:
        enum QUERY_MODE {
            SELECT,
            INSERT,
            UPDATE,
            DELETE
        };

        QUERY_MODE m_mode = QUERY_MODE::SELECT;

        // General Purpose 
        std::vector<Reflector_t> reflectors;
        std::vector<Table_s> tables;
        
        // For INSERT and UPDATE
        std::vector<iSet_t> int_sets;
        std::vector<uiSet_t> uint_sets;
        std::vector<bSet_t> bool_sets;
        std::vector<fSet_t> float_sets;
        std::vector<sSet_t> string_sets;

        // For SELECT
        std::vector<InnerJoin_t> inner_joins;
        std::vector<LeftJoin_t> left_joins;
        std::vector<RightJoin_t> right_joins;
        std::vector<CrossJoin_t> cross_joins;
        std::vector<SelfJoin_t> self_joins;

    public:
        QueryBuilder() { }
        ~QueryBuilder() { }

        template<typename... Args>
        QueryBuilder& select(const Args&... args) {
            m_mode = QUERY_MODE::SELECT;
            
            for (const auto& arg : { args... }) {
                reflectors.push_back({ std::string(arg) });
            }

            return *this;
        }

        QueryBuilder& insert() {
            m_mode = QUERY_MODE::INSERT;
            return *this;
        }

        QueryBuilder& del() {
            m_mode = QUERY_MODE::DELETE;
            return *this;
        }

        QueryBuilder& update(std::string table) {
            m_mode = QUERY_MODE::UPDATE;

            tables.clear();
            tables.push_back({ table });

            return *this;
        }

        QueryBuilder& from(std::string name, std::string alias = "") {
            if (m_mode != QUERY_MODE::SELECT && m_mode != QUERY_MODE::DELETE) {
                std::cerr << "from() is incomatible with current mode. Only supports SELECT and DELETE" << std::endl;
                exit(EXIT_FAILURE);
            }
            tables.push_back({ name, alias });
            return *this;
        }

        QueryBuilder& from(QueryBuilder subquery, std::string alias = "") {
            if (m_mode != QUERY_MODE::SELECT && m_mode != QUERY_MODE::DELETE) {
                std::cerr << "from() is incomatible with current mode. Only supports SELECT and DELETE" << std::endl;
                exit(EXIT_FAILURE);
            }
            tables.push_back({ subquery.str(), alias, true}); // @todo need a way to do this without compiling the subquery first
            return *this;
        }

        QueryBuilder& into(std::string name) {
            if (m_mode != QUERY_MODE::INSERT) {
                std::cerr << "into() is incomatible with current mode. Only supports INSERT" << std::endl;
                exit(EXIT_FAILURE);
            }
            tables.clear();
            tables.push_back({ name });
        }

        QueryBuilder& addSelect(std::string content, std::string alias) {
            reflectors.push_back({ content, alias });
            return *this;
        }



        QueryBuilder& addSelect(QueryBuilder subquery, std::string alias = "") {
            reflectors.push_back({ subquery.str(), alias, true }); // @todo need a way to do this without compiling the subquery first
            return *this;
        }

        std::string str() {
            // run compiler

            return "";
        }

    
    };

}