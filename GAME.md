# GAME.md

# Working title

**Evil Eye: Units Defense Roguelite**

This document describes the initial implementation concept for a game that combines:

- units-based tower defense,
- roguelite progression,
- light RTS control,
- monster blueprint design,
- simple programmable unit behavior,
- dungeon-defense fantasy.

The goal is to provide clear implementation guidance for an LLM or programmer building the first playable prototype.

---

# 1. Core concept

The player controls an evil magical entity represented by a physical **Eye** placed on the map.

The player defends the dungeon from incoming groups of adventurers. The main defense is not towers, but **minions** created from configurable **blueprints**.

The player can also use a magical **Hand of Power** cursor to intervene directly, but this should be an emergency tool, not the main way to fight.

Between combat waves, the player modifies blueprints, chooses rewards, improves the Eye, and prepares for the next wave.

---

# 2. Target genre

The game should be treated primarily as:

```text
units-defense roguelite
```

The game should not initially be implemented as:

- a full 4X game,
- a full RTS,
- a free-form dungeon digging game,
- a complex factory game,
- a full programming game.

Some elements of these genres may appear later, but the first version should focus on a clear combat loop.

---

# 3. Core gameplay loop

```text
Preparation phase
    ↓
Player selects active blueprints
Player edits unit blueprints
Player places crystals / minion spawn points / limited structures
Player reviews next enemy wave
    ↓
Combat phase
    ↓
Enemy adventurers enter the dungeon
Player spawns minions from active blueprints
Minions fight using their blueprint stats and brain commands
Player uses Hand of Power only in emergencies
Crystals extend power range and support the defense
    ↓
Wave result
    ↓
Player gains minerals, ki, parts, brain commands, and upgrade choices
Player modifies the build
    ↓
Next wave
```

A full run should contain several waves. For the prototype, 5 waves are enough.

---

# 4. Main design pillars

## 4.1 Player expression through blueprints

The main creative system is monster design.

The player should feel that they are not only buying predefined units, but creating unit types from parts.

A unit blueprint defines:

- body type,
- equipment,
- traits,
- optional brain,
- brain commands,
- cost,
- stats,
- role.

Example:

```text
Blueprint: Guard Skeleton
Body: Skeleton
Weapon: Sword
Defense: Shield
Trait: Fire Resistance
Brain: Small Brain
Command: Guard nearest crystal
Cost: 20 minerals, 5 ki, 15 energy
```

## 4.2 Minions are the main defense

Minions should be more efficient than direct Hand of Power actions.

The player should usually win by:

- designing good blueprints,
- placing/spawning units well,
- using terrain and chokepoints,
- reacting to enemy composition.

The Hand of Power should help recover from mistakes or emergencies.

## 4.3 One-screen tactical clarity

The initial combat map should fit on one screen.

The player should see:

- the Eye,
- enemy entrance,
- main path,
- crystals,
- minions,
- enemies,
- important threat indicators.

Avoid large scrolling RTS maps in the first implementation.

## 4.4 Roguelite progression

Each run should provide different parts, commands, upgrades, and enemy compositions.

Progression should support experimentation with different blueprint builds.

---

# 5. Game phases

## 5.1 Preparation phase

During preparation, the player can:

- inspect the next enemy wave,
- edit available blueprints,
- choose active blueprints,
- place crystals in available power nodes,
- place initial minions or spawn points if the design allows it,
- select rewards or upgrades from the previous wave.

No enemies are active during this phase.

The player should not be under time pressure in the prototype.

## 5.2 Combat phase

During combat:

- enemies enter from one or more entrances,
- enemies follow a predefined path or tactical behavior,
- the player can spawn minions from active blueprints,
- the player can use the Hand of Power,
- units fight automatically based on stats and brain commands,
- the wave ends when all enemies are defeated, routed, or when the Eye is destroyed.

Combat should be short in the prototype.

Recommended initial duration:

```text
2-5 minutes per wave
```

Do not start with 30-minute combat stages. Longer stages may be considered later after the core loop is proven.

