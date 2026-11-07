# Geometry Defender --- Development Roadmap

This roadmap outlines the multi-phase development plan for **Geometry Defender**, a mobile geometric tower-defence game for Android. Formulated and approved by the **Development Council**, this document establishes clear, milestone-driven objectives for achieving a Minimum Viable Product (MVP) and progressing to a polished Production Release.

---

## Council Overview & Key Ownership

| Role | Council Member | Primary Focus in Roadmap |
| :--- | :--- | :--- |
| **Game Director** | Mara Venn | Scope control, core loop vision, milestone approval |
| **Lead Game Designer** | Elias Ward | Pathing, tower combinations, placement rules, land removal mechanics |
| **Systems & Balance Designer** | Nia Okafor | Tower stats, enemy size-to-health formulas, 10-level scaling curves |
| **Economy Designer** | Felix Hart | Kill reward mechanics, placement & upgrade cost balance |
| **Art Director & 2D Artist** | Sora Kim & Jules Mercer | Nested shape visual hierarchy, spinning attack animations, 10-level color palettes |
| **UI/UX Designer** | Priya Shah | Touchscreen placement controls, upgrade HUD, combat readability |
| **Technical Lead** | Rowan Blake | Game architecture, path generation algorithm, modular ECS / object pooling |
| **Gameplay Programmer** | Theo Grant | Tower firing logic, hybrid combination behavior, dot size reduction |
| **Mobile & Platform Engineer** | Amara Lewis | GameActivity integration, touch input handling, thermal & 60 FPS optimization |
| **Tools & Build Engineer** | Benji Cole | Data-driven JSON configuration for towers, waves, and enemy stats |
| **QA Lead & Accessibility** | Morgan Price & Devon Ellis | Stress testing, edge case verification, colorblind modes & game feel |
| **Producer & Publishing** | Callum Reed & Anika Brooks | Milestone schedules, dependency tracking, Play Store submission |

---

## PART 1: MINIMUM VIABLE PRODUCT (MVP) ROADMAP

The primary goal of the MVP is to prove that the core loop—procedural pathing, distinct shape towers, shape combinations, and dot health reduction—is engaging, performant, and fun on touchscreen devices.

---

### Phase 1: Core Engine & Procedural Path Foundation
**Lead Owners:** Technical Lead (Rowan Blake), Mobile Engineer (Amara Lewis), Gameplay Programmer (Theo Grant)  
**Council Reviewers:** Game Director (Mara Venn), Art Director (Sora Kim)

* **1.1 Engine & Architecture Setup**
  * Establish modular game loop architecture supporting rendering, input, and entity management via Native Game SDK / C++ (`GameActivity`) and Kotlin integration.
  * Define data structures for Entities (Towers, Projectiles, Enemies, Map Grid).
* **1.2 Data-Driven Configuration System (Tools Engineer: Benji Cole)**
  * Implement JSON/Data schemas for unit base stats (damage, fire rate, range, cost) and enemy parameters.
  * Enable hot-reloading or configuration file loading without code recompilation.
* **1.3 Procedural Path Generation (Lead Designer: Elias Ward)**
  * Develop the top-to-bottom "Grand Canyon" procedural path generator weaving through a grid-based map.
  * Ensure path validation guarantees at least one contiguous, non-blocking path from top spawn point to bottom exit point.
  * Reserve placement tiles adjacent to the path for tower construction.

**Phase 1 Deliverable:** A running application rendering a procedurally generated map with a playable grid and defined top-to-bottom enemy path.

---

### Phase 2: Base Defenders & Enemy Mechanics
**Lead Owners:** Gameplay Programmer (Theo Grant), Systems Designer (Nia Okafor), 2D Artist (Jules Mercer)  
**Council Reviewers:** Lead Designer (Elias Ward), Game Feel Specialist (Devon Ellis)

* **2.1 Three Base Defensive Units**
  * **Square (Machine Gun):** High rate of fire, mid-range, single-target projectile attack.
  * **Circle (Area Effect):** Burst area-of-effect attack with periodic "flame on / flame off" timing.
  * **Triangle (Sniper / Long Range):** Long range, low rate of fire, high damage per shot.
