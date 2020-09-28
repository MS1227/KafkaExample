#include "/usr/local//Cellar/librdkafka/1.5.0/include/librdkafka/rdkafkacpp.h"
#include <iostream>
#pragma once
class DeliveryCallbackHandler : public RdKafka::DeliveryReportCb
{
public:
    void dr_cb(RdKafka::Message &message);
};
