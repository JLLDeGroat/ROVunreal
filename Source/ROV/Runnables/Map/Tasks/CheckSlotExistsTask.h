#pragma once

#include "CoreMinimal.h"
#include "Async/TaskGraphInterfaces.h"
#include "../../../Pawns/Components/PawnMapSlotSpawnerComponent.h"
#include "Misc/ScopeLock.h"
#include "VgCore/Domain/Debug/DebugMessages.h"

class CheckSlotExistsTask : public FNonAbandonableTask
{
public:
    UPawnMapSlotSpawnerComponent *SpawnComp;
    int TestXValue;
    int TestYValue;

    bool *Exists;
    bool *IsComplete;

    // Constructor to initialize the task with the reference and output pointer
    CheckSlotExistsTask(UPawnMapSlotSpawnerComponent *inSpawnComp, int inX, int inY, bool *OutExists, bool *OutComplete)
        : SpawnComp(inSpawnComp), TestXValue(inX), TestYValue(inY), Exists(OutExists), IsComplete(OutComplete)
    {
    }

    void DoWork()
    {
        if (IsValid(SpawnComp))
        {
            *Exists = SpawnComp->GetSlotAlreadyExists(TestXValue, TestYValue);
            UDebugMessages::LogDisplay(UDebugMessages::StaticClass(), "did work");
            *IsComplete = true;
        }
    }

    // Optional: Providing a stat ID for this task
    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(LoadBpActorTask, STATGROUP_ThreadPoolAsyncTasks);
    }

    ENamedThreads::Type GetDesiredThread() { return ENamedThreads::GameThread; }
    static ESubsequentsMode::Type GetSubsequentsMode() { return ESubsequentsMode::TrackSubsequents; }
    // This method is invoked to execute the task on the Game Thread
    void DoTask(ENamedThreads::Type CurrentThread, FGraphEventRef MyCompletionGraphEvent)
    {
        DoWork();
    }
};