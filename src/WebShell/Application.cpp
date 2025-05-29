//
// Created by erik on 29.05.25.
//

#include "Application.h"

#include "WidgetWindow.h"
#include "constants.h"

namespace WebShell {

    void initializeWebExtension(WebKitWebContext* context, gpointer user_data);

    Application::Application()
    {
        initialize();
    }

    Application::~Application() { }

    void Application::run() const
    {
        m_application->run();
    }

    void Application::initialize()
    {
        m_application = Gtk::Application::create("org.darman96.web-shell");

        auto context = webkit_web_context_get_default();
        webkit_web_context_add_path_to_sandbox(context, WEB_EXTENSION_DIR.c_str(), true);
        g_signal_connect(context, "initialize-web-process-extensions", G_CALLBACK(initializeWebExtension), this);

        m_application->signal_activate().connect([this]()
        {
            const auto overlayWindow = new WidgetWindow(WidgetSpecifications{
                .title = "Overlay Widget",
                .layer = WidgetLayer::Overlay,
                .anchor = WidgetAnchor::None,
                .size = {400, 300},
            });

            m_application->add_window(*overlayWindow->getGtkWindow());
            m_widgets.push_back(overlayWindow);
            overlayWindow->show();

            const auto barWindow = new WidgetWindow(WidgetSpecifications{
                .title = "Bar Widget",
                .layer = WidgetLayer::Top,
                .anchor = WidgetAnchor::Top | WidgetAnchor::Left | WidgetAnchor::Right,
                .size = {0, 32},
                .margins = {10, 10, 0, 10},
            });

            m_application->add_window(*barWindow->getGtkWindow());
            m_widgets.push_back(barWindow);
            barWindow->show();
        });
    }

    void initializeWebExtension(WebKitWebContext* context, gpointer user_data)
    {
        static guint32 uniqueId = 0;

        webkit_web_context_set_web_process_extensions_directory(context, WEB_EXTENSION_DIR.c_str());
        webkit_web_context_set_web_process_extensions_initialization_user_data(context, g_variant_new_uint32(uniqueId++));
    }

} // WebShell