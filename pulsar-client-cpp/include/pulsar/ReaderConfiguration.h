/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef PULSAR_READER_CONFIGURATION_H_
#define PULSAR_READER_CONFIGURATION_H_

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <pulsar/Result.h>
#include <pulsar/Message.h>

#pragma GCC visibility push(default)
namespace pulsar {

class Reader;
class PulsarWrapper;

/// Callback definition for non-data operation
typedef boost::function<void(Result result)> ResultCallback;

/// Callback definition for MessageListener
typedef boost::function<void(Reader reader, const Message& msg)> ReaderListener;

class ReaderConfigurationImpl;

/**
 * Class specifying the configuration of a consumer.
 */
class ReaderConfiguration {
 public:
    ReaderConfiguration();
    ~ReaderConfiguration();
    ReaderConfiguration(const ReaderConfiguration&);
    ReaderConfiguration& operator=(const ReaderConfiguration&);

    /**
     * A message listener enables your application to configure how to process
     * messages. A listener will be called in order for every message received.
     */
    ReaderConfiguration& setReaderListener(ReaderListener listener);
    ReaderListener getReaderListener() const;
    bool hasReaderListener() const;

    /**
     * Sets the size of the reader receive queue.
     *
     * The consumer receive queue controls how many messages can be accumulated by the Consumer before the
     * application calls receive(). Using a higher value could potentially increase the consumer throughput
     * at the expense of bigger memory utilization.
     *
     * Setting the consumer queue size as zero decreases the throughput of the consumer, by disabling pre-fetching of
     * messages. This approach improves the message distribution on shared subscription, by pushing messages only to
     * the consumers that are ready to process them. Neither receive with timeout nor Partitioned Topics can be
     * used if the consumer queue size is zero. The receive() function call should not be interrupted when
     * the consumer queue size is zero.
     *
     * Default value is 1000 messages and should be good for most use cases.
     *
     * @param size
     *            the new receiver queue size value
     */
    void setReceiverQueueSize(int size);
    int getReceiverQueueSize() const;

    void setReaderName(const std::string& readerName);
    const std::string& getReaderName() const;

 private:
    boost::shared_ptr<ReaderConfigurationImpl> impl_;
};

}
#pragma GCC visibility pop
#endif /* PULSAR_READER_CONFIGURATION_H_ */
