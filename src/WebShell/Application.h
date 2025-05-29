//
// Created by erik on 29.05.25.
//

#pragma once

#include <vector>
#include <gtkmm.h>

namespace WebShell {
    class WidgetWindow;

    class Application {

    public:
        Application();
        ~Application();

        void run() const;

    private:
        void initialize();

    private:
        Glib::RefPtr<Gtk::Application> m_application;
        std::vector<WidgetWindow*> m_widgets;
    };

} // WebShell

