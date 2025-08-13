

if( ENABLE_BILLPAY )
  add_subdirectory( BillPay  )
endif()

add_subdirectory( Customer )

set( GCW_FILES ${GCW_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountComboBox.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountEditor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountRegister.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountRegisterEditor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountSuggestionEdit.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AccountSuggestionPopup.cpp
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

