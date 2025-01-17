#include "pluginsreload.hpp"

#include <boost/log/trivial.hpp>
#include <git2.h>

#include "../../lua/plugins/plugin.hpp"
#include "../../lua/plugins/pluginengine.hpp"

using porla::Lua::Plugins::PluginEngine;
using porla::Lua::Plugins::PluginInstallOptions;

using porla::Methods::PluginsReload;
using porla::Methods::PluginsReloadReq;
using porla::Methods::PluginsReloadRes;

PluginsReload::PluginsReload(PluginEngine& plugin_engine)
    : m_plugin_engine(plugin_engine)
{
}

void PluginsReload::Invoke(const PluginsReloadReq& req, WriteCb<PluginsReloadRes> cb)
{
    auto plugin_state = m_plugin_engine.Plugins().find(req.name);

    if (plugin_state == m_plugin_engine.Plugins().end())
    {
        return cb.Error(-1, "Plugin not found");
    }

    m_plugin_engine.Reload(req.name);

    cb.Ok({});
}
