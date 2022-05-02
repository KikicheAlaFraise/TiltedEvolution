#pragma once

#include <World.h>
#include <Events/EventDispatcher.h>
#include <Games/Events.h>

struct ImguiService;
struct QuestInitHandler;
struct QuestStageHandler;
struct QuestStartStopHandler;
struct NotifyQuestUpdate;

struct TESQuest;

/**
* @brief Handles quest sync
* 
* This service is currently not in use.
*/
class QuestService final : public 
    BSTEventSink<TESQuestStartStopEvent>, 
    BSTEventSink<TESQuestStageEvent>
{
public:
    QuestService(World&, entt::dispatcher&);
    ~QuestService() = default;

    static bool IsNonSyncableQuest(TESQuest* apQuest);
    static void DebugDumpQuests();

private:
    friend struct QuestEventHandler;

    void OnConnected(const ConnectedEvent&) noexcept;
    void OnDisconnected(const DisconnectedEvent&) noexcept;

    BSTEventResult OnEvent(const TESQuestStartStopEvent*, const EventDispatcher<TESQuestStartStopEvent>*) override;
    BSTEventResult OnEvent(const TESQuestStageEvent*, const EventDispatcher<TESQuestStageEvent>*) override;

    void OnQuestUpdate(const NotifyQuestUpdate&) noexcept;

    TESQuest* SetQuestStage(uint32_t aformId, uint16_t aStage);
    bool StopQuest(uint32_t aformId);

    World& m_world;

    entt::scoped_connection m_joinedConnection;
    entt::scoped_connection m_leftConnection;
    entt::scoped_connection m_questUpdateConnection;
};