* **2.2 Firing & Rotation Mechanics**
  * Implement targeting logic (First, Strongest, Weakest, Nearest).
  * Implement spinning tower rotation animation triggered when an enemy target enters the tower's range.
* **2.3 Enemy "Dot" Health & Size Reduction System**
  * Spawn dot enemies at the top of the path moving down at set speeds.
  * Map enemy size directly to health: as dots take damage, their size shrinks dynamically until vanishing upon death.
  * Grant monetary reward to player upon dot destruction.

**Phase 2 Deliverable:** Playable arena where 3 base towers can be placed to shoot at dots walking along the path, reducing their size and destroying them.

---

### Phase 3: Hybrid Tower Combination & Level 1–10 Progression
**Lead Owners:** Systems Designer (Nia Okafor), Economy Designer (Felix Hart), Gameplay Programmer (Theo Grant)  
**Council Reviewers:** Game Director (Mara Venn), UI/UX Designer (Priya Shah)

* **3.1 Stacking & Hybrid Combination Logic**
  * Allow towers to stack 1 of each shape type (Circle, Square, Triangle), reaching Level 3.
  * **Order-based hybrid attack modifications:**
    * *Square + Triangle (Square first):* Longer range machine gun.
    * *Triangle + Square (Triangle first):* Faster firing long-range weapon.
    * *Circle + Square / Triangle:* AoE machine gun or AoE long-range pulses.
  * Render nested shape visuals (e.g., Square inside Triangle inside Circle) to clearly reflect tower composition.
* **3.2 Level 4–10 Upgrades & Stat Scaling**
  * Enable upgrade progression beyond Level 3 up to Level 10 once all 3 shape types are stacked (or per single tower progression path).
  * Apply mathematical scaling formulas for damage, fire rate, and range across levels 1–10.
  * Map distinct color themes to each of the 10 levels for clear visual recognition.
* **3.3 Economy & Wave Spawner Loop**
  * Implement gold/currency tracking for kills, tower purchases, and upgrades.
  * Build wave spawner with scaling dot enemy counts, speeds, and sizes per wave.

**Phase 3 Deliverable:** Fully functional combination mechanics and 10-level tower upgrades integrated into an operational wave spawner economy.

---

### Phase 4: Touch Controls, HUD & MVP Release Candidate
**Lead Owners:** UI/UX Designer (Priya Shah), Mobile Engineer (Amara Lewis), QA Lead (Morgan Price)  
**Council Reviewers:** Player Researcher (Leila Morgan), Producer (Callum Reed)

* **4.1 Touch Controls & Placement UX**
  * Drag-and-drop or tap-to-place tower selection interface tailored for mobile screens.
  * Range circle indicators on placement and selection.
  * Contextual upgrade panel showing combination previews and cost.
* **4.2 In-Game HUD & Wave Controls**
  * Top bar displaying Base Health, Gold Currency, Current Wave, and Next Wave button.
  * Pause, speed toggle (1x/2x), and game over / victory overlay screens.
* **4.3 MVP Playtest & Evaluation**
  * Conduct internal playtests with player research feedback (Leila Morgan).
  * Verify that each shape offers a distinct strategic advantage and that combinations feel rewarding.

**MVP Milestone Gate:** Game Director (Mara Venn) and Producer (Callum Reed) sign off on MVP build readiness.

---

## PART 2: PRODUCTION & FULL RELEASE ROADMAP

Once the MVP validates core combat and progression, development shifts to dynamic environmental mechanics, visual/audio polish, mobile performance optimization, and store release.

---

### Phase 5: Dynamic Land Removal & Advanced Map Mechanics
**Lead Owners:** Lead Designer (Elias Ward), Gameplay Programmer (Theo Grant), Systems Designer (Nia Okafor)  
**Council Reviewers:** QA Lead (Morgan Price), Technical Lead (Rowan Blake)

* **5.1 Land Removal Mechanic**
  * Implement wave-based land removal: as wave numbers increase, non-path land tiles disappear/crumble, shrinking available placement space.
  * Handle edge cases: fallback logic if a tower occupies a removed tile (e.g., refund option or forced repositioning).
