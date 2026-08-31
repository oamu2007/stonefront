# Stonefront — Game Design Document

*A working design doc.*

## 0. Project Context

- Solo dev
- Tech stack: C++ in VS Code, version controlled with GitHub.
- Graphics: SFML (prior experience, but unsure if SFML will be sufficient for the full scope of this game - flag for later evaluation).
- Inspirations:
  - **EA FC Career Mode** — negotiation system (contract/transfer negotiation mechanic as the model for haggling with customers).
  - **Minecraft Hypixel Skyblock** — Auction House and Dark Auctions (as the model for the Online Auction and Underground Auction systems).

---

## 1. Premise / Story

Everyone in the world is a cat. You move out of your parents' house to start a business trading the one thing your whole town loves: **rocks**. The game is a first-person rock-trading shop sim with a negotiation-driven economy.

---

## 2. Core Gameplay Loop

You run a shop from a first-person POV, talking to customers one at a time at your counter. Negotiation plays out similarly to EA FC's manager/career-mode negotiations. There are three customer types: **Regular**, **Scammer**, and **Special** (see Section 4).

Each day is split into two phases:
1. **Shop Phase** — attend in-person customers using your daily time budget.
2. **Auction Phase** — once you close shop, any remaining time can be spent on the Online Auction (Section 6). Time not used in the shop rolls into auction time.

---

## 3. Rock Valuation System

Every rock's value is built from two layers:

### 3.1 Rock Type Value
Each rock type (opal, gold, ruby, topaz, diamond, etc.) has:
- **Fixed Value** — hardcoded, constant baseline value per rock type.
- **Fluctuating Value** — starts within a hardcoded range (range size varies per rock type) and drifts slightly day to day.
  - **News Events** can heavily swing this value on a given day (e.g., "Celebrity X says diamonds are trash!"). News is read voluntarily from a stand in your shop (see Section 7 — Newspaper Membership).

### 3.2 Stat Score
Each individual rock also has its own stats — candidates include **purity, sharpness, brightness, shape**, etc. (exact stat list and weighting still TBD, but will be constant across all rocks). These stats sum together and adjust the rock's value up or down from the baseline set by its type.

**Open questions:**
- How many stats total, and how each is weighted.
- Exact formula combining Fixed Value + Fluctuating Value + Stat Score.

---

## 4. Customer Types

### 4.1 Regular
- Has an internal valuation of the rock roughly **±15% of its true value**.
- Negotiates toward a fair price. Reaching agreement = successful deal.

### 4.2 Scammer
- Always offers to buy your rocks low or sell their rocks high, in the range of **15–50% off** true value.
- If correctly identified as a scammer and refused, this is the "correct" play.
- Scammers do not negotiate in good faith.

### 4.3 Special
- Custom, scripted customers who trigger unique one-off events. Ideas so far (not final):
  - **Connoisseurs** — searching for specific rare/valuable rocks.
  - **Vendors** — offering to sell you shop upgrades, e.g. a rock evaluation machine.
  - **Recruiters** — inviting you to the Underground Auction (UA).
- Full roster and behavior of Specials still TBD.

---

## 5. Popularity Meter

Starts empty at the beginning of the game. Tracks your shop's reputation and gates content.

**Increases when:**
- Completing a deal with a Regular or Special (Specials give more).
- Correctly refusing to negotiate with a Scammer.

**Decreases when:**
- Failing to close a deal with a Regular or Special (due to lack of funds, lack of rocks, or failure to agree on a fair price) — Specials penalize more than Regulars.
- Refusing to negotiate with a non-Scammer (Regular or Special).
- Small penalty for not attending to all customers before time runs out (see Section 6 — Time System).

**Effects of a higher Popularity Meter:**
- Fewer Scammers appear.
- More Specials appear.
- More total daily customers appear.

---

## 6. Time System

- You have a set amount of daily time to attend in-person customers (exact amount TBD, needs playtesting).
- This same time pool is shared with the Online Auction — you use the shop first, and whatever time remains after you choose to close shop carries over to Auction browsing.
- Failing to see all customers before time runs out costs a small Popularity Meter penalty.

---

## 7. Your Shop

The shop is your home base and can house the following, most of which are purchased from Specials or the Underground Auction and can be upgraded at a cost:

