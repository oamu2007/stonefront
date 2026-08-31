#pragma once

#include <array>
#include <string>

namespace stonefront
{

// Placeholder/dummy values — not balanced yet. See design doc Section 3
// (Rock Valuation System) for the intended formula this will feed into.
struct RockStatWeights
{
    float purityWeight;
    float brightnessWeight;
    float shapeWeight;
};

struct RockType
{
    std::string id;           // stable identifier, e.g. "diamond"
    std::string displayName;  // player-facing name, e.g. "Diamond"
    int fixedValue;           // hardcoded baseline value
    int fluctuatingMin;       // lower bound of the day-to-day drifting range
    int fluctuatingMax;       // upper bound of the day-to-day drifting range
    RockStatWeights statWeights;
};

// Hardcoded rock type table. Values are placeholders — tune during
// Milestone 2 once the valuation formula itself is decided.
inline const std::array<RockType, 5> kRockTypes = {{
    { "opal",    "Opal",    50,  40,  60, { 1.0f, 1.5f, 0.5f } },
    { "gold",    "Gold",   120, 100, 140, { 2.0f, 1.0f, 0.25f } },
    { "ruby",    "Ruby",    90,  70, 110, { 1.5f, 1.5f, 1.0f } },
    { "topaz",   "Topaz",   45,  35,  55, { 1.0f, 1.0f, 0.5f } },
    { "diamond", "Diamond", 200, 160, 240, { 2.5f, 2.0f, 1.0f } },
}};

} // namespace stonefront