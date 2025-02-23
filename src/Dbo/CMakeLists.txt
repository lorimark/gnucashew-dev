
add_subdirectory( Accounts        )
add_subdirectory( BillTerms       )
add_subdirectory( Books           )
#add_subdirectory( BudgetAmounts   )
#add_subdirectory( Budgets         )
add_subdirectory( Commodities     )
add_subdirectory( Customers       )
add_subdirectory( Employees       )
add_subdirectory( Entries         )
add_subdirectory( GncLock         )
#add_subdirectory( GnuCashewVars   )
add_subdirectory( Invoices        )
add_subdirectory( Jobs            )
#add_subdirectory( Lots            )
#add_subdirectory( Orders          )
#add_subdirectory( Prices          )
#add_subdirectory( Recurrences     )
#add_subdirectory( SchedXactions   )
add_subdirectory( Slots           )
add_subdirectory( Splits          )
#add_subdirectory( TaxTableEntries )
#add_subdirectory( TaxTables       )
add_subdirectory( Transactions    )
add_subdirectory( Users           )
add_subdirectory( Vars            )
#add_subdirectory( Vendors         )
add_subdirectory( Versions        )

set( GCW_FILES ${GCW_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/AbstractSession.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Prefrences.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SessionGnuCashew.cpp
  PARENT_SCOPE
)


