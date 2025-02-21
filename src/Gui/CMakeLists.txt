
add_subdirectory( BillPay  )
add_subdirectory( Customer )

set( GCW_FILES ${GCW_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountEditor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountRegister.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountsTreeView.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CentralWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/EmployeesWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/LanguagePicker.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainMenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.cpp
  # ${CMAKE_CURRENT_SOURCE_DIR}/SlotsWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FilePropertiesWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TableView.cpp
  PARENT_SCOPE
)

