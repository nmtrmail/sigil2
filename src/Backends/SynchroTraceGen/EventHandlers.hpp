#ifndef STGEN_EVENTHANDLERS_H
#define STGEN_EVENTHANDLERS_H

#include "Core/Backends.hpp"
#include "ThreadContext.hpp"

namespace STGen
{

auto onParse(Args args) -> void;
auto onExit() -> void;
auto requirements() -> sigil2::capabilities;
/* Sigil2 hooks */

class EventHandlers : public BackendIface
{
  public:
    EventHandlers() {}
    EventHandlers(const EventHandlers &) = delete;
    EventHandlers &operator=(const EventHandlers &) = delete;
    virtual ~EventHandlers() override;

    virtual auto onSyncEv(const sigil2::SyncEvent &ev) -> void override;
    virtual auto onCompEv(const sigil2::CompEvent &ev) -> void override;
    virtual auto onMemEv(const sigil2::MemEvent &ev) -> void override;
    virtual auto onCxtEv(const sigil2::CxtEvent &ev) -> void override;
    /* Sigil2 event hooks */

  private:
    auto onSwapTCxt(TID newTID) -> void;
    auto onCreate(Addr data) -> void;
    auto onBarrier(Addr data) -> void;
    auto convertAndFlush(const sigil2::SyncEvent &ev) -> void;
    /* helpers */

    std::unordered_map<TID, std::unique_ptr<ThreadContext>> tcxts;
    TID currentTID{SO_UNDEF};
    ThreadContext *cachedTCxt{nullptr};
};

}; //end namespace STGen

#endif