---

# 6. Map design

## 6.1 Map size

Recommended prototype map:

```text
24x14 tiles
```

Alternative:

```text
30x18 tiles
```

The exact resolution depends on the visual style, but the full combat area should fit on one screen.

## 6.2 Map structure

The map should contain:

- one enemy entrance,
- one Eye position,
- one main path,
- several chokepoints,
- 2-4 power nodes for crystals,
- 1-3 optional side areas,
- limited placement areas for minions or structures.

Example layout:

```text
[ Enemy Entrance ] ---> corridor ---> chamber ---> chokepoint ---> [ Eye ]

Side areas:
- crystal node
- spawn area
- optional reward chamber
- defensive position
```

## 6.3 Digging

For the first implementation, free digging should not be a core mechanic.

Use predefined paths and rooms.

Optional later mechanics:

- unlock side chamber,
- open shortcut,
- seal one passage,
- modify one predefined segment,
- activate hidden power node.

Do not implement free-form terrain destruction in the prototype unless it is trivial.

---

# 7. Player entity: The Eye

The Eye is the player's physical core.

If the Eye is destroyed, the run ends.

The Eye provides:

- base Hand of Power range,
- energy storage,
- energy regeneration,
- possible passive bonuses.

The Eye should be placed visibly on the map.

Enemies may target the Eye directly or indirectly depending on their role.

---

# 8. Crystals

Crystals are built on predefined power nodes.

Crystals provide:

- extended Hand of Power range,
- increased energy regeneration,
- increased energy storage,
- possible local buffs to minions.

Crystals are strategic defense points.

Enemies may choose to attack crystals before attacking the Eye.

## 8.1 Crystal destruction anti-death-spiral effect

When a crystal is destroyed, it should trigger an emergency defensive effect.

This effect exists to prevent immediate collapse after losing a key point.

It must not be an efficient combat strategy.

Recommended effect:

```text
On crystal destruction:
- enemies in radius are frozen for 4 seconds,
- enemies receive Soul Burn for 12 seconds,
- Soul Burn reduces movement speed by 30%,
- Soul Burn reduces damage by 20%,
- weak enemies may be killed,
- elite enemies are only weakened,
- the destroyed power node cannot be rebuilt until the wave ends.
```

Important rule:

```text
Destroying your own crystals or intentionally sacrificing crystals must not be economically profitable.
```

Possible safeguards:

- destroyed node disabled until end of wave,
- crystal cost is significant,
- explosion does not drop resources,
- explosion does not kill elite enemies,
- repeated crystal loss reduces final reward.

---

# 9. Hand of Power

The Hand of Power is the player's magical cursor.

It can interact with the map, units, and enemies.

It uses energy.

It should be useful but inefficient compared to minion-based defense.

## 9.1 Allowed actions

Prototype Hand actions:

- lightning strike,
- move one friendly unit,
- emergency repair or shield,
- accelerate one minion spawn,
- possibly destroy weak obstacles if used later.

## 9.2 Range rules

The Hand can act only within power range.

Power range is generated by:

- the Eye,
- active crystals.

The range should be visualized clearly.

## 9.3 Line blocking rule

The Hand cannot attack through enemy units.

For attack actions:

```text
The Hand can target only the first reachable enemy in a line or local engagement.
```

This means backline enemies cannot be directly attacked if frontline enemies block access.

This supports tactical formations and prevents the player from sniping all high-value enemies.

## 9.4 Economic rule

Direct Hand damage must be less efficient than minions.

For example:

```text
Lightning strike:
- high energy cost,
- low-to-medium damage,
- good for finishing or interrupting,
- bad as the main DPS source.
```

The player should feel that using the Hand too often is a sign of emergency or poor planning.

---

# 10. Resources

The prototype should use three main resources.

## 10.1 Minerals

Minerals represent material.

Used for:

- basic unit bodies,
- equipment,
- crystals,
- limited structures.

Sources:

- wave rewards,
- destroyed dungeon material,
- miner units if implemented,
- reward choices.

