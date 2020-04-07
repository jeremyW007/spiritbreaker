#ifndef _PUBLISHER_H_
#define _PUBLISHER_H_

#include "sbs_decl.h"
#include <unordered_map>
#include <memory>
#include <mutex>

#include "webrtcconnection.h"

SBS_NAMESPACE_DECL_BEGIN
class Peer;
class Subscriber;
class Publisher
{
public:
    Publisher(uint32_t id, std::shared_ptr<Peer> peer);
    ~Publisher();

    bool AddSubscriber(std::shared_ptr<Subscriber> s);
    bool RemoveSubscriber(uint32_t peerid);
    std::shared_ptr<Subscriber> GetSubscriber(uint32_t peerid);

    int SetRemoteSdp(const std::string &sdp, std::string &lsdp);

    uint32_t id(){return id_;}
    Json::Value GetCandidate(){return webrtc_conn_->GetCandidate();}

private:
    uint32_t id_;
    std::shared_ptr<Peer> peer_;
    // The key is the peer id of the Subscriber belongs to.
    std::unordered_map<uint32_t, std::shared_ptr<Subscriber>> subscribers_;
    std::mutex subscribers_mutex_;

    // Just recv data
    rtc::scoped_refptr<WebRtcConnection> webrtc_conn_;
};
SBS_NAMESPACE_DECL_END
#endif//_PUBLISHER_H_

