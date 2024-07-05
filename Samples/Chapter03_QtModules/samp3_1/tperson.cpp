#include "tperson.h"

TPerson::TPerson(QString aName, QObject *parent)
    : QObject{parent}
{
    // 构造函数
    m_name = aName;
}

TPerson::~TPerson()
{
    // 构造函数里显示信息，可以看到对象是否被删除
    qDebug("TPerson对象被删除了");
}

int TPerson::age()
{
    // 返回age属性的值
    return m_age;
}

void TPerson::setAge(int value)
{
    // 设置age属性的值
    if(m_age != value)
    {
        m_age = value;
        emit ageChanged(m_age); // 发射信号
    }
}

void TPerson::incAge()
{
    m_age ++;
    emit ageChanged(m_age); // 发射信号
}
