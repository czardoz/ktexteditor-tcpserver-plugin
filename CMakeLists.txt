find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES})
kde4_add_plugin(ktexteditor-tcpserver tcpserver.cpp)

target_link_libraries(ktexteditor-tcpserver ${KDE4_KDECORE_LIBS} ${KDE4_KDEUI_LIBS} ktexteditor)

install(TARGETS ktexteditor-tcpserver DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES tcpserverui.rc DESTINATION ${DATA_INSTALL_DIR}/ktexteditor-tcpserver)

install(FILES ktexteditor-tcpserver.desktop DESTINATION ${SERVICES_INSTALL_DIR})
