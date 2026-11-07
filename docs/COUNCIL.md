Geometry Defender --- Development Council
A fictional cross-functional council responsible for designing,
building, testing, and preparing Geometry Defender, a mobile
tower-defence game in which geometric shapes are the player's defensive
units.

The council is intentionally sized to cover the important disciplines
without creating an unnecessarily large team. Members are fictional
roles, not real people.
1. Creative Direction and Product
   1.1 Game Director --- Mara Venn
   Role: Owns the overall vision, priorities, and quality bar.
- Keeps the game focused on its central idea: circles, squares, and
  triangles as distinct defensive units.
- Resolves disagreements between design, engineering, art, and
  production.
- Approves major changes to scope and game direction.
- Ensures new features support the core tower-defence experience.
  1.2 Lead Game Designer --- Elias Ward
  Role: Defines the rules and moment-to-moment gameplay.
- Designs the core game loop, wave structure, maps, objectives, and
  progression.
- Establishes how players earn, place, upgrade, and combine defensive
  shapes.
- Creates the initial game design document and maintains it as
  decisions are made.
- Keeps mechanics understandable on a small mobile screen.
  1.3 Systems and Balance Designer --- Nia Okafor
  Role: Makes the strategic systems coherent and balanced.
- Defines the strengths, weaknesses, costs, range, attack speed, and
  upgrade paths of each shape.
- Builds enemy attributes and interactions that create meaningful
  tactical choices.
- Models difficulty curves, wave pacing, rewards, and long-term
  progression.
- Tests whether one shape or strategy becomes an obvious dominant
  choice.
  1.4 Economy and Progression Designer --- Felix Hart
  Role: Designs the player's longer-term goals and reward structure.
- Plans currencies, unlocks, upgrades, milestones, and any
  meta-progression.
- Makes rewards feel useful without forcing repetitive grinding.
- Balances session rewards against the overall progression pace.
- Advises on ethical monetisation if the project later includes it.
2. Art, Animation, and User Experience
   2.1 Art Director --- Sora Kim
   Role: Establishes the visual identity of the game.
- Defines the shape language, colour palette, effects, environments,
  and visual hierarchy.
- Ensures circles, squares, and triangles are recognisable at small
  sizes.
- Sets standards for consistency across menus, gameplay, icons, and
  promotional art.
- Keeps the visual style achievable for a small development project.
  2.2 2D Artist and Animator --- Jules Mercer
  Role: Creates the visual assets and animation.
- Produces shape-unit designs, enemies, projectiles, environments, and
  interface assets.
- Animates attacks, impacts, damage states, upgrades, and destruction.
- Creates visual feedback that communicates what is happening during
  busy waves.
- Prepares reusable sprite sheets and effects where appropriate.
  2.3 UI/UX Designer --- Priya Shah
  Role: Designs the mobile interface and player experience.
- Designs menus, HUD, placement controls, upgrade panels, settings,
  and tutorials.
- Makes controls comfortable for touchscreens and different device
  sizes.
- Ensures essential information is readable during combat.
- Tests onboarding so new players can understand the game without
  lengthy instructions.
3. Engineering
   3.1 Technical Lead / Gameplay Architect --- Rowan Blake
   Role: Owns the technical architecture and engineering standards.
- Selects and documents the game architecture and core technologies.
- Defines how towers, enemies, projectiles, waves, and status effects
  interact.
- Keeps gameplay systems modular and maintainable.
- Reviews major technical decisions and manages performance risks.
  3.2 Gameplay Programmer --- Theo Grant
  Role: Implements the playable game systems.
- Builds tower targeting, firing, projectile movement, damage, enemy
  behaviour, and wave logic.
- Implements placement, upgrades, targeting priorities, and special
  abilities.
- Tunes the feel of combat in collaboration with the designers.
- Builds tools or debug views that make balancing easier.
  3.3 Mobile and Platform Engineer --- Amara Lewis
  Role: Handles mobile-specific implementation.
- Implements touch input, screen scaling, device lifecycle handling,
  and platform integration.
- Manages performance, memory, battery use, and loading times.
- Handles mobile builds, signing, store configuration, and platform
  requirements.
- Tests behaviour across a representative range of Android and iOS
  devices.
  3.4 Tools and Build Engineer --- Benji Cole
  Role: Improves the team's development workflow.
- Creates editor tools and data-driven configuration for units,
  enemies, and waves.
- Automates builds and repeatable validation tasks.
- Maintains project structure, version-control conventions, and build
  documentation.
- Helps make content iteration possible without changing code for
  every balance adjustment.
4. Quality and Player Research
   4.1 QA and Test Lead --- Morgan Price
   Role: Owns testing strategy and release quality.
- Creates test plans for core gameplay, progression, menus, saving,
  and device behaviour.
- Tests edge cases such as overlapping enemies, full placement areas,
  and interrupted sessions.
- Tracks bugs, reproduction steps, severity, and regression risk.
- Verifies fixes and checks release candidates.
  4.2 Game Feel and Accessibility Specialist --- Devon Ellis
  Role: Evaluates clarity, comfort, and accessibility.
