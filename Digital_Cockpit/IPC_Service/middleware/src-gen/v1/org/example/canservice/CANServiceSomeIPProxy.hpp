/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.14.v202310241606.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#ifndef V1_ORG_EXAMPLE_CANSERVICE_CAN_SERVICE_SOMEIP_PROXY_HPP_
#define V1_ORG_EXAMPLE_CANSERVICE_CAN_SERVICE_SOMEIP_PROXY_HPP_

#include <v1/org/example/canservice/CANServiceProxyBase.hpp>
#include <v1/org/example/canservice/CANServiceSomeIPDeployment.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/Factory.hpp>
#include <CommonAPI/SomeIP/Proxy.hpp>
#include <CommonAPI/SomeIP/Types.hpp>
#include <CommonAPI/SomeIP/Event.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <string>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace org {
namespace example {
namespace canservice {

class CANServiceSomeIPProxy
    : virtual public CANServiceProxyBase,
      virtual public CommonAPI::SomeIP::Proxy {
public:
    CANServiceSomeIPProxy(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection);

    virtual ~CANServiceSomeIPProxy();

    virtual OnCANDataReceivedEvent& getOnCANDataReceivedEvent();

    virtual void getCANData(CommonAPI::CallStatus &_internalCallStatus, uint32_t &_id, CommonAPI::ByteBuffer &_data, const CommonAPI::CallInfo *_info);

    virtual std::future<CommonAPI::CallStatus> getCANDataAsync(GetCANDataAsyncCallback _callback, const CommonAPI::CallInfo *_info);

    virtual void getOwnVersion(uint16_t &_major, uint16_t &_minor) const;

    virtual std::future<void> getCompletionFuture();

private:
    CommonAPI::SomeIP::Event<OnCANDataReceivedEvent, CommonAPI::Deployable< uint32_t, CommonAPI::SomeIP::IntegerDeployment<uint32_t> >, CommonAPI::Deployable< CommonAPI::ByteBuffer, CommonAPI::SomeIP::ByteBufferDeployment >> onCANDataReceived_;

};

} // namespace canservice
} // namespace example
} // namespace org
} // namespace v1

#endif // V1_ORG_EXAMPLE_CANSERVICE_CAN_Service_SOMEIP_PROXY_HPP_
