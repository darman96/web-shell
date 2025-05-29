//
// Created by erik on 29.05.25.
//

#include "WidgetWindow.h"

#include <gtkmm.h>
#include <gtk4-layer-shell.h>
#include <webkit/webkit.h>
#include <jsc/jsc.h>

namespace WebShell {

    WidgetWindow::WidgetWindow(const WidgetSpecifications& specifications)
        : m_window(nullptr), m_webViewWidget(nullptr), m_webView(nullptr)
    {
        initializeWindow(specifications);
        initializeWebView();
    }

    WidgetWindow::~WidgetWindow() = default;

    void WidgetWindow::show() const
    {
        if (m_window) {
            m_window->present();
        }
    }

    void WidgetWindow::initializeWindow(const WidgetSpecifications& specifications)
    {
        m_window = new Gtk::Window();
        m_window->set_title(specifications.title);
        m_window->set_default_size(specifications.size.width, specifications.size.height);

        gtk_layer_init_for_window(m_window->gobj());

        GtkLayerShellLayer layer = GTK_LAYER_SHELL_LAYER_OVERLAY;

        switch (specifications.layer)
        {
            case WidgetLayer::Top:
                layer = GTK_LAYER_SHELL_LAYER_TOP;
                break;
            case WidgetLayer::Bottom:
                layer = GTK_LAYER_SHELL_LAYER_BOTTOM;
                break;
            case WidgetLayer::Overlay:
                layer = GTK_LAYER_SHELL_LAYER_OVERLAY;
                break;
        }
        
        gtk_layer_set_layer(m_window->gobj(), layer);

        // Reset all anchors to false first
        gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_TOP, false);
        gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
        gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, false);
        gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, false);

        // Set anchors based on bitmask
        if (specifications.anchor != WidgetAnchor::None)
        {
            gtk_layer_set_exclusive_zone(m_window->gobj(), 32);
            gtk_layer_auto_exclusive_zone_enable(m_window->gobj());
        }
        if ((specifications.anchor & WidgetAnchor::Top) == WidgetAnchor::Top)
            gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
        if ((specifications.anchor & WidgetAnchor::Bottom) == WidgetAnchor::Bottom)
            gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
        if ((specifications.anchor & WidgetAnchor::Left) == WidgetAnchor::Left)
            gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
        if ((specifications.anchor & WidgetAnchor::Right) == WidgetAnchor::Right)
            gtk_layer_set_anchor(m_window->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);

        gtk_layer_set_margin(m_window->gobj(), GTK_LAYER_SHELL_EDGE_TOP, specifications.margins.top);
        gtk_layer_set_margin(m_window->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, specifications.margins.bottom);
        gtk_layer_set_margin(m_window->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, specifications.margins.left);
        gtk_layer_set_margin(m_window->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, specifications.margins.right);
    }

    void WidgetWindow::initializeWebView()
    {
        const auto widgetHandle = webkit_web_view_new();
        m_webViewWidget = Glib::wrap(widgetHandle);
        m_webView = WEBKIT_WEB_VIEW(widgetHandle);
        m_window->set_child(*m_webViewWidget);

        webkit_web_view_load_uri(m_webView, "file:///mnt/hdd_01/data/Dev/repos/web-shell-widgets/dist/widgets/launcher/index.html");
    }

} // WebShell
