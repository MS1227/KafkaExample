#include "KafkaClientBase.h"
KafkaClientBase::KafkaClientBase(const std::string name, const std::string topic)
{
    m_Name = name;
    m_Topics.push_back(topic);
}
std::string KafkaClientBase::getName()
{
    return m_Name;
}
std::string KafkaClientBase::getTopic()
{
    return m_Topics.front();
}
