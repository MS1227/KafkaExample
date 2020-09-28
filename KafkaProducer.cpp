#include "KafkaProducer.h"
#include <iostream>
#include <string>
#include <chrono>
KafkaProducer::KafkaProducer(std::string name, std::string topic) :
               KafkaClientBase(name,topic)
{

}
void KafkaProducer::configure(RdKafka::Conf *configuration)
{

    if (configuration->set("bootstrap.servers","localhost:9092", ErrorString) !=
        RdKafka::Conf::CONF_OK)
    {
        std::cerr << ErrorString << std::endl;
    }

    if (configuration->set("dr_cb", &cbHandler,ErrorString) !=
        RdKafka::Conf::CONF_OK)
    {
        std::cerr << ErrorString << '\n';
    }

}
void KafkaProducer::producer()
{
    int i = 0;
    while (true)
    {
        std::string message = getName() +" - Topic: " + getTopic() + " - " + std::to_string(i);
        messageProducer->poll(0);
        std::this_thread::sleep_for (std::chrono::seconds(1));
        messageProducer->produce(getTopic(), RdKafka::Topic::PARTITION_UA,
                                 RdKafka::Producer::RK_MSG_COPY,
                                 const_cast<char *>(message.c_str()),message.length(),
                                 NULL, 0,
                                 0, NULL);
        i++;

    }
}
std::thread KafkaProducer::startThread(RdKafka::Conf *configuration)
{
    configure(configuration);
    create(configuration);

    return std::thread ([=] {producer();});
}
void KafkaProducer::create(RdKafka::Conf *configuration)
{
    messageProducer = RdKafka::Producer::create(configuration, ErrorString);

    if (!messageProducer)
    {
        std::cerr << "Producer Creation Failed!" << '\n';
        exit(1);
    }
}
