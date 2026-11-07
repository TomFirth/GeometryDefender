# Geometry Defender --- Development Roadmap

This roadmap outlines the multi-phase development plan for **Geometry Defender**, a mobile geometric tower-defence game for Android. Formulated and approved by the **Development Council**, this document establishes clear, milestone-driven objectives for achieving a Minimum Viable Product (MVP) and progressing to a polished Production Release.

---

## Council Overview & Key Ownership

| Role | Council Member | Primary Focus in Roadmap |
| :--- | :--- | :--- |
| **Game Director** | Mara Venn | Scope control, core loop vision, milestone approval |
| **Lead Game Designer** | Elias Ward | Pathing, tower combinations, placement rules, upper/lower land removal mechanics |
| **Systems & Balance Designer** | Nia Okafor | Tower stats, enemy size-to-health formulas, 10-level scaling curves, unit HP |
| **Economy Designer** | Felix Hart | Kill reward mechanics, placement costs, 75% upper refund / 50% lower refund balance |
| **Art Director & 2D Artist** | Sora Kim & Jules Mercer | Nested shape visual hierarchy, spinning attack animations, green upper / brown lower terrain |
| **UI/UX Designer** | Priya Shah | Bottom-screen between-wave menu, drag-and-drop placement, during-wave upgrade HUD |
| **Technical Lead** | Rowan Blake | Game architecture, path generation algorithm, modular ECS / object pooling |
| **Gameplay Programmer** | Theo Grant | Tower firing logic, hybrid combination behavior, enemy tick damage on lower land units |
| **Mobile & Platform Engineer** | Amara Lewis | GameActivity integration, touch input handling, thermal & 60 FPS optimization |
| **Tools & Build Engineer** | Benji Cole | Data-driven JSON configuration for towers, waves, and enemy stats |
| **QA Lead & Accessibility** | Morgan Price & Devon Ellis | Stress testing, edge case verification, colorblind modes & game feel |
| **Producer & Publishing** | Callum Reed & Anika Brooks | Milestone schedules, dependency tracking, Play Store submission |

---

## PART 1: MINIMUM VIABLE PRODUCT (MVP) ROADMAP

The primary goal of the MVP is to prove that the core loop—procedural pathing, distinct shape towers, shape combinations, two-tier terrain, and dot health reduction—is engaging, performant, and fun on touchscreen devices.

---

### Phase 1: Core Engine & Procedural Path Foundation
**Lead Owners:** Technical Lead (Rowan Blake), Mobile Engineer (Amara Lewis), Gameplay Programmer (Theo Grant)  
**Council Reviewers:** Game Director (Mara Venn), Art Director (Sora Kim)

* **1.1 Engine & Architecture Setup**
  * Establish modular game loop architecture supporting rendering, input, and entity management via Native Game SDK / C++ (`GameActivity`) and Kotlin integration.
  * Define data structures for Entities (Towers, Projectiles, Enemies, Map Grid, Terrain Tiers).
* **1.2 Data-Driven Configuration System (Tools Engineer: Benji Cole)**
  * Implement JSON/Data schemas for unit base stats (damage, fire rate, range, cost, HP) and enemy parameters.
  * Enable hot-reloading or configuration file loading without code recompilation.
* **1.3 Procedural Path Generation & Terrain Tiers (Lead Designer: Elias Ward)**
  * Develop the top-to-bottom "Grand Canyon" procedural path generator weaving through a grid-based map.
  * Define **Upper Land (Green)**: Non-walkable by enemies, buildable area.
  * Define **Lower Land (Brown / Path)**: Walkable path for enemies.
  * Ensure path validation guarantees at least one contiguous, non-blocking path from top spawn point to bottom exit point.

**Phase 1 Deliverable:** A running application rendering a procedurally generated map with Upper (Green) and Lower (Brown) terrain tiers.

---

