//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Work/taskGraph.h"

#include "Work/loops.h"

PXR_NAMESPACE_OPEN_SCOPE

WorkTaskGraph::BaseTask::~BaseTask() = default;

void
WorkTaskGraph::RunLists(const TaskLists &taskLists)
{
    WorkParallelForTBBRange(taskLists.range(), 
        [this] (const TaskLists::range_type &range){
            for (const TaskList &taskList: range) {
                for (const auto task: taskList) {
                    RunTask(task);
                }
            }
        }
    );
}

PXR_NAMESPACE_CLOSE_SCOPE
