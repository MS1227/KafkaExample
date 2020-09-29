#include "KafkaConsumerTest.h"
#include <iostream>
#include <string>
#include <chrono>
KafkaConsumerTest::KafkaConsumerTest(std::string name, std::string topic, std::string groupId) :
                   KafkaClientBase(name, topic)
{
    m_groupId = groupId;
}
void KafkaConsumerTest::configure(RdKafka::Conf *configuration)
{

    if (configuration->set("bootstrap.servers","localhost:9092", ErrorString) !=
        RdKafka::Conf::CONF_OK)
    {
        std::cerr << ErrorString << std::endl;
    }

    if (configuration->set("group.id",
                           m_groupId,
                           ErrorString) !=
        RdKafka::Conf::CONF_OK)
    {
        std::cerr << ErrorString << '\n';
    }

    if (configuration->set("auto.offset.reset",
                           "earliest",
                           ErrorString) !=
        RdKafka::Conf::CONF_OK)
    {
        std::cerr << ErrorString << '\n';
    }

}
void KafkaConsumerTest::consumer()
{
    RdKafka::Message *tempMessage = NULL;
    while (true)
    {
        std::this_thread::sleep_for (std::chrono::seconds(1));
        tempMessage = messageConsumer->consume(0);
        if (tempMessage->err() == RdKafka::ErrorCode::ERR_NO_ERROR)
        {
            printMessage(tempMessage);
        }
    }
}
void KafkaConsumerTest::printMessage(RdKafka::Message* message)
{
    std::cout << "Length: " << static_cast<int>(message->len()) <<
         " Payload: " << static_cast<const char *>(message->payload()) << std::endl;
}
std::thread KafkaConsumerTest::startThread(RdKafka::Conf* configuration)
{
    configure(configuration);
    create(configuration);

    return std::thread ([=] {consumer();});
}
void KafkaConsumerTest::create(RdKafka::Conf *configuration)
{
    messageConsumer = RdKafka::KafkaConsumer::create(configuration, ErrorString);

    if (!messageConsumer)
    {
        std::cerr << "Consumer Creation Failed!" << '\n';
        exit(1);
    }

    RdKafka::ErrorCode status = messageConsumer->subscribe(m_Topics);

    if (status != RdKafka::ErrorCode::ERR_NO_ERROR)
    {
        std::cerr << "Topic subscribe failed! - Error Code:" << status << '\n';
    }
}