### Phase 2: Base Defenders & Enemy Mechanics
**Lead Owners:** Gameplay Programmer (Theo Grant), Systems Designer (Nia Okafor), 2D Artist (Jules Mercer)  
**Council Reviewers:** Lead Designer (Elias Ward), Game Feel Specialist (Devon Ellis)

* **2.1 Three Base Defensive Units**
  * **Square (Machine Gun):** High rate of fire, mid-range, single-target projectile attack.
  * **Circle (Area Effect):** Burst area-of-effect attack with periodic flame pulses.
  * **Triangle (Sniper / Long Range):** Long range, low rate of fire, high damage per shot.
* **2.2 Firing & Rotation Mechanics**
  * Implement targeting logic and spinning tower rotation animation triggered when an enemy target enters range.
* **2.3 Enemy "Dot" Health & Size Reduction System**
  * Spawn dot enemies at the top of the path moving down at set speeds.
  * Map enemy size directly to health: as dots take damage, their size shrinks dynamically until vanishing upon death.
  * Grant monetary reward to player upon dot destruction.

**Phase 2 Deliverable:** Playable arena where 3 base towers shoot at dots walking along the path, reducing their size and destroying them.

---

### Phase 3: Hybrid Tower Combination, Progression & Wave Loop
**Lead Owners:** Systems Designer (Nia Okafor), Economy Designer (Felix Hart), Gameplay Programmer (Theo Grant)  
**Council Reviewers:** Game Director (Mara Venn), UI/UX Designer (Priya Shah)

* **3.1 Stacking & Hybrid Combination Logic**
  * Allow towers to stack 1 of each shape type (Circle, Square, Triangle), reaching Level 3 with order-based hybrid attack modifications.
* **3.2 Level 4–10 Upgrades (During Waves)**
  * Enable upgrade progression up to Level 10.
  * **Rule Implementation:** **Units can only be upgraded in level during active waves.**
* **3.3 Wave Spawner & Economy Loop**
  * Implement gold/currency tracking for kills, tower purchases, and upgrades.
  * Build wave spawner with scaling dot enemy counts, speeds, and sizes per wave.

**Phase 3 Deliverable:** Fully functional combination mechanics and during-wave level upgrades integrated into wave spawner economy.

---

### Phase 4: Touch Controls, Between-Wave Menu & MVP Release Candidate
**Lead Owners:** UI/UX Designer (Priya Shah), Mobile Engineer (Amara Lewis), QA Lead (Morgan Price)  
**Council Reviewers:** Player Researcher (Leila Morgan), Producer (Callum Reed)

* **4.1 Bottom-Screen Menu & Placement Flow (Between Waves)**
  * Implement bottom-screen menu appearing **only between rounds**:
    * **Bottom-Left:** 3 shapes (Square, Circle, Triangle) available for drag-and-drop placement onto Upper (Green) land.
    * **Bottom-Right:** Player currency display.
  * **Placement Rule:** Dragging a shape onto the arena spends currency; dragging it back to the menu cancels the purchase. **New units can only be built between waves.**
* **4.2 In-Game HUD & Wave Controls**
  * Top/side bar displaying Base Health, Wave counter, and Next Wave button.
* **4.3 MVP Playtest & Evaluation**
  * Verify that between-wave building and during-wave upgrades create clear strategic pacing.

**MVP Milestone Gate:** Game Director (Mara Venn) and Producer (Callum Reed) sign off on MVP build readiness.

---

## PART 2: PRODUCTION & FULL RELEASE ROADMAP

Once MVP validates core combat and progression, development shifts to dynamic environmental mechanics, land removal, visual/audio polish, and store release.

---

### Phase 5: Two-Tier Land Destruction & Enemy Combat Interaction
**Lead Owners:** Lead Designer (Elias Ward), Gameplay Programmer (Theo Grant), Systems Designer (Nia Okafor)  
**Council Reviewers:** QA Lead (Morgan Price), Technical Lead (Rowan Blake)

