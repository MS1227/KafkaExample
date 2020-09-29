#include "/usr/local/Cellar/librdkafka/1.5.0/include/librdkafka/rdkafkacpp.h"
#include <thread>
#include <string>

#pragma once

class KafkaClientBase
{
public:
    KafkaClientBase(const std::string name, const std::string topic);
    virtual std::thread startThread(RdKafka::Conf *configuration) = 0;

protected:
    virtual void configure(RdKafka::Conf *configuration) = 0;
    virtual void create(RdKafka::Conf *configuration) = 0;
    std::string getName();
    std::string getTopic();

    std::string m_Name;
    std::vector<std::string> m_Topics;
    RdKafka::Conf *conf = NULL;
    std::string ErrorString;

};
