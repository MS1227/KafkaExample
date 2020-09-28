#include "KafkaProducer.h"
#include "KafkaConsumerTest.h"
#include <iostream>
#include <thread>

int main()
{
    RdKafka::Conf *prodConf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    RdKafka::Conf *consConf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    //RdKafka::Conf *topicConf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    KafkaProducer *Producer = new KafkaProducer("KafkaProducer", "testTopic");
    KafkaConsumerTest *Consumer = new KafkaConsumerTest("KafkaConsumer", "testTopic");

    std::thread tProd = Producer->startThread(prodConf);
    std::thread tCons = Consumer->startThread(consConf);

    tProd.join();
    tCons.join();

    return 0;
}
