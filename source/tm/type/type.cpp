// Type function definitions
// Copyright David Stone 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <tm/type/type.hpp>

#include <tm/move/moves.hpp>

#include <tm/generation.hpp>

namespace technicalmachine {

auto get_type(Generation const generation, Moves const move, bounded::optional<Type> const hidden_power) -> Type {
	switch (move) {
		case Moves::Pass: return Type::Typeless;
		case Moves::Switch0: return Type::Typeless;
		case Moves::Switch1: return Type::Typeless;
		case Moves::Switch2: return Type::Typeless;
		case Moves::Switch3: return Type::Typeless;
		case Moves::Switch4: return Type::Typeless;
		case Moves::Switch5: return Type::Typeless;
		case Moves::Hit_Self: return Type::Typeless;
		case Moves::Pound: return Type::Normal;
		case Moves::Karate_Chop: return generation == Generation::one ? Type::Normal : Type::Fighting;
		case Moves::Double_Slap: return Type::Normal;
		case Moves::Comet_Punch: return Type::Normal;
		case Moves::Mega_Punch: return Type::Normal;
		case Moves::Pay_Day: return Type::Normal;
		case Moves::Fire_Punch: return Type::Fire;
		case Moves::Ice_Punch: return Type::Ice;
		case Moves::Thunder_Punch: return Type::Electric;
		case Moves::Scratch: return Type::Normal;
		case Moves::Vice_Grip: return Type::Normal;
		case Moves::Guillotine: return Type::Normal;
		case Moves::Razor_Wind: return Type::Normal;
		case Moves::Swords_Dance: return Type::Normal;
		case Moves::Cut: return Type::Normal;
		case Moves::Gust: return generation == Generation::one ? Type::Normal : Type::Flying;
		case Moves::Wing_Attack: return Type::Flying;
		case Moves::Whirlwind: return Type::Normal;
		case Moves::Fly: return Type::Flying;
		case Moves::Bind: return Type::Normal;
		case Moves::Slam: return Type::Normal;
		case Moves::Vine_Whip: return Type::Grass;
		case Moves::Stomp: return Type::Normal;
		case Moves::Double_Kick: return Type::Fighting;
		case Moves::Mega_Kick: return Type::Normal;
		case Moves::Jump_Kick: return Type::Fighting;
		case Moves::Rolling_Kick: return Type::Fighting;
		case Moves::Sand_Attack: return generation == Generation::one ? Type::Normal : Type::Ground;
		case Moves::Headbutt: return Type::Normal;
		case Moves::Horn_Attack: return Type::Normal;
		case Moves::Fury_Attack: return Type::Normal;
		case Moves::Horn_Drill: return Type::Normal;
		case Moves::Tackle: return Type::Normal;
		case Moves::Body_Slam: return Type::Normal;
		case Moves::Wrap: return Type::Normal;
		case Moves::Take_Down: return Type::Normal;
		case Moves::Thrash: return Type::Normal;
		case Moves::Double_Edge: return Type::Normal;
		case Moves::Tail_Whip: return Type::Normal;
		case Moves::Poison_Sting: return Type::Poison;
		case Moves::Twineedle: return Type::Bug;
		case Moves::Pin_Missile: return Type::Bug;
		case Moves::Leer: return Type::Normal;
		case Moves::Bite: return generation == Generation::one ? Type::Normal : Type::Dark;
		case Moves::Growl: return Type::Normal;
		case Moves::Roar: return Type::Normal;
		case Moves::Sing: return Type::Normal;
		case Moves::Supersonic: return Type::Normal;
		case Moves::Sonic_Boom: return Type::Normal;
		case Moves::Disable: return Type::Normal;
		case Moves::Acid: return Type::Poison;
		case Moves::Ember: return Type::Fire;
		case Moves::Flamethrower: return Type::Fire;
		case Moves::Mist: return Type::Ice;
		case Moves::Water_Gun: return Type::Water;
		case Moves::Hydro_Pump: return Type::Water;
		case Moves::Surf: return Type::Water;
		case Moves::Ice_Beam: return Type::Ice;
		case Moves::Blizzard: return Type::Ice;
		case Moves::Psybeam: return Type::Psychic;
		case Moves::Bubble_Beam: return Type::Water;
		case Moves::Aurora_Beam: return Type::Ice;
		case Moves::Hyper_Beam: return Type::Normal;
		case Moves::Peck: return Type::Flying;
		case Moves::Drill_Peck: return Type::Flying;
		case Moves::Submission: return Type::Fighting;
		case Moves::Low_Kick: return Type::Fighting;
		case Moves::Counter: return Type::Fighting;
		case Moves::Seismic_Toss: return Type::Fighting;
		case Moves::Strength: return Type::Normal;
		case Moves::Absorb: return Type::Grass;
		case Moves::Mega_Drain: return Type::Grass;
		case Moves::Leech_Seed: return Type::Grass;
		case Moves::Growth: return Type::Normal;
		case Moves::Razor_Leaf: return Type::Grass;
		case Moves::Solar_Beam: return Type::Grass;
		case Moves::Poison_Powder: return Type::Poison;
		case Moves::Stun_Spore: return Type::Grass;
		case Moves::Sleep_Powder: return Type::Grass;
		case Moves::Petal_Dance: return Type::Grass;
		case Moves::String_Shot: return Type::Bug;
		case Moves::Dragon_Rage: return Type::Dragon;
		case Moves::Fire_Spin: return Type::Fire;
		case Moves::Thunder_Shock: return Type::Electric;
		case Moves::Thunderbolt: return Type::Electric;
		case Moves::Thunder_Wave: return Type::Electric;
		case Moves::Thunder: return Type::Electric;
		case Moves::Rock_Throw: return Type::Rock;
		case Moves::Earthquake: return Type::Ground;
		case Moves::Fissure: return Type::Ground;
		case Moves::Dig: return Type::Ground;
		case Moves::Toxic: return Type::Poison;
		case Moves::Confusion: return Type::Psychic;
		case Moves::Psychic: return Type::Psychic;
		case Moves::Hypnosis: return Type::Psychic;
		case Moves::Meditate: return Type::Psychic;
		case Moves::Agility: return Type::Psychic;
		case Moves::Quick_Attack: return Type::Normal;
		case Moves::Rage: return Type::Normal;
		case Moves::Teleport: return Type::Psychic;
		case Moves::Night_Shade: return Type::Ghost;
		case Moves::Mimic: return Type::Normal;
		case Moves::Screech: return Type::Normal;
		case Moves::Double_Team: return Type::Normal;
		case Moves::Recover: return Type::Normal;
		case Moves::Harden: return Type::Normal;
		case Moves::Minimize: return Type::Normal;
		case Moves::Smokescreen: return Type::Normal;
		case Moves::Confuse_Ray: return Type::Ghost;
		case Moves::Withdraw: return Type::Water;
		case Moves::Defense_Curl: return Type::Normal;
		case Moves::Barrier: return Type::Psychic;
		case Moves::Light_Screen: return Type::Psychic;
		case Moves::Haze: return Type::Ice;
		case Moves::Reflect: return Type::Psychic;
		case Moves::Focus_Energy: return Type::Normal;
		case Moves::Bide: return Type::Normal;
		case Moves::Metronome: return Type::Normal;
		case Moves::Mirror_Move: return Type::Flying;
		case Moves::Self_Destruct: return Type::Normal;
		case Moves::Egg_Bomb: return Type::Normal;
		case Moves::Lick: return Type::Ghost;
		case Moves::Smog: return Type::Poison;
		case Moves::Sludge: return Type::Poison;
		case Moves::Bone_Club: return Type::Ground;
		case Moves::Fire_Blast: return Type::Fire;
		case Moves::Waterfall: return Type::Water;
		case Moves::Clamp: return Type::Water;
		case Moves::Swift: return Type::Normal;
		case Moves::Skull_Bash: return Type::Normal;
		case Moves::Spike_Cannon: return Type::Normal;
		case Moves::Constrict: return Type::Normal;
		case Moves::Amnesia: return Type::Psychic;
		case Moves::Kinesis: return Type::Psychic;
		case Moves::Soft_Boiled: return Type::Normal;
		case Moves::High_Jump_Kick: return Type::Fighting;
		case Moves::Glare: return Type::Normal;
		case Moves::Dream_Eater: return Type::Psychic;
		case Moves::Poison_Gas: return Type::Poison;
		case Moves::Barrage: return Type::Normal;
		case Moves::Leech_Life: return Type::Bug;
		case Moves::Lovely_Kiss: return Type::Normal;
		case Moves::Sky_Attack: return Type::Flying;
		case Moves::Transform: return Type::Normal;
		case Moves::Bubble: return Type::Water;
		case Moves::Dizzy_Punch: return Type::Normal;
		case Moves::Spore: return Type::Grass;
		case Moves::Flash: return Type::Normal;
		case Moves::Psywave: return Type::Psychic;
		case Moves::Splash: return Type::Normal;
		case Moves::Acid_Armor: return Type::Poison;
		case Moves::Crabhammer: return Type::Water;
		case Moves::Explosion: return Type::Normal;
		case Moves::Fury_Swipes: return Type::Normal;
		case Moves::Bonemerang: return Type::Ground;
		case Moves::Rest: return Type::Psychic;
		case Moves::Rock_Slide: return Type::Rock;
		case Moves::Hyper_Fang: return Type::Normal;
		case Moves::Sharpen: return Type::Normal;
		case Moves::Conversion: return Type::Normal;
		case Moves::Tri_Attack: return Type::Normal;
		case Moves::Super_Fang: return Type::Normal;
		case Moves::Slash: return Type::Normal;
		case Moves::Substitute: return Type::Normal;
		case Moves::Struggle: return generation == Generation::one ? Type::Normal : Type::Typeless;
		case Moves::Sketch: return Type::Normal;
		case Moves::Triple_Kick: return Type::Fighting;
		case Moves::Thief: return Type::Dark;
		case Moves::Spider_Web: return Type::Bug;
		case Moves::Mind_Reader: return Type::Normal;
		case Moves::Nightmare: return Type::Ghost;
		case Moves::Flame_Wheel: return Type::Fire;
		case Moves::Snore: return Type::Normal;
		case Moves::Curse: return generation <= Generation::four ? Type::Typeless : Type::Ghost;
		case Moves::Flail: return Type::Normal;
		case Moves::Conversion_2: return Type::Normal;
		case Moves::Aeroblast: return Type::Flying;
		case Moves::Cotton_Spore: return Type::Grass;
		case Moves::Reversal: return Type::Fighting;
		case Moves::Spite: return Type::Ghost;
		case Moves::Powder_Snow: return Type::Ice;
		case Moves::Protect: return Type::Normal;
		case Moves::Mach_Punch: return Type::Fighting;
		case Moves::Scary_Face: return Type::Normal;
		case Moves::Feint_Attack: return Type::Dark;
		case Moves::Sweet_Kiss: return generation <= Generation::five ? Type::Normal : Type::Fairy;
		case Moves::Belly_Drum: return Type::Normal;
		case Moves::Sludge_Bomb: return Type::Poison;
		case Moves::Mud_Slap: return Type::Ground;
		case Moves::Octazooka: return Type::Water;
		case Moves::Spikes: return Type::Ground;
		case Moves::Zap_Cannon: return Type::Electric;
		case Moves::Foresight: return Type::Normal;
		case Moves::Destiny_Bond: return Type::Ghost;
		case Moves::Perish_Song: return Type::Normal;
		case Moves::Icy_Wind: return Type::Ice;
		case Moves::Detect: return Type::Fighting;
		case Moves::Bone_Rush: return Type::Ground;
		case Moves::Lock_On: return Type::Normal;
		case Moves::Outrage: return Type::Dragon;
		case Moves::Sandstorm: return Type::Rock;
		case Moves::Giga_Drain: return Type::Grass;
		case Moves::Endure: return Type::Normal;
		case Moves::Charm: return generation <= Generation::five ? Type::Normal : Type::Fairy;
		case Moves::Rollout: return Type::Rock;
		case Moves::False_Swipe: return Type::Normal;
		case Moves::Swagger: return Type::Normal;
		case Moves::Milk_Drink: return Type::Normal;
		case Moves::Spark: return Type::Electric;
		case Moves::Fury_Cutter: return Type::Bug;
		case Moves::Steel_Wing: return Type::Steel;
		case Moves::Mean_Look: return Type::Normal;
		case Moves::Attract: return Type::Normal;
		case Moves::Sleep_Talk: return Type::Normal;
		case Moves::Heal_Bell: return Type::Normal;
		case Moves::Return: return Type::Normal;
		case Moves::Present: return Type::Normal;
		case Moves::Frustration: return Type::Normal;
		case Moves::Safeguard: return Type::Normal;
		case Moves::Pain_Split: return Type::Normal;
		case Moves::Sacred_Fire: return Type::Fire;
		case Moves::Magnitude: return Type::Ground;
		case Moves::Dynamic_Punch: return Type::Fighting;
		case Moves::Megahorn: return Type::Bug;
		case Moves::Dragon_Breath: return Type::Dragon;
		case Moves::Baton_Pass: return Type::Normal;
		case Moves::Encore: return Type::Normal;
		case Moves::Pursuit: return Type::Dark;
		case Moves::Rapid_Spin: return Type::Normal;
		case Moves::Sweet_Scent: return Type::Normal;
		case Moves::Iron_Tail: return Type::Steel;
		case Moves::Metal_Claw: return Type::Steel;
		case Moves::Vital_Throw: return Type::Fighting;
		case Moves::Morning_Sun: return Type::Normal;
		case Moves::Synthesis: return Type::Grass;
		case Moves::Moonlight: return generation <= Generation::five ? Type::Normal : Type::Fairy;
		case Moves::Hidden_Power: return *hidden_power;
		case Moves::Cross_Chop: return Type::Fighting;
		case Moves::Twister: return Type::Dragon;
		case Moves::Rain_Dance: return Type::Water;
		case Moves::Sunny_Day: return Type::Fire;
		case Moves::Crunch: return Type::Dark;
		case Moves::Mirror_Coat: return Type::Psychic;
		case Moves::Psych_Up: return Type::Normal;
		case Moves::Extreme_Speed: return Type::Normal;
		case Moves::Ancient_Power: return Type::Rock;
		case Moves::Shadow_Ball: return Type::Ghost;
		case Moves::Future_Sight: return Type::Psychic;
		case Moves::Rock_Smash: return Type::Fighting;
		case Moves::Whirlpool: return Type::Water;
		case Moves::Beat_Up: return Type::Dark;
		case Moves::Fake_Out: return Type::Normal;
		case Moves::Uproar: return Type::Normal;
		case Moves::Stockpile: return Type::Normal;
		case Moves::Spit_Up: return Type::Normal;
		case Moves::Swallow: return Type::Normal;
		case Moves::Heat_Wave: return Type::Fire;
		case Moves::Hail: return Type::Ice;
		case Moves::Torment: return Type::Dark;
		case Moves::Flatter: return Type::Dark;
		case Moves::Will_O_Wisp: return Type::Fire;
		case Moves::Memento: return Type::Dark;
		case Moves::Facade: return Type::Normal;
		case Moves::Focus_Punch: return Type::Fighting;
		case Moves::Smelling_Salts: return Type::Normal;
		case Moves::Follow_Me: return Type::Normal;
		case Moves::Nature_Power: return Type::Normal;
		case Moves::Charge: return Type::Electric;
		case Moves::Taunt: return Type::Dark;
		case Moves::Helping_Hand: return Type::Normal;
		case Moves::Trick: return Type::Psychic;
		case Moves::Role_Play: return Type::Psychic;
		case Moves::Wish: return Type::Normal;
		case Moves::Assist: return Type::Normal;
		case Moves::Ingrain: return Type::Grass;
		case Moves::Superpower: return Type::Fighting;
		case Moves::Magic_Coat: return Type::Psychic;
		case Moves::Recycle: return Type::Normal;
		case Moves::Revenge: return Type::Fighting;
		case Moves::Brick_Break: return Type::Fighting;
		case Moves::Yawn: return Type::Normal;
		case Moves::Knock_Off: return Type::Dark;
		case Moves::Endeavor: return Type::Normal;
		case Moves::Eruption: return Type::Fire;
		case Moves::Skill_Swap: return Type::Psychic;
		case Moves::Imprison: return Type::Psychic;
		case Moves::Refresh: return Type::Normal;
		case Moves::Grudge: return Type::Ghost;
		case Moves::Snatch: return Type::Dark;
		case Moves::Secret_Power: return Type::Normal;
		case Moves::Dive: return Type::Water;
		case Moves::Arm_Thrust: return Type::Fighting;
		case Moves::Camouflage: return Type::Normal;
		case Moves::Tail_Glow: return Type::Bug;
		case Moves::Luster_Purge: return Type::Psychic;
		case Moves::Mist_Ball: return Type::Psychic;
		case Moves::Feather_Dance: return Type::Flying;
		case Moves::Teeter_Dance: return Type::Normal;
		case Moves::Blaze_Kick: return Type::Fire;
		case Moves::Mud_Sport: return Type::Ground;
		case Moves::Ice_Ball: return Type::Ice;
		case Moves::Needle_Arm: return Type::Grass;
		case Moves::Slack_Off: return Type::Normal;
		case Moves::Hyper_Voice: return Type::Normal;
		case Moves::Poison_Fang: return Type::Poison;
		case Moves::Crush_Claw: return Type::Normal;
		case Moves::Blast_Burn: return Type::Fire;
		case Moves::Hydro_Cannon: return Type::Water;
		case Moves::Meteor_Mash: return Type::Steel;
		case Moves::Astonish: return Type::Ghost;
		case Moves::Weather_Ball: return Type::Normal;
		case Moves::Aromatherapy: return Type::Grass;
		case Moves::Fake_Tears: return Type::Dark;
		case Moves::Air_Cutter: return Type::Flying;
		case Moves::Overheat: return Type::Fire;
		case Moves::Odor_Sleuth: return Type::Normal;
		case Moves::Rock_Tomb: return Type::Rock;
		case Moves::Silver_Wind: return Type::Bug;
		case Moves::Metal_Sound: return Type::Steel;
		case Moves::Grass_Whistle: return Type::Grass;
		case Moves::Tickle: return Type::Normal;
		case Moves::Cosmic_Power: return Type::Psychic;
		case Moves::Water_Spout: return Type::Water;
		case Moves::Signal_Beam: return Type::Bug;
		case Moves::Shadow_Punch: return Type::Ghost;
		case Moves::Extrasensory: return Type::Psychic;
		case Moves::Sky_Uppercut: return Type::Fighting;
		case Moves::Sand_Tomb: return Type::Ground;
		case Moves::Sheer_Cold: return Type::Ice;
		case Moves::Muddy_Water: return Type::Water;
		case Moves::Bullet_Seed: return Type::Grass;
		case Moves::Aerial_Ace: return Type::Flying;
		case Moves::Icicle_Spear: return Type::Ice;
		case Moves::Iron_Defense: return Type::Steel;
		case Moves::Block: return Type::Normal;
		case Moves::Howl: return Type::Normal;
		case Moves::Dragon_Claw: return Type::Dragon;
		case Moves::Frenzy_Plant: return Type::Grass;
		case Moves::Bulk_Up: return Type::Fighting;
		case Moves::Bounce: return Type::Flying;
		case Moves::Mud_Shot: return Type::Ground;
		case Moves::Poison_Tail: return Type::Poison;
		case Moves::Covet: return Type::Normal;
		case Moves::Volt_Tackle: return Type::Electric;
		case Moves::Magical_Leaf: return Type::Grass;
		case Moves::Water_Sport: return Type::Water;
		case Moves::Calm_Mind: return Type::Psychic;
		case Moves::Leaf_Blade: return Type::Grass;
		case Moves::Dragon_Dance: return Type::Dragon;
		case Moves::Rock_Blast: return Type::Rock;
		case Moves::Shock_Wave: return Type::Electric;
		case Moves::Water_Pulse: return Type::Water;
		case Moves::Doom_Desire: return Type::Steel;
		case Moves::Psycho_Boost: return Type::Psychic;
		case Moves::Roost: return Type::Flying;
		case Moves::Gravity: return Type::Psychic;
		case Moves::Miracle_Eye: return Type::Psychic;
		case Moves::Wake_Up_Slap: return Type::Fighting;
		case Moves::Hammer_Arm: return Type::Fighting;
		case Moves::Gyro_Ball: return Type::Steel;
		case Moves::Healing_Wish: return Type::Psychic;
		case Moves::Brine: return Type::Water;
		case Moves::Natural_Gift: return Type::Normal;
		case Moves::Feint: return Type::Normal;
		case Moves::Pluck: return Type::Flying;
		case Moves::Tailwind: return Type::Flying;
		case Moves::Acupressure: return Type::Normal;
		case Moves::Metal_Burst: return Type::Steel;
		case Moves::U_turn: return Type::Bug;
		case Moves::Close_Combat: return Type::Fighting;
		case Moves::Payback: return Type::Dark;
		case Moves::Assurance: return Type::Dark;
		case Moves::Embargo: return Type::Dark;
		case Moves::Fling: return Type::Dark;
		case Moves::Psycho_Shift: return Type::Psychic;
		case Moves::Trump_Card: return Type::Normal;
		case Moves::Heal_Block: return Type::Psychic;
		case Moves::Wring_Out: return Type::Normal;
		case Moves::Power_Trick: return Type::Psychic;
		case Moves::Gastro_Acid: return Type::Poison;
		case Moves::Lucky_Chant: return Type::Normal;
		case Moves::Me_First: return Type::Normal;
		case Moves::Copycat: return Type::Normal;
		case Moves::Power_Swap: return Type::Psychic;
		case Moves::Guard_Swap: return Type::Psychic;
		case Moves::Punishment: return Type::Dark;
		case Moves::Last_Resort: return Type::Normal;
		case Moves::Worry_Seed: return Type::Grass;
		case Moves::Sucker_Punch: return Type::Dark;
		case Moves::Toxic_Spikes: return Type::Poison;
		case Moves::Heart_Swap: return Type::Psychic;
		case Moves::Aqua_Ring: return Type::Water;
		case Moves::Magnet_Rise: return Type::Electric;
		case Moves::Flare_Blitz: return Type::Fire;
		case Moves::Force_Palm: return Type::Fighting;
		case Moves::Aura_Sphere: return Type::Fighting;
		case Moves::Rock_Polish: return Type::Rock;
		case Moves::Poison_Jab: return Type::Poison;
		case Moves::Dark_Pulse: return Type::Dark;
		case Moves::Night_Slash: return Type::Dark;
		case Moves::Aqua_Tail: return Type::Water;
		case Moves::Seed_Bomb: return Type::Grass;
		case Moves::Air_Slash: return Type::Flying;
		case Moves::X_Scissor: return Type::Bug;
		case Moves::Bug_Buzz: return Type::Bug;
		case Moves::Dragon_Pulse: return Type::Dragon;
		case Moves::Dragon_Rush: return Type::Dragon;
		case Moves::Power_Gem: return Type::Rock;
		case Moves::Drain_Punch: return Type::Fighting;
		case Moves::Vacuum_Wave: return Type::Fighting;
		case Moves::Focus_Blast: return Type::Fighting;
		case Moves::Energy_Ball: return Type::Grass;
		case Moves::Brave_Bird: return Type::Flying;
		case Moves::Earth_Power: return Type::Ground;
		case Moves::Switcheroo: return Type::Dark;
		case Moves::Giga_Impact: return Type::Normal;
		case Moves::Nasty_Plot: return Type::Dark;
		case Moves::Bullet_Punch: return Type::Steel;
		case Moves::Avalanche: return Type::Ice;
		case Moves::Ice_Shard: return Type::Ice;
		case Moves::Shadow_Claw: return Type::Ghost;
		case Moves::Thunder_Fang: return Type::Electric;
		case Moves::Ice_Fang: return Type::Ice;
		case Moves::Fire_Fang: return Type::Fire;
		case Moves::Shadow_Sneak: return Type::Ghost;
		case Moves::Mud_Bomb: return Type::Ground;
		case Moves::Psycho_Cut: return Type::Psychic;
		case Moves::Zen_Headbutt: return Type::Psychic;
		case Moves::Mirror_Shot: return Type::Steel;
		case Moves::Flash_Cannon: return Type::Steel;
		case Moves::Rock_Climb: return Type::Normal;
		case Moves::Defog: return Type::Flying;
		case Moves::Trick_Room: return Type::Psychic;
		case Moves::Draco_Meteor: return Type::Dragon;
		case Moves::Discharge: return Type::Electric;
		case Moves::Lava_Plume: return Type::Fire;
		case Moves::Leaf_Storm: return Type::Grass;
		case Moves::Power_Whip: return Type::Grass;
		case Moves::Rock_Wrecker: return Type::Rock;
		case Moves::Cross_Poison: return Type::Poison;
		case Moves::Gunk_Shot: return Type::Poison;
		case Moves::Iron_Head: return Type::Steel;
		case Moves::Magnet_Bomb: return Type::Steel;
		case Moves::Stone_Edge: return Type::Rock;
		case Moves::Captivate: return Type::Normal;
		case Moves::Stealth_Rock: return Type::Rock;
		case Moves::Grass_Knot: return Type::Grass;
		case Moves::Chatter: return Type::Flying;
		case Moves::Judgment: return Type::Normal;
		case Moves::Bug_Bite: return Type::Bug;
		case Moves::Charge_Beam: return Type::Electric;
		case Moves::Wood_Hammer: return Type::Grass;
		case Moves::Aqua_Jet: return Type::Water;
		case Moves::Attack_Order: return Type::Bug;
		case Moves::Defend_Order: return Type::Bug;
		case Moves::Heal_Order: return Type::Bug;
		case Moves::Head_Smash: return Type::Rock;
		case Moves::Double_Hit: return Type::Normal;
		case Moves::Roar_of_Time: return Type::Dragon;
		case Moves::Spacial_Rend: return Type::Dragon;
		case Moves::Lunar_Dance: return Type::Psychic;
		case Moves::Crush_Grip: return Type::Normal;
		case Moves::Magma_Storm: return Type::Fire;
		case Moves::Dark_Void: return Type::Dark;
		case Moves::Seed_Flare: return Type::Grass;
		case Moves::Ominous_Wind: return Type::Ghost;
		case Moves::Shadow_Force: return Type::Ghost;
		case Moves::Hone_Claws: return Type::Dark;
		case Moves::Wide_Guard: return Type::Rock;
		case Moves::Guard_Split: return Type::Psychic;
		case Moves::Power_Split: return Type::Psychic;
		case Moves::Wonder_Room: return Type::Psychic;
		case Moves::Psyshock: return Type::Psychic;
		case Moves::Venoshock: return Type::Poison;
		case Moves::Autotomize: return Type::Steel;
		case Moves::Rage_Powder: return Type::Bug;
		case Moves::Telekinesis: return Type::Psychic;
		case Moves::Magic_Room: return Type::Psychic;
		case Moves::Smack_Down: return Type::Rock;
		case Moves::Storm_Throw: return Type::Fighting;
		case Moves::Flame_Burst: return Type::Fire;
		case Moves::Sludge_Wave: return Type::Poison;
		case Moves::Quiver_Dance: return Type::Bug;
		case Moves::Heavy_Slam: return Type::Steel;
		case Moves::Synchronoise: return Type::Psychic;
		case Moves::Electro_Ball: return Type::Electric;
		case Moves::Soak: return Type::Water;
		case Moves::Flame_Charge: return Type::Fire;
		case Moves::Coil: return Type::Poison;
		case Moves::Low_Sweep: return Type::Fighting;
		case Moves::Acid_Spray: return Type::Poison;
		case Moves::Foul_Play: return Type::Dark;
		case Moves::Simple_Beam: return Type::Normal;
		case Moves::Entrainment: return Type::Normal;
		case Moves::After_You: return Type::Normal;
		case Moves::Round: return Type::Normal;
		case Moves::Echoed_Voice: return Type::Normal;
		case Moves::Chip_Away: return Type::Normal;
		case Moves::Clear_Smog: return Type::Poison;
		case Moves::Stored_Power: return Type::Psychic;
		case Moves::Quick_Guard: return Type::Fighting;
		case Moves::Ally_Switch: return Type::Psychic;
		case Moves::Scald: return Type::Water;
		case Moves::Shell_Smash: return Type::Normal;
		case Moves::Heal_Pulse: return Type::Psychic;
		case Moves::Hex: return Type::Ghost;
		case Moves::Sky_Drop: return Type::Flying;
		case Moves::Shift_Gear: return Type::Steel;
		case Moves::Circle_Throw: return Type::Fighting;
		case Moves::Incinerate: return Type::Fire;
		case Moves::Quash: return Type::Dark;
		case Moves::Acrobatics: return Type::Flying;
		case Moves::Reflect_Type: return Type::Normal;
		case Moves::Retaliate: return Type::Normal;
		case Moves::Final_Gambit: return Type::Fighting;
		case Moves::Bestow: return Type::Normal;
		case Moves::Inferno: return Type::Fire;
		case Moves::Water_Pledge: return Type::Water;
		case Moves::Fire_Pledge: return Type::Fire;
		case Moves::Grass_Pledge: return Type::Grass;
		case Moves::Volt_Switch: return Type::Electric;
		case Moves::Struggle_Bug: return Type::Bug;
		case Moves::Bulldoze: return Type::Ground;
		case Moves::Frost_Breath: return Type::Ice;
		case Moves::Dragon_Tail: return Type::Dragon;
		case Moves::Work_Up: return Type::Normal;
		case Moves::Electroweb: return Type::Electric;
		case Moves::Wild_Charge: return Type::Electric;
		case Moves::Drill_Run: return Type::Ground;
		case Moves::Dual_Chop: return Type::Dragon;
		case Moves::Heart_Stamp: return Type::Psychic;
		case Moves::Horn_Leech: return Type::Grass;
		case Moves::Sacred_Sword: return Type::Fighting;
		case Moves::Razor_Shell: return Type::Water;
		case Moves::Heat_Crash: return Type::Fire;
		case Moves::Leaf_Tornado: return Type::Grass;
		case Moves::Steamroller: return Type::Bug;
		case Moves::Cotton_Guard: return Type::Grass;
		case Moves::Night_Daze: return Type::Dark;
		case Moves::Psystrike: return Type::Psychic;
		case Moves::Tail_Slap: return Type::Normal;
		case Moves::Hurricane: return Type::Flying;
		case Moves::Head_Charge: return Type::Normal;
		case Moves::Gear_Grind: return Type::Steel;
		case Moves::Searing_Shot: return Type::Fire;
		case Moves::Techno_Blast: return Type::Normal;
		case Moves::Relic_Song: return Type::Normal;
		case Moves::Secret_Sword: return Type::Fighting;
		case Moves::Glaciate: return Type::Ice;
		case Moves::Bolt_Strike: return Type::Electric;
		case Moves::Blue_Flare: return Type::Fire;
		case Moves::Fiery_Dance: return Type::Fire;
		case Moves::Freeze_Shock: return Type::Ice;
		case Moves::Ice_Burn: return Type::Ice;
		case Moves::Snarl: return Type::Dark;
		case Moves::Icicle_Crash: return Type::Ice;
		case Moves::V_create: return Type::Fire;
		case Moves::Fusion_Flare: return Type::Fire;
		case Moves::Fusion_Bolt: return Type::Electric;
		case Moves::Flying_Press: return Type::Fighting;
		case Moves::Mat_Block: return Type::Fighting;
		case Moves::Belch: return Type::Poison;
		case Moves::Rototiller: return Type::Ground;
		case Moves::Sticky_Web: return Type::Bug;
		case Moves::Fell_Stinger: return Type::Bug;
		case Moves::Phantom_Force: return Type::Ghost;
		case Moves::Trick_or_Treat: return Type::Ghost;
		case Moves::Noble_Roar: return Type::Normal;
		case Moves::Ion_Deluge: return Type::Electric;
		case Moves::Parabolic_Charge: return Type::Electric;
		case Moves::Forests_Curse: return Type::Grass;
		case Moves::Petal_Blizzard: return Type::Grass;
		case Moves::Freeze_Dry: return Type::Ice;
		case Moves::Disarming_Voice: return Type::Typeless;
		case Moves::Parting_Shot: return Type::Dark;
		case Moves::Topsy_Turvy: return Type::Dark;
		case Moves::Draining_Kiss: return Type::Typeless;
		case Moves::Crafty_Shield: return Type::Typeless;
		case Moves::Flower_Shield: return Type::Typeless;
		case Moves::Grassy_Terrain: return Type::Grass;
		case Moves::Misty_Terrain: return Type::Typeless;
		case Moves::Electrify: return Type::Electric;
		case Moves::Play_Rough: return Type::Typeless;
		case Moves::Fairy_Wind: return Type::Typeless;
		case Moves::Moonblast: return Type::Typeless;
		case Moves::Boomburst: return Type::Normal;
		case Moves::Fairy_Lock: return Type::Typeless;
		case Moves::Kings_Shield: return Type::Steel;
		case Moves::Play_Nice: return Type::Normal;
		case Moves::Confide: return Type::Normal;
		case Moves::Diamond_Storm: return Type::Rock;
		case Moves::Steam_Eruption: return Type::Water;
		case Moves::Hyperspace_Hole: return Type::Psychic;
		case Moves::Water_Shuriken: return Type::Water;
		case Moves::Mystical_Fire: return Type::Fire;
		case Moves::Spiky_Shield: return Type::Grass;
		case Moves::Aromatic_Mist: return Type::Typeless;
		case Moves::Eerie_Impulse: return Type::Electric;
		case Moves::Venom_Drench: return Type::Poison;
		case Moves::Powder: return Type::Bug;
		case Moves::Geomancy: return Type::Typeless;
		case Moves::Magnetic_Flux: return Type::Electric;
		case Moves::Happy_Hour: return Type::Normal;
		case Moves::Electric_Terrain: return Type::Electric;
		case Moves::Dazzling_Gleam: return Type::Typeless;
		case Moves::Celebrate: return Type::Normal;
		case Moves::Hold_Hands: return Type::Normal;
		case Moves::Baby_Doll_Eyes: return Type::Typeless;
		case Moves::Nuzzle: return Type::Electric;
		case Moves::Hold_Back: return Type::Normal;
		case Moves::Infestation: return Type::Bug;
		case Moves::Power_Up_Punch: return Type::Fighting;
		case Moves::Oblivion_Wing: return Type::Flying;
		case Moves::Thousand_Arrows: return Type::Ground;
		case Moves::Thousand_Waves: return Type::Ground;
		case Moves::Lands_Wrath: return Type::Ground;
		case Moves::Light_of_Ruin: return Type::Typeless;
		case Moves::Origin_Pulse: return Type::Water;
		case Moves::Precipice_Blades: return Type::Ground;
		case Moves::Dragon_Ascent: return Type::Flying;
		case Moves::Hyperspace_Fury: return Type::Dark;
		case Moves::Breakneck_Blitz: return Type::Normal;
		case Moves::All_Out_Pummeling: return Type::Fighting;
		case Moves::Supersonic_Skystrike: return Type::Flying;
		case Moves::Acid_Downpour: return Type::Poison;
		case Moves::Tectonic_Rage: return Type::Ground;
		case Moves::Continental_Crush: return Type::Rock;
		case Moves::Savage_Spin_Out: return Type::Bug;
		case Moves::Never_Ending_Nightmare: return Type::Ghost;
		case Moves::Corkscrew_Crash: return Type::Steel;
		case Moves::Inferno_Overdrive: return Type::Fire;
		case Moves::Hydro_Vortex: return Type::Water;
		case Moves::Bloom_Doom: return Type::Grass;
		case Moves::Gigavolt_Havoc: return Type::Electric;
		case Moves::Shattered_Psyche: return Type::Psychic;
		case Moves::Subzero_Slammer: return Type::Ice;
		case Moves::Devastating_Drake: return Type::Dragon;
		case Moves::Black_Hole_Eclipse: return Type::Dark;
		case Moves::Twinkle_Tackle: return Type::Typeless;
		case Moves::Catastropika: return Type::Electric;
		case Moves::Shore_Up: return Type::Ground;
		case Moves::First_Impression: return Type::Bug;
		case Moves::Baneful_Bunker: return Type::Poison;
		case Moves::Spirit_Shackle: return Type::Ghost;
		case Moves::Darkest_Lariat: return Type::Dark;
		case Moves::Sparkling_Aria: return Type::Water;
		case Moves::Ice_Hammer: return Type::Ice;
		case Moves::Floral_Healing: return Type::Typeless;
		case Moves::High_Horsepower: return Type::Ground;
		case Moves::Strength_Sap: return Type::Grass;
		case Moves::Solar_Blade: return Type::Grass;
		case Moves::Leafage: return Type::Grass;
		case Moves::Spotlight: return Type::Normal;
		case Moves::Toxic_Thread: return Type::Poison;
		case Moves::Laser_Focus: return Type::Normal;
		case Moves::Gear_Up: return Type::Steel;
		case Moves::Throat_Chop: return Type::Dark;
		case Moves::Pollen_Puff: return Type::Bug;
		case Moves::Anchor_Shot: return Type::Steel;
		case Moves::Psychic_Terrain: return Type::Psychic;
		case Moves::Lunge: return Type::Bug;
		case Moves::Fire_Lash: return Type::Fire;
		case Moves::Power_Trip: return Type::Dark;
		case Moves::Burn_Up: return Type::Fire;
		case Moves::Speed_Swap: return Type::Psychic;
		case Moves::Smart_Strike: return Type::Steel;
		case Moves::Purify: return Type::Poison;
		case Moves::Revelation_Dance: return Type::Normal;
		case Moves::Core_Enforcer: return Type::Dragon;
		case Moves::Trop_Kick: return Type::Grass;
		case Moves::Instruct: return Type::Psychic;
		case Moves::Beak_Blast: return Type::Flying;
		case Moves::Clanging_Scales: return Type::Dragon;
		case Moves::Dragon_Hammer: return Type::Dragon;
		case Moves::Brutal_Swing: return Type::Dark;
		case Moves::Aurora_Veil: return Type::Ice;
		case Moves::Sinister_Arrow_Raid: return Type::Ghost;
		case Moves::Malicious_Moonsault: return Type::Dark;
		case Moves::Oceanic_Operetta: return Type::Water;
		case Moves::Guardian_of_Alola: return Type::Typeless;
		case Moves::Soul_Stealing_7_Star_Strike: return Type::Ghost;
		case Moves::Stoked_Sparksurfer: return Type::Electric;
		case Moves::Pulverizing_Pancake: return Type::Normal;
		case Moves::Extreme_Evoboost: return Type::Normal;
		case Moves::Genesis_Supernova: return Type::Psychic;
		case Moves::Shell_Trap: return Type::Fire;
		case Moves::Fleur_Cannon: return Type::Typeless;
		case Moves::Psychic_Fangs: return Type::Psychic;
		case Moves::Stomping_Tantrum: return Type::Ground;
		case Moves::Shadow_Bone: return Type::Ghost;
		case Moves::Accelerock: return Type::Rock;
		case Moves::Liquidation: return Type::Water;
		case Moves::Prismatic_Laser: return Type::Psychic;
		case Moves::Spectral_Thief: return Type::Ghost;
		case Moves::Sunsteel_Strike: return Type::Steel;
		case Moves::Moongeist_Beam: return Type::Ghost;
		case Moves::Tearful_Look: return Type::Normal;
		case Moves::Zing_Zap: return Type::Electric;
		case Moves::Natures_Madness: return Type::Typeless;
		case Moves::Multi_Attack: return Type::Normal;
		case Moves::m10000000_Volt_Thunderbolt: return Type::Electric;
		case Moves::Mind_Blown: return Type::Fire;
		case Moves::Plasma_Fists: return Type::Electric;
		case Moves::Photon_Geyser: return Type::Psychic;
		case Moves::Light_That_Burns_the_Sky: return Type::Psychic;
		case Moves::Searing_Sunraze_Smash: return Type::Steel;
		case Moves::Menacing_Moonraze_Maelstrom: return Type::Ghost;
		case Moves::Lets_Snuggle_Forever: return Type::Typeless;
		case Moves::Splintered_Stormshards: return Type::Rock;
		case Moves::Clangorous_Soulblaze: return Type::Dragon;
		case Moves::Zippy_Zap: return Type::Electric;
		case Moves::Splishy_Splash: return Type::Water;
		case Moves::Floaty_Fall: return Type::Flying;
		case Moves::Pika_Papow: return Type::Electric;
		case Moves::Bouncy_Bubble: return Type::Water;
		case Moves::Buzzy_Buzz: return Type::Electric;
		case Moves::Sizzly_Slide: return Type::Fire;
		case Moves::Glitzy_Glow: return Type::Psychic;
		case Moves::Baddy_Bad: return Type::Dark;
		case Moves::Sappy_Seed: return Type::Grass;
		case Moves::Freezy_Frost: return Type::Ice;
		case Moves::Sparkly_Swirl: return Type::Typeless;
		case Moves::Veevee_Volley: return Type::Normal;
		case Moves::Double_Iron_Bash: return Type::Steel;
	}
}

}	// namespace technicalmachine