## 10.2 Ki

Ki represents spiritual or magical essence gained from defeated enemies.

Used for:

- brains,
- special traits,
- magical parts,
- advanced units,
- blueprint upgrades.

Sources:

- defeated enemies,
- special wave rewards,
- elite enemies,
- bosses.

## 10.3 Energy

Energy is used by the Hand of Power and possibly by fast spawning.

Energy:

- regenerates automatically,
- has a maximum storage value,
- regeneration can be improved by crystals and upgrades.

Used for:

- lightning strike,
- moving units,
- emergency shield,
- fast spawn,
- special interventions.

Avoid energy upkeep for units in the prototype.

Energy upkeep may be added later if needed, but it risks making the game too punishing.

---

# 11. Blueprint system

## 11.1 Blueprint overview

A blueprint defines a unit type.

The player can own many blueprints, but only a limited number are active during combat.

Initial active blueprint slots:

```text
2
```

This can increase through roguelite upgrades.

## 11.2 Active blueprint rule

Only active blueprints can be used to spawn units.

Changing active blueprints during combat should be possible, but it needs a cost or drawback.

Avoid immediately destroying all units of a deactivated blueprint in the first version. That is too punishing and discourages experimentation.

Recommended rule:

```text
If a blueprint is deactivated during combat:
- existing units of that blueprint remain active for 60 seconds,
- after that, they decay and die,
- alternatively, they remain but generate instability cost.
```

For the prototype, use the simpler decay version.

## 11.3 Blueprint parts

Possible part categories:

```text
Body
Weapon
Defense
Trait
Brain
Brain commands
```

Example bodies:

- Skeleton,
- Beast,
- Slime,
- Construct,
- Imp.

Example weapons:

- Sword,
- Bow,
- Claws,
- Pickaxe,
- Staff.

Example defenses:

- Shield,
- Bone Armor,
- Thick Hide,
- Magic Ward.

Example traits:

- Fire Resistance,
- Poison,
- Fast Movement,
- Regeneration,
- Explosive Death,
- Fear Aura.

Example brains:

- Tiny Brain,
- Small Brain,
- Medium Brain,
- Large Brain.

Example commands:

- Attack nearest enemy,
- Attack weakest enemy,
- Guard nearest crystal,
- Retreat below 30% health,
- Hold position,
- Dig marked wall,
- Focus healer,
- Protect ally.

## 11.4 Blueprint stat calculation

Each part modifies unit stats.

Recommended basic stats:

```text
Health
Damage
Attack speed
Range
Armor
Movement speed
Energy spawn cost
Mineral cost
Ki cost
Brain slots
```

The implementation should keep stat formulas simple.

Example:

```text
Final health = body health + defense health bonus + trait bonus
Final damage = weapon damage + trait damage bonus
Final cost = body cost + weapon cost + defense cost + brain cost + trait cost
```

Avoid complex multiplicative stacking in the prototype.

## 11.5 Blueprint UI requirements

The blueprint editor should show:

- selected parts,
- resulting stats,
- unit cost,
- brain slot count,
- assigned commands,
- warnings if blueprint is invalid.

Invalid blueprint examples:

- no body,
- too many commands for brain slots,
- incompatible weapon/body pair,
- missing required resource.

---

# 12. Brain system

## 12.1 Purpose

Brains define how autonomous a unit is.

Without a brain, a unit should have very simple default behavior.

Example default behavior:

```text
Move toward nearest enemy and attack.
```

Brains add command slots.

## 12.2 Brain sizes

Recommended prototype brain types:

| Brain | Slots | Notes |
|---|---:|---|
| No Brain | 0 | Default behavior only |
| Tiny Brain | 1 | One simple command |
| Small Brain | 2 | Basic tactical behavior |
| Medium Brain | 3 | Useful specialized unit |
| Large Brain | 4 | Advanced unit, expensive |

## 12.3 Command design

Commands must be simple and expressive.

A command should be readable as one short behavior rule.

Good examples:

