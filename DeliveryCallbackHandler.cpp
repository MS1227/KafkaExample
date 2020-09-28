#include "DeliveryCallbackHandler.h"
void DeliveryCallbackHandler::dr_cb(RdKafka::Message &message)
{
    if (message.err())
    {
        std::cerr << "Message Failed Delivery" << '\n';
    }
}
