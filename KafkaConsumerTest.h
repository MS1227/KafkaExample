#include "/usr/local/Cellar/librdkafka/1.5.0/include/librdkafka/rdkafkacpp.h"
#include "DeliveryCallbackHandler.h"
#include "KafkaClientBase.h"
#include <thread>
class KafkaConsumerTest : public KafkaClientBase
{
    public:
        KafkaConsumerTest(std::string name, std::string topic, std::string groupId);
        virtual std::thread startThread(RdKafka::Conf* configuration);
    private:
        virtual void configure(RdKafka::Conf* configuration);
        virtual void create(RdKafka::Conf* configuration);
        void consumer();
        void printMessage(RdKafka::Message* message);

        std::string m_groupId;
        std::thread m_Thread;
        RdKafka::KafkaConsumer *messageConsumer = NULL;

};
