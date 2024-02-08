#include <iostream>

#include "cquel.hpp"

#define DO_DESIGN_GOAL false

int main()
{
    std::cout << "CQuel MySQL Builder - Tests and Examples" << std::endl;

    // Design Goal:
#if DO_DESIGN_GOAL
    
    CQ::QueryBuilder qb();
    
    qb.select().from("test_table", "t").str();  // SELECT `t`.`*` FROM `test_table` as `t`

    qb.select("col1", "col2").from("test_table", "t").str(); // SELECT `t`.`col1`, `t`.`col2`, `t`.`col3` FROM `test_table` as `t` 

    qb.select("col1").from("test_table", "t").addSelect("col2", "newName").str(); // SELECT `t`.`col1`, `t`.`col2` as `newName` FROM `test_table` as `t`

#endif
    
    CQ::QueryBuilder qb;

    auto test1 = 
        qb.select("*", "test")
          .addSelect("col3", "differentName")
          .from("test_table", "t")
          .str();


    exit(EXIT_SUCCESS);
}