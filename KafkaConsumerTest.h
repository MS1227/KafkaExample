#include "/usr/local/Cellar/librdkafka/1.5.0/include/librdkafka/rdkafkacpp.h"
#include "DeliveryCallbackHandler.h"
#include "KafkaClientBase.h"
#include <thread>
class KafkaConsumerTest : public KafkaClientBase
{
    public:
        KafkaConsumerTest(std::string name, std::string topic);
        virtual std::thread startThread(RdKafka::Conf* configuration);
    private:
        virtual void configure(RdKafka::Conf* configuration);
        virtual void create(RdKafka::Conf* configuration);
        void consumer();
        void printMessage(RdKafka::Message* message);

        std::string ErrorString;
        RdKafka::Conf *conf = NULL;
        RdKafka::KafkaConsumer *messageConsumer = NULL;
        DeliveryCallbackHandler cbHandler;


};
