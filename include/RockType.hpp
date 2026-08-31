#pragma once

#include <array>
#include <string>

namespace stonefront
{

// Placeholder/dummy values — not balanced yet. See design doc Section 3
// (Rock Valuation System) for the intended formula this will feed into.
struct RockStatWeights // the weights are constant multipliers for each stat in the valuation formula for all rocks
{
    float purityWeight;
    float brightnessWeight;
    float shapeWeight;
    float sizeWeight;
};

struct RockType
{
    std::string id;           // stable identifier, e.g. "diamond"
    std::string displayName;  // player-facing name, e.g. "Diamond"
    int fixedValue;           // hardcoded baseline value
    int fluctuatingRange;       // range of value fluctuation (e.g. +-20 of value)
};

// Hardcoded rock type table. Values are placeholders - tune during
// Milestone 2 once the valuation formula itself is decided.
inline const std::array<RockType, 10> kRockTypes = {{
    { "opal",    "Opal",    50,  10 },
    { "gold",    "Gold",   120, 20 },
    { "ruby",    "Ruby",    90,  20 },
    { "topaz",   "Topaz",   45,  10 },
    { "diamond", "Diamond", 200, 40 },
    { "emerald", "Emerald", 150, 30 },
    { "sapphire", "Sapphire", 130, 30 },
    { "amethyst", "Amethyst", 70, 20 },
    { "flint", "Flint", 25, 10 },
    { "quartz", "Quartz", 40, 10},
}};

} // namespace stonefront