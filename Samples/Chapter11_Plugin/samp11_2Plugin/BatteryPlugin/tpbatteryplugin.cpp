#include "tpbatteryplugin.h"
#include "tpbattery.h"

#include <QtPlugin>

TPBatteryPlugin::TPBatteryPlugin(QObject *parent)
    : QObject(parent)
{}

void TPBatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPBatteryPlugin::isInitialized() const
{
    // 是否初始化
    return m_initialized;
}

QWidget *TPBatteryPlugin::createWidget(QWidget *parent)
{
    // 返回自定义Widget组件的实例
    return new TPBattery(parent);
}

QString TPBatteryPlugin::name() const
{
    // 自定义Widget组件类的名称
    return QLatin1String("TPBattery");
}

QString TPBatteryPlugin::group() const
{
    // 组件面板中所属分组名称
    return QLatin1String("My Widgets");
}

QIcon TPBatteryPlugin::icon() const
{
    // 图标文件名
    return QIcon();
}

QString TPBatteryPlugin::toolTip() const
{
    // toolTip信息
    return QLatin1String("");
}

QString TPBatteryPlugin::whatsThis() const
{
    // what's this信息
    return QLatin1String("");
}

bool TPBatteryPlugin::isContainer() const
{
    // 是否作为容器，false表示该组件上不允许再放其他组件
    return false;
}

QString TPBatteryPlugin::domXml() const
{
    // XML文件描述符
    return QLatin1String(R"(<widget class="TPBattery" name="tPBattery">
</widget>)");
}

QString TPBatteryPlugin::includeFile() const
{
    // 包含文件名
    return QLatin1String("tpbattery.h");
}
