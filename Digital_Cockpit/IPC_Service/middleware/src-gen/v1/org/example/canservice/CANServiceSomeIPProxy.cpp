/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.14.v202310241606.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#include "EventGroupIDs.h"
#include <v1/org/example/canservice/CANServiceSomeIPProxy.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v1 {
namespace org {
namespace example {
namespace canservice {

std::shared_ptr<CommonAPI::SomeIP::Proxy> createCANServiceSomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection) {
    return std::make_shared< CANServiceSomeIPProxy>(_address, _connection);
}

void initializeCANServiceSomeIPProxy() {
    CommonAPI::SomeIP::Factory::get()->registerProxyCreateMethod(
        "org.example.canservice.CANService:v1_0",
        &createCANServiceSomeIPProxy);
}

INITIALIZER(registerCANServiceSomeIPProxy) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeCANServiceSomeIPProxy);
}

CANServiceSomeIPProxy::CANServiceSomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection)
        : CommonAPI::SomeIP::Proxy(_address, _connection),
          onCANDataReceived_(*this, UNDEFINED_EVENTGROUP_ID, CommonAPI::SomeIP::event_id_t(0x80e8), CommonAPI::SomeIP::event_type_e::ET_EVENT , CommonAPI::SomeIP::reliability_type_e::RT_UNRELIABLE, false, std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint32_t>* >(nullptr), static_cast< CommonAPI::SomeIP::ByteBufferDeployment* >(nullptr)))
{
}

CANServiceSomeIPProxy::~CANServiceSomeIPProxy() {
}


CANServiceSomeIPProxy::OnCANDataReceivedEvent& CANServiceSomeIPProxy::getOnCANDataReceivedEvent() {
    return onCANDataReceived_;
}

void CANServiceSomeIPProxy::getCANData(CommonAPI::CallStatus &_internalCallStatus, uint32_t &_id, CommonAPI::ByteBuffer &_data, const CommonAPI::CallInfo *_info) {
    CommonAPI::Deployable< uint32_t, CommonAPI::SomeIP::IntegerDeployment<uint32_t>> deploy_id(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint32_t>* >(nullptr));
    CommonAPI::Deployable< CommonAPI::ByteBuffer, CommonAPI::SomeIP::ByteBufferDeployment> deploy_data(static_cast< CommonAPI::SomeIP::ByteBufferDeployment* >(nullptr));
    CommonAPI::SomeIP::ProxyHelper<
        CommonAPI::SomeIP::SerializableArguments<
        >,
        CommonAPI::SomeIP::SerializableArguments<
            CommonAPI::Deployable<
                uint32_t,
                CommonAPI::SomeIP::IntegerDeployment<uint32_t>
            >,
            CommonAPI::Deployable<
                CommonAPI::ByteBuffer,
                CommonAPI::SomeIP::ByteBufferDeployment
            >
        >
    >::callMethodWithReply(
        *this,
        CommonAPI::SomeIP::method_id_t(0xbb8),
        false,
        false,
        (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
        _internalCallStatus,
        deploy_id, deploy_data);
    _id = deploy_id.getValue();
    _data = deploy_data.getValue();
}

std::future<CommonAPI::CallStatus> CANServiceSomeIPProxy::getCANDataAsync(GetCANDataAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    CommonAPI::Deployable< uint32_t, CommonAPI::SomeIP::IntegerDeployment<uint32_t>> deploy_id(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint32_t>* >(nullptr));
    CommonAPI::Deployable< CommonAPI::ByteBuffer, CommonAPI::SomeIP::ByteBufferDeployment> deploy_data(static_cast< CommonAPI::SomeIP::ByteBufferDeployment* >(nullptr));
    return CommonAPI::SomeIP::ProxyHelper<
        CommonAPI::SomeIP::SerializableArguments<
        >,
        CommonAPI::SomeIP::SerializableArguments<
            CommonAPI::Deployable<
                uint32_t,
                CommonAPI::SomeIP::IntegerDeployment<uint32_t>
            >,
            CommonAPI::Deployable<
                CommonAPI::ByteBuffer,
                CommonAPI::SomeIP::ByteBufferDeployment
            >
        >
    >::callMethodAsync(
        *this,
        CommonAPI::SomeIP::method_id_t(0xbb8),
        false,
        false,
        (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable< uint32_t, CommonAPI::SomeIP::IntegerDeployment<uint32_t> > _id, CommonAPI::Deployable< CommonAPI::ByteBuffer, CommonAPI::SomeIP::ByteBufferDeployment > _data) {
            if (_callback)
                _callback(_internalCallStatus, _id.getValue(), _data.getValue());
        },
        std::make_tuple(deploy_id, deploy_data));
}

void CANServiceSomeIPProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
}

std::future<void> CANServiceSomeIPProxy::getCompletionFuture() {
    return CommonAPI::SomeIP::Proxy::getCompletionFuture();
}

} // namespace canservice
} // namespace example
} // namespace org
} // namespace v1