* **5.2 Dynamic Pathing & Environmental Hazards**
  * Support optional map mutations (e.g., path shifts or temporary speed-up tiles for enemies).
  * Balance land removal speed so strategic pressure increases without rendering levels unplayable.

**Phase 5 Deliverable:** Dynamic terrain system active in waves, stripping buildable land over time.

---

### Phase 6: Art Direction, Visual FX, Audio & Accessibility Polish
**Lead Owners:** Art Director (Sora Kim), 2D Artist (Jules Mercer), Game Feel & Accessibility Specialist (Devon Ellis)  
**Council Reviewers:** UI/UX Designer (Priya Shah), Mobile Engineer (Amara Lewis)

* **6.1 Visual & Particle Effects**
  * Polished muzzle flashes, spinning attack animations, explosion/burst effects for Circle AoE.
  * Smooth scaling and particle effect transitions when dot enemies shrink and pop.
  * Nested shape rendering refinement with sharp vector-like contrast.
* **6.2 Audio Infrastructure**
  * Sound effects for shape attacks (machine gun pulse, flamethrower burst, long-range heavy shot).
  * Audio feedback for dot hits, upgrades, placement, and wave completion.
  * Ambient background music track aligned with geometric sci-fi theme.
* **6.3 Accessibility & Colorblind Support**
  * Colorblind palette options for the 10 level colors.
  * Contrast checks for enemy dots against path and background terrain.
  * Motion-reduction toggles for screen shake and intense visual bursts.

**Phase 6 Deliverable:** Fully polished visual presentation, sound effects, music, and complete accessibility menu options.

---

### Phase 7: Mobile Performance Optimization & Comprehensive QA
**Lead Owners:** Mobile Engineer (Amara Lewis), QA Lead (Morgan Price), Technical Lead (Rowan Blake)  
**Council Reviewers:** Producer (Callum Reed)

* **7.1 Memory & Frame Rate Optimization**
  * Implement object pooling for all enemy dots, projectiles, and particle effects.
  * Ensure consistent 60 FPS performance across a wide range of Android device specs.
  * Profile and optimize battery consumption, CPU usage, and thermal footprint during high enemy count waves.
* **7.2 Robust Test Plan & Session Persistence**
  * Implement game state saving and seamless pause/resume handling during Android activity lifecycle events (e.g., incoming phone calls, switching apps).
  * Comprehensive edge-case testing (e.g., max tower level, screen resolutions, notch handling, low memory conditions).

**Phase 7 Deliverable:** High-performance, stable build passing all QA test suites without crashes or memory leaks.

---

### Phase 8: Play Store Publishing & Launch Preparation
**Lead Owners:** Publishing Specialist (Anika Brooks), Producer (Callum Reed), Game Director (Mara Venn)  
**Council Reviewers:** All Council Members

* **8.1 Store Listing & Marketing Assets**
  * High-resolution app icon, feature graphics, screenshots highlighting shape combination and dot reduction gameplay.
  * Write clear store descriptions highlighting core features and intuitive mechanics.
* **8.2 Android Packaging & Compliance**
  * Generate optimized Android App Bundle (AAB) with dynamic target SDK compliance.
  * Complete Google Play Console setup, privacy policy, content rating questionnaire, and signing keys.
* **8.3 Final Release Candidate Sign-Off**
  * Final Council meeting review for launch approval.
  * Staged rollout setup (10% -> 25% -> 50% -> 100%) on Google Play Store.

**Production Milestone:** Public release of Geometry Defender on the Google Play Store!

---

## Summary of Council Approval

| Milestone | Target Objective | Council Sign-Off |
| :--- | :--- | :--- |
| **Phase 1–4 (MVP)** | Playable core loop: Procedural path, 3 towers, stacking/combinations, Lvl 1-10 upgrades, dot health shrinking, HUD | Game Director, Tech Lead, Producer |
| **Phase 5–8 (Production)** | Dynamic land removal, visual FX/audio, 60 FPS pooling, accessibility, Google Play Store publication | Full Council |