- Reviews readability, contrast, motion, audio cues, and feedback
  during combat.
- Checks that units can be distinguished by shape as well as colour.
- Recommends options for reduced motion, adjustable audio, and
  accessible controls.
- Evaluates whether difficulty and tutorial steps are fair and
  understandable.
  4.3 Player Researcher --- Leila Morgan
  Role: Represents the perspective of actual players.
- Plans small playtests with people unfamiliar with the project.
- Observes where players hesitate, misunderstand mechanics, or lose
  interest.
- Collects structured feedback rather than relying only on developer
  opinions.
- Reports usability issues and prioritises findings with the design
  team.
5. Production and Release
   5.1 Producer / Project Manager --- Callum Reed
   Role: Keeps the project deliverable and organised.
- Breaks the project into milestones and manageable tasks.
- Maintains the backlog, tracks dependencies, and identifies scope
  risks.
- Coordinates hand-offs between design, art, engineering, and QA.
- Keeps documentation and decisions easy to find.
  5.2 Publishing and Store Specialist --- Anika Brooks
  Role: Prepares the game for release and discovery.
- Plans store listings, screenshots, feature graphics, descriptions,
  and launch assets.
- Checks platform submission requirements and release readiness.
- Advises on analytics and player feedback channels.
- Helps plan updates after launch.
6. Council Responsibilities and Decision-Making
   The council should work as a collaborative review group, not as a
   requirement to involve every role in every decision.
   Decision area           Primary owner           Required reviewers
   Core game concept and   Game Director           Lead Designer,
   scope                                           Producer, Technical
   Lead

Tower and enemy         Lead Designer           Systems Designer,
mechanics                                       Gameplay Programmer

Unit and wave balance   Systems Designer        Lead Designer, Gameplay
Programmer

Progression and rewards Economy Designer        Game Director, Lead
Designer

Visual direction        Art Director            Game Director, UI/UX
Designer

Interface and controls  UI/UX Designer          Mobile Engineer, QA
Lead, Accessibility
Specialist

Architecture and        Technical Lead          Gameplay Programmer,
technical standards                             Mobile Engineer, Tools
Engineer

Performance and         Mobile Engineer         Technical Lead, QA Lead
platform support

Testing and release     QA Lead                 Relevant feature
quality                                         owners, Producer

Milestones and scope    Producer                Game Director,
Technical Lead,
discipline leads
Store and launch        Publishing Specialist   Producer, Art Director,
preparation                                     Game Director
Working principles
1. Prototype before over-designing. Prove the central combat loop
   with simple shapes and placeholder art before building large content
   systems.
2. Make decisions explicit. Record important decisions,
   alternatives considered, and the reason for the chosen approach.
3. Keep content data-driven. Unit statistics, enemy attributes,
   wave composition, and upgrade values should be easy to tune.
4. Design for mobile from the start. Touch controls, readability,
   performance, and screen layout are core requirements.
5. Balance through playtesting. Use repeatable tests and player
   observations rather than relying only on intuition.
6. Protect the core concept. New features should strengthen the
   strategic use of geometric defenders, not distract from it.
7. Suggested Initial Work Plan
   Phase 1 --- Define the game
- Agree the target audience, platform, visual direction, and intended
  session length.
- Define the core loop and the initial roles of circles, squares, and
  triangles.
- Establish a small set of enemy types and one test environment.
- Write the first concise game design document.
  Phase 2 --- Build a combat prototype
- Implement a basic map, enemy path, wave spawner, and base health.
- Add one working defensive unit for each shape.
- Implement placement, targeting, attacks, damage, and defeat
  conditions.
- Use placeholder visuals and simple effects.
  Phase 3 --- Validate the strategy
- Playtest whether the three shapes have distinct tactical purposes.
- Adjust costs, range, attack speed, damage, and enemy interactions.
- Test difficulty and whether the player has meaningful decisions
  during a wave.
- Refine touch controls and combat readability.
  Phase 4 --- Build the first vertical slice
- Add a polished sample level, a small enemy roster, upgrades, audio,
  menus, and tutorial.
- Implement saving and basic progression.
- Test performance on real mobile devices.
- Review the scope and quality before expanding content.
  Phase 5 --- Content and release preparation
- Expand levels, enemies, challenges, and progression only after the
  core is working.
- Complete accessibility, QA, store assets, analytics, and platform
  checks.
- Run a release candidate test cycle and address high-priority issues.
8. First Council Agenda
   The first meeting should answer these questions:
1. What is the core gameplay loop, from starting a level to completing
   a wave?
2. What does each shape do that the other two cannot do as well?
3. Are defenders placed freely, on fixed build points, or along a path?
4. Do enemies follow a fixed route, choose routes, or interact with the
   map?
5. What decisions does the player make during a wave, rather than only
   between waves?
6. What is the smallest prototype that can prove the game is fun?
7. Which features are explicitly out of scope for the first playable
   version?
   Initial success criterion: A small playable level in which circles,
   squares, and triangles each provide a distinct and useful defensive
   role, and the player must make meaningful placement and upgrade
   decisions to survive increasingly difficult waves.