```text
Guard nearest crystal
Attack weakest enemy
Retreat below 30% health
Focus healer
Hold position
Protect ranged ally
```

Avoid complex programming syntax in the prototype.

Do not implement a full scripting language.

## 12.4 Command priority

Commands should be evaluated in order from top to bottom.

Example:

```text
1. Retreat below 30% health
2. Focus healer
3. Attack nearest enemy
```

If command 1 applies, it runs.
If not, command 2 is checked.
If not, command 3 is checked.
If no command applies, the unit uses default behavior.

## 12.5 Command drops

Brain commands can drop from defeated enemies.

Example:

- defeating a ranger may unlock "Focus ranged enemy",
- defeating a cleric may unlock "Focus healer",
- defeating a rogue may unlock "Flank",
- defeating a shield warrior may unlock "Hold chokepoint".

---

# 13. Minion spawning and control

## 13.1 Spawning

The player can spawn units from active blueprints.

Possible spawn models:

### Option A: Spawn near Eye or crystals

Units can be spawned within power range.

This is simple and fits the Eye/crystal system.

### Option B: Spawn from specific spawn points

The player places or unlocks spawn points.

This is more tactical but slightly more complex.

For the prototype, use Option A.

## 13.2 Unit placement

Units should not require heavy micro-management.

Basic controls:

- spawn unit,
- move unit with Hand of Power,
- maybe set rally point,
- maybe select a local defense point.

The unit AI should handle most behavior.

## 13.3 Unit death

When a unit dies:

- it disappears,
- it may leave a corpse or essence later,
- it should not refund full cost.

Partial refund may be considered later for accessibility, but not needed in the first version.

---

# 14. Enemy adventurers

Enemies are adventuring parties entering the dungeon.

They should feel like small RPG parties, not only anonymous tower defense creeps.

## 14.1 Enemy roles

Prototype enemy types:

| Enemy | Role |
|---|---|
| Seeker | Weak early explorer |
| Warrior | Frontline melee |
| Archer | Ranged backline |
| Cleric | Healer/support |
| Rogue | Fast unit, may target crystals |
| Mage | Area damage or shield |
| Paladin | Mini-boss / elite |

## 14.2 Enemy party behavior

Enemy groups can have simple party behavior:

- move along path,
- attack blocking minions,
- target crystals if nearby,
- heal allies,
- keep ranged units behind frontline,
- retreat if morale breaks,
- rest at predefined camp point if used.

For the prototype, path-following with role-based targeting is enough.

## 14.3 Enemy objectives

Possible objectives:

- reach and destroy the Eye,
- destroy a crystal,
- steal a relic,
- scout the dungeon and escape,
- escort a stronger unit,
- survive long enough to call reinforcements.

Prototype objective:

```text
Reach and destroy the Eye.
```

Secondary behavior:

```text
Attack crystals if they block or support the defense nearby.
```

## 14.4 Wave structure

Prototype waves:

```text
Wave 1:
- Seekers only

Wave 2:
- Seekers + Warrior

Wave 3:
- Warriors + Archer

Wave 4:
- Warriors + Archer + Cleric

Wave 5:
- Paladin mini-boss + support party
```

Each wave should introduce one new problem.

---

# 15. Rewards and drops

After each wave, the player should receive rewards.

Reward types:

- minerals,
- ki,
- new part,
- new brain,
- new command,
- Eye upgrade,
- crystal upgrade,
- blueprint slot upgrade,
- reroll token.

## 15.1 Drop logic

Enemies may drop items related to their role.

Examples:

| Enemy | Possible drop |
|---|---|
| Warrior | Sword, Shield, Hold Position |
| Archer | Bow, Focus Weakest |
| Cleric | Healing Trait, Focus Healer |
| Rogue | Fast Movement, Flank |
| Mage | Magic Ward, Fire Resistance |
| Paladin | Holy Shield, Large Brain fragment |

## 15.2 Reward choice

After a wave, present 3 reward choices.

Example:

