#include "tcpserver.hpp"
 
#include <ktexteditor/document.h>
 
#include <kpluginfactory.h>
#include <kpluginloader.h>
#include <klocale.h>
#include <kaction.h>
#include <kactioncollection.h>
#include <kdatetime.h>

K_PLUGIN_FACTORY(TCPServerPluginFactory,
                    registerPlugin<TCPServerPlugin>();
                )

K_EXPORT_PLUGIN(TCPServerPluginFactory("ktexteditor-tcpserver", "ktexeditor_plugins"))

TCPServerPlugin::TCPServerPlugin(QObject *parent, const QVariantList &args)
    :KTextEditor::Plugin(parent)
{
    Q_UNUSED(args);
}

TCPServerPlugin::~TCPServerPlugin()
{
}

void TCPServerPlugin::addView(KTextEditor::View *view)
{
    TCPServerPluginView *nview = new TCPServerPluginView(view);
    m_views.append(nview);
}

void TCPServerPlugin::removeView(KTextEditor::View *view)
{
    for(int z = 0; z < m_views.size(); z++)
    {
        if (m_views.at(z)->parentClient() == view)
        {
            TCPServerPluginView *nview = m_views.at(z);
            m_views.removeAll(nview);
            delete nview;
        }
    }
}

void TCPServerPlugin::readConfig()
{
}

void TCPServerPlugin::writeConfig()
{
}

TCPServerPluginView::TCPServerPluginView(KTextEditor::View *view)
    : QObject(view)
    , KXMLGUIClient(view)
    , m_view(view)
{
    setComponentData(TCPServerPluginFactory::componentData());

    KAction *action = new KAction(i18n("Insert thing from TCP Socket"), this);
    actionCollection()->addAction("tools_insert_chars", action);
    action->setShortcut(Qt::CTRL + Qt::Key_M);
    connect(action, SIGNAL(triggered()), this, SLOT(slotInsertText()));
    setXMLFile("tcpserverui.rc");
}

TCPServerPluginView::~TCPServerPluginView()
{
}

void TCPServerPluginView::slotInsertText()
{
    kDebug() << "Server!";
    m_view->document()->insertText(m_view->cursorPosition(), QString("Awesome server"));
}

#include "tcpserver.moc"
