# Stonefront

A first-person cat-run rock-trading shop sim. Negotiate with regulars, refuse
scammers, chase specials, and work the Online Auction after hours — all while
a bank loan quota looms over your head.

Inspired by EA FC Career Mode's negotiation system and Hypixel Skyblock's
Auction House / Dark Auctions.

Status: **early development.** No gameplay yet — see `docs/design_doc.md` for
the full design and the milestone-by-milestone build order.

## Tech Stack

- **C++20**
- **SFML 3** (rendering/window/audio) — pulled automatically via CMake `FetchContent`
- **nlohmann/json** — for external rock/customer/event data files
- Custom pixel art (low-end-PC friendly by design)

## Building

Requirements: CMake 3.20+, a C++20-capable compiler.

```bash
git clone https://github.com/<your-username>/stonefront.git
cd stonefront
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

First configure will take a while — it's fetching and building SFML and
nlohmann/json from source. Subsequent builds are fast.

Run the built executable from `build/` (path varies by platform/generator);
assets are copied alongside it automatically as a post-build step.

## Project Structure

```
stonefront/
├── src/            # .cpp source files
├── include/         # .hpp headers
├── assets/
│   ├── textures/     # sprites, pixel art
│   ├── fonts/
│   └── data/          # JSON: rock types, customer scripts, news events
├── docs/            # design_doc.md and other planning docs
├── tests/            # unit tests (optional, off by default)
└── CMakeLists.txt
```

## Design Doc

The full design — story, valuation system, customer types, popularity meter,
auctions, shop upgrades, quota system, and the buildable milestone order —
lives in [`docs/design_doc.md`](docs/design_doc.md).

## License

TBD.
