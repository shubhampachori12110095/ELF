/**
* Copyright (c) 2017-present, Facebook, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-style license found in the
* LICENSE file in the root directory of this source tree. An additional grant
* of patent rights can be found in the PATENTS file in the same directory.
*/

#pragma once

#include "elf/pybind_helper.h"
#include "elf/comm_template.h"
#include "elf/ai_comm.h"

#include "ai.h"
#include "go_game_specific.h"
#include "go_state.h"
#include <random>
#include <map>

// Game interface for Go.
class GoGame {
private:
    int _game_idx = -1;
    uint64_t _seed = 0;
    GameOptions _options;

    std::vector<std::unique_ptr<AIWithComm>> _ais;
    int _curr_loader_idx;
    std::mt19937 _rng;
    
    // Only used when we want to run online 
    GoState _state;

public:
    GoGame(int game_idx, const GameOptions& options);

    void Init(AIComm *ai_comm);

    void MainLoop(const std::atomic_bool& done) {
        // Main loop of the game.
        while (true) {
            Act(done);
            if (done.load()) break;
        }
    }

    void Act(const std::atomic_bool& done);
    string ShowBoard() const { return _state.ShowBoard(); }
};
