#pragma once
#include <Siv3D.hpp> // OpenSiv3D v0.6.2

enum class SceneState {
    Title,
    Game
};

struct GameData {
};

using MyApp = SceneManager<SceneState, GameData>;