```text
Choose one:
1. New part: Shield
2. Upgrade: +15 max energy
3. Command: Retreat below 30% health
```

This supports roguelite build direction.

---

# 16. Roguelite meta-progression

Meta-progression should unlock new options more often than it gives pure stat inflation.

## 16.1 Good meta upgrades

Recommended upgrades:

- +1 active blueprint slot,
- unlock new body type,
- unlock new brain type,
- unlock new command category,
- unlock new crystal type,
- start each run with one random rare part,
- increase reward choices from 3 to 4,
- unlock reroll after waves,
- unlock new enemy regions.

## 16.2 Simple stat upgrades

Allowed but should not dominate:

- +10 max energy,
- +5% energy regeneration,
- +5% mineral gain,
- +5% ki gain,
- +5% Hand damage,
- +5% drop chance.

Use these sparingly.

The game should not feel like a grind where the same strategy works only after enough stat upgrades.

---

# 17. Combat mechanics

## 17.1 Unit targeting

Default minion targeting:

```text
Target nearest enemy in range.
```

Brain commands can override this.

Enemy targeting:

```text
Attack blocking minion.
If no blocking minion, continue toward objective.
If crystal is nearby and strategically relevant, attack crystal.
If Eye is reached, attack Eye.
```

## 17.2 Collision and blocking

Units should physically block enemies if possible.

This is important for units-defense gameplay.

At minimum:

- melee minions can block path tiles,
- enemies must attack or move around blockers,
- ranged enemies can shoot over frontline if line of sight allows.

## 17.3 Ranged combat

Ranged units should be useful but fragile.

Ranged enemy backline should be protected by frontline units.

Hand of Power should not be able to freely snipe ranged backline through frontline enemies.

## 17.4 Status effects

Prototype status effects:

- Frozen,
- Slowed,
- Poisoned,
- Burning,
- Shielded,
- Soul Burn.

Keep effects readable and visually clear.

---

# 18. Difficulty and balance principles

## 18.1 Player should lose from bad preparation

The main failure mode should be:

- poor blueprint design,
- wrong active blueprints,
- bad placement,
- poor energy use,
- ignoring enemy composition.

The player should not mostly lose because of unclear controls.

## 18.2 Hand of Power should save but not carry

If the player relies only on Hand actions, they should run out of energy.

## 18.3 Crystal destruction should buy time

Crystal death effects should prevent immediate collapse, not win the fight.

## 18.4 Each wave introduces a readable problem

Examples:

- Wave 1: basic damage race,
- Wave 2: frontline pressure,
- Wave 3: ranged backline,
- Wave 4: healer must be handled,
- Wave 5: boss with support.

---

# 19. Prototype scope

## 19.1 Must-have features

Implement these first:

- one-screen map,
- Eye entity,
- energy resource,
- Hand of Power lightning,
- crystals with range extension,
- crystal destruction freeze/Soul Burn effect,
- minerals and ki,
- blueprint editor with simple parts,
- 2 active blueprint slots,
- minion spawning,
- simple brain command system,
- 5 enemy waves,
- reward choice after each wave,
- run win/loss condition.

## 19.2 Nice-to-have features

Add later:

- more map layouts,
- multiple entrances,
- advanced adventurer AI,
- resting/scouting enemy behavior,
- more brain commands,
- meta-progression tree,
- rare parts,
- boss modifiers,
- side objectives,
- limited arena modification.

## 19.3 Do not implement in the first prototype

Avoid these initially:

- full 4X map,
- free-form digging,
- complex economy,
- energy upkeep for all units,
- full scripting language,
- large scrolling RTS maps,
- multiplayer,
- complex diplomacy,
- huge tech tree,
- procedural map generation unless trivial.

---

# 20. Suggested data model

This section gives implementation-oriented structures. Names are illustrative.

## 20.1 Part definition

```json
{
  "id": "sword_basic",
  "name": "Basic Sword",
  "category": "weapon",
  "statModifiers": {
    "damage": 8,
    "attackRange": 1
  },
  "costModifiers": {
    "minerals": 5,
    "ki": 0,
    "energy": 2
  },
  "tags": ["melee"]
}
```

