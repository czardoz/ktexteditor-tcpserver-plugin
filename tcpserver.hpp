#ifndef _TCPSERVER_HPP
#define _TCPSERVER_HPP

#include <ktexteditor/plugin.h>
#include <ktexteditor/view.h>
#include <kxmlguiclient.h>
#include <klocalizedstring.h>
 
#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtNetwork>

class TCPServerPlugin
  : public KTextEditor::Plugin
{
    public:

        explicit TCPServerPlugin(QObject *parent, 
                                 const QVariantList &args);

        virtual ~TCPServerPlugin();
        void addView (KTextEditor::View *view);
        void removeView (KTextEditor::View *view);
     
        void readConfig();
        void writeConfig();

    private:
        QList<class TCPServerPluginView*> m_views;
};

class TCPServerPluginView
    : public QObject, public KXMLGUIClient
{
    Q_OBJECT

    public:
        explicit TCPServerPluginView(KTextEditor::View* view = 0);
        ~TCPServerPluginView();

    private Q_SLOTS:
        void slotInsertText();
        void slotHandleConnection();
        void slotGetData();
        void slotDisconnected();
        
    private:
        KTextEditor::View *m_view;
        QTcpServer *srv;
        QTcpSocket *clientSocket;
};

#endif