* **5.1 Upper Land Deletion (End of Wave)**
  * Implement wave-end land removal: 1–2 pieces of Upper (Green) land are deleted based on how many enemies reached the bottom of the screen.
  * **Refund Rule:** If a unit is built on deleted upper land, it is destroyed and the player receives **75% of the total cost back**.
* **5.2 Lower Land Enemy Interaction & Unit Destruction**
  * Units built on Lower (Brown / Path) land are not deleted at wave end.
  * **Enemy Attack Tick:** If an enemy walks into/over a tower on the brown path, it deals damage on tick (scaled by unit type and wave).
  * **Unit HP Balance:** Triangles are weakest, squares mid, circles strongest (Level 10 circle is strongest of all).
  * **Refund Rule:** If a unit on lower land is destroyed by enemy attacks, the player receives **50% of the total cost back**.

**Phase 5 Deliverable:** Active two-tier terrain destruction system with upper land deletion refunds (75%) and lower land enemy combat destruction ticks (50% refund).

---

### Phase 6: Art Direction, Visual FX, Audio & Accessibility Polish
**Lead Owners:** Art Director (Sora Kim), 2D Artist (Jules Mercer), Game Feel & Accessibility Specialist (Devon Ellis)  
**Council Reviewers:** UI/UX Designer (Priya Shah), Mobile Engineer (Amara Lewis)

* **6.1 Visual & Particle Effects**
  * Polished muzzle flashes, spinning attack animations, explosion/burst effects for Circle AoE.
  * Smooth scaling and particle effect transitions when dot enemies shrink and pop.
  * Clear visual distinction between Green Upper land, Brown Lower path, and nested tower shapes.
* **6.2 Audio & Accessibility**
  * Sound effects for shape attacks, dot hits, upgrades, and land destruction.
  * Colorblind palette options and motion-reduction toggles.

**Phase 6 Deliverable:** Fully polished visual presentation, sound effects, music, and complete accessibility menu options.

---

### Phase 7: Mobile Performance Optimization & Comprehensive QA
**Lead Owners:** Mobile Engineer (Amara Lewis), QA Lead (Morgan Price), Technical Lead (Rowan Blake)  
**Council Reviewers:** Producer (Callum Reed)

* **7.1 Memory & Frame Rate Optimization**
  * Object pooling for enemy dots, projectiles, and particle effects.
  * Ensure consistent 60 FPS performance across a wide range of Android device specs.
* **7.2 Robust Test Plan & Session Persistence**
  * Game state saving and seamless pause/resume handling during Android activity lifecycle events.

**Phase 7 Deliverable:** High-performance, stable build passing all QA test suites without crashes or memory leaks.

---

### Phase 8: Play Store Publishing & Launch Preparation
**Lead Owners:** Publishing Specialist (Anika Brooks), Producer (Callum Reed), Game Director (Mara Venn)  
**Council Reviewers:** All Council Members

* **8.1 Store Listing & Marketing Assets**
  * High-resolution app icon, feature graphics, screenshots highlighting shape combination and terrain destruction gameplay.
* **8.2 Android Packaging & Compliance**
  * Generate optimized Android App Bundle (AAB) with dynamic target SDK compliance and Google Play Console setup.

**Production Milestone:** Public release of Geometry Defender on the Google Play Store!

---

## Summary of Council Approval

| Milestone | Target Objective | Council Sign-Off |
| :--- | :--- | :--- |
| **Phase 1–4 (MVP)** | Playable core loop: Procedural path, 3 towers, stacking/combinations, between-wave building menu, during-wave upgrades, dot health shrinking, HUD | Game Director, Tech Lead, Producer |
| **Phase 5–8 (Production)** | Two-tier land destruction, 75% upper refund / 50% lower refund, enemy attack ticks, visual FX/audio, 60 FPS pooling, Google Play Store publication | Full Council |
