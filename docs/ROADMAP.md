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
| **Mobile & Platform Engineer** | Amara Lewis | GameActivity integration, touch input handling, AdMob SDK integration, 60 FPS optimization |
| **Tools & Build Engineer** | Benji Cole | Data-driven JSON configuration for towers, waves, and enemy stats |
| **QA Lead & Accessibility** | Morgan Price & Devon Ellis | Stress testing, edge case verification, colorblind modes & game feel |
| **Producer & Publishing** | Callum Reed & Anika Brooks | Milestone schedules, dependency tracking, Play Store submission, AdMob setup |

---

## PART 1: MINIMUM VIABLE PRODUCT (MVP) ROADMAP [x]

### Phase 1: Core Engine & Procedural Path Foundation [x]
### Phase 2: Base Defenders & Enemy Mechanics [x]
### Phase 3: Hybrid Tower Combination, Progression & Wave Loop [x]
### Phase 4: Touch Controls, Between-Wave Menu & Lives / AdMob Integration [x]

---

## PART 2: PRODUCTION & FULL RELEASE ROADMAP [x]

### Phase 5: Two-Tier Land Destruction & Enemy Combat Interaction [x]
### Phase 6: Art Direction, Visual FX, Audio & Accessibility Polish [x]
### Phase 7: Mobile Performance Optimization & Comprehensive QA [x]

### Phase 8: Play Store Publishing & Launch Preparation [x]
**Lead Owners:** Publishing Specialist (Anika Brooks), Producer (Callum Reed), Game Director (Mara Venn)  
**Council Reviewers:** All Council Members

* **[x] 8.1 Store Listing & Marketing Assets**
  * Created store listing description (`store_listing.txt`) and privacy policy (`privacy_policy.md`) in `/builds/storeListing/`.
* **[x] 8.2 Android Packaging & AdMob Production Setup**
  * Generated release APK (`builds/GeometryDefender_1.0.0.apk`) and AdMob compliance file (`app-ads.txt`).

**Production Milestone:** Geometry Defender is fully built, polished, packaged, and ready for public release on the Google Play Store with AdMob monetization! *(Completed)*

---

## Summary of Council Approval

| Milestone | Target Objective | Council Sign-Off |
| :--- | :--- | :--- |
| **Phase 1–4 (MVP)** | Playable core loop & AdMob lives flow | Game Director, Tech Lead, Producer *(Signed Off)* |
| **Phase 5 (Two-Tier Terrain)** | Upper land deletion & Lower land combat ticks | Lead Designer, Systems Designer, Tech Lead *(Signed Off)* |
| **Phase 6–7 (Polish & Perf)** | Object pooling, 60 FPS optimization, motion-reduction accessibility, session persistence | Full Council *(Signed Off)* |
| **Phase 8 (Publishing)** | Google Play Store publication & store assets | Full Council *(Signed Off)* |