## 20.2 Brain definition

```json
{
  "id": "small_brain",
  "name": "Small Brain",
  "slots": 2,
  "costModifiers": {
    "minerals": 0,
    "ki": 8,
    "energy": 3
  }
}
```

## 20.3 Command definition

```json
{
  "id": "retreat_low_hp",
  "name": "Retreat below 30% health",
  "condition": "health_below_percent",
  "conditionValue": 30,
  "action": "retreat_to_nearest_crystal"
}
```

## 20.4 Blueprint definition

```json
{
  "id": "guard_skeleton",
  "name": "Guard Skeleton",
  "parts": {
    "body": "skeleton_body",
    "weapon": "sword_basic",
    "defense": "shield_basic",
    "trait": "fire_resistance",
    "brain": "small_brain"
  },
  "commands": [
    "guard_nearest_crystal",
    "attack_nearest"
  ],
  "active": true
}
```

## 20.5 Unit instance

```json
{
  "id": "unit_001",
  "blueprintId": "guard_skeleton",
  "position": { "x": 10, "y": 6 },
  "health": 80,
  "state": "fighting",
  "currentTargetId": "enemy_003",
  "statusEffects": []
}
```

## 20.6 Enemy definition

```json
{
  "id": "cleric_basic",
  "name": "Cleric",
  "role": "support",
  "health": 60,
  "damage": 3,
  "armor": 1,
  "moveSpeed": 0.8,
  "abilities": ["heal_ally"],
  "possibleDrops": ["focus_healer", "healing_trait"]
}
```

## 20.7 Wave definition

```json
{
  "id": "wave_04",
  "name": "The First Real Party",
  "enemies": [
    { "enemyId": "warrior_basic", "count": 3, "spawnDelay": 0 },
    { "enemyId": "archer_basic", "count": 2, "spawnDelay": 5 },
    { "enemyId": "cleric_basic", "count": 1, "spawnDelay": 8 }
  ],
  "rewardChoices": 3
}
```

---

# 21. AI command evaluation

Each unit with a brain should evaluate commands in priority order.

Pseudo-code:

```text
for command in unit.commands:
    if command.condition_is_met(unit, world):
        command.execute(unit, world)
        return

unit.execute_default_behavior(world)
```

Default behavior:

```text
if enemy in attack range:
    attack nearest enemy
else:
    move toward nearest enemy or assigned guard point
```

Example command logic:

```text
Command: Retreat below 30% health

Condition:
    unit.health / unit.maxHealth < 0.30

Action:
    move toward nearest friendly crystal
```

```text
Command: Focus healer

Condition:
    visible enemy with role == healer exists

Action:
    target nearest visible healer
```

---

# 22. Win and loss conditions

## 22.1 Wave victory

A wave is won when:

- all enemies are defeated,
- or all surviving enemies retreat.

For the prototype, use:

```text
all enemies defeated
```

## 22.2 Run victory

A prototype run is won after wave 5 is defeated.

## 22.3 Run loss

A run is lost when:

```text
Eye health reaches 0
```

Optional later loss conditions:

- all crystals destroyed and Eye exposed,
- enemy steals key relic,
- doom timer reaches maximum.

---

# 23. User interface requirements

## 23.1 Combat UI

Show:

- Eye health,
- energy bar,
- minerals,
- ki,
- active blueprints,
- selected Hand action,
- current wave progress,
- crystal ranges,
- enemy health bars,
- important status effects.

## 23.2 Preparation UI

Show:

- blueprint editor,
- available parts,
- active blueprint slots,
- next wave preview,
- rewards/upgrades,
- map placement options.

## 23.3 Visual clarity

Important visual rules:

- Hand range must be visible.
- Crystal range must be visible.
- Enemy frontline/backline must be readable.
- Brain command behavior should be inspectable.
- Resource costs must be visible before spawning.

---

# 24. Tone and theme