| Feature | Starting State | Upgradeable? | Notes |
|---|---|---|---|
| Counter | Available from start | — | Where you attend customers |
| Rock Storage Chest | Small, starting default | Yes | Total inventory cap; can't receive rocks once full |
| Rock Scanner | Not owned at start | Yes | Gives an estimated value for a chosen rock (yours or a customer's); accuracy and daily use count scale with upgrade level |
| Computer (Online Auction access) | Not owned at start | No upgrades, one-time unlock cost | Required to access the Online Auction after closing shop |
| Newspaper Membership | Not owned at start | Yes, one upgrade tier | Base tier reports yesterday's value-affecting news events; upgrades to a tablet that reports today's events |

---

## 8. Online Auction (Daily)

Accessed once you close shop, using leftover daily time. Has three pages:

### 8.1 Buy-It-Now (BIN)
- Browse a filtered list of rocks (filters e.g. rock type, minimum purity) with fixed prices.
- Instant purchase; rock is delivered the next morning.

### 8.2 Sell-It-Now (SIN)
- Same logic as BIN, but for listing your own rocks at any price you choose.
- Lower prices (relative to true value) sell faster.
- Unsold rocks are returned to you when the listing period ends.

### 8.3 Auction
- Standard bidding auction. Each rock has a random short expiration timer and a current highest bid.
- Final price is influenced by the rock's value plus randomness/luck.
- You can bid on multiple rocks simultaneously.
- If outbid, your prior bid on that rock is refunded once that rock's timer expires.
- Outbid notifications are customizable (e.g., only notify for high-value rock outbids).

### 8.4 Cross-Cutting Rule for Online Auction (BIN + SIN + Auction)
- You can only see/trade rock types you have already acquired at least once from an in-person customer — the online market is gated by prior real-world exposure to that rock type.

---

## 9. Underground Auction (UA) — Weekly Event

- Access likely granted via a Special customer (TBD).
- Displays **one high-value item at a time**, drawn from a set item pool — this can include valuable rocks *and* shop upgrades.
- Each item is shown for **10 seconds**; when time is running low, new bids reset the timer to **3 seconds**.
- **7 items total** are shown per UA session.
- You compete against a small number of in-person rich NPC bidders.
- Attendance is optional — you can skip the UA entirely and instead spend that time working the shop as normal.

---

## 10. The Quota (Loan System)

- At the start of the game, you take out a large loan from the bank to get the shop.
- You owe a recurring quota payment that **grows over time** (growth curve — linear, exponential, etc. — still TBD) until the loan is fully paid off.
- **Missed payments:**
  - 1st and 2nd missed/partial payment: game continues, but the quota growth rate increases as a penalty.
  - 3rd missed payment: **game over.**

---

## 11. Graphics & Tech Stack

**Decision: SFML + custom pixel art.**

This is a solid fit for the project, not just a "good enough for now" compromise:

- The game is fundamentally UI/2D-scene heavy — a static first-person shop view, dialogue/negotiation panels, inventory grids, an auction browser. None of that needs 3D rendering or a heavyweight engine. SFML's 2D sprite/text/shape rendering is well-suited to exactly this.
- Pixel art is cheap to produce well at small scale, which matters for a solo dev balancing this alongside coursework. It also scales great on low-end hardware, since small textures are being pushed instead of high-res assets — this lines up directly with the low-end-PC goal.
- Render load for this kind of game (a handful of UI panels, some sprites, light particle effects) is trivial for even weak hardware. The real performance bottleneck will be game logic (rock valuation calculations, auction simulation, customer AI) — not rendering — and C++ handles that fine regardless of graphics backend.
- Prior SFML experience reduces risk more than switching backend would reduce it. For a project this ambitious in scope, picking up a new engine (Godot, Unity, etc.) at the same time would add risk, not reduce it.
- "Charm" comes from art direction and juice (small animations, sound feedback on a good negotiation, UI flourish) — not rendering horsepower. SFML doesn't hold that back. Pixel-art + SFML is basically the canonical low-end indie shop/sim stack.

**Trade-offs to plan for:**

- No built-in UI framework — buttons, negotiation sliders/dialogue trees, scrollable auction lists, tooltips, etc. all need to be built or brought in via a helper library. This is real work, budget time for it.
- No animation system, tilemap editor, or scene graph — build these yourself or use a small helper lib. Minor loss for a shop game that's mostly static scenes and UI-driven interaction.
- Build against **SFML 3** (current major version) from day one rather than following older SFML 2 tutorials — the API changed meaningfully between versions, and starting on 3 avoids relearning syntax mid-project.

### 11.1 Useful SFML-adjacent Libraries

| Library | Purpose | Why it's relevant here |
|---|---|---|
| **Dear ImGui** (with the SFML backend, `imgui-sfml`) | Immediate-mode GUI | Great for quickly building debug tools, and can be pushed into real UI for data-heavy screens like the Auction House browser (filters, tables, tooltips) without hand-rolling every widget. |
| **TGUI** | Retained-mode GUI built specifically for SFML | Better fit than ImGui for *player-facing*, styled UI (buttons, panels, sliders) since it's meant to look like part of the game rather than a debug overlay. Worth evaluating against ImGui for the negotiation and shop UI. |
| **Thor** | SFML extension library | Adds particle systems, animation helpers, and resource management on top of SFML — useful if hand-rolling animation/particles becomes too much overhead. |
| **nlohmann/json** | JSON parsing (not SFML-specific) | Useful for defining rock types, stat weights, news events, and Special customer scripts as external data files instead of hardcoding them — makes balancing/tuning much faster. |
| **SQLite** (via `sqlite3` or a C++ wrapper like `SQLiteCpp`) | Lightweight embedded database | Worth considering for save data (inventory, popularity meter, quota state, auction history) instead of hand-rolled save files, especially once the auction systems generate a lot of persistent state. |
| **spdlog** | Logging | Not glamorous, but useful for debugging a project with this many interacting systems (valuation, auctions, popularity, quota) without littering the code with `std::cout`. |

You don't need all of these — start with plain SFML and pull in a UI library (TGUI or ImGui) once you hit the point where hand-rolled buttons/panels start slowing you down.

---

## 12. Buildable Order (Suggested Milestones)

Given the scope, the goal is to reach a *minimum playable loop* as early as possible, then layer systems on top. Rough order, front-loading the things everything else depends on:

**Milestone 1 — Skeleton & Static Shop Scene**
- SFML window, game loop, basic asset loading.
- Static first-person shop background rendered.
- A single placeholder customer sprite and a basic dialogue/text box.
- No real gameplay yet — just proving the render pipeline and scene structure work.

**Milestone 2 — Rock Data & Valuation Core**
- Define rock types as data (ideally external file, e.g. JSON) with Fixed Value, Fluctuating Value range, and stat fields.
- Implement the value formula (even a placeholder version) combining Fixed + Fluctuating + Stat Score.
- No customers yet — just a way to generate a rock and print/display its computed value, to validate the math in isolation.

**Milestone 3 — One Customer Type: Regular, with Negotiation**
- Implement the Regular customer's internal valuation (±15%) and a basic negotiation UI/flow (offer, counter-offer, accept/reject).
- This is the core interaction loop of the whole game — get it feeling good before adding anything else.
- At this point you have a genuinely playable (if shallow) loop: rock shows up → customer wants to trade → you negotiate → deal or no deal.

**Milestone 4 — Scammer Customer Type + Popularity Meter (basic)**
- Add Scammer behavior (jacked/lowballed offers, no negotiation).
- Add the Popularity Meter with its core rules (deal success/failure, correct/incorrect scammer refusal).
- Still no time system yet — customers can be handled in any order/pace.

**Milestone 5 — Time System & Day Structure**
- Add the daily time budget and the "close shop" transition.
- Add the day-end penalty for unattended customers.
- This turns the game into actual day-by-day play rather than an open sandbox.

**Milestone 6 — Shop Upgrades (Storage + Scanner)**
- Add the storage chest (with capacity limits) and rock scanner (with accuracy/use-count tied to upgrade level).
- Establishes the money-sink/upgrade loop before auctions complicate the economy.

**Milestone 7 — Online Auction: BIN & SIN**
- These are simpler than the bidding Auction page (fixed-price buy/sell), so build them first.
- Requires the computer shop-upgrade to be unlocked.

**Milestone 8 — Online Auction: Bidding Page**
- Add the timer-based bidding mechanic, multiple simultaneous bids, outbid refunds/notifications.
- This is more complex (needs simulated competing bidders), so it comes after BIN/SIN are stable.

**Milestone 9 — News Events & Newspaper Membership**
- Add the news system that swings Fluctuating Value, plus the newspaper/tablet upgrade.
- This plugs into the valuation core from Milestone 2, now with a daily read/skip choice layered on top.

**Milestone 10 — Special Customers**
- Start with 1-2 Special customer types (e.g. connoisseur, upgrade vendor) before building out the full roster.
- These depend on the Popularity Meter (spawn rate) and shop upgrade system already being in place.

**Milestone 11 — Underground Auction (UA)**
- Build last among the major systems — it's the most mechanically distinct (live countdown bidding against NPC rivals, weekly cadence, item pool) and depends on Special customers to grant access.

**Milestone 12 — Quota / Loan System**
- Layer the recurring payment, growth curve, and missed-payment penalties on top of a working economy.
- Deliberately late: you need money flowing in/out from a stable game before quota pressure can be tuned meaningfully.

**Ongoing throughout:** balancing/tuning (rock values, negotiation ranges, popularity effects, quota growth) should be treated as a continuous pass, not a milestone — this is why keeping rock/customer/event data external and easy to edit (Milestone 2, via JSON) pays off across the whole build.

---

## 13. Open Design Questions (Running List)

- Full list and weighting of rock stats (purity, sharpness, brightness, shape, etc.).
- Exact formula combining Fixed Value, Fluctuating Value, and Stat Score.
- Full roster and mechanics for Special customer events.
- Exact daily time budget (needs playtesting).
- How UA access is unlocked.
- Quota growth curve (linear vs. exponential vs. other).
- Whether SFML will be sufficient for the full scope, or if another approach is needed.

---

## 14. Explicit Non-Goals (For Now)

- No code has been written yet — this document is planning/scoping only.
- Nothing below this line has been decided; it's just an idea log to revisit later.
