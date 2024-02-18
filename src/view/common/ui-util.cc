#include "ui-util.h"

#include <gtkmm-4.0/gtkmm.h>
#include <string.h>

int view::UpdateBuilder(
    const Glib::RefPtr<Gtk::Builder>& ref_builder,
    const std::string& filename) {
    try {
        if (!ref_builder->add_from_resource(filename)) {
            printf("Builder failed to add_from_file\n");
            return -1;
        }

    } catch (const Glib::FileError& ex) {
        printf("FileError: %s\n", ex.what());
        return -1;

    } catch (const Glib::MarkupError& ex) {
        printf("MarkupError: %s\n", ex.what());
        return -1;

    } catch (const Gtk::BuilderError& ex) {
        printf("BuilderError: %s\n", ex.what());
        return -1;
    }

    return 0;
}