The tone can be dark fantasy with some dark humor.

The player is not a heroic commander. The player is an evil dungeon entity trying to survive adventurer attacks.

Suggested tone:

- grim,
- slightly absurd,
- tactical,
- readable,
- not overly serious.

Enemy adventurers should feel like classic RPG parties invading the dungeon.

Minions can be creepy, funny, pathetic, or weird.

---

# 25. Art direction for prototype

Use simple readable visuals.

Recommended prototype style:

```text
simplified 2D top-down or isometric view
```

Avoid complex animations at first.

Each role must be visually distinguishable:

- tank,
- melee,
- ranged,
- healer,
- boss,
- crystal,
- Eye,
- Hand range.

---

# 26. Audio direction for prototype

Optional but useful:

- crystal hum,
- Eye pulse,
- Hand lightning sound,
- enemy wave horn,
- minion spawn effect,
- crystal destruction blast,
- victory/failure sting.

Do not prioritize audio over core gameplay.

---

# 27. Implementation priorities

Recommended order:

1. Static one-screen map.
2. Enemy pathing from entrance to Eye.
3. Eye health and loss condition.
4. Basic minion spawning.
5. Basic combat between minions and enemies.
6. Energy and Hand lightning.
7. Crystals and range extension.
8. Crystal destruction emergency effect.
9. Blueprint data model.
10. Blueprint editor with simple parts.
11. Brain command evaluation.
12. Rewards after waves.
13. Five-wave prototype run.
14. Basic roguelite upgrades.

---

# 28. Prototype success criteria

The prototype is successful if:

- the player can complete a 5-wave run,
- at least 3 different blueprint strategies are viable,
- Hand of Power feels useful but not dominant,
- crystal loss feels dangerous but not instantly fatal,
- enemy roles create different tactical problems,
- brain commands visibly change unit behavior,
- the player wants to try a different build after losing or winning.

---

# 29. Design risks

## 29.1 Too many systems

Risk:

```text
The game becomes hard to understand and hard to implement.
```

Mitigation:

```text
Keep the first prototype small.
Do not add full 4X, free digging, or large RTS maps early.
```

## 29.2 Hand of Power dominates combat

Risk:

```text
Player ignores minions and wins by clicking enemies.
```

Mitigation:

```text
High energy cost.
Limited range.
Blocked by frontline enemies.
Low efficiency compared to minions.
```

## 29.3 Blueprint editor becomes too complex

Risk:

```text
Player spends too much time reading stats and not enough time playing.
```

Mitigation:

```text
Use few part categories.
Show clear role summary.
Use simple stat formulas.
Warn about invalid builds.
```

## 29.4 Brain commands become too much like programming

Risk:

```text
The game appeals only to programmers.
```

Mitigation:

```text
Use readable behavior cards.
Limit command slots.
Avoid scripting syntax.
Use priority list only.
```

## 29.5 Crystal explosion becomes exploitable

Risk:

```text
Player intentionally sacrifices crystals as cheap bombs.
```

Mitigation:

```text
Explosion mostly freezes/weakens.
Destroyed node disabled until wave end.
Crystal cost is meaningful.
No reward from explosion kills if needed.
```

---

# 30. Recommended first playable version

The first playable version should contain:

```text
One map.
One Eye.
Two crystal nodes.
Two active blueprint slots.
Six unit parts.
Three brain commands.
Three enemy types.
Five waves.
One Hand attack.
One crystal destruction effect.
Three reward choices after each wave.
```

Suggested initial parts:

```text
Bodies:
- Skeleton

Weapons:
- Sword
- Bow
- Pickaxe

Defense:
- Shield

Brains:
- Tiny Brain
- Small Brain
```

Suggested initial commands:

```text
- Attack nearest enemy
- Guard nearest crystal
- Retreat below 30% health
```

Suggested enemies:

```text
- Seeker
- Warrior
- Archer
- Cleric
- Paladin mini-boss
```

This is enough to test the core idea without building a monster that eats its own production schedule.
