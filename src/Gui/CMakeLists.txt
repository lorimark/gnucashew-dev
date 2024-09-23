
add_subdirectory( BillPay )

set( GCW_FILES ${GCW_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountEditor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountRegister.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountsTreeView.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CentralWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CustomerReportWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CustomersWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.cpp
  # ${CMAKE_CURRENT_SOURCE_DIR}/SlotsWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FilePropertiesWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TableView.cpp
  PARENT_SCOPE
)

