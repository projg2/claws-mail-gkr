#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <glib.h>
#include <glib/gi18n.h>

#include "gkr-if.h"

#include "version.h"
#include "plugin.h"
#include "hooks.h"
#include "account.h"

#define PLUGIN_NAME (_("gnome-keyring"))

static guint get_hookid;

gint plugin_init(gchar **error)
{
	if (!check_plugin_version(MAKE_NUMERIC_VERSION(3,8,0,0),
				VERSION_NUMERIC, PLUGIN_NAME, error))
		return -1;

	get_hookid = hooks_register_hook(PASSWORD_GET_HOOKLIST, &password_get_hook, NULL);
	return 0;
}

gboolean plugin_done(void)
{
	hooks_unregister_hook(PASSWORD_GET_HOOKLIST, get_hookid);
	return TRUE;
}

const gchar *plugin_name(void)
{
	return PLUGIN_NAME;
}

const gchar *plugin_desc(void)
{
	return _("This plugin adds support for stroing password in gnome-keyring.");
}

const gchar *plugin_type(void)
{
	return "GTK2";
}

const gchar *plugin_licence(void)
{
	return "BSD";
}

const gchar *plugin_version(void)
{
	return VERSION;
}

struct PluginFeature *plugin_provides(void)
{
	static struct PluginFeature features[] = {
		{PLUGIN_OTHER, N_("Password storage")},
		{PLUGIN_NOTHING, NULL}
	};

	return features;
}
