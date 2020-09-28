#include "/usr/local/Cellar/librdkafka/1.5.0/include/librdkafka/rdkafkacpp.h"
#include "DeliveryCallbackHandler.h"
#include "KafkaClientBase.h"
#include <thread>
#pragma once
class KafkaProducer : public KafkaClientBase
{
    public:
        KafkaProducer(std::string name, std::string topic);
        virtual std::thread startThread(RdKafka::Conf *configuration);
    private:
        virtual void configure(RdKafka::Conf* configuration);
        virtual void create(RdKafka::Conf* configuration);
        void producer();

        std::string ErrorString;
        RdKafka::Conf *conf = NULL;
        RdKafka::Producer *messageProducer = NULL;
        DeliveryCallbackHandler cbHandler;


